#include "gilbert.h"
#include <cmath>

inverse_matrix_gilbert::inverse_matrix_gilbert(double *m, int n){
    matrix = new double [n*n];
    conmatrix = new double [n*n];
    this->n = n;
    this->det = 1.0;
    this->swaps = 0;
    for (int i = 0; i < (this->n)*(this->n); i++) this->matrix[i] = *(m +i);
    for (int i=0; i < (this->n)*(this->n); i++){
        *(conmatrix + i) = 0.;
    }
    for (int i=0; i < (this->n); i++){
        *(conmatrix + n*i + i) = 1.;
    }
}

inverse_matrix_gilbert::~inverse_matrix_gilbert(){
    if(matrix) {
        delete []matrix;
        matrix = nullptr;
    }
    delete []conmatrix;
    conmatrix = nullptr;
}

double inverse_matrix_gilbert::GetDet()const{
    if (swaps % 2 == 0)return det;
    else return -1*det;
}

int inverse_matrix_gilbert::neededrow(int skip)const{// по дефолту скип равен нулю
    double loc, mx=abs(*(matrix + skip*n + skip));
    int numrow=skip;
    for (int i = skip; i < n; i++){
        loc = abs(*(matrix + n*i + skip));
        if (loc > mx){
            mx = loc;
            numrow = i;
        }
    }
    return numrow;
}

void inverse_matrix_gilbert::swaprows(int we_swap1){
    int we_swap = neededrow(we_swap1);
    double loc[n];
    double loccon[n];
    swaps++;
    if (we_swap1 == we_swap) return;
    for (int i=0; i < n; i++){
        loc[i] = *(matrix + we_swap1*n + i);
        loccon[i] = *(conmatrix + we_swap1*n + i);
    }
    for (int i=0; i < n; i++){
        *(matrix + we_swap1*n + i) = *(matrix + we_swap*n + i);
        *(matrix + we_swap*n + i) = loc[i];
        *(conmatrix + we_swap1*n + i) = *(conmatrix + we_swap*n + i);
        *(conmatrix + we_swap*n + i) = loccon[i];
    }
}

void inverse_matrix_gilbert::divisionrow(int num){
    double el = *(matrix + n*num + num);
    if (el == 0) {det = 0.;;return;}
    det *= el;
    for (int i = 0; i < n; i++){
        *(matrix + n*num + i) /= el;
        *(conmatrix + n*num + i) /= el;
    }
}

void inverse_matrix_gilbert::subtraction(int current){
    double loc[n];
    double loccon[n];
    for (int i = 0; i < n; i++){
        loc[i] = *(matrix + current*n + i);
        loccon[i] = *(conmatrix + current*n + i);
    }
    for (int k = (current + 1); k < n; k++){
        double mnozh = *(matrix + k*n + current);
        for (int i = 0; i < n; i++){
            *(matrix + k*n + i) -= mnozh*loc[i];
            *(conmatrix + k*n + i) -= mnozh*loccon[i];
        }
    }
}

void inverse_matrix_gilbert::triangle(){
    int skip=-1;
    for (int i=0; i < n; i++){
        skip++;
        swaprows(skip);
        divisionrow(skip);
        subtraction(skip);
    }
}

void inverse_matrix_gilbert::obrat(){
    double koof;
    for (int i=(n - 1); i >= 0; i--){
        for (int k = (i - 1); k >= 0; k--){
            koof = *(matrix + n*k + i);
            for (int j=0; j < n; j++){
                *(conmatrix + n*k + j) -= koof * (*(conmatrix + n*i + j));
                *(matrix + n*k + j) -= koof * (*(matrix + n*i + j));
            }
        }
    }
}

void inverse_matrix_gilbert::reverse(){
    triangle();
    obrat();
}

void inverse_matrix_gilbert::TakeReverse() {reverse();}
double * inverse_matrix_gilbert::GetMatrix()const {return this->conmatrix;}
double inverse_matrix_gilbert::GetElement(int i, int j)const {return matrix[n*i + j];}

