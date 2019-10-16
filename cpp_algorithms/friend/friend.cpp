#include <iostream>
#include <string.h> 

#include "Vector3D.h"
#include "Point3D.h"

using namespace std; 

class Woman25
{
private:
    char *name; 
    int weight; 

    friend void setData(char *, int, Woman25&); 
    friend void getData(Woman25&); 
public:
    Woman25()
    {
        name = new char[20]; 
        strcpy(name, "Norma");
        weight = 60; 
    }
    ~Woman25()
    {
        cout << "Destructor " << name << endl; 
        delete [] name; 
        
    }

    void setData(char *n, int w)
    {
        strcpy(name, n);
        weight = w; 
    } 
    void getData()
    {
        cout << name << "\t" << weight << " kg" << endl; 
    }
    void advise()
    {
        if(weight < 55) 
        {
            cout << "You need to consume more callories!" << endl;
            cout << "=====================================" << endl << endl;
        }
        else if(weight >= 55 && weight <= 65)
        {
            cout << "Your weight is normal!" << endl;
            cout << "=====================================" << endl << endl;
        }
        else
        {
            cout << "You need to lose weight!" << endl;
            cout << "=====================================" << endl << endl;
        }
    }
};

void setData(char *n, int w, Woman25& obj)
{
    strcpy(obj.name, n); 
    obj.weight = w; 
}

void getData(Woman25& obj)
{
    cout << obj.name << "\t" << obj.weight << " kg" << endl; 
}

class Humidity;

class Temperature
{
private:
    int m_temp;
public:
    Temperature(int temp = 0)
    {
        m_temp = temp;
    }

    friend void outWeather(const Temperature & temp, const Humidity &hum);
};

class Humidity
{
private:
    int m_humidity;
public:
    Humidity(int hum = 0)
    {
        m_humidity = hum;
    }

    friend void outWeather(const Temperature & temp, const Humidity &hum);
};

void outWeather(const Temperature & temp, const Humidity &hum)
{
    cout << "The weather is " << temp.m_temp << 
            " and the humidity is " << hum.m_humidity << endl;
}

class Values;

class Printer
{
public:
    void showValues(Values & val);
};

class Values
{
private:
    int m_intValue; 
    double m_dValue; 
public:
    Values(int intVal, double dValue)
    {
        m_intValue  = intVal;
        m_dValue    = dValue;
    }

    friend class Display; // Display is friend of Values 

    friend void Printer::showValues(Values & val);
};

void Printer::showValues(Values & val)
{
    cout << val.m_intValue << " " << val.m_dValue << endl; 
}

/* 
    Any of Display membres has an access to any of Value members
    because Display is a friend of Values
    BUT Values is not a friend of Display 
 */
class Display
{
private:
    bool m_dispIntFirst;
public: 
    Display(bool d)
    {
        m_dispIntFirst = d; 
    }

    void displayItems(Values &val)
    {
        if(m_dispIntFirst)
            cout << val.m_intValue << " " << val.m_dValue << endl;
        else
            cout << val.m_dValue << " " << val.m_intValue << endl; 
    }
};

int main()
{
    Woman25 Norm; 
    Norm.getData(); 

    Woman25 Anna; 
    Anna.setData("Anna", 100); 
    Anna.getData(); 
    Anna.advise(); 

    Woman25 Inna; 
    setData("Inna", 50, Inna);
    getData(Inna); 
    Inna.advise();

    Temperature t(15); 
    Humidity h(11);

    outWeather(t, h);

    Values v(7, 8.4);
    Display d(false);

    d.displayItems(v);

    Point3D pnt(3.0, 4.0, 5.0);
    Vector3D vec(3.0, 3.0, -2.0);

    pnt.print();
    vec.print();
    pnt.moveByVector(vec);
    pnt.print();

    return 0; 
}