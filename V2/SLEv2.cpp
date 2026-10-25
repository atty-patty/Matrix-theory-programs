#include<iostream>
#include"Lvectors.h"
#include"Matrices.h"

int main(){
    
    int ColA,RowA,dim;
    std::cout << "enter the rows and columns of A: ";
    std::cin >> RowA >> ColA;
    std::cout << "enter the size of vector x: ";
    std::cin >> dim;

    Matrix A(RowA,ColA);
    Vector v(dim);

    std::cout << "Enter the Matrix\n";
    A.TakeInput();
    std::cout << "Enter the Vector\n";
    v.takeInput();
    Vector b = MVProduct(A,v);

    b.Print();
}