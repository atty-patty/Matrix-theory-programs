#include<iostream>
#include"Lvectors.h"

int main(){
    Vector* A = new Vector(4);

    A->v[1] = 3;

    A->Print();

    A->Remove();
}