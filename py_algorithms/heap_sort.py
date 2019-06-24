import random 
import time 

'''
	Algorithm complexity is O(n log(n))
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''

def heapify(data, heap_size, root_indx):
	largest = root_indx 
	left_child = root_indx + 1
	right_child = root_indx + 2 

	if left_child < heap_size and data[left_child] > data[largest]:
		largest = left_child

	if right_child < heap_size and data[right_child] > data[largest]:
		largest = right_child

	if largest != root_indx:
		data[root_indx], data[largest] = data[largest], data[root_indx]
		heapify(data, heap_size, largest)


def heap_sort(data):
	n = len(data)
	# reverse n, n-1, n-2 ... 0 
	for i in range(n, -1, -1):
		# create heap from data (max value is the top)
		heapify(data, n, i)

	data = data[::-1]

	return data


def runner():
	start = time.time()
	rand_list = random.sample(range(10), 5)
	print(f"The initial data: {rand_list}")
	heap_sort(rand_list)
	result = heap_sort(rand_list)
	print(f"The result data: {result}")
	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")


if __name__ == "__main__":
	runner()
