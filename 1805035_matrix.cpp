#include "1805035_matrix.h"

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0.0)) {}

Matrix::Matrix(int rows, int cols, const std::vector<std::vector<double>>& data) : rows(rows), cols(cols), matrix(data) {
    if (data.size() != rows || (!data.empty() && data[0].size() != cols)) {
        throw std::invalid_argument("Provided data doesn't match specified dimensions");
    }
}

int Matrix::numRows() const {
    return rows;
}

int Matrix::numCols() const {
    return cols;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[i][j];
}

void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Index out of bounds");
    }
    matrix[i][j] = value;
}

void Matrix::printMatrix() const {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::cout << "| ";
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}

void Matrix::printSubmatrix(int subRows, int subCols) const {
    std::cout << "Submatrix:" << std::endl;
    for (int i = 0; i < subRows && i < rows; ++i) {
        std::cout << "| ";
        for (int j = 0; j < subCols && j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

// Implementations of other operators and member functions go here...

// Example: Implementing operator- as a non-member function
Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if (m1.numRows() != m2.numRows() || m1.numCols() != m2.numCols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }

    Matrix result(m1.numRows(), m1.numCols());
    for (int i = 0; i < m1.numRows(); ++i) {
        for (int j = 0; j < m1.numCols(); ++j) {
            result.set(i, j, m1.get(i, j) - m2.get(i, j));
        }
    }
    return result;
}

// Implementations of other operators and member functions go here...
// ... (previous code)

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Number of columns in the first matrix must match the number of rows in the second matrix for multiplication");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

// Implementations of other operators and member functions go here...

// Non-member function for scalar multiplication
Matrix operator*(double scalar, const Matrix& matrix) {
    Matrix result(matrix.numRows(), matrix.numCols());
    for (int i = 0; i < matrix.numRows(); ++i) {
        for (int j = 0; j < matrix.numCols(); ++j) {
            result.set(i, j, scalar * matrix.get(i, j));
        }
    }
    return result;
}

// Non-member function for scalar multiplication (scalar on the right-hand side)
Matrix operator*(const Matrix& matrix, double scalar) {
    return scalar * matrix; // Reuse the previously defined operator
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.set(j, i, matrix[i][j]);
        }
    }
    return result;
}

Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square for inversion");
    }

    int n = rows; // Assuming rows == cols
    Matrix augmented(n, 2 * n);

    // Create the augmented matrix [A | I]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented.set(i, j, matrix[i][j]);
        }
        augmented.set(i, i + n, 1.0); // Identity matrix on the right
    }

    // Apply Gauss-Jordan elimination
    for (int i = 0; i < n; ++i) {
        // Divide the current row by the diagonal element to make it 1
        double diagonalElement = augmented.get(i, i);
        for (int j = 0; j < 2 * n; ++j) {
            augmented.set(i, j, augmented.get(i, j) / diagonalElement);
        }

        // Make other rows zero in the current column
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double factor = augmented.get(j, i);
                for (int k = 0; k < 2 * n; ++k) {
                    augmented.set(j, k, augmented.get(j, k) - factor * augmented.get(i, k));
                }
            }
        }
    }

    // Extract the inverse matrix from the augmented matrix
    Matrix inverseMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix.set(i, j, augmented.get(i, j + n));
        }
    }

    return inverseMatrix;
}
