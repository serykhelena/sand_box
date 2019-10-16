#ifndef STUDENT_H
#define STUDENT_H

#include "Human.h"
#include <string>
#include <vector>

class Student: public Human
{
    private:
        vector<int> scores; 
    public:
        Student(string last_name, string name, 
                string second_name, vector<int> scores)
                : Human(last_name, name, second_name) 
        {
            this -> scores = scores; 
        }

        float get_average_score()
        {
            unsigned int count_scores = scores.size(); 
            unsigned int sum_scores = 0; 
            float average_scores = 0; 

            for( auto i = 0; i < count_scores; i++)
            {
                sum_scores += scores[i];
            }
            average_scores = (float) sum_scores / (float) count_scores; 
            return average_scores; 
        }
};

#endif