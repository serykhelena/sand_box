#include <iostream>
#include <vector>

#include "Human.h"
#include "Student.h"
#include "Teacher.h"

using namespace std; 

int main()
{
    vector<int> scores; 

    for(auto i = 0; i < 5; i++)
    {
        scores.push_back(i);
    }

    Student *st = new Student("Ivanov", "Ivan", "Ivanovich", scores);

    cout << st -> get_full_name() << endl; 
    cout << "Average score is " << st -> get_average_score() << endl; 

    unsigned int teacher_wt = 40; 
    Teacher *tch = new Teacher("Petrov", "Petr", "Petrovich", teacher_wt);

    cout << tch -> get_full_name() << endl;
    cout << tch -> get_work_time() << endl;


    return 0; 
}