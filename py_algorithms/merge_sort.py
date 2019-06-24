import random 
import time 

'''
	Algorithm complexity is O(n log(n))
	https://tproger.ru/translations/sorting-algorithms-in-python/
'''
def merge(left_list, right_list):
	sorted_list = [] 
	left_list_indx = right_list_indx = 0 

	left_list_len, right_list_len = len(left_list), len(right_list)

	for _ in range(left_list_len + right_list_len):
		if left_list_indx < left_list_len and right_list_indx < right_list_len:

			if left_list[left_list_indx] <= right_list[right_list_indx]:
				sorted_list.append(left_list[left_list_indx])
				left_list_indx += 1
			else:
				sorted_list.append(right_list[right_list_indx])
				right_list_indx += 1

		# if it is the end of left list
		# add right list elements in the end of sorted list 	
		elif left_list_indx == left_list_len:
			sorted_list.append(right_list[right_list_indx])
			right_list_indx += 1
		elif right_list_indx == right_list_len:
			sorted_list.append(left_list[left_list_indx])
			left_list_indx += 1

	return sorted_list

def merge_sort(data):
	if len(data) <= 1:
		return data 

	mid = len(data) // 2 # division without remainder 

	left_list = merge_sort(data[:mid])
	right_list = merge_sort(data[mid:])

	return merge(left_list, right_list)



def runner():
	start = time.time()
	rand_list = random.sample(range(10), 5)
	print(f"The initial data: {rand_list}")
	result = merge_sort(rand_list)
	print(f"The result data: {result}")
	end = time.time()
	print(f"Time of execution: {round(end - start, 5)} s")


if __name__ == "__main__":
	runner()