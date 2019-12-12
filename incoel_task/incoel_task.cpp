#include <iostream>
#include <memory>

using namespace std; 

class SomeClass {
public:
	SomeClass()
	{
		try {
			x1 = shared_ptr<char>(new char[1024], [] (char* i) { 
				delete [] i;
				});
		}
		catch ( const bad_alloc& ba1)
		{
			cerr << "Not enought memory for x1: " << ba1.what() << endl;
		}
		
		try {

			x2 = shared_ptr<char>(new char[1024 * 1024], [] (char* i) {
				delete [] i;
			});
		}
		catch ( const bad_alloc& ba2)
		{
			cerr << "Not enought memory for x2: " << ba2.what() << endl;
		}
	}

private:
	shared_ptr<char> x1;
	shared_ptr<char> x2; 
};

int main()
{
	SomeClass obj = SomeClass();

	return 0; 
}