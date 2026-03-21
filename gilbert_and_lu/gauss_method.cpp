#include "gauss_method.h"
#include <cmath>

gauss_method::gauss_method(double *m, int n) {
  matrix = new double[n * n];
  conmatrix = new double[n * n];
  this->n = n;
  this->det = 1.0;
  this->swaps = 0;
  for (int i = 0; i < (this->n) * (this->n); i++)
    this->matrix[i] = *(m + i);
  for (int i = 0; i < (this->n) * (this->n); i++) {
    *(conmatrix + i) = 0.;
  }
  for (int i = 0; i < (this->n); i++) {
    *(conmatrix + n * i + i) = 1.;
  }
}

gauss_method::~gauss_method() {
  if (matrix) {
    delete[] matrix;
    matrix = nullptr;
  }
  delete[] conmatrix;
  conmatrix = nullptr;
}

double gauss_method::GetDet() const {
  if (swaps % 2 == 0)
    return det;
  else
    return -1 * det;
}

int gauss_method::neededrow(int skip) const { // по дефолту скип равен нулю
  double loc, mx = std::abs(*(matrix + skip * n + skip));
  int numrow = skip;
  for (int i = skip; i < n; i++) {
    loc = std::abs(*(matrix + n * i + skip));
    if (loc > mx) {
      mx = loc;
      numrow = i;
    }
  }
  return numrow;
}

void gauss_method::swaprows(int we_swap1) {
  int we_swap = neededrow(we_swap1);
  double loc[n];
  double loccon[n];
  swaps++;
  if (we_swap1 == we_swap)
    return;
  for (int i = 0; i < n; i++) {
    loc[i] = *(matrix + we_swap1 * n + i);
    loccon[i] = *(conmatrix + we_swap1 * n + i);
  }
  for (int i = 0; i < n; i++) {
    *(matrix + we_swap1 * n + i) = *(matrix + we_swap * n + i);
    *(matrix + we_swap * n + i) = loc[i];
    *(conmatrix + we_swap1 * n + i) = *(conmatrix + we_swap * n + i);
    *(conmatrix + we_swap * n + i) = loccon[i];
  }
}

void gauss_method::divisionrow(int num) {
  double el = *(matrix + n * num + num);
  if (el == 0) {
    det = 0.;
    ;
    return;
  }
  det *= el;
  for (int i = 0; i < n; i++) {
    *(matrix + n * num + i) /= el;
    *(conmatrix + n * num + i) /= el;
  }
}

void gauss_method::subtraction(int current) {
  double loc[n];
  double loccon[n];
  for (int i = 0; i < n; i++) {
    loc[i] = *(matrix + current * n + i);
    loccon[i] = *(conmatrix + current * n + i);
  }
  for (int k = (current + 1); k < n; k++) {
    double mnozh = *(matrix + k * n + current);
    for (int i = 0; i < n; i++) {
      *(matrix + k * n + i) -= mnozh * loc[i];
      *(conmatrix + k * n + i) -= mnozh * loccon[i];
    }
  }
}

void gauss_method::triangle() {
  int skip = -1;
  for (int i = 0; i < n; i++) {
    skip++;
    swaprows(skip);
    divisionrow(skip);
    subtraction(skip);
  }
}

void gauss_method::obrat() {
  double koof;
  for (int i = (n - 1); i >= 0; i--) {
    for (int k = (i - 1); k >= 0; k--) {
      koof = *(matrix + n * k + i);
      for (int j = 0; j < n; j++) {
        *(conmatrix + n * k + j) -= koof * (*(conmatrix + n * i + j));
        *(matrix + n * k + j) -= koof * (*(matrix + n * i + j));
      }
    }
  }
}

void gauss_method::reverse() {
  triangle();
  obrat();
}

double *gauss_method::Solve(double *b) {
  for (int i = 0; i < n; i++) {
    conmatrix[n * i] = b[i];
  }
  triangle();
  obrat();

  double *result = new double[n];

  for (int i = 0; i < n; i++) {
    result[i] = conmatrix[n * i];
  }

  return result;
}

void gauss_method::SolveForTests(double *b) {
  for (int i = 0; i < n; i++) {
    conmatrix[n * i] = b[i];
  }
  triangle();
  obrat();
}

void gauss_method::TakeReverse() { reverse(); }
double *gauss_method::GetMatrix() const { return this->conmatrix; }
double gauss_method::GetElement(int i, int j) const {
  return matrix[n * i + j];
}
