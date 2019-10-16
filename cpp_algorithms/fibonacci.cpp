#include <iostream>

using namespace std; 

int fib_rec(int n)
{
    if(n == 1)
        return 0;
    else if(n <= 3)
        return 1;
    else
    {
        return fib_rec(n - 2) + fib_rec(n - 1);
    }
}

int fib(int n)
{
    if(n == 1)
        return 0;
    else if(n <= 3)
        return 1;
    else
    {
        int res = 2;
        int tmp = 2;
        int prev = 1; 
        for(int i = 4; i < n; i++)
        {
            res = tmp + prev;
            prev = tmp; 
            tmp = res; 
        }
        return res;
    }
}


int main()
{
    for(int i = 1; i < 10; i++)
    {
        cout << fib_rec(i) << "\t";
        cout << fib(i) << endl;
    }

    return 0; 
}