/*
========================================================
File: e_math.h
Author: Kenneth Stepney
Purpose: Math Utilities 

========================================================
*/


#ifndef VECTOR_H
#define VECTOR_H

#include "defs.h"
#include "math.h"

#define PI 3.14159265359

enum VECTOR_POS
{
    X_POS,
    Y_POS,
    Z_POS,

    NUM_POS
};

namespace e_math
{
    template<class T>
    inline T pow(T number, int pow)
    {
        T result = number;

        for(int i = 0; i < pow; i++)
        {
            result *= result;
        }

        return result;
    }
    //Take the absolute value of a number
    /*
        float num - number to take the absolute value of.
    */
    inline float abs(float num)
    {
        return (num < 0 ? -num : num);
    }

    //Custom modulo operation, since th ec library's version techincal isn't modulo
    /*
        int32 operand1 - operand to (operand1) mod (operand2)
        int32 operand2 - operand to (operand1) mod (operand2)
    */
    inline int modulo(int operand1, int operand2)
    {
        int m = (operand1 % operand2);
        return m < 0 ? (m + operand2) : m;
    }

    inline double degreeToRad(int degree)
    {
        return degree * ( PI / 180);
    }

    template <class T>
    class Vector
    {
    public:
        Vector() : x(0), y(0), z(0) {}
        Vector(T set_x, T set_y, T set_z) : 
                                            x(set_x), y(set_y), 
                                            z(set_z) {}
        Vector(const Vector<T>& vector) 
        {
            *this = vector;
        }

        virtual ~Vector() {}

        Vector<T>& operator=(const Vector<T>& vector2)
        {
            (*this)[X_POS] = vector2.getX();
            (*this)[Y_POS] = vector2.getY();
            (*this)[Z_POS] = vector2.getZ();

            return *this;
        }

        T& operator[](int index)
        {
            switch(index)
            {
                case X_POS:
                {
                    return x;
                } 
                case Y_POS:
                {
                    return y;
                }
                case Z_POS:
                {
                    return z;
                } 
            }

            printf("Error! Index Out of Bounds: %d\n", index);
            return x;
        }

        Vector<T>& operator+=(Vector<T>& vector2)
        {
            for(int i = 0; i < NUM_POS; i++) (*this)[i] += vector2[i];
            return *this;
        }

        Vector<T>& operator-=(Vector<T>& vector2)
        {
            for(int i = 0; i < NUM_POS; i++) (*this)[i] -= vector2[i];
            return *this;
        }

        //prefix
        Vector<T>& operator++()
        {
            for(int i = 0; i < NUM_POS; i++) (*this)[i]++;
            return *this;
        }

        //postfix
        Vector<T> operator++(int)
        {
            Vector<T> vector = *this;

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i]++;
            }

            return vector;
        }

        Vector<T>& operator--()
        {
            for(int i = 0; i < NUM_POS; i++) (*this)[i]--;
            return *this;
        }

        Vector<T> operator--(int)
        {
            Vector<T> vector = *this;

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i]--;
            }

            return vector;
        }

        Vector<T>& operator*=(int scalar)
        {
            for(int i = 0; i < NUM_POS; i++)(*this)[i] *= scalar;
            return *this;
        }

        Vector<T>& operator/=(int scalar)
        {
            for(int i = 0; i < NUM_POS; i++) (*this)[i] /= scalar;
            return *this;
        }

        bool operator==(Vector<T>& vector2)
        {
            bool equal = false;
            for(int i = 0; i < NUM_POS; i++) equal = (*this)[i] == vector2[i];
            return equal;
        }

        bool operator!=(Vector<T>& vector2)
        {
            bool not_equal = false;
            for(int i = 0; i < NUM_POS; i++) not_equal = !((*this)[i] != vector2[i]);
            return not_equal;
        }

        Vector<T> operator+(Vector<T>& vector2)
        {
            Vector<T> vector(x, y, z);

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i] += vector2[i];
            }

            return vector;
        }

        Vector<T> operator-(Vector<T>& vector2)
        {
            Vector<T> vector(x, y, z);

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i] -= vector2[i];
            }

            return vector;
        }

        Vector<T> operator*(int scalar)
        {
            Vector<T> vector(x, y, z);

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i] *= scalar;
            }

            return vector;
        }

        Vector<T> operator/(int scalar)
        {
            Vector<T> vector(x, y, z);

            for(int i = 0; i < NUM_POS; i++)
            {
                vector[i] /= scalar;
            }

            return vector;
        }


        void printTests(Vector<T>& vector)
        {
            Vector<T> vector_main(*this);

            (vector_main + vector).printStats();
            (vector_main - vector).printStats();
            vector_main += vector;
            vector_main.printStats();
            vector_main -= vector;
            vector_main.printStats();

            (vector_main * pow<int>(2, 2)).printStats();
            (vector_main / 5).printStats();

            vector_main *= 2;
            vector_main.printStats();
            vector_main /= 2;
            vector_main.printStats();

            vector_main++;
            vector_main.printStats();
            vector_main--;
            vector_main.printStats();

            printf("Index: %d %d %d\n", vector_main[X_POS], vector_main[Y_POS], vector_main[Z_POS]);
            //printf("Test: %d\n%d\n", (*this)[X_POS], X_POS);
        }

        void printStats()
        {
            printf("Vector - \nX: %d\nY: %d\nZ: %d\n", (int)x, (int)y, (int)z);
        }


        //returns the vector equal to the this vector rotated along the y-axis
        Vector<T> rotate2D(int degree)
        {
            double rad = degreeToRad(degree);

            T xx = (T)(x * cos(rad) - y * sin(rad));
            T yy = (T)(x * sin(rad) + y * cos(rad));
            
            Vector<T> vector(xx, yy, 0);
            return vector; 
        }

        T getX() const { return x; }
        T getY() const { return y; }
        T getZ() const { return z; }

    private:
        T x;
        T y;
        T z;
    };

    typedef Vector<int> vec3i;
    typedef Vector<float> vec3f;
    typedef Vector<double> vec3d;

    const vec3i zero_vector();
}


#endif