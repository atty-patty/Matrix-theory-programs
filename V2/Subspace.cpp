#include<new>
#include <iostream>
#include "Subspace.h"
#include "Lvectors.h"
#include <stdlib.h>

Subspace::Subspace(int dimension,int VectorDimension){
    spaceDim = dimension;
    vectorDim = VectorDimension;
    Basis = (Vector*)malloc(spaceDim*sizeof(Vector));

    for(int i = 0;i < spaceDim;i++){
        new (&Basis[i]) Vector(vectorDim);
    }
}

Subspace::Subspace(const Subspace& other){
    spaceDim = other.spaceDim;
    vectorDim = other.vectorDim;

    Basis = (Vector*)malloc(spaceDim*sizeof(Vector));
    for(int i = 0;i < spaceDim;i++){
        new (&Basis[i]) Vector(other.Basis[i]);
    }
}

Subspace::~Subspace(){
    for(int i = 0;i < spaceDim;i++){
        Basis[i].~Vector();
    }
    free(Basis);
}

void Subspace::PrintSubspace(){
    for(int i = 1;i <= spaceDim;i++){
        std::cout << "C" << i << "[";
        Basis[i-1].Print();
        std::cout << "]";
        if(i != spaceDim){
            std::cout << " + ";
        }
    }
}

Subspace NullSpace(const Matrix& R){
    //get the locations of all the pivots
    int Pivotcolumn[R.rank];
    //and of free columns too
    int FreeColumn[R.NumCol - R.rank];
    int currentRow = 0;
    int PivotIndex = 0;
    int FreeIndex = 0;
    for(int i = 0;i < R.NumCol;i++){
        //if we have not reached the pivot column of this row yet,clearly is a free column
        //or if we found all the pivots already,then we do this
        if(currentRow >= R.NumRow || R.a[currentRow][i] == 0){
            FreeColumn[FreeIndex] = i;
            FreeIndex++;
        }else{
            Pivotcolumn[PivotIndex] = i;
            PivotIndex++;
            //now we found the pivot of this row we can go down to the next row
            //provided we not already reached the last row;
            currentRow++;
        }
    }


    //since dimension of null space is n-r,and the vectors are in R^n
    Subspace nullSpace(R.NumCol-R.rank,R.NumCol);

    //the method remember is go through all the free columns setting 1,and rest 0
    //and the pivot variables will be it's value negated
    Vector V(R.NumCol);
    //loop for each vector in the basis
    for(int i = 0;i < R.NumCol-R.rank;i++){
        //first go through all the the free columns set the ith one to 1 rest all 0;
        for(int j = 0;j < FreeIndex;j++){
            if(j==i)
                V.v[FreeColumn[j]] = 1;
            else 
               V.v[FreeColumn[j]] = 0;
        }
        //then simply check the ith free column ie the one set to 1
        //and set the pivot columns to have value negative of it
        for(int j = 0;j < PivotIndex;j++){
            V.v[Pivotcolumn[j]] = -R.a[j][FreeColumn[i]];
        }
        nullSpace.Basis[i] = V;
    }
    return nullSpace;
}