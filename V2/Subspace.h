#pragma once
#include"Lvectors.h"
#include"Matrices.h"

class Subspace{
    public:
        int spaceDim;
        int vectorDim;
        Vector* Basis;

        Subspace(int dimension,int VectorDimension);
        Subspace(const Subspace& other);
        ~Subspace();

        void PrintSubspace();
};

Subspace NullSpace(const Matrix& R);