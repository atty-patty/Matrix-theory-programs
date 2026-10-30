#include<iostream>
#include"Lvectors.h"
#include"Matrices.h"
#include"Subspace.h"

int main(){
    
    int ColA,RowA;
    std::cout << "enter the number of equations and the number of variables: ";
    std::cin >> RowA >> ColA;

    Matrix Ab(RowA,ColA+1);
    std::cout <<  "coefficients of variables in the equation with right hand side:\n";
    Ab.TakeInput();

    Matrix Rb = Elimination(Ab);
    int PivotIndex[Rb.rank] = {0};
    for(int i = 0;i < Rb.rank;i++){
        while (Rb.a[i][PivotIndex[i]] == 0)
        {
            PivotIndex[i]++;
        }
        if(i != Rb.rank-1)
            PivotIndex[i+1] = PivotIndex[i]+1;
    }
    //if the last pivot is in the rhs column we know we got no solution
    if(PivotIndex[Rb.rank -1] == Rb.NumCol-1){
        std::cout << "No exact solution exists\n";
        Matrix A = RemoveRHS(Ab);
        Matrix ATA = MatrixProduct(Transpose(A),A);
        Vector b = GetRHS(Ab);
        Vector ATb = MVProduct(Transpose(A),b);

        Matrix ATAb = JoinRHS(ATA,ATb);
        Rb = Elimination(ATAb);
    }
    RREF(Rb);
    Vector Xp = GetParticularSolution(Rb);
    Matrix R = RemoveRHS(Rb);
    Subspace nullA = NullSpace(R);

    //printing out the solution
    Xp.Print();
    if(nullA.spaceDim != 0)
        std::cout << " + ";
    nullA.PrintSubspace();
    
}