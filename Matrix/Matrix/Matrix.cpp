#include <iostream>
#include <vector>
#include <thread>

class MatrixMultiplier {
private:
    std::vector<std::vector<int>> matrix1;
    std::vector<std::vector<int>> matrix2;
    std::vector<std::vector<int>> result;

public:
    void inputMatrix1() {
        size_t rows, cols;
        std::cout << "Enter the number of rows for Matrix 1: ";
        std::cin >> rows;
        std::cout << "Enter the number of columns for Matrix 1: ";
        std::cin >> cols;

        matrix1.resize(rows, std::vector<int>(cols));

        std::cout << "Enter the elements of Matrix 1:" << std::endl;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << "Enter element [" << i << "][" << j << "]: ";
                std::cin >> matrix1[i][j];
            }
        }
    }

    void inputMatrix2() {
        size_t rows, cols;
        std::cout << "Enter the number of rows for Matrix 2: ";
        std::cin >> rows;
        std::cout << "Enter the number of columns for Matrix 2: ";
        std::cin >> cols;

        matrix2.resize(rows, std::vector<int>(cols));

        std::cout << "Enter the elements of Matrix 2:" << std::endl;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << "Enter element [" << i << "][" << j << "]: ";
                std::cin >> matrix2[i][j];
            }
        }
    }

    void multiplyMatrices() {
        size_t rows1 = matrix1.size();
        size_t cols1 = matrix1[0].size();
        size_t rows2 = matrix2.size();
        size_t cols2 = matrix2[0].size();

        if (cols1 != rows2) {
            std::cout << "Error: Matrix dimensions are incompatible for multiplication." << std::endl;
            return;
        }

        result.resize(rows1, std::vector<int>(cols2));

        std::vector<std::thread> threads;
        for (size_t i = 0; i < rows1; ++i) {
            threads.emplace_back([this, i, cols1, cols2]() {
                for (size_t j = 0; j < cols2; ++j) {
                    int sum = 0;
                    for (size_t k = 0; k < cols1; ++k) {
                        sum += matrix1[i][k] * matrix2[k][j];
                    }
                    result[i][j] = sum;
                }
                });
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }

    void printResult() {
        size_t rows = result.size();
        size_t cols = result[0].size();

        std::cout << "Resulting matrix:" << std::endl;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    
    MatrixMultiplier multiplier;

    std::cout << "Matrix 1:" << std::endl;
    multiplier.inputMatrix1();

    std::cout << "Matrix 2:" << std::endl;
    multiplier.inputMatrix2();

    multiplier.multiplyMatrices();

    multiplier.printResult();

    return 0;
}