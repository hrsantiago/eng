#include <iostream>
#include "matrix.h"

Matrix::Matrix(int rows, int columns)
{
    if(rows > 0 && columns > 0) {
        m_values = new real*[rows];
        for(int i = 0; i < rows; ++i)
            m_values[i] = new real[columns];
    }

    m_rows = rows;
    m_columns = columns;
}

Matrix::Matrix(const Matrix& matrix)
{
    m_rows = matrix.getRows();
    m_columns = matrix.getColumns();

    if(m_rows > 0 && m_columns > 0) {
        m_values = new real*[m_rows];
        for(int i = 0; i < m_rows; ++i)
            m_values[i] = new real[m_columns];

        for(int i = 0; i < m_rows; ++i)
            for(int j = 0; j < m_columns; ++j)
                setValue(i, j, matrix.getValue(i, j));
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i < m_rows; ++i)
        delete []m_values[i];
    delete []m_values;
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

Matrix Matrix::createCopy()
{
    Matrix matrix(m_rows, m_columns);
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
            matrix.setValue(i, j, m_values[i][j]);
    return matrix;
}

Matrix Matrix::createIdentity(int size)
{
    Matrix matrix(size, size);
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            matrix.setValue(i, j, i==j ? 1 : 0);
    return matrix;
}

void Matrix::fill(real value)
{
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
            m_values[i][j] = value;
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
        m_values[row][j] *= scalar;
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
        temp = m_values[row1][j];
        m_values[row1][j] = m_values[row2][j];
        m_values[row2][j] = temp;
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
        m_values[row1][j] += m_values[row2][j] * scalar;
}

void Matrix::upperTriangularMatrix()
{
    for(int j = 0; j < m_columns-1; ++j) {
        int i = j;
        for(; i < m_rows; ++i) {
            if(m_values[i][j] != 0) {
                if(i != j)
                    rowSwap(j, i);
                break;
            }
        }

        if(i == m_rows) // this column is filled with 0
            continue;

        for(i = j+1; i < m_rows; ++i) {
            real coeficient = -(m_values[i][j] / m_values[j][j]);
            if(coeficient != 0)
                rowAdd(i, j, coeficient);
        }
    }
}

real Matrix::getDeterminant()
{
    if(m_rows != m_columns) {
        std::cout << "There is no determinant in this matrix. It must be square." << std::endl;
        return 0;
    }

    Matrix matrix = createCopy();
    matrix.upperTriangularMatrix();

    int determinant = 1;
    for(int i = 0; i < m_rows; ++i)
        determinant *= matrix.getValue(i, i);

    return determinant;
}

Matrix Matrix::getInverse()
{
    if(m_rows != m_columns) {
        std::cout << "Only square matrixes can be inversed" << std::endl;
        return Matrix();
    }

    Matrix matrix = createCopy();
    Matrix inverse = Matrix::createIdentity(m_rows);

    for(int j = 0; j < matrix.getColumns()-1; ++j) {
        int i = j;
        for(; i < matrix.getRows(); ++i) {
            if(matrix.getValue(i, j) != 0) {
                if(i != j) {
                    matrix.rowSwap(j, i);
                    inverse.rowSwap(j, i);
                }
                break;
            }
        }

        if(i == matrix.getRows()) // this column is filled with 0
            continue;

        if(matrix.getValue(j, j) == 0) {
            std::cout << "This matrix is not invertible." << std::endl;
            return Matrix();
        }
        //real coeficient = 1.0 / matrix.getValue(j, j);
        //matrix.rowMultiply(j, coeficient);
        //inverse.rowMultiply(j, coeficient);

        for(i = j+1; i < matrix.getRows(); ++i) {
            real coeficient = -(matrix.getValue(i, j) / matrix.getValue(j, j));
            if(coeficient != 0) {
                matrix.rowAdd(i, j, coeficient);
                inverse.rowAdd(i, j, coeficient);
            }
        }
    }

    for(int j = matrix.getColumns()-1; j >= 0; --j) {
        int i = j;
        for(; i >= 0; --i) {
            if(matrix.getValue(i, j) != 0) {
                if(i != j) {
                    matrix.rowSwap(j, i);
                    inverse.rowSwap(j, i);
                }
                break;
            }
        }

        if(i < 0) // this column is filled with 0
            continue;

        if(matrix.getValue(j, j) == 0) {
            std::cout << "This matrix is not invertible." << std::endl;
            return Matrix();
        }
        real coeficient = 1.0 / matrix.getValue(j, j);
        matrix.rowMultiply(j, coeficient);
        inverse.rowMultiply(j, coeficient);

        for(i = j-1; i >= 0; --i) {
            real coeficient = -(matrix.getValue(i, j) / matrix.getValue(j, j));
            if(coeficient != 0) {
                matrix.rowAdd(i, j, coeficient);
                inverse.rowAdd(i, j, coeficient);
            }
        }
    }
    return inverse;
}

Matrix Matrix::multiply(const Matrix& matrix)
{
    if(m_columns != matrix.getRows()) {
        std::cout << "These matrixes can't be multiplied. Columns != Rows" << std::endl;
        return Matrix();
    }

    Matrix result(m_rows, matrix.getColumns());
    for(int ri = 0; ri < m_rows; ++ri) {
        for(int rj = 0; rj < matrix.getColumns(); ++rj) {
            int coeficient = 0;
            for(int j = 0; j < m_columns; ++j) // or matrix->getRows() also valid.
                coeficient += getValue(ri, j) * matrix.getValue(j, rj);
            result.setValue(ri, rj, coeficient);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
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
