#include <stdio.h>
#include <iostream>
#include "matrix.h"

int main()
{
//    Matrix matrix = Matrix(2, 2);
//    matrix(1,1) = 1;
//    matrix(1,2) = 2;
//    matrix(2,1) = 3;
//    matrix(2,2) = 4;

    Matrix matrix = Matrix(3, 3);
    matrix(1,1) = 2;
    matrix(1,2) = 3;
    matrix(1,3) = 5;
    matrix(2,1) = 1;
    matrix(2,2) = 7;
    matrix(2,3) = 4;
    matrix(3,1) = 6;
    matrix(3,2) = 9;
    matrix(3,3) = 8;
    //matrix.upperTriangularMatrix();
    std::cout << matrix << matrix.getDeterminant() << std::endl;
    return 0;
}
