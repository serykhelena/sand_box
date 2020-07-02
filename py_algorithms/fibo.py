

def fib_even_only(num):
	'''
		Return only even numbers from Fibonacci sequence

		Args: 
			num 	- number of even values 

		Return
			[list]	- array with even-only values  
	'''
    counter = 1 
    res = [0]
    temp = [1, 1]
    if num <= 0: 
    	return None 
    
    while counter < num: 
        cur_val = temp[len(temp) - 2] + temp[len(temp) - 1]
        temp[0], temp[1] = temp[1], cur_val
        
        if cur_val % 2 == 0:
            res.append(cur_val)
            counter += 1 

    return res 


def fib(pos):
    if pos in (1, 2):
        return 1
    else:
        return fib(pos - 1) + fib(pos - 2)


def print_fib(num):
    for i in range(1, num + 1):
        print(fib(i), end=' ')

if __name__ == "__main__":
    print_fib(3)
    print('\n')
    print(fib_even_only(0), end=' ')

