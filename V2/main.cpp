#include<iostream>
#include"Lvectors.h"
#include"Matrices.h"

int main(){
    
    int ColA,RowA;
    std::cout << "enter the rows and columns of A: ";
    std::cin >> RowA >> ColA;

    Matrix A(RowA,ColA);

    std::cout << "Enter A\n";
    A.TakeInput();

    Matrix U = Elimination(A);

    U.PrintAugmented();
    RREF(U);
    U.PrintAugmented();
}