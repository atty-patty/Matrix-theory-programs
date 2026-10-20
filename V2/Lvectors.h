#pragma once
class Vector{

    public:
        int size;
        float* v;

        Vector(int n);

        void Print();
        //free up the dyanmically allocated memory
        void Remove();
};

float Dot(Vector* a,Vector* b);

Vector* Add(Vector* a,Vector* b);

Vector* Scale(Vector* a,float scale);

bool IsEqual(Vector* a,Vector* b);