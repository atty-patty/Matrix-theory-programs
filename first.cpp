#include <bits/stdc++.h>
using namespace std;

//does one pass of elimination
//the step variable to control the pivot variable and the operations to be done
double* elimination(double coefficients[],int n,int step){
    //when we reduce it to one variable we are done
    if(n == step - 2){
        return coefficients;
    }
    //the pivots are the diagnol variable whose index = step*no of column + step
    double pivot = coefficients[step*(n+2)];

    for(int i = step+1;i < n;i++){
        //find the value of lambda that makes pivot variable 0
        //the variable we care about will be directly below pivote so increase row number by adding (n+1)
        double lambda = coefficients[(n+1)*i +step]/pivot;
        coefficients[(n+1)*i + step] = 0;

        //applying the row trandfromation Rj -> Rj - lamba*R1
        for(int j = step+1;j < n + 1;j++){
            coefficients[(n + 1)*i + j] -= lambda*coefficients[(n+1)*step + j];
        }
        cout << endl;

    }

    return elimination(coefficients,n,step+1);
}

double* backward_sub(double coefficients[],double variables[],int n,int step){
    //now this also will be a recursive call back
    //the step variable will hold the current row index being worked on
    if(step == -1){
        return variables;
    }
    double rhs = coefficients[step*(n+1)+n];
    //start the fpr loop from just before rhs index in the row
    //and end it till just beofre pivot variable
    for(int i = step*(n+1) + n-1;i > step*(n+2);i--){
        //don't ask, i have no idea either
        rhs -= coefficients[i]*variables[i- step*(n+1)];
    }
    variables[step] = rhs/coefficients[step*(n+2)];
    return backward_sub(coefficients,variables,n,step-1);
}

int main() {

    int VarNum;
    cout << "how many variables do you have? ";
    cin >> VarNum;
    double coefficients[VarNum * (VarNum +1)];
    double variables[VarNum];

    for(int i =0;i < VarNum;i++){
        variables[i] = 0;
        printf("enter coefficients of equation %d: ",i+1);

        for(int j = 0;j <= VarNum;j++){
            cin >> coefficients[i*(VarNum+1) + j];
        }
    }

    double* rowEcholonPtr;
    rowEcholonPtr = elimination(coefficients,VarNum,0);

    /*for(int i = 0;i < VarNum;i++){
        for(int j = 0;j <= VarNum;j++){
            cout << rowEcholonPtr[i*(VarNum+1) + j] << " ";
        }
        cout << "\n";
    }*/

    double* finalValues;
    finalValues = backward_sub(rowEcholonPtr,variables,VarNum,VarNum-1);


    cout <<"the values of the variables are:";
    for(int i = 0;i < VarNum;i++){
        cout << finalValues[i] << " ";
    }
    
}