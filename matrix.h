#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

class Matrix
{
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> matrix;

public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, const std::vector<std::vector<double>>& data);

    int numRows() const;
    int numCols() const;
    
    double get(int i, int j) const;
    void set(int i, int j, double value);

    void printMatrix() const;
    void printSubmatrix(int rows, int cols) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;
    Matrix operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;

    Matrix transpose() const;
    Matrix inverse() const;
    double determinant() const;
};

#endif

