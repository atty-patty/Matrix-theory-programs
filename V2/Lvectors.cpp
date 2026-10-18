#include "Lvectors.h"
#include<iostream>
#include<stdlib.h>

Vector::Vector(int n){
    size = n;
    v = (float*)calloc(n,sizeof(float));
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

float Dot(Vector* a,Vector* b){
    if(a->size !=  b->size){
        std::cout << "Error: Vectors of diffrent dimensions\n";
        return 0;
    }
    float innerP = 0;
    for(int i = 0;i < a->size;i++){
        innerP += a->v[i] * b->v[i];
    }

    return innerP;
}