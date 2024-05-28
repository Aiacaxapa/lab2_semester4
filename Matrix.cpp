#include "Matrix.h"
#include <random>
#include <iostream>

Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {

    data = new int* [m];
    for (unsigned int i = 0; i < m; ++i) {   //¬ыдел€ем пам€ть дл€ двумерного массива
        data[i] = new int[n];
    }
}

Matrix::~Matrix() {
    for (unsigned int i = 0; i < m; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::fillRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            data[i][j] = dis(gen); // √енераци€ случайного числа от 0 до 9
        }
    }
}

int* Matrix::operator[](unsigned int i) {
    return data[i];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (unsigned int i = 0; i < matrix.m; ++i) {
        for (unsigned int j = 0; j < matrix.n; ++j) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& other) {
    if (m != other.m || n != other.n) {
        throw std::invalid_argument("такие матрицы не сложить");
    }

    Matrix result(m, n);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (m != other.m || n != other.n) {
        throw std::invalid_argument("такие матрицы не сложить");
    }

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            data[i][j] += other.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator-(const Matrix& other) {
    if (m != other.m || n != other.n) {
        throw std::invalid_argument("не вычесть никак, размеры не подход€т");
    }

    Matrix result(m, n);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (m != other.m || n != other.n) {
        throw std::invalid_argument("не вычесть никак, размеры не подход€т");
    }

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (n != other.m) {
        throw std::invalid_argument("матрицы не перемножатс€");
    }

    Matrix result(m, other.n);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < other.n; ++j) {
            result.data[i][j] = 0;
            for (unsigned int k = 0; k < n; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (m != other.m || n != other.n) {
        return false;
    }

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}
