#include <iostream>
#include "matrix.h"

Matrix::Matrix(int rows, int columns)
{
    m_matrix = new real*[rows];
    for(int i = 0; i < rows; ++i)
        m_matrix[i] = new real[columns];

    m_rows = rows;
    m_columns = columns;
}

Matrix::~Matrix()
{
    for(int i = 0; i < m_rows; ++i)
        delete []m_matrix[i];
    delete []m_matrix;
}

void Matrix::fill(real value)
{
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
            m_matrix[i][j] = value;
}

std::ostream& operator<<(std::ostream& out, Matrix& matrix)
{
    for(int i = 0; i < matrix.getRows(); ++i) {
        for(int j = 0; j < matrix.getColumns(); ++j) {
            std::cout.setf(std::ios_base::right, std::ios_base::basefield);
            std::cout.width(9);
            out << matrix.getValue(i, j);
        }
        out << std::endl;
    }
    return out;
}
