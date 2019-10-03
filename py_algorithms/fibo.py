

def fib(pos):
    if pos in (1, 2):
        return 1
    else:
        return fib(pos - 1) + fib(pos - 2)

def print_fib(num):
    for i in range(1, num + 1):
        print(fib(i))

if __name__ == "__main__":
    print_fib(3)
