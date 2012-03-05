#include <stdio.h>
#include <iostream>
#include "matrix.h"

int main()
{
    Matrix matrix = Matrix(10, 10);
    matrix.fill((real)1000/3);
    matrix(1,1) = 10;
    std::cout << matrix;


    return 0;
}
