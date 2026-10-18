#include "Lvectors.h"
#include<iostream>
#include<stdlib.h>

Vector::Vector(int n){
    size = n;
    v = (int*)calloc(n,sizeof(int));
}

void Vector::Remove(){
    free(v);
    v = nullptr;
}

void Vector::Print(){
    for(int i = 0;i < size;i++){
        std::cout << " " << v[i];
    }
}