import functools 

def my_decorator(func_to_decor):

    def wrapper_for_origin_func():
        print("before calling the function")
        func_to_decor()
        print("after calling the function")
    
    return wrapper_for_origin_func

def lonely_function():
    print("I'm so lonely")


@my_decorator
def another_lonely_func():
    print("Leave me alone")

def bread(func):
    def wrapper():
        print()
        func()
        print(r"<\______/>")
    return wrapper 

def ingredients(func):
    def wrapper():
        print("#tomatos#")
        func()
        print("~salad~")
    return wrapper

@bread
@ingredients
def sandwich(food="--ham--"):
    print(food)

def decor_with_args(fun_to_decor):
    def wrapper_with_args(arg1, arg2):
        print("Here are arguments: ", arg1, arg2)
        fun_to_decor(arg1, arg2)
    return wrapper_with_args

@decor_with_args
def print_full_name(first_name, last_name):
    print("My name is ", first_name, last_name)

def method_friendly_decorator(method_to_decor):
    def wrapper(self, lie):
        lie -= 3
        return method_to_decor(self, lie)
    return wrapper

class Lucy:
    def __init__(self):
        self.age = 32 
    
    @method_friendly_decorator
    def sayYourAge(self, lie):
        print(f"I'm {self.age + lie} y.o.")


def decorator_with_arbitrary_args(func_to_decor):
    def wrapper_with_arbitrary_args(*args, **kwargs):
        print("Hey from decorator")
        func_to_decor(*args, **kwargs)
    return wrapper_with_arbitrary_args

@decorator_with_arbitrary_args
def func_with_no_args():
    print("No args here")

@decorator_with_arbitrary_args
def func_with_args(a, b):
    print(a, b)

@decorator_with_arbitrary_args
def func_with_named_args(a, b, test="Why not?"):
    print(f"Do {a} and {b} love cats? {test}")

class Mary:
    def __init__(self):
        self.age = 31 

    @decorator_with_arbitrary_args
    def sayYourAge(self, lie=-3):
        print(f"I'm {self.age + lie} y.o. Is it true?")

def decorator_maker():
    print("I'm a decorator maker. I would be called only once, when you want to create a decorator")
    def my_decorator(func):
        print("I'm decorator. I would be called only once, when you want ot decor function")
        def wrapper():
            print("I would be called every times when you call function to decorate")
            return func()
        return wrapper 
    return my_decorator

def decorated_func():
    print("I'm decorated function")

@decorator_maker()
def decorated_func2():
    print("I'm decorated function")


def decorator_maker_with_args(arg1, arg2):
    def my_decorator(func):
        def wrapper(func_arg1, func_arg2):
            print("Inside wrapper with args")
            return func(func_arg1, func_arg2)
        return wrapper
    return my_decorator

@decorator_maker_with_args("Leonard", "Sheldon")
def decorated_func_with_args(func_arg1, func_arg2):
    print("I'm decorated function with arguments")


def bar(func):
    def wrapper():
        print("bar")
        return func()
    return wrapper 

@bar
def foo():
    print("foo")

def bar2(func):
    @functools.wraps(func)
    def wrapper():
        print("bar")
        return func()
    return wrapper 

@bar2
def foo2():
    print("foo2")


def mydecorator(msg):
    def decorated(f):
        def wrapper(*args, **kwargs):
            print(f"The messgae is {msg}")
            print("Inside of the decorator BEFORE")
            print(msg)
            f(*args, **kwargs)
            print("Inside of the decorator AFTER")
        return wrapper 
    return decorated 

@mydecorator(msg="Hello")
def print_my_name(name):
    print(name)


if __name__ == '__main__':
    lonely_function = my_decorator(lonely_function)
    lonely_function()

    another_lonely_func()

    sandwich()

    print_full_name("Ivan", "Ivanov")

    girl = Lucy()
    girl.sayYourAge(-3)

    func_with_no_args()
    func_with_args(1, 2)
    func_with_named_args("rats", "mouses")
    
    m = Mary()
    m.sayYourAge()

    new_decorator = decorator_maker()
    decorated_func = new_decorator(decorated_func)
    decorated_func()
    decorated_func2()

    decorated_func_with_args("Howard", "Emmy")

    print(foo.__name__)
    print(foo2.__name__)

    print_my_name('Bob')