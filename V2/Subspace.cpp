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