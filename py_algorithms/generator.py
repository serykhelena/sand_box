
def simple_generator(val):
    while val > 0:
        val -= 1
        yield 1 

if __name__ == '__main__':
    gen_itr = simple_generator(5)
    print(next(gen_itr))
    print(next(gen_itr))
    print(next(gen_itr))
    print(next(gen_itr))
    print(next(gen_itr))