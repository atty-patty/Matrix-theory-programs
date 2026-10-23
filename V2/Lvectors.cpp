#include "Lvectors.h"
#include<iostream>
#include<stdlib.h>

Vector::Vector(int n){
    size = n;
    v = (float*)calloc(n,sizeof(float));
}

void Vector::takeInput(){
    for(int i = 0;i < size;i++){
        std::cin >> v[i];
    }
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
    //use dot product formula it not that deep guys
    for(int i = 0;i < a->size;i++){
        innerP += a->v[i] * b->v[i];
    }

    return innerP;
}

Vector* Add(Vector* a,Vector* b){
    if(a->size != b->size){
        std::cout << "Error: Vectors are of diffrent Dimensions\n";
        return nullptr;
    }
    //we do element wise addition
    Vector* c = new Vector(a->size);
    for(int i = 0;i < a->size;i++){
        c->v[i] = a->v[i] + b->v[i];
    }
    return c;
}

Vector* Scale(Vector* a,float scale){
    Vector* c = new Vector(a->size);
    //simply scale every element by scale
    for(int i = 0;i < a->size;i++){
        c->v[i] = scale * a->v[i];
    }

    return c;
}

bool IsEqual(Vector* a,Vector* b){
    if(a->size != b->size){
        std::cout << "Error: cannot check for equality between vector of diffrent dimension\n";
        return false;
    }

    //check elementwise if any diffrence,if show return false,else if all elemnts same return true
    for(int i = 0;i < a->size;i++){
        if( a->v[i] != b->v[i])
            return false;
    }
    return true;
}