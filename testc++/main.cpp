#include <iostream>
#include "gilbert.h"
int main(){
    double data[6] = {1., 2., 0.,
                       0., 1., 2., // 2*3
                   };
    double data1[12] = {1., 12., 10,5., 6., -1., 7., -5, 1., 6., 13., 22.}; // 3*4
    double data2[9] = {1., 2., 3., 4., 5., 65., 7., 8., 9.}; // 3*3
    double data3[9] = {12., 21., 21., 123.4, 12.45, 67.5, 13., 10.1, 3.12}; // 3*3
    matrixes matrix(data, 2, 3);
    matrixes mat1(data1, 3, 4);
    matrixes mat2(data2, 3, 3);
    matrixes mat3(data3, 3, 3);
    matrixes test(5,  5);
    int c = 0;
    std::cout << "Произведение матриц 2*3 и 3*4" << std::endl;
    for (int i = 0; i < 8; i++){
        c++;
        std::cout << *((matrix * mat1).GetMatrix() + i) << " ";
        if (c % 4 == 0) std::cout << std::endl;
    }
    c = 0;
    std::cout << "Вычитание матриц 3*3" << std::endl;
    for (int i = 0; i < 9; i++){
        c ++;
        std::cout << *((mat2 - mat3).GetMatrix() + i) << " ";
        if (c % 3 == 0) std::cout << std::endl;
    }
    c = 0;
    std::cout << "Сложение матриц 3*3" << std::endl;
    for (int i = 0; i < 9; i++){
        c++;
        std::cout << *((mat2 + mat3).GetMatrix() + i) << " ";
        if (c%3 == 0) std::cout << std::endl;
    }
    c = 0;
    test.MakeOnes();
    std::cout << "Единичная матрица 5*5" << std::endl;
    for (int i = 0; i < 25; i++){
        c ++;
        std::cout << *(test.GetMatrix() + i) << " ";
        if (c % 5 == 0) std::cout << std::endl;
    }
    c = 0;
    test.MakeGilbert();
    std::cout << "Матрица Гильберта 5*5" << std::endl;
    for (int i = 0; i < 25; i++){
        c ++;
        std::cout << *(test.GetMatrix() + i) << " ";
        if (c % 5 == 0) std::cout << std::endl;
    }
    c = 0;
    std::cout << "Обратная матрица от матрицы Гильберта 5*5" << std::endl;
    for (int i = 0; i < 25; i++){
        c ++;
        std::cout << *(test.GetInverseMatrix() + i) << " ";
        if (c % 5 == 0) std::cout << std::endl;
    }
    std::cout << "Определитель матрицы  3*3" << std::endl;
    std::cout << mat2.GetDet() << std::endl;
    return 0;
}

