#include "default_gauss.h"
#include <cmath>
#include <vector> // Добавлено для std::vector

default_gauss::default_gauss(double *m, int n) {
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

default_gauss::~default_gauss() {
  if (matrix) {
    delete[] matrix;
    matrix = nullptr;
  }
  delete[] conmatrix;
  conmatrix = nullptr;
}

double default_gauss::GetDet() const {
  if (swaps % 2 == 0)
    return det;
  else
    return -1 * det;
}

int default_gauss::neededrow(int skip) const { // по дефолту скип равен нулю
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

void default_gauss::swaprows(int we_swap1) {
  int we_swap = neededrow(we_swap1);

  // Замена массивов переменной длины на std::vector
  std::vector<double> loc(n);
  std::vector<double> loccon(n);

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

void default_gauss::divisionrow(int num) {
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

void default_gauss::subtraction(int current) {
  // Замена массивов переменной длины на std::vector
  std::vector<double> loc(n);
  std::vector<double> loccon(n);

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

void default_gauss::triangle() {
  for (int i = 0; i < n; i++) {
    divisionrow(i);
    subtraction(i);
  }
}

void default_gauss::obrat() {
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

void default_gauss::reverse() {
  triangle();
  obrat();
}

double *default_gauss::Solve(double *b) {
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

void default_gauss::SolveForTests(double *b) {
  for (int i = 0; i < n; i++) {
    conmatrix[n * i] = b[i];
  }
  triangle();
  obrat();
}

void default_gauss::TakeReverse() { reverse(); }
double *default_gauss::GetMatrix() const { return this->conmatrix; }
double default_gauss::GetElement(int i, int j) const {
  return matrix[n * i + j];
}
