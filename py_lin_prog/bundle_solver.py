from collections import Counter
import numpy as np 
import pandas as pd 
from pulp import LpMaximize, LpProblem, LpStatus, lpSum, LpVariable


class Solver:
    def __init__(self):
        # To store input data 
        self.bundles = {} 
        self.items = {} 
        self.discounts = {}
        self.basket = {}
        self.bundle_number = {} 
        
        # To calculate costs of basket 
        self.bundle_number_col = np.array([], dtype=np.int)
        self.bundle_matrix = np.array([], dtype=np.int)
        self.prices_row = np.array([], dtype=np.int)
        self.basket_row = np.array([], dtype=np.int)
        self.discount_col = np.array([], dtype=np.int)


    def set_bundles(self, bundles): 
        '''
            Set dictionary with bundle's names and configuration 

            Format: 
                keys    [string]            :   Name of bundle
                values  [list of strings]   :   Lists with item's names 
                e.g. 'b1': ['a', 'a', 'b']
            Note:   if item is used several times in bundle, add it sequentially 
        '''
        if not isinstance(bundles, dict):
            raise TypeError("Only dictionaries are allowed for bundles!")
        if not all(isinstance(key, str) for key in bundles.keys()):
            raise TypeError("Bundle's keys must be strings")
        if not all(isinstance(val, list) for val in bundles.values()):
            raise TypeError("Bundle's values must be lists")
        if not all(all(isinstance(v, str) for v in val) for val in bundles.values()):
            raise TypeError("Bundle's values inside lists must be strings")
        self.bundles = bundles 
    

    def set_items(self, items): 
        '''
            Set dictionary with item's names and their prices  

            Format: 
                keys    [string]    :   Unique name of item 
                values  [float]     :   Item price 
                e.g. 'a': 1.0
        '''
        if not isinstance(items, dict):
            raise TypeError("Only dictionaries are allowed for items!")
        if not all(isinstance(key, str) for key in items.keys()):
            raise TypeError("Item's keys (item names) must be strings")
        if not all(isinstance(val, float) for val in items.values()):
            raise TypeError("Item's values (prices of items) must be float")
        if not all(val > 0.0 for val in  items.values()):
            raise ValueError("Prices of item can not be negative")
        self.items = items 
    

    def set_discounts(self, discounts):
        '''
            Set dictionary with discount's values 

            Format: 
                keys    [string]    :   Name of bundle 
                values  [float]     :   Discount of bundle  
                e.g. 'b1': 0.1
            Note1:  value of discount must be in range [0.0, 1.0]
            Note2:  keys must match the bundle's names    
        '''
        if not isinstance(discounts, dict):
            raise TypeError("Only dictionaries are allowed for discounts!")
        if not all(isinstance(key, str) for key in discounts.keys()):
            raise TypeError("Discount's keys must be strings")
        if not all(isinstance(val, float) for val in discounts.values()):
            raise TypeError("Discount's values must be float")
        if not all(0.0 <= val <= 1.0 for val in  discounts.values()):
            raise ValueError("Discount's values must be more than 0.0 and less than 1.0")
        self.discounts = discounts 


    def set_basket(self, basket):
        '''
            Set dictionary with item's number in the basket

            Format: 
                keys    [string]    :   Name of item 
                values  [int]       :   Number of item in basket   
                e.g. 'a': 5
            Note1:  values can not be less than 0 
            Note2:  keys must match the item's names    
        '''
        if not isinstance(basket, dict):
            raise TypeError("Only dictionaries are allowed for basket configuration!")
        if not all(isinstance(key, str) for key in basket.keys()):
            raise TypeError("Basket's keys must be strings")
        if not all(isinstance(val, int) for val in basket.values()):
            raise TypeError("Number of item in basket must be integers")
        if not all(val >= 0 for val in  basket.values()):
            raise ValueError("Number of item in basket can not be negative")
        self.basket = basket 


    def calculate_max_number_of_bundles(self, min_bundles=0):
        '''
            Calculate dictionary with max number of each bundle depend on basket configuration 

            Args: 
                min_bundles [int]   :   min value of used bundle for optimization (low bound)
                                        default value = 0  
            Returns: 
                [dict]:   dictionary with max number of each bundles       
                    keys    [string]:   bundle's names
                    values  [int]   :   max number of each bundle 
        '''
        # empty dictionary checking 
        if not self.bundles:
            raise ValueError("Bundle's dictionary is empty. Please, use .set_bundles() to fill the dictionary.")
        if not self.items: 
            raise ValueError("Item's dictionary is empty. Please, use .set_items() to fill the dictionary.")
        if not self.discounts:
            raise ValueError("Discounts's dictionary is empty. Please, use .set_discounts() to fill the dictionary.")
        if not self.basket:
            raise ValueError("Basket's dictionary is empty. Please, use .set_basket() to fill the dictionary.")

        # corresponding keys checking 
        if self.bundles.keys() != self.discounts.keys():
            raise KeyError("Bundle's names in bundles-dict and discounts-dict must be the same.")
        if self.items.keys() != self.basket.keys():
            raise KeyError("Item's names in items-dict and basket-dict must be the same.")

        # check if items in bundles match items in item-dict
        items_names = set(self.items.keys())
        bundle_items_names = self.get_unique_items_from_bundles()
        if not bundle_items_names.issubset(items_names):
            raise ValueError(f"Items not from items-dict are used in bundles! ",
                             f"Valid item's names {items_names}. ",
                             f"Items in bundles {bundle_items_names}")

        # permissible value of min_bundles checking 
        if min_bundles < 0:
            raise ValueError("Min number of bundles can not be negative")
        if not isinstance(min_bundles, int):
            raise TypeError("Number of bundles must be integer")

        
        # list of decision variables
        # number of each bundle
        bundle_lp = list(self.bundles.keys())

        # MAXIMIZE value of discount  
        # Create the model
        model = LpProblem(name="Find max discount's value problem", sense=LpMaximize)
        # Initialize the decision variables
        # output values - only integers 
        x_vars = LpVariable.dicts('x', bundle_lp, lowBound=min_bundles, cat='Integer')
        # dict with number of items, not with their names 
        coded_bundle_dict = self.get_coded_bundle_dict()
        # get only prices
        # convert to np.array 
        product_prices = np.array(list(self.items.values()))
        # dict with row-sum prices for each bundle without discount 
        # keys:     bundle's names 
        # values:   int-value of summarized prices   
        total_prices_of_bundles_without_discount = {
            key: np.asscalar(np.array(coded_bundle_dict[key]).dot(product_prices.T)) for key in bundle_lp
        }
        # Z = sum(b_i * b_matr_i * prices * discount_i)
        model += lpSum([x_vars[i] * total_prices_of_bundles_without_discount[i] * self.discounts[i]  for i in bundle_lp])
        # array of basket values 
        basket_prod_number = np.array(list(self.basket.values()))
        # Restriction 
        # number of products in bundles must be less or equal with products number in basket 
        for p in range(len(self.items)):
            model += lpSum([coded_bundle_dict[b][p] * x_vars[b] for b in bundle_lp]) <= basket_prod_number[p]
        # get the solution 
        model.solve() 
        # result value of bundle's number 
        self.bundle_number = {bundle_lp[i]: int(model.variables()[i].varValue) for i in range(len(model.variables()))}

        ######### Preparation for cost calculation #########

        # get from dict only values and convert to numpy row vector 
        bun_num_row_vec = self.get_val_array_from_dict(self.bundle_number, np.int) 
        # reshape row-vector to column-vector 
        self.bundle_number_col = bun_num_row_vec.reshape(len(self.bundle_number), 1)

        # matrix with number-values of bundles
        self.bundle_matrix = self.get_bundle_matrix()

        # item's prices in row-vector 
        self.prices_row = self.get_val_array_from_dict(self.items, np.float) 

        # item's number in basket in row-vector 
        self.basket_row = self.get_val_array_from_dict(self.basket, np.int)

        # price coeffitients in column-vector 
        self.discount_col = 1 - self.get_val_array_from_dict(self.discounts, np.float).reshape(len(self.discounts), 1)
        

    @staticmethod
    def get_bundle_vector(bundle, classes):
        '''
            Get vector with number of each item in specified bundle 

            Args:
                bundle  [row-vector]    :   one bundle 
                classes [list]          :   item's names 
            Return:
                [list if int]           : item's number in one bundle 
        '''

        vector = []
        for class_ in classes:
            if class_ in bundle:
                vector.append(Counter(bundle)[class_])
            else:
                vector.append(0)
        return vector


    def get_bundle_numbers(self):
        '''
            Get dictionary with bundle's number 
        '''
        return self.bundle_number


    @staticmethod
    def get_val_array_from_dict(dict_, type_):
        '''
            Get values of dictionary and pack them into numpy-array
            with specified type 

            Return:
                [np.array]  : row-vector with dict values 
        '''
        return np.array(list(dict_.values()), dtype=type_)
    

    def get_bundle_matrix(self):
        '''
            Get matrix of coded bundles values

            Return:
                [np.ndarray]    : matrix of item's number in each bundle 
                        [row]   : bundle
                        [column]: number of item   
        '''
        coded_bundles = self.get_coded_bundle_dict()
        return pd.DataFrame.from_dict(coded_bundles, orient='index').values


    def get_unique_items_from_bundles(self):
        '''
            Get unique names of items are used in all bundles 
        ''' 
        unique_set = set()
        for lst in self.bundles.values():
            for val in lst: 
                unique_set.add(val)
        return unique_set


    def get_coded_bundle_dict(self):
        '''
            Get dict of bundles with counted products in them 
            
            Returs: 
                [dict]
                    keys    [string]        :   bundle's names 
                    values  [array of int]  :   number of each product in bundle 
        '''
        return {key: self.get_bundle_vector(val, self.items.keys()) for key, val in self.bundles.items()}


    def get_bundled_cost(self):
        '''
            Get cost value for only bundled products
            
            Return:
                [float] : cost value for bundles only 
        '''
        current_discounts = (self.bundle_number_col > 0) * self.discount_col
        bundle_cost = np.asscalar(
                (
                    (self.bundle_number_col * self.bundle_matrix).dot(self.prices_row.T) * current_discounts.T
                ).sum()
            )
        return bundle_cost


    def get_no_bundled_cost(self, no_bundles=False):
        '''
            Get cost value of non-bundled products
            Args:
                no_bundles  [bool]  : usage of generated bundle_number vector 
                            True    : no bundles are used (raw cost of basket, bundle_nums = 0)
                            False   : use generated bundel_number vector from solver/model    
            Return:
                [float]             : cost value for non-bundled products 
        '''
        if no_bundles:
            bundle_num_col = np.zeros((self.bundle_number_col.shape[0], 1))
        else:
            bundle_num_col = self.bundle_number_col
     
        return np.asscalar(
            (self.basket_row - bundle_num_col.T.dot(self.bundle_matrix)).dot(self.prices_row.T)
        )


    def get_total_cost(self):
        '''
            Get total cost value of all products
            
            Return:
                [float] : cost value for all products with used bundle's discounts 
        '''

        no_bundled_cost = self.get_no_bundled_cost()
        bundled_cost = self.get_bundled_cost()
        
        return round(no_bundled_cost + bundled_cost, 2)