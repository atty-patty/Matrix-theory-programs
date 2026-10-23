#include "Matrices.h"
#include<stdlib.h>

Matrix::Matrix(int m,int n){
    NumRow = m;
    NumCol = n;
    a = (float**)calloc(m,sizeof(float*));
    for(int i = 0;i < m;i++){
        a[i] = (float*)calloc(n,sizeof(float));
    }
}

void Matrix::Remove(){
    for(int i = 0;i < NumRow;i++){
        free(a[i]);
        a[i]= nullptr;
    }
    free(a);
    a = nullptr;
}