#include<iostream>
#include"Lvectors.h"

int main(){
    Vector* A = new Vector(4);
    Vector* B = new Vector(4);

    A->v[1] = 3;
    A->v[3] = -1.1;

    B->v[1] = -1.3;

    std::cout << Dot(A,B);

    A->Remove();
}