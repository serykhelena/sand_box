
class Singleton(object):
    # overwritiing method for creating objects to control it 
    def __new__(cls):
        # hasattr - method to check if the obj has a feature 
        if not hasattr(cls, 'instanse'):
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance

