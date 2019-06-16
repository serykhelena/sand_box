#include <iostream>
#include <cstdint>

using namespace std; 

struct A {

	virtual ostream &put(ostream &o) const = 0;
   
};

struct B : public A {
    ostream &put(ostream &o) const override {
        return o << 'B';
    }  
};

ostream &operator<<(ostream &o, const A& a)
{
    return a.put(o);

}

int main()
{
    B b;
    cout << b << endl;

    return 0; 
}
