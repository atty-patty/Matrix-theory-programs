#include<iostream>
#include"Lvectors.h"

int main(){
    
    int dimA,dimB;
    std::cout << "enter the dimension of first vector\n";
    std::cin >> dimA;

    Vector* a = new Vector(dimA);

    std::cout << "enter the dimension of second vector\n";
    std::cin >> dimB;

    Vector* b = new Vector(dimB);

    std::cout << "enter the first vector(values seprated by spaces on one line)\n";
    for(int i = 0;i < dimA;i++){
        std::cin >> a->v[i];
    }
    std::cout << "enter the second vector(values seprated by spaces on one line)\n";
    for(int i = 0;i < dimB;i++){
        std::cin >> b->v[i];
    }

    Vector* c = Add(Scale(a,2),Scale(b,-1));
    Vector* d = Add(a,b);

    if(c == nullptr || d == nullptr){
        return 1;
    }
    if(IsEqual(c,d)){
        std::cout << "2a-b is equal to a+b\n";
    }else{
        std::cout << "it ain't chat simple as that\n";
    }

    a->Remove();
    b->Remove();
    c->Remove();
    d->Remove();
}