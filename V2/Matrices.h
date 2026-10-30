#include"Lvectors.h"

#pragma once
class Matrix{

    public:
        double** a;
        int NumRow;
        int NumCol;

        int rank;

        //constructor
        Matrix(int m,int n);
        //for copying
        Matrix(const Matrix& other);

        void TakeInput();
        void Print();
        void PrintNice();
        void PrintAugmented();

        void SwapRows(int row1,int row2);
        bool SwapWithNonZero(int startRow,int colIndex);
        //destructor
        ~Matrix();
};

bool IsEqual(const Matrix& A,const Matrix& B);

Matrix Add(const Matrix& A,const Matrix& B);
Matrix Scale(const Matrix& A,float scale);
Matrix Transpose(const Matrix& A);

Matrix MatrixProduct(const Matrix& A,const Matrix& B);
Vector MVProduct(const Matrix& A,const Vector& v);

Matrix Elimination(Matrix& A);
void RREF(Matrix& U);