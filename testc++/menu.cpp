#include <iostream>

#include "menu.h"
#include "matrixes.h"
#include "gilbert.h"

#define max_matrices = 20;

using namespace std

static matixes* matrices[max_matrices];
static int matrices_count = 0;
void PrintInfo(){
    cout << "1 - Создать матрицу" << endl; 
    cout << "2 - Заполнить матрицей гильберта"<< endl;
    cout << "3 - Заполнить единичной матрицей"<< endl;
    cout << "4 - Посчитать обратную матрицу методом Гильберта с выбором ведушего элемента для матрицы"<< endl;
    cout << "5 - Посчитать обратную матрицу LU разложением "<< endl;
    cout << "6 - Сетнуть элемент матрицы"

}

void Print_Matrix(const matrixes* matrix)const{
    cout << "| ";
    for (int index = 0; index < matrix->rows * matrix->cols; index++){
        cout << matrix->Get(index) << " ";
        if ((index + 1) % matrix->cols){
            coout << "|";
            cout << endl;
        }
        if (index % matrix->cols = 0){
            cout << "|"
        }
    }
    cout << "|";
}

void open_menu(){
    int choise = -1;
    switch (case){

        
    }
}