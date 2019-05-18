import random 

def binary_search(sorted_list, item):
		low = 0
		high = len(sorted_list) - 1

		while low <= high:
			mid = int((low + high) / 2)
			guess = sorted_list[mid]
			if guess == item:
				return mid
			elif guess > item:
				high = mid - 1
			else:
				low = mid + 1

my_list = []
for i in range(0, 10):
	my_list.append(random.randint(1,10))

my_list.sort()
print(my_list)
print(binary_search(my_list, 11))	
