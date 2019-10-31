#include <iostream>
#include <string>

using namespace std;

template <class Type>
class SmartPointer
{
private:
    Type* ptr;
public:
    SmartPointer(Type* p): ptr(p){}

    operator Type*() { return ptr; }
    Type *operator->()
    {
        if( !ptr )
        {
            ptr = new Type();
            cerr << "Bad pointer!" << endl;
        }
        return ptr;
    }

    ptrdiff_t operator-(SmartPointer<Type> p)
    {
        return ptr - p;
    }

    ptrdiff_t operator-(void* p)
    {
        return ptr - p;
    }
};

class StringPointer
{
private:
    string *ptr;

public:
    StringPointer(string *p): ptr(p) {}

    operator string*()
    {
        if( !ptr )
        {
            ptr = new string();
        }
        return ptr;
    }

    string *operator->()
    {
        if( !ptr )
        {
            ptr = new string();
        }
        return ptr;
    }

    ~StringPointer()
    {
        if( !ptr ) delete ptr;
    }
};


class Foo
{
private:
    int16_t a, b;
public:
    Foo(): a(0), b(0) {}
    Foo(int16_t a, int16_t b): a(a), b(b) {}

    int16_t Sum() { return a + b; }

};


int main()
{
    SmartPointer<Foo> sp(NULL);

    string s1 = "Hello, world!";

    StringPointer sp1(&s1);
    StringPointer sp2(NULL);

    cout << sp1 -> length() << endl;
    cout << *sp1 << endl;
    cout << sp2 -> length() << endl;
    cout << *sp2 << endl;
//    cout << sp -> Sum() << endl;
    return 0;
}
