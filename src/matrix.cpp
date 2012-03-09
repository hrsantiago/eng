#include <iostream>
#include "matrix.h"

Matrix::Matrix(int rows, int columns)
{
    if(rows == 0 || columns == 0) {
        std::cout << "Both Rows and Columns of a matrix must be > 0.";
        return;
    }

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

bool Matrix::isRowValid(int row)
{
    if(row < 0 || row >= m_rows) {
        std::cout << "Row " << row+1 << " is invalid." << std::endl;
        return false;
    }
    return true;
}

bool Matrix::isColumnValid(int column)
{
    if(column < 0 || column >= m_columns) {
        std::cout << "Column " << column+1 << " is invalid." << std::endl;
        return false;
    }
    return true;
}

Matrix *Matrix::createCopy()
{
    Matrix *matrix = new Matrix(m_rows, m_columns);
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
            matrix->setValue(i, j, m_matrix[i][j]);
    return matrix;
}

void Matrix::fill(real value)
{
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
            m_matrix[i][j] = value;
}

void Matrix::rowMultiply(int row, real scalar)
{
    if(!isRowValid(row))
        return;
    if(scalar == 0) {
        std::cout << "Scalar must not be zero." << std::endl;
        return;
    }
    for(int j = 0; j < m_columns; ++j)
        m_matrix[row][j] *= scalar;
}

void Matrix::rowSwap(int row1, int row2)
{
    if(row1 == row2) {
        std::cout << "Row1 and Row2 must not be equal." << std::endl;
        return;
    }
    if(!isRowValid(row1) || !isRowValid(row2))
        return;

    real temp;
    for(int j = 0; j < m_columns; ++j) {
        temp = m_matrix[row1][j];
        m_matrix[row1][j] = m_matrix[row2][j];
        m_matrix[row2][j] = temp;
    }
}

void Matrix::rowAdd(int row1, int row2, real scalar)
{
    if(row1 == row2) {
        std::cout << "Row1 and Row2 must not be equal." << std::endl;
        return;
    }
    if(scalar == 0 || !isRowValid(row1) || !isRowValid(row2))
        return;

    for(int j = 0; j < m_columns; ++j)
        m_matrix[row1][j] += m_matrix[row2][j] * scalar;
}

void Matrix::upperTriangularMatrix()
{
    for(int j = 0; j < m_columns-1; ++j) {
        int i = j;
        for(; i < m_rows; ++i) {
            if(m_matrix[i][j] != 0) {
                if(i != j)
                    rowSwap(j, i);
                break;
            }
        }

        if(i == m_rows) // this column is filled with 0
            continue;

        for(i = j+1; i < m_rows; ++i)
            rowAdd(i, j, -(m_matrix[i][j] / m_matrix[j][j]));
    }
}

real Matrix::getDeterminant()
{
    if(m_rows != m_columns) {
        std::cout << "There is no determinant in this matrix. It must be square." << std::endl;
        return 0;
    }

    Matrix *matrix = createCopy();
    matrix->upperTriangularMatrix();

    int determinant = 1;
    for(int i = 0; i < m_rows; ++i)
        determinant *= matrix->getValue(i, i);

    delete matrix;
    return determinant;
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
