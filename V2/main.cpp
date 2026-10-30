#include<iostream>
#include"Lvectors.h"
#include"Matrices.h"
#include"Subspace.h"

int main(){
    
    int ColA,RowA;
    std::cout << "enter the rows and columns of A: ";
    std::cin >> RowA >> ColA;

    Matrix A(RowA,ColA);
    std::cout <<  "enter A:\n";
    A.TakeInput();

    Matrix R = Elimination(A);
    R.PrintNice();
    RREF(R);
    R.PrintNice();
    Subspace nullSpace = NullSpace(R);

    nullSpace.PrintSubspace();
}