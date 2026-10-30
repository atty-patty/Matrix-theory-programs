#include "Lvectors.h"
#include<iostream>
#include<stdlib.h>

Vector::Vector(int n){
    size = n;

    if(n == 0){
        v = nullptr;
        return;
    }
    v = (double*)calloc(n,sizeof(double));
}

Vector::Vector(const Vector& other){
    size = other.size;

    if(size == 0){
        v = nullptr;
        return;
    }

    v = (double*)calloc(size,sizeof(double));
    for(int i = 0;i < size;i++){
        v[i] = other.v[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    double* newData = nullptr;

    if (other.size > 0) {
        newData = (double*)calloc(other.size,sizeof(double));

        for (int i = 0; i < other.size; i++) {
            newData[i] = other.v[i];
        }
    }

    free(v);

    v = newData;
    size = other.size;

    return *this;
}

void Vector::takeInput(){
    for(int i = 0;i < size;i++){
        std::cin >> v[i];
    }
}

Vector::~Vector(){
    free(v);
    v = nullptr;
}

void Vector::Print(){

    std::cout << "[";
    for(int i = 0;i < size;i++){
        //i don't like seeing -0,so this a way to remove it  ;
        std::cout << v[i]+0.0;
        if(i != size - 1){
            std::cout << " ";
        }
    }
    std::cout << "]";
}

float Dot(const Vector& a,const Vector& b){

    if(a.size == 0 || b.size == 0){
        std::cout << "ERROR: cannot take dot product of Invalid vectors\n";
        return 0;
    }
    //check if have vectors of diffrent sizes
    if(a.size !=  b.size){
        std::cout << "ERROR: cannot take dot product of vector of diffrent sizes\n";
        return 0;
    }

    float innerP = 0;
    //use dot product formula it not that deep guys
    for(int i = 0;i < a.size;i++){
        innerP += a.v[i] * b.v[i];
    }

    return innerP;
}

Vector Add(const Vector& a,const Vector& b){
    if(a.size == 0 || b.size == 0){
        std::cout << "ERROR:invalid vector as input\n";
        return Vector(0);
    }

    if(a.size != b.size){
        std::cout << "ERROR: Vectors are of diffrent Dimensions\n";
        return Vector(0);
    }
    //we do element wise addition(duh)
    Vector c(a.size);

    for(int i = 0;i < a.size;i++){
        c.v[i] = a.v[i] + b.v[i];
    }
    return c;
}

Vector Scale(const Vector& a,float scale){

    if(a.size == 0){
        std::cout << "ERROR: invalid vector as input\n";
        return Vector(0);
    }
    Vector c(a.size);

    //simply scale every element by scale
    for(int i = 0;i < a.size;i++){
        c.v[i] = scale * a.v[i];
    }

    return c;
}

bool IsEqual(const Vector& a,const Vector& b){
    if(a.size != b.size){
        std::cout << "Error: cannot check for equality between vector of diffrent dimension\n";
        return false;
    }
    if(a.size == 0 || b.size == 0){
        std::cout << "ERROR: cannot check for equality as Invalid vector as inputs\n";
        return false;
    }

    //check elementwise if any diffrence,if show return false,else if all elemnts same return true
    for(int i = 0;i < a.size;i++){
        if(a.v[i] != b.v[i])
            return false;
    }
    return true;
}