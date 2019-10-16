#include <iostream>
#include <string>
#include <cstring>
#include <algorithm> 

using namespace std; 

void reverseString(string& str)
{
    int n = str.length(); 
    for(int i = 0; i < n / 2; i++)
    {
        swap(str[i], str[n - 1 - i]); 
    }
}

void print_reverse(string& str)
{
    for(int i = str.length() - 1; i >= 0; i--)
    {
        cout << str[i];
    }
}

char* reverseConstString(char const *str)
{
    int n = strlen(str);

    char *rev = new char[n + 1];
    strcpy(rev, str); 
    for(int i = 0, j = n - 1; i < j; i++, j--)
    {
        swap(rev[i], rev[j]);
    }

    return rev; 
}

void inv(char* str)
{
    char *start = str; 
    char *end = start + strlen(str) - 1;
    
    while(start < end)
    {
        char tmp = *end; 
        *end = *start; 
        *start = tmp; 
        start ++;
        end--;
    }
}

int main()
{
    string str = "Hello";
    cout << str << "\t";
    reverseString(str);
    cout << str << endl; 

    cout << str << "\t";
    reverse(str.begin(), str.end());
    cout << str << endl; 

    print_reverse(str);
    cout << "\n";
    const char *s = "Constant";

    cout << s << "\t" << reverseConstString(s) << endl;

    char ss[] = "Dynamic";
    cout << ss << "\t";
    inv(ss); 
    cout << ss << endl; 
    

    return 0;
}