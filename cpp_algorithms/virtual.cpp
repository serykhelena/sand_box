#include <iostream>

using namespace std; 

class Animal
{
public:
    virtual void voice(void)
    {
        cout << "Animal!" << endl; 
    } 

};

class Cat: public Animal
{
public:
    void voice(void) override
    {
        cout << "Myau" << endl; 
    }
};

class Dog: public Animal
{
public:
    void voice(void) override 
    {
        cout << "Wow" << endl;
    }
};

class Puddle: public Dog
{

};

class MagicAnimal: public Animal
{

};

void show_whoose_voice(Animal & an)
{
    an.voice();
}

class Figure 
{
protected:
    double x, y; 
public:
    void set_dim(double i, double j = 0)
    {
        x = i; 
        y = j; 
    }
    virtual void show_area() = 0;   // pure virtual function
};

class Triangle: public Figure
{
public: 
    void show_area() override
    {
        cout << "Triangle with height " << x << " and base " << y;
        cout << " has an area of " << x * 0.5 * y << endl;
    }
};

class Square: public Figure
{
    void show_area() override
    {
        cout << "Square with dimensions " << x << "x" << y;
        cout << " has an area of " << x * y << endl; 
    }
};

class Circle: public Figure
{
public: 
    void show_area()
    {
        cout << "Circle with radius " << x;
        cout << " has an area of " << 3.14 * x * x << endl; 
    }
};

class Temp
{
private:
    int counter; 
public: 
    Temp()
    {
        counter = 0; 
        cout << "Temp created" << endl; 
    }    

    ~Temp()
    {
        cout << "Temp determinated" << endl; 
    }

};

int main()
{
    Animal a; 
    Animal *a_ptr; 

    Cat cat; 
    Dog dog; 
    Puddle pud; 
    MagicAnimal ma; 

    a_ptr = &a; 
    cout << "Animal says: ";
    a_ptr -> voice();  
    /* Указатель на базовый класс м.б. использован 
       для любого производного класса */
    a_ptr = &cat; 
    cout << "Cat says: ";
    a_ptr -> voice(); 

    a_ptr = &dog; 
    cout << "Dog says: ";
    a_ptr -> voice(); 

    a_ptr = &pud; 
    cout << "Puddle says: ";
    a_ptr -> voice();

    a_ptr = &ma; 
    cout << "Magic animal says: ";
    a_ptr -> voice();

    show_whoose_voice(a);
    show_whoose_voice(cat);
    show_whoose_voice(dog);

/************************************/
    Figure *f_ptr; 
    Triangle t; 
    Square sq; 

    f_ptr = &t; 
    f_ptr -> set_dim(10.0, 5.0);
    f_ptr -> show_area(); 

    f_ptr = &sq; 
    f_ptr -> set_dim(10.0, 5.0);
    f_ptr -> show_area();

    Circle c; 
    f_ptr = &c;
    f_ptr -> set_dim(9.0);
    f_ptr -> show_area();

    return 0; 
}