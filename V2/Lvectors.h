#pragma once
class Vector{

    public:
        int size;
        float* v;

        //for creating vector from scratch
        Vector(int n);
        //for copying a vector properly
        Vector(const Vector& other);

        Vector& operator=(const Vector& other);

        void takeInput();
        void Print();
        //destructor
        ~Vector();
};

float Dot(Vector* a,Vector* b);

Vector Add(const Vector& a,const Vector& b);

Vector Scale(const Vector& a,float scale);

bool IsEqual(const Vector& a,const Vector& b);