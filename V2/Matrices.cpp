#include "Matrices.h"
#include "Lvectors.h"
#include<stdlib.h>
#include<iostream>

//CONSTRUCTOER DESTRUCTOR
Matrix::Matrix(int m,int n){
    NumRow = m;
    NumCol = n;

    a = (double**)calloc(m,sizeof(double*));
    for(int i = 0;i < m;i++){
        a[i] = (double*)calloc(n,sizeof(double));
    }
}

Matrix::Matrix(const Matrix& other){
    NumRow = other.NumRow;
    NumCol = other.NumCol;

    if(NumCol == 0 || NumRow == 0){
        a = nullptr;
        return;
    }

    a = (double**)calloc(NumRow,sizeof(double*));

    for(int i = 0;i < NumRow;i++){
        a[i] = (double*)calloc(NumCol,sizeof(double));
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

//INPUT OUTPUT
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

    std::cout << "\n";
    for(int i = 0;i < NumRow;i++){
        std::cout << "|";
        for(int j = 0;j < NumCol;j++){
            printf("%3g ",a[i][j]);
        }
        std::cout << "|";
        std::cout << "\n";
    }
}

void Matrix::PrintAugmented(){
    std::cout << "\n";
    for(int i = 0;i < NumRow;i++){
        std::cout << "|";
        for(int j = 0;j < NumCol;j++){
            if(j == NumCol -1)
                printf("|");
            printf("%3g ",a[i][j]);
        }
        std::cout << "|";
        std::cout << "\n";
    }
}

//SWAPPING ROW STUFF
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
        if(a[i-1][colIndex-1] > 0.001f || a[i-1][colIndex-1] < -0.001f){
            CanSwap = true;
            SwapRows(startRow,i);
            break;
        }
    }
    return CanSwap;
}

//Equality checking
bool IsEqual(const Matrix& A,const Matrix& B){
    if(A.NumCol != B.NumCol || B.NumRow != A.NumRow){
        printf("ERROR: Cannot check for equality of diffrent dimension matrix\n");
        return false;
    }
    for(int i = 0 ;i < A.NumRow;i++){
        for(int j = 0;j < A.NumCol;j++){
            if(A.a[i][j] != B.a[i][j]){
                return false;
            }
        }
    }
    return true;
}


//BASIC OPERATIONS
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

Matrix Transpose(const Matrix& A){
    Matrix At(A.NumCol,A.NumRow);

    for(int i = 0;i < A.NumRow;i++){
        for(int j = 0;j < A.NumCol;j++){
            At.a[j][i] = A.a[i][j];
        }
    }
    return At;
}


//Product of Matrices and vectore
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

//ELIMINATION STUFF
Matrix Elimination(Matrix& A){
    Matrix U = A;
    //gonna store the coeff for row transformations
    double lambda;
    //gonna store the current pivot column and row;
    int PivotColumn = 1;
    int PivotRow = 1;

    //gonna store the rank of matrix too using this function
    int rank = 0;

    while (PivotColumn <= U.NumCol && PivotRow < U.NumRow){
        //if pivot entry is close to 0,we gotta trySwapping it
        if(U.a[PivotRow-1][PivotColumn-1] < 0.001f && U.a[PivotRow-1][PivotColumn-1] > -0.001f){
            //if we can't swap it,so we know this not a pivot column so go next one and try again
            if(!U.SwapWithNonZero(PivotRow,PivotColumn)){
                PivotColumn++;
            }
            continue;
        }
        //if have valid pivot then go through all rows below pivot
        for(int i = PivotRow+1;i <= U.NumRow;i++){
            //find the value of lambda
            lambda = (U.a[i-1][PivotColumn-1])/(U.a[PivotRow-1][PivotColumn-1]);
            //do Ri = Ri - lambda*Rp
            U.a[i-1][PivotColumn-1] = 0;
            for(int j = PivotColumn+1;j <= U.NumCol;j++){
                U.a[i-1][j-1] -= lambda*U.a[PivotRow-1][j-1];
                if(U.a[i-1][j-1] < 1e-10 && U.a[i-1][j-1] > -1e-10){
                    U.a[i-1][j-1] = 0;
                }
            }
        }
        //the next pivot at closest is 1 diagnol below,also incrememnt rank by 1
        rank++;
        PivotColumn++;
        PivotRow++;
    }
    //something extra we need to add because we skip the loop when we reach last row
    if(PivotRow == U.NumRow){
        for(int i = PivotColumn - 1;i < U.NumCol;i++){
            if (U.a[PivotRow-1][i] > 0.001f || U.a[PivotRow-1][i] < -0.001f){
                rank++;
                break;
            }
        }
    }
    A.rank = rank;
    U.rank = rank;
    return U;
}

void RREF(Matrix& U){

    int PivotIndex[U.rank] = {0};
    for(int i = 0;i < U.rank;i++){
        while (U.a[i][PivotIndex[i]] == 0)
        {
            PivotIndex[i]++;
        }
        if(i != U.rank-1)
            PivotIndex[i+1] = PivotIndex[i]+1;
    }
    //go through the list backward and remove the componenet above the pivots
    for(int i = U.rank-1;i >= 0;i--){
        //first divide by value if pivot column to get 1 there
        for(int j = PivotIndex[i]+1;j < U.NumCol;j++){
            U.a[i][j] /= U.a[i][PivotIndex[i]];
        }
        U.a[i][PivotIndex[i]] = 1;

        //then we need to remove all the element above it,ig
        for(int j = 0;j < i;j++){
            double lambda = U.a[j][PivotIndex[i]];
            //do  Ri = Ri - Rp
            U.a[j][PivotIndex[i]] = 0;
            for(int k = PivotIndex[i]+1;k < U.NumCol;k++){
                U.a[j][k] -= lambda*U.a[i][k];
                if(U.a[j][k] < 1e-10 && U.a[j][k] > -1e-10){
                    U.a[j][k] = 0;
                }
            }
        }
    }

}