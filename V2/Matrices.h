#pragma once
class Matrix{

    public:
        float** a;
        int NumRow;
        int NumCol;

        Matrix(int m,int n);

        void Remove();
};
