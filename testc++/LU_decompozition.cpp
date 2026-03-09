#include "LU_decompozition.h"
#include <cmath>
#include <algorithm> // для std::swap

LU_Decomposition:: LU_Decomposition(double *matrix_data, int n) {
    this->n = n;
    this->swaps = 0;
    
    L = new double[n * n];
    U = new double[n * n];
    P = new int[n];

    for (int i = 0; i < n; i++) {
        P[i] = i; 
        for (int j = 0; j < n; j++) {
            U[i * n + j] = matrix_data[i * n + j]; 
            
            if (i == j) {
                L[i * n + j] = 1.0;
            } else {
                L[i * n + j] = 0.0;
            }
        }
    }
}

LU_Decomposition:: ~LU_Decomposition() {
    delete[] L;
    delete[] U;
    delete[] P;
}

int LU_Decomposition::neededrow(int skip) const {
    double mx = std::abs(U[skip * n + skip]);
    int numrow = skip;
    for (int i = skip + 1; i < n; i++) {
        double loc = std::abs(U[i * n + skip]);
        if (loc > mx) {
            mx = loc;
            numrow = i;
        }
    }
    return numrow;
}

void LU_Decomposition::swaprows(int step) {
    int we_swap = neededrow(step);
    
    if (step == we_swap) return;

    swaps++;

    std::swap(P[step], P[we_swap]);

    for (int j = step; j < n; j++) {
        std::swap(U[step * n + j], U[we_swap * n + j]);
    }

    for (int j = 0; j < step; j++) {
        std::swap(L[step * n + j], L[we_swap * n + j]);
    }
}

void LU_Decomposition::subtraction(int current) {
    double pivot = U[current * n + current];
    
    if (std::abs(pivot) < 1e-9) return; 

    for (int k = current + 1; k < n; k++) {
        double mnozh = U[k * n + current] / pivot;
        L[k * n + current] = mnozh;

        for (int j = current; j < n; j++) {
            U[k * n + j] -= mnozh * U[current * n + j];
        }
    }
}

void LU_Decomposition::decompose() {
    for (int i = 0; i < n - 1; i++) {
        swaprows(i);
        subtraction(i);
    }
}

double* LU_Decomposition::GetL() const { return L; }
double* LU_Decomposition::GetU() const { return U; }
int* LU_Decomposition::GetP() const { return P; }

double LU_Decomposition::GetDet() const {
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        det *= U[i * n + i];
    }

    if (swaps % 2 != 0) {
        det = -det;
    }
    return det;
}
