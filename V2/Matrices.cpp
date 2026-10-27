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

void Matrix::PrintNice(){

    for(int i = 0;i < NumRow;i++){
        std::cout << "|";
        for(int j = 0;j < NumCol;j++){
            printf("%3g ",a[i][j]);
        }
        std::cout << "|";
        std::cout << "\n";
    }
}

void Matrix::SwapRows(int row1,int row2){
    if(row1 > NumRow || row2 > NumRow){
        std::cout << "ERROR: invalid rows entered to be swapped\n";
        return;
    }

    if(row1 == row2){
        std::cout << "WARNING:trying to swap a row with itself\n";
    }
    //done so we can have the parameter be numbered like  we do in matrices
    //starting from one,but since array need starting from 0,we subtract 1;
    row1--;
    row2--;
    float temp;
    for(int i = 0;i < NumCol;i++){
        temp = a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}

bool Matrix::SwapWithNonZero(int startRow,int colIndex){
    bool CanSwap = false;
    for(int i = startRow+1;i <= NumRow;i++){
        if(a[i-1][colIndex-1] != 0){
            CanSwap = true;
            SwapRows(startRow,i);
            break;
        }
    }
    return CanSwap;
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

Matrix Transpose(const Matrix& A){
    Matrix At(A.NumCol,A.NumRow);

    for(int i = 0;i < A.NumRow;i++){
        for(int j = 0;j < A.NumCol;j++){
            At.a[j][i] = A.a[i][j];
        }
    }
    return At;
}

Matrix Elimination(Matrix& A){
    Matrix U = A;
    //gonna store the coeff for row transformations
    int lambda;
    //gonna store the current pivot column and row;
    int PivotColumn = 1;
    int PivotRow = 1;
    while (PivotColumn <= U.NumCol && PivotRow < U.NumRow){
        //if pivot entry is close to 0,we gotta trySwapping it
        if(U.a[PivotRow-1][PivotColumn-1] < 0.001f && U.a[PivotRow-1][PivotColumn-1] > -0.001f){
            //if we can't swap it,append PivotColumn by 1 and try again
            if(!U.SwapWithNonZero(PivotRow,PivotColumn)){
                PivotColumn++;
            }
            continue;
        }
        for(int i = PivotRow+1;i <= U.NumRow;i++){
            lambda = (U.a[i-1][PivotColumn-1])/(U.a[PivotRow-1][PivotColumn-1]);
            U.a[i-1][PivotColumn-1] = 0;
            for(int j = PivotColumn+1;j <= U.NumCol;j++){
                U.a[i-1][j-1] -= lambda*U.a[PivotRow-1][j-1];
            }
        }
        PivotColumn++;
        PivotRow++;
    }

    return U;
}