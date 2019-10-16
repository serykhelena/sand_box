#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <sstream>

using namespace std; 

class Human
{
    private:
        string name; 
        string last_name;
        string second_name; 
    public:
        Human(string last_name, string name, string second_name) 
            : name(name), last_name(last_name), second_name(second_name) {}
        
        string get_full_name()
        {
            ostringstream full_name; 
            full_name << last_name << " "
                      << name << " "
                      << second_name;
            return full_name.str();
        }
};

#endif 