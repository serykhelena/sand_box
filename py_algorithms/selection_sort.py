import random 
import time 

'''
	Algorithm complexity is O(n^2)
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''

def selection_sort(data):
	for d in range(len(data)):
		lowest_indx = d # the min element  
		for i in range(d+1, len(data)):
			if data[i] < data[lowest_indx]:	# find another min element 
				lowest_indx = i 
		data[d], data[lowest_indx] = data[lowest_indx], data[d]	# change 

	return data 

def runner():
	start = time.time()
	rand_list = random.sample(range(10), 5)
	print(f"The innitial data: {rand_list}")
	result = selection_sort(rand_list)
	print(f"The result data: {result}")
	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")


if __name__ == "__main__":
	runner()

