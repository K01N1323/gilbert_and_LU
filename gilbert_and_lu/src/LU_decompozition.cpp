#include "LU_decompozition.h"
#include <algorithm> // для std::swap
#include <cmath>

// Конструктор: выделяет память и выполняет декомпозицию
LU_Decomposition::LU_Decomposition(double *matrix_data, int n) {
  this->n = n;
  this->swaps = 0;

  L = new double[n * n];
  U = new double[n * n];
  P = new int[n];
  x = new double[n];
  y = new double[n];

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

  decompose();
}

// Деструктор: освобождает выделенную память
LU_Decomposition::~LU_Decomposition() {
  delete[] L;
  delete[] U;
  delete[] P;
  delete[] x;
  delete[] y;
}

// Ищет максимальный по модулю ведущий элемент в текущем столбце
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

// Переставляет строки для устойчивости алгоритма
void LU_Decomposition::swaprows(int step) {
  int we_swap = neededrow(step);

  if (step == we_swap) {
    return;
  }

  swaps++;

  std::swap(P[step], P[we_swap]);

  for (int j = step; j < n; j++) {
    std::swap(U[step * n + j], U[we_swap * n + j]);
  }

  for (int j = 0; j < step; j++) {
    std::swap(L[step * n + j], L[we_swap * n + j]);
  }
}

// Вычитает строки и формирует L и U
void LU_Decomposition::subtraction(int current) {
  double pivot = U[current * n + current];

  if (std::abs(pivot) < 1e-9) {
    return;
  }

  for (int k = current + 1; k < n; k++) {
    double mnozh = U[k * n + current] / pivot;
    L[k * n + current] = mnozh;

    for (int j = current; j < n; j++) {
      U[k * n + j] -= mnozh * U[current * n + j];
    }
  }
}

// Основной цикл LU-разложения
void LU_Decomposition::decompose() {
  for (int i = 0; i < n - 1; i++) {
    swaprows(i);
    subtraction(i);
  }
}

// Возвращает матрицу L
double *LU_Decomposition::GetL() const { return L; }

// Возвращает матрицу U
double *LU_Decomposition::GetU() const { return U; }

// Возвращает массив перестановок
int *LU_Decomposition::GetP() const { return P; }

// Вычисляет и возвращает определитель матрицы
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

// Решает СЛАУ: сначала LY = Pb, затем UX = Y
double *LU_Decomposition::Solve(double *b) const {
  for (int i = 0; i < n; i++) {
    y[i] = b[P[i]];

    for (int j = 0; j < i; j++) {
      y[i] -= L[i * n + j] * y[j];
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    x[i] = y[i];

    for (int j = i + 1; j < n; j++) {
      x[i] -= U[i * n + j] * x[j];
    }

    x[i] /= U[i * n + i];
  }

  return x;
}

// Решение СЛАУ без возврата ответа (для тестов скорости)
void LU_Decomposition::SolveForTests(double *b) const {
  for (int i = 0; i < n; i++) {
    y[i] = b[P[i]];

    for (int j = 0; j < i; j++) {
      y[i] -= L[i * n + j] * y[j];
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    x[i] = y[i];

    for (int j = i + 1; j < n; j++) {
      x[i] -= U[i * n + j] * x[j];
    }

    x[i] /= U[i * n + i];
  }
}
