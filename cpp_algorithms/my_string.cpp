#include <iostream>
#include <string> 

class String 
{
private:
    char* m_Buffer; 
    usigned int m_Size;
public:
    String( const char* string )
    {
        m_Size = strlen( string ); 
        m_Buffer = new char[m_Size + 1]; 

        memcpy(m_Buffer, string, m_Size);     
        m_Buffer[m_Size] = 0; // for /0 in the end of the string
    }

    String(const String& other) // copy constructor, deep copy 
        : m_Size(other.m_Size)
    {
        m_Buffer = new char[m_Size + 1]; 
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1); 

    }

    ~String()
    {
        delete [] m_Buffer;
    }

    char& operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_Buffer(); 
    return stream; 
}

int main( )
{
    String string = "Hello";
    std::cout << string << std::endl; 
    String second = string; // shallowed copy -> try to free the same block of memory twice (if there is no copy contructor)

    std::cin.get();
    return 0; 
}
