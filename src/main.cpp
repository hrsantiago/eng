#include <stdio.h>
#include <iostream>
#include "matrix.h"

int main()
{
    Matrix matrix(3, 3);
    matrix(1,1) = 1;
    matrix(1,2) = 1;
    matrix(1,3) = 1;
    matrix(2,1) = 1;
    matrix(2,2) = 2;
    matrix(2,3) = 2;
    matrix(3,1) = 1;
    matrix(3,2) = 3;
    matrix(3,3) = 2;

    std::cout << matrix.getInverse() << matrix.getInverse() * matrix << std::endl;

    return 0;
}
