
class SimpleIterator:
    def __init__(self, limit):
        self.limit = limit
        self.counter = 0
    
    def __next__(self):
        if self.counter < self.limit:
            self.counter += 1
            return 1
        else:
            raise StopIteration
    
    def __iter__(self):
        return self

if __name__ == '__main__':

    n_list = [1, 2, 3]
    for i in n_list:
        print(i, end=" ")
    print('\n')

    itr = iter(n_list)
    print(next(itr), end=" ")
    print(next(itr), end=" ")
    print(next(itr), end=" ")
    print('\n')

    s_itr = SimpleIterator(3)
    for i in s_itr:
        print(i)