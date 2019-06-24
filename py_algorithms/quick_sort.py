import random 
import time 

'''
	Algorithm complexity is O(n log(n))
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''

def partition(data, low, high):

	pivot = data[(low + high) // 2]
	i = low
	j = high

	while True: 

		print(f"{i} :: {j}")
		while data[i] < pivot:
			i += 1 

		while data[j] > pivot:
			j -= 1

		if i <= j:
			data[i], data[j] = data[j], data[i] 
			i += 1
			j -= 1
		if i <= j:
			break 

	return j 


	
	# while True:
	# 	i += 1
	# 	while data[i] < pivot:
	# 		i += 1 

	# 	j -= 1
	# 	while data[j] > pivot: 
	# 		j -= 1

	# 	if i >= j:
	# 		return j 

	# 	data[i], data[j] = data[j], data[i] 

def quick_sort(data):
	def _quick_sort(items, low, high):
		split_indx = partition(items, low, high)
		_quick_sort(items, low, split_indx)
		_quick_sort(items, split_indx+1, high)

	return _quick_sort(data, 0, len(data)-1)


def runner():
	start = time.time()

	rand_list = random.sample(range(10), 5)
	print(f"The initial data: {rand_list}")

	result = quick_sort(rand_list)
	print(f"The result data: {result}")

	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")


if __name__ == "__main__":
	runner()