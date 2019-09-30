
class Node:
    def __init__(self, value = None, next = None):
        self.value = value
        self.next = next 

class LinkedList:
    def __init__(self):
        self.first = None
        self.last = None
        self.length = 0

    def __str__(self):
        if self.first != None:
            current = self.first
            out = 'LinkedList [\n' + str(current.value) + '\n'
            while current.next != None:
                current = current.next 
                out += str(current.value) + '\n'
            return out + ']'
        return 'LinkedList []'

    def get_length(self):
        self.length = 0
        if self.first != None:
            self.length += 1
            current = self.first
            while current.next != None:
                current = current.next
                self.length += 1
        return self.length
    
    def begin_push(self, val):
        if self.first != None:
            self.first = Node(val, None)
            self.last = self.first 
        else:
            self.first = Node(val, self.first)

    
    def clear(self):
        self.__init__()

if __name__ == '__main__':
    L = LinkedList()
    L.begin_push(5)
    # L.add(1)
    # L.add(2)
    # L.add(3)
    print(L.get_length())
