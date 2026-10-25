#include<iostream>
#include"Lvectors.h"

int main(){
    
    int dimA,dimB;
    std::cout << "enter the dimension of first vector\n";
    std::cin >> dimA;

    std::cout << "enter the dimension of second vector\n";
    std::cin >> dimB;

    Vector a(dimA);
    Vector b(dimB);

    std::cout << "enter the first vector(values seprated by spaces on one line)\n";
    a.takeInput();
    std::cout << "enter the second vector(values seprated by spaces on one line)\n";
    b.takeInput();

    Vector d = Add(a,b);
    Vector c = Add(d,a);

    d.Print();
}