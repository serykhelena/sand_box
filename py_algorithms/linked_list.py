# http://greenteapress.com/thinkpython/html/chap17.html 


class Node:
    def __init__(self, value = None, next = None):
        self.value = value
        self.next = next 
    
    def print_backward(self):
        if self.next != None:
            tail = self.next
            tail.print_backward() 
        print(self.value, end=" ")
    
    def __str__(self):
        return str(self.value)


class LinkedList:
    def __init__(self):
        self.length = 0
        self.head = None 

    def print_backward(self):
        print('[', end="")
        if self.head != None:
            self.head.print_backward()
        print(']')
    
    def print_forward(self):
        print_head = self.head

        if print_head == None:
            print("The List is empty )=")
            return

        print('[', end="")
        while print_head:
            if print_head.next != None:
                print(print_head, end="")
                print(', ', end="")
            else:
                print(print_head, end="")
            print_head = print_head.next
        print(']')
        return 
    
    def add_first(self, value):
        node = Node(value)
        if self.head != None:
            node.next = self.head
        else:
            node.next = None 
        self.head = node 
        self.length += 1 
    
    def add(self, value):
        node = Node(value)
        if self.head != None:
            tail = self.head 
            while tail.next != None:
                tail = tail.next 
            tail.next = node 
            node.next = None 
        else:
            self.head = node 
        self.length += 1
    
    def insert_element(self, pos, value):
        counter = 0
        if pos == 0:
            self.add_first(value)
        elif pos == self.length + 1:
            self.add(value)
            self.length += 1
        elif self.head == None: 
            self.add(value)
            self.length += 1
        elif self.head != None:
            find_el = self.head 
            while counter != pos - 1:
                find_el = find_el.next 
                counter += 1 
            insert_el = Node(value, find_el.next)
            find_el.next = insert_el 
            self.length += 1
    
    def pop_head(self):
        if self.head == None: 
            print('The list is emtpy')
        else:
            if self.head.next != None: 
                self.head = self.head.next
            else:
                self.head = None 
            self.length -= 1

    def delete_element(self, pos):
        counter = 0
        if pos == 0:
            self.pop_head()
        elif self.head == None:
            print("The linked list is empty")
            return 
        elif self.head.next == None: 
            print(self.get_length())
        else:
            find_el = self.head
            while counter != pos - 1:
                find_el = find_el.next 
                counter += 1
            del_el = find_el.next 
            find_el.next = del_el.next 
            del_el = None 
            self.length -= 1

    def get_length(self):
        return 'The length of linked list is: ' + str(self.length)

    def __str__(self):
        print_head = self.head 
        if self.head != None:
            out = 'LinkedList [\n\t' + str(print_head.value)
            while print_head.next != None:
                out += ', '
                print_head = print_head.next 
                out += str(print_head.value)
            return out + '\n]'
        return 'LinkedList []'

    def clean(self):
        self.__init__()
    
if __name__ == '__main__':
    L1 = LinkedList()
    L1.add(1)
    L1.add(2)
    L1.add(3)
    L1.insert_element(3, 5)
    print(L1)
    print(L1.get_length())
    L1.pop_head()
    print(L1)
    print(L1.get_length())
    L1.delete_element(1)
    print(L1)
    print(L1.get_length())
