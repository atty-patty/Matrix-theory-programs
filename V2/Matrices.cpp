#include "Matrices.h"
#include "Lvectors.h"
#include<stdlib.h>
#include<iostream>

Matrix::Matrix(int m,int n){
    NumRow = m;
    NumCol = n;

    a = (float**)calloc(m,sizeof(float*));
    for(int i = 0;i < m;i++){
        a[i] = (float*)calloc(n,sizeof(float));
    }
}

Matrix::Matrix(const Matrix& other){
    NumRow = other.NumRow;
    NumCol = other.NumCol;

    if(NumCol == 0 || NumRow == 0){
        a = nullptr;
        return;
    }

    a = (float**)calloc(NumRow,sizeof(float*));

    for(int i = 0;i < NumRow;i++){
        a[i] = (float*)calloc(NumCol,sizeof(float));
        for(int j = 0;j < NumCol;j++){
            a[i][j] = other.a[i][j];
        }
    }
}

Matrix::~Matrix(){
    for(int i = 0;i < NumRow;i++){
        free(a[i]);
        a[i] = nullptr;
    }
    free(a);
    a= nullptr;
}

void Matrix::TakeInput(){
    for(int i = 0;i < NumRow;i++){
        for(int j = 0;j < NumCol;j++){
            std::cin >> a[i][j];
        }
    }
}

void Matrix::Print(){
    for(int i = 0;i < NumRow;i++){
        for(int j = 0;j < NumCol;j++){
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix Add(const Matrix& A,const Matrix& B){

    if(A.NumCol == 0 || B.NumCol == 0 || A.NumRow == 0 || B.NumRow == 0){
        std::cout << "ERROR: invalid matrix cannot be added\n";
        return Matrix(0,0);
    }

    if(A.NumCol !=  B.NumCol || A.NumRow != B.NumRow){
        std::cout << "Error:cannot add 2 matrixes of diffrent sizes\n";
        return Matrix(0,0);
    }

    Matrix C = Matrix(A.NumRow,A.NumCol);

    for(int i = 0;i < A.NumRow;i++){
        for(int j = 0;j < A.NumCol;j++){
            C.a[i][j] = A.a[i][j] + B.a[i][j];
        }
    }

    return C;
}

Matrix Scale(const Matrix& A,float scale){

    if(A.NumCol == 0 || A.NumRow == 0){
        std::cout << "ERROR: invalid matrix cannot be scaled\n";
        return Matrix(0,0);
    }

    Matrix C = Matrix(A.NumRow,A.NumCol);

    for(int i = 0;i < A.NumRow;i++){
        for(int j = 0;j < A.NumCol;j++){
            C.a[i][j] = scale* A.a[i][j];
        }
    }

    return C;
}

Matrix MatrixProduct(const Matrix& A,const Matrix& B){
    if(A.NumCol == 0 || B.NumCol == 0){
        std::cout << "ERROR:one of the matrix is undefined\n";
        return Matrix(0,0);
    }

    if(A.NumCol != B.NumRow){
        std::cout << "ERROR: the 2 matrices cannot be multiplied\n";
        return Matrix(0,0);
    }
    float sum = 0;
    Matrix C(A.NumRow,B.NumCol);

    for(int i = 0;i < C.NumRow;i++){
        for(int j = 0;j < C.NumCol;j++){
            sum = 0;
            for(int k = 0;k < A.NumCol;k++){
                sum += A.a[i][k]*B.a[k][j];
            }
            C.a[i][j] = sum;
        }
    }
    return C;
}

Vector MVProduct(const Matrix& A,const Vector& v){
    if(A.NumCol == 0){
        std::cout << "ERROR:invalid matrix in MV product\n";
        return Vector(0);
    }
    if(v.size == 0){
        std::cout << "ERROR:invalid Vector in MV product\n";
    }

    if(A.NumCol != v.size){
        std::cout << "ERROR: cannot do this Matrix Vector product\n";
    }

    Vector b(A.NumRow);
    float Sum = 0;
    for(int i = 0;i < b.size;i++){
        Sum = 0;
        for(int j = 0;j < v.size;j++){
            Sum += v.v[j]*A.a[i][j];
        }
        b.v[i] = Sum;
    }

    return b;
}