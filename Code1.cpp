/*
Drew franke
3131934
Lab session: Wednesday 1:00pm
Lab Assignment: 07-1
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int size;

public:
    Matrix(int n) : size(n), data(n, std::vector<int>(n)) {}

    // load matrix from a specific part of the file
    void loadFromFile(std::ifstream& file) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data[i][j];
            }
        }
    }

    // display matrix in a user-friendly format
    void display() const {
        for (const auto& row : data) {
            for (int elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // operator overloading for matrix addition
    Matrix operator+(const Matrix& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrix sizes do not match for addition.");
        }
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrix sizes do not match for multiplication.");
        }
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // sum the main and secondary diagonal elements
    int sumDiagonals() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;
        for (int i = 0; i < size; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][size - i - 1];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // swap rows in the matrix
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw std::out_of_range("Row indices out of range.");
        }
        std::swap(data[row1], data[row2]);
    }
};

int main() {
    try {
        // load the size of the matrix
        std::ifstream file("matrix_input.txt");
        if (!file) {
            throw std::runtime_error("Error opening file.");
        }

        int size;
        file >> size; // read matrix size

        Matrix matrix1(size), matrix2(size);  // create matrices of the specified size

        // load the first matrix
        matrix1.loadFromFile(file);
        // load the second matrix
        matrix2.loadFromFile(file);

        // display loaded matrices
        std::cout << "Matrix 1:" << std::endl;
        matrix1.display();
        std::cout << "\nMatrix 2:" << std::endl;
        matrix2.display();

        // matrix addition
        Matrix sumMatrix = matrix1 + matrix2;
        std::cout << "\nSum of matrices:" << std::endl;
        sumMatrix.display();

        // matrix multiplication
        Matrix productMatrix = matrix1 * matrix2;
        std::cout << "\nProduct of matrices:" << std::endl;
        productMatrix.display();

        // sum of diagonal elements
        int diagonalSum1 = matrix1.sumDiagonals();
        int diagonalSum2 = matrix2.sumDiagonals();
        std::cout << "\nSum of main and secondary diagonals in Matrix 1: " << diagonalSum1 << std::endl;
        std::cout << "\nSum of main and secondary diagonals in Matrix 2: " << diagonalSum2 << std::endl;

        // row swapping
        int row1 = 0, row2 = 1;
        matrix1.swapRows(row1, row2);
        std::cout << "\nMatrix 1 after swapping rows 1 and 2:" << std::endl;
        matrix1.display();

        matrix2.swapRows(row1, row2);
        std::cout << "\nMatrix 2 after swapping rows 1 and 2:" << std::endl;
        matrix2.display();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}