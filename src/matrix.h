#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>

typedef float real;

class Matrix
{
public:
    Matrix(int rows, int columns);
    ~Matrix();

    bool isRowValid(int row);
    bool isColumnValid(int column);

    Matrix *createCopy();
    void fill(real value);

    void rowMultiply(int row, real scalar);
    void rowSwap(int row1, int row2);
    void rowAdd(int row1, int row2, real scalar = 1);

    void setValue(int row, int column, real value) { m_matrix[row][column] = value; }

    const int getRows() const { return m_rows; }
    const int getColumns() const { return m_columns; }
    const real getValue(int row, int column) const { return m_matrix[row][column]; }

    void upperTriangularMatrix();
    real getDeterminant();

    // for user usage.
    real& operator()(int row, int column) { return m_matrix[row-1][column-1]; }

private:
    real **m_matrix;
    int m_rows, m_columns;
};

std::ostream& operator<<(std::ostream& out, Matrix& matrix);

#endif
