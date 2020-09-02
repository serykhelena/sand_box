
def even_fib(num):
    '''
        Get only even numbers from Fibonacci sequence 

        args:       
            num     - number of even numbers 
        return:
            [list]  - list with only even numbers     
    '''
    return [fib(i * 3) for i in range(num)]


def fib(pos):
    if pos == 0:
        return 0
    if pos in (1, 2):
        return 1
    else:
        return fib(pos - 1) + fib(pos - 2)


def print_fib(num):
    for i in range(1, num + 1):
        print(fib(i), end=' ')

if __name__ == "__main__":
    print(even_fib(4))

