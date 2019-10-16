#pragma once 

#include "Point3D.h"

class Vector3D
{
    private:
        double m_x;
        double m_y;
        double m_z; 
    public:
        Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : m_x(x), m_y(y), m_z(z) {}

        void print();
        friend void Point3D::moveByVector(const Vector3D &v); 
};
