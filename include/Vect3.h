#ifndef __OPENGL_EXPERIMENT_TRIPLE_H__
#define __OPENGL_EXPERIMENT_TRIPLE_H__

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

// Vect3 
struct Vect3 
{
    float xyz[3];

    Vect3()
    {
        xyz[0] = 0.0; xyz[1] = 0.0; xyz[2] = 0.0;
    }

    Vect3(const Vect3& v)
    {
        xyz[0]=v.xyz[0]; xyz[1]=v.xyz[1]; xyz[2]=v.xyz[2]; 
    }

    Vect3& operator=(const float* array3f)
    {
        xyz[0]=array3f[0]; xyz[1]=array3f[1]; xyz[2]=array3f[2];
        return *this;
    }

    void Set(float x, float y, float z)
    {
        xyz[0] = x; xyz[1] = y; xyz[2] = z; 
    }

    Vect3& operator=(const Vect3& v)
    {
        xyz[0]=v.xyz[0]; xyz[1]=v.xyz[1]; xyz[2]=v.xyz[2]; 
        return *this;
    }

    Vect3 operator+(const Vect3& other) const
    {
        Vect3 v;
        v += other;
        return v;
    }

    Vect3 operator-(const Vect3& other) const
    {
        Vect3 v;
        v -= other;
        return v;
    }

    Vect3 operator*(const float& a) const
    {
        Vect3 v;
        v *= a;
        return v;
    }
    
    Vect3& operator+=(const Vect3& other)
    {
        xyz[0] = other.xyz[0];  xyz[1] += other.xyz[1]; xyz[2] += other.xyz[2];
        return *this;
    }
    
    Vect3& operator-=(const Vect3& other)
    {
        xyz[0] -= other.xyz[0];  xyz[1] -= other.xyz[1]; xyz[2] -= other.xyz[2];
        return *this;
    }

    Vect3& operator*=(const float& a)
    {
        xyz[0] *= a; xyz[1] *= a; xyz[2] *= a;
        return *this;
    }

    float dot(const Vect3& v) const
    {
        return xyz[0]*v.xyz[0] + xyz[1]*v.xyz[1] + xyz[2]*v.xyz[2];
    }

    Vect3 cross(const Vect3& v) const
    {
        Vect3 c;
        c.xyz[0] = xyz[1]*v.xyz[2] - xyz[2]*v.xyz[1];
        c.xyz[1] = xyz[2]*v.xyz[0] - xyz[0]*v.xyz[2];
        c.xyz[2] = xyz[0]*v.xyz[1] - xyz[1]*v.xyz[0];
        return c;
    }

    float norm2() const
    {
        return (xyz[0] * xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
    }

    float norm() const
    {
        return std::sqrt(norm2());
    }

} __attribute__((packed));

#endif
