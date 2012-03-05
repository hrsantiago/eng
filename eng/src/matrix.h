#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>

typedef float real;

class Matrix
{
public:
    Matrix(int rows, int columns);
    ~Matrix();

    const int getRows() const { return m_rows; }
    const int getColumns() const { return m_columns; }
    const real getValue(int row, int column) const { return m_matrix[row][column]; }

    void fill(real value);

    // for user usage.
    real& operator()(int row, int column) { return m_matrix[row-1][column-1]; }

private:
    real **m_matrix;
    int m_rows, m_columns;
};

std::ostream& operator<<(std::ostream& out, Matrix& matrix);

#endif
