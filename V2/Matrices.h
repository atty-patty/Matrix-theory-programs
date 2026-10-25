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

        //destructor
        ~Matrix();
};

Matrix Add(const Matrix& A,const Matrix& B);
Matrix Scale(const Matrix& A,float scale);
