#include <random>
#include <iostream>


class Matrix {
private:
    unsigned int m;
    unsigned int n;
    int** data;

public:
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();

    void fillRandom();

    int* operator[](unsigned int i);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    Matrix operator+(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix operator*(const Matrix& other);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};






Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
   
    data = new int* [m];
    for (unsigned int i = 0; i < m; ++i) {   //Выделяем память для двумерного массива
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
            data[i][j] = dis(gen); // Генерация случайного числа от 0 до 9
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
        throw std::invalid_argument("не вычесть никак, размеры не подходят");
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
        throw std::invalid_argument("не вычесть никак, размеры не подходят");
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
        throw std::invalid_argument("матрицы не перемножатся");
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



int main() {
  
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

  
    matrix1.fillRandom();
    matrix2.fillRandom();      

    
    std::cout << "матрица 1:\n" << matrix1 << std::endl;
    std::cout << "матрица 2:\n" << matrix2 << std::endl;

    if (matrix1 == matrix2) {
            std::cout << "Матрицы равны.\n";
        }
        else {
            std::cout << "Матрицы не равны.\n\n";
        }

   
    Matrix sum = matrix1 + matrix2;
    std::cout << "Сумма матриц:\n" << sum << std::endl;

 
    Matrix subtract = matrix1 - matrix2;
    std::cout << "Разность матриц:\n" << subtract << std::endl;

    
    Matrix multiply = matrix1 * matrix2;
    std::cout << "Произведение матриц:\n" << multiply << std::endl;

    
    
  

    return 0;
}