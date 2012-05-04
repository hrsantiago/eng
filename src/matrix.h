#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>

typedef float real;

class Matrix
{
public:
    Matrix(int rows = 0, int columns = 0);
    Matrix(const Matrix& matrix);
    ~Matrix();

    bool isRowValid(int row);
    bool isColumnValid(int column);

    static Matrix createIdentity(int size);
    Matrix createCopy();
    void fill(real value);

    void rowMultiply(int row, real scalar);
    void rowSwap(int row1, int row2);
    void rowAdd(int row1, int row2, real scalar = 1);

    void setValue(int row, int column, real value) { m_values[row][column] = value; }

    const int getRows() const { return m_rows; }
    const int getColumns() const { return m_columns; }
    const real getValue(int row, int column) const { return m_values[row][column]; }

    void upperTriangularMatrix();
    real getDeterminant();
    Matrix getInverse();

    Matrix multiply(const Matrix& matrix);

    // for user usage.
    Matrix operator*(const Matrix& matrix) { return multiply(matrix); }
    real& operator()(int row, int column) { return m_values[row-1][column-1]; }

private:
    real **m_values;
    int m_rows, m_columns;
};


std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

#endif
