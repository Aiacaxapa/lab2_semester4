#include <iostream>
#include "Matrix.h"

int main() {
    setlocale(LC_ALL, "rus");

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
