import random 
import time 

'''
	Algorithm complexity is O(n log(n))
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''

def quick_sort_eat_memory(data):

	if len(data) <= 1:
		return data
	else:

		i = 0
		j = len(data)-1
		pivot = data[(i + j) // 2]
		left = []
		mid = []
		right = []

		for d in data:
			if d < pivot:
				left.append(d)
			elif d > pivot:
				right.append(d)
			else:
				mid.append(d)

		return quick_sort_eat_memory(left) + mid + quick_sort_eat_memory(right)

	
def quick_sort_economy(data, low, high):
	if low >= high:
		return 
	else:
		pivot = data[(low+high) // 2]
		i = low
		j = high

		while i <= j:
			while data[i] < pivot:
				i += 1

			while data[j] > pivot:
				j -= 1

			if i <= j: 
				data[i], data[j] = data[j], data[i]
				i += 1
				j -= 1
				quick_sort_economy(data, low, j)
				quick_sort_economy(data, i, high)
	

def runner():
	start = time.time()

	rand_list = random.sample(range(10), 5)
	print(f"The initial data: {rand_list}")

	quick_sort_economy(rand_list, 0, len(rand_list)-1)
	print(f"The result data: {rand_list}")

	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")


if __name__ == "__main__":
	runner()