import random 
import time 

'''
	Algorithm complexity is O(n^2)
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''

def bubble_sort(data):
	swapped = True 
	while swapped:
		swapped = False
		for d in range(len(data)-1):
			if data[d] > data[d+1]:
				data[d], data[d+1] = data[d+1], data[d]
				swapped = True 

	return data 

def runner():
	start = time.time()
	rand_list = random.sample(range(10), 5)
	print(f"The innitial data: {rand_list}")
	result = bubble_sort(rand_list)
	print(f"The result data: {result}")
	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")

if __name__ == "__main__":
	runner()	

