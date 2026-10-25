#include"Lvectors.h"

#pragma once
class Matrix{

    public:
        float** a;
        int NumRow;
        int NumCol;

        //constructor
        Matrix(int m,int n);
        //for copying
        Matrix(const Matrix& other);

        void TakeInput();
        void Print();

        //destructor
        ~Matrix();
};

Matrix Add(const Matrix& A,const Matrix& B);
Matrix Scale(const Matrix& A,float scale);

Matrix MatrixProduct(const Matrix& A,const Matrix& B);
Vector MVProduct(const Matrix& A,const Vector& v);
