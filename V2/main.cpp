#include<iostream>
#include"Lvectors.h"
#include"Matrices.h"
#include"Subspace.h"

int main(){
    
    int ColA,RowA;
    std::cout << "enter the rows and columns of A: ";
    std::cin >> RowA >> ColA;

    Subspace CA = Subspace(ColA,RowA);
    Vector V(RowA);
    std::cout << "Enter the vectors that are basis of subspace:\n";
    for(int i = 0;i < ColA;i++){
        V.takeInput();
        CA.Basis[i] = V;
    }
    CA.PrintSubspace();
    
}