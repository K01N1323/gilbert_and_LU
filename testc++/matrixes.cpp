#include "matrixes.h"
#include <cmath>

matrixes::matrixes(int rows, int cols) : matrixes(nullptr, rows, cols) {}
matrixes::matrixes(double *data, int rows, int cols) : rows(rows), cols(cols){
    matrix = new double [(rows*cols)];
    if (data == nullptr){
        for (int i = 0; i < (rows * cols); i++){
            *(matrix + i) = 0.;
        }
    }
    else{
        for (int i = 0; i < (rows * cols); i++){
            *(matrix + i) = data[i];
        }
    }
}

matrixes::~matrixes(){
    if (matrix){
        delete []matrix;
        matrix = nullptr;
    }
}

double matrixes:: double Get(int index) const {return *(matrix + index);}
double* matrixes::GetMatrix()const { return matrix;}
void matrixes::MakeGilbert(){
    if (rows != cols) {return;}
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix[cols*i + j] = (1.0 / (i + j + 1));
        }
    }
}

double* matrixes::GetInverseMatrix()const{
    inverse_matrix_gilbert mat(matrix, rows);
    mat.TakeReverse();
    matrixes matrix(rows, rows);
    double *result = new double [rows*rows];
    for (int i = 0; i < (rows*rows); i++){
        *(result + i) = *(mat.GetMatrix() + i);
    }
    return result;
}

void matrixes::MakeOnes(){
    if (rows != cols) {return;}
    for (int i = 0; i < rows*cols; i++){
        *(matrix + i) = 0;
    }
    for (int i = 0; i < rows; i++){
        matrix[rows*i + i] = 1.0;
    }
}

const matrixes matrixes::operator+(const matrixes &rv)const{
    if ((rows == rv.rows) && (cols == rv.cols)){
        matrixes mat(rows, cols);
        for(int i = 0; i < rows*cols; i++){
            *(mat.matrix + i) = *(matrix + i) + *(rv.matrix + i);
        }
        return mat;
    }
    return matrixes(0,0);
}

const matrixes matrixes::operator-(const matrixes &rv)const{
    if ((rows == rv.rows) && (cols == rv.cols)){
        matrixes mat(rows, cols);
        for(int i = 0; i < rows*cols; i++){
            *(mat.matrix + i) = *(matrix + i) - *(rv.matrix + i);
        }
        return mat;
    }
    return matrixes(0,0);
}

const double matrixes::SubstrRowCol(const matrixes &rv, const int n1, int n2)const{
    double element=0.;
    for (int i = 0; i < cols; i++){
        element += matrix[cols*n1 + i] * rv.matrix[rv.cols*i + n2];
    }
    return element;
}

const matrixes matrixes::operator*(const matrixes &rv)const{
    double sum=0.;
    int count = -1;
    if (cols != rv.rows) return (matrixes(0, 0));
    if (cols == 1){
        for (int i =0; i < rows; i++){
            sum += *(matrix + i) * *(rv.matrix + i);
        }
        double *loc = new double [1];
        *loc = sum;
        matrixes mat(loc, 1, 1);
        delete []loc;
        return mat;
    }
    else{
        matrixes multmat(rows, rv.cols);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < rv.cols; j++){
                count++;
                *(multmat.matrix + count) = SubstrRowCol(rv, i, j);
            }
        }
        return multmat;
    }
}

double matrixes::GetDet()const{
    if (rows != cols) return NAN;
    inverse_matrix_gilbert mat(matrix, rows);
    mat.TakeReverse();
    return mat.det;
}
