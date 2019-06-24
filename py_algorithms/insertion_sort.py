import random 
import time 

'''
	Algorithm complexity is O(n^2)
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''
def insertion_sort(data):
	# assume that first element is already sorted 
	for d in range(1, len(data)):
		item_to_insert = data[d]
		# index of previous element 
		j = d - 1

		while j >= 0 and data[j] > item_to_insert:
			data[j+1] = data[j]
			j -= 1

		data[j+1] = item_to_insert
	return data 

def runner():
	start = time.time()
	rand_list = random.sample(range(10), 5)
	print(f"The innitial data: {rand_list}")
	result = insertion_sort(rand_list)
	print(f"The result data: {result}")
	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")

if __name__ == "__main__":
	runner()