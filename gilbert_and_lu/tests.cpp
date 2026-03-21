#include <chrono>
#include <iostream>
#include <random>

#include "LU_decompozition.h"
#include "default_gauss.h"
#include "gauss_method.h"
#include "matrixes.h"
#include "tests.h"

using namespace std;

struct ExecutionTime {
  double lu_time;
  double solve_time;
};

double Solve_with_default_gauss(int n) {

  matrixes Matrix(n, n);
  Matrix.MakeRandomNormal();

  double *b = new double[n];

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);
  for (int i = 0; i < n; i++) {
    b[i] = dis(gen);
  }

  default_gauss Matrix_for_gauss(Matrix.GetMatrix(), n);

  auto start_gauss = std::chrono::high_resolution_clock::now();
  Matrix_for_gauss.SolveForTests(b);
  auto end_gauss = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time = end_gauss - start_gauss;

  delete[] b;
  return time.count();
}

double Solve_with_gauss(int n) {

  matrixes Matrix(n, n);
  Matrix.MakeRandomNormal();

  double *b = new double[n];

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  for (int i = 0; i < n; i++) {
    b[i] = dis(gen);
  }

  gauss_method Matrix_for_gauss(Matrix.GetMatrix(), n);

  auto start_gauss = std::chrono::high_resolution_clock::now();
  Matrix_for_gauss.SolveForTests(b);
  auto end_gauss = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time = end_gauss - start_gauss;

  delete[] b;
  return time.count();
}

ExecutionTime Solve_with_LU(int n) {
  matrixes Matrix(n, n);
  Matrix.MakeRandomNormal();

  double *b = new double[n];

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  for (int i = 0; i < n; i++) {
    b[i] = dis(gen);
  }

  auto start_lu = std::chrono::high_resolution_clock::now();
  LU_Decomposition Matrix_for_LU(Matrix.GetMatrix(), n);
  auto end_lu = std::chrono::high_resolution_clock::now();

  auto start_solve = std::chrono::high_resolution_clock::now();
  Matrix_for_LU.SolveForTests(b);
  auto end_solve = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff_lu = end_lu - start_lu;
  std::chrono::duration<double> diff_solve = end_solve - start_solve;

  delete[] b;
  return {diff_lu.count(), diff_solve.count()};
}

ExecutionTime Solving_immutable_b(int k) {
  double summ_time_for_gauss = 0;
  double summ_time_for_lu = 0;
  int n = 500;
  matrixes matrix(n, n);

  matrix.MakeRandomNormal();

  gauss_method matrix_for_gauss(matrix.GetMatrix(), n);

  auto start_lu_decompoze = std::chrono::high_resolution_clock::now();
  LU_Decomposition matrix_for_LU(matrix.GetMatrix(), n);
  auto end_lu_decompoze = std::chrono::high_resolution_clock::now();

  summ_time_for_lu += (end_lu_decompoze - start_lu_decompoze).count();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  double *b = new double[n];

  for (int i = 0; i < k; i++) {
    for (int k = 0; k < 500; k++) {
      b[k] = dis(gen);
    }
    auto start_gauss = std::chrono::high_resolution_clock::now();
    matrix_for_gauss.SolveForTests(b);
    auto end_gauss = std::chrono::high_resolution_clock::now();

    auto start_lu = std::chrono::high_resolution_clock::now();
    matrix_for_LU.SolveForTests(b);
    auto end_lu = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_for_gauss = end_gauss - start_gauss;

    std::chrono::duration<double> time_for_lu = end_lu - start_lu;

    summ_time_for_gauss += time_for_gauss.count();
    summ_time_for_lu += time_for_lu.count();
  }

  delete[] b;

  return {summ_time_for_gauss, summ_time_for_lu};
}

ExecutionTime Gilbert_tests_for_default_gauss(int n) {
  matrixes matrix(n, n);
  matrix.MakeGilbert();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  double *b = new double[n];
  for (int i = 0; i < n; i++) {
    b[i] = 0;
    for (int j = 0; j < n; j++) {
      b[i] += matrix.GetIJ(i, j);
    }
  }

  default_gauss matrix_for_gauss(matrix.GetMatrix(), n);
  double *x = matrix_for_gauss.Solve(b);

  double result_for_normal = 0;
  for (int i = 0; i < n; i++) {
    result_for_normal += std::abs(x[i] - 1.0);
  }

  double result_for_discrepancy = 0.;
  for (int i = 0; i < n; i++) {
    double Hx_i = 0;
    for (int j = 0; j < n; j++) {
      Hx_i += matrix.GetIJ(i, j) * x[j];
    }
    result_for_discrepancy += std::abs(b[i] - Hx_i);
  }

  delete[] b;

  return {result_for_normal, result_for_discrepancy};
}

ExecutionTime Gilbert_tests_for_gauss(int n) {
  matrixes matrix(n, n);
  matrix.MakeGilbert();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  double *b = new double[n];
  for (int i = 0; i < n; i++) {
    b[i] = 0;
    for (int j = 0; j < n; j++) {
      b[i] += matrix.GetIJ(i, j);
    }
  }

  gauss_method matrix_for_gauss(matrix.GetMatrix(), n);
  double *x = matrix_for_gauss.Solve(b);

  double result_for_normal = 0;
  for (int i = 0; i < n; i++) {
    result_for_normal += std::abs(x[i] - 1.0);
  }

  double result_for_discrepancy = 0.;
  for (int i = 0; i < n; i++) {
    double Hx_i = 0;
    for (int j = 0; j < n; j++) {
      Hx_i += matrix.GetIJ(i, j) * x[j];
    }
    result_for_discrepancy += std::abs(b[i] - Hx_i);
  }

  delete[] b;

  return {result_for_normal, result_for_discrepancy};
}

ExecutionTime Gilbert_tests_for_lu(int n) {
  matrixes matrix(n, n);
  matrix.MakeGilbert();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);

  double *b = new double[n];
  for (int i = 0; i < n; i++) {
    b[i] = 0;
    for (int j = 0; j < n; j++) {
      b[i] += matrix.GetIJ(i, j);
    }
  }

  LU_Decomposition matrix_for_lu(matrix.GetMatrix(), n);
  double *x = matrix_for_lu.Solve(b);

  double result_for_normal = 0;
  for (int i = 0; i < n; i++) {
    result_for_normal += std::abs(x[i] - 1.0);
  }

  double result_for_discrepancy = 0.;
  for (int i = 0; i < n; i++) {
    double Hx_i = 0;
    for (int j = 0; j < n; j++) {
      Hx_i += matrix.GetIJ(i, j) * x[j];
    }
    result_for_discrepancy += std::abs(b[i] - Hx_i);
  }

  delete[] b;

  return {result_for_normal, result_for_discrepancy};
}
void run_all_tests() {
  cout << "НАЧАЛО ТЕСТОВ МЕТОДОВ РЕШЕНИЯ СЛАУ" << endl;

  cout << "МЕТОД ГАУССА БЕЗ ВЫБОРА ВЕДУЩЕГО ЭЛЕМЕНТА" << endl;
  cout << "Время нахождения решения для матрицы 100 на 100" << endl;
  cout << Solve_with_default_gauss(100) << endl;
  cout << "Время нахождения решения для матрицы 200 на 200" << endl;
  cout << Solve_with_default_gauss(200) << endl;
  cout << "Время нахождения решения для матрицы 500 на 500" << endl;
  cout << Solve_with_default_gauss(500) << endl;

  cout << "МЕТОД ГАУССА С ВЫБОРОМ ВЕДУЩЕГО ЭЛЕМЕНТА" << endl;
  cout << "Время нахождения решения для матрицы 100 на 100" << endl;
  cout << Solve_with_gauss(100) << endl;
  cout << "Время нахождения решения для матрицы 200 на 200" << endl;
  cout << Solve_with_gauss(200) << endl;
  cout << "Время нахождения решения для матрицы 500 на 500" << endl;
  cout << Solve_with_gauss(500) << endl;

  cout << "LU-ДЕКОМПОЗИЦИЯ" << endl;

  cout << "Время нахождения решения для матрицы 100 на 100" << endl;
  ExecutionTime t100 = Solve_with_LU(100);
  cout << "Время LU: " << t100.lu_time << endl;
  cout << "Время Solve: " << t100.solve_time << endl;
  cout << "Суммарно: " << t100.lu_time + t100.solve_time << endl;

  cout << "Время нахождения решения для матрицы 200 на 200" << endl;
  ExecutionTime t200 = Solve_with_LU(200);
  cout << "Время LU: " << t200.lu_time << endl;
  cout << "Время Solve: " << t200.solve_time << endl;
  cout << "Суммарно: " << t200.lu_time + t200.solve_time << endl;

  cout << "Время нахождения решения для матрицы 500 на 500" << endl;
  ExecutionTime t500 = Solve_with_LU(500);
  cout << "Время LU: " << t500.lu_time << endl;
  cout << "Время Solve: " << t500.solve_time << endl;
  cout << "Суммарно: " << t500.lu_time + t500.solve_time << endl;

  cout << "Тесты скорости решения СЛАУ LU разложением при неизменной матрице "
          "коэффициентов"
       << endl;
  cout << "Для k == 1" << std::endl;
  ExecutionTime t3 = Solving_immutable_b(1);
  cout << "Время для метода Гаусса: " << t3.lu_time << endl;
  cout << "Время для LU разложения: " << t3.solve_time << endl;
  cout << endl;

  cout << "Для k == 10" << std::endl;
  ExecutionTime t10 = Solving_immutable_b(10);
  cout << "Время для метода Гаусса: " << t10.lu_time << endl;
  cout << "Время для LU разложения: " << t10.solve_time << endl;
  cout << endl;

  cout << "Для k == 100" << std::endl;
  ExecutionTime t100_ = Solving_immutable_b(100);
  cout << "Время для метода Гаусса: " << t100_.lu_time << endl;
  cout << "Время для LU разложения: " << t100_.solve_time << endl;
  cout << endl;
}
