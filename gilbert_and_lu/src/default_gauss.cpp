#include "default_gauss.h"
#include <cmath>
#include <vector> // Добавлено для std::vector

// Конструктор метода Гаусса без выбора ведущего элемента
default_gauss::default_gauss(double *m, int n) {
    matrix = new double[n * n];
    conmatrix = new double[n * n];

    this->n = n;
    this->det = 1.0;
    this->swaps = 0;

    for (int i = 0; i < (this->n) * (this->n); i++) {
        this->matrix[i] = *(m + i);
    }

    for (int i = 0; i < (this->n) * (this->n); i++) {
        *(conmatrix + i) = 0.;
    }

    for (int i = 0; i < (this->n); i++) {
        *(conmatrix + n * i + i) = 1.;
    }
}

// Деструктор
default_gauss::~default_gauss() {
    if (matrix) {
        delete[] matrix;
        matrix = nullptr;
    }

    delete[] conmatrix;
    conmatrix = nullptr;
}

// Возвращает знак определителя в зависимости от перестановок
double default_gauss::GetDet() const {
    if (swaps % 2 == 0)
        return det;
    else
        return -1 * det;
}

// Ищет максимальный по модулю элемент в столбце для устойчивости
int default_gauss::neededrow(int skip) const { // по дефолту скип равен нулю
    double loc;
    double mx = std::abs(*(matrix + skip * n + skip));
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

// Переставляет строки так, чтобы ведущий элемент был сверху
void default_gauss::swaprows(int we_swap1) {
    int we_swap = neededrow(we_swap1);

    // Замена массивов переменной длины на std::vector
    std::vector<double> loc(n);
    std::vector<double> loccon(n);

    swaps++;

    if (we_swap1 == we_swap) {
        return;
    }

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

// Делит текущую строку на ведущий элемент, делая его равным 1
void default_gauss::divisionrow(int num) {
    double el = *(matrix + n * num + num);

    if (el == 0) {
        det = 0.;
        return;
    }

    det *= el;

    for (int i = 0; i < n; i++) {
        *(matrix + n * num + i) /= el;
        *(conmatrix + n * num + i) /= el;
    }
}

// Вычитает текущую строку из всех последующих, обнуляя элементы под ведущим
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

// Прямой ход Гаусса: приведение матрицы к верхнетреугольному виду
void default_gauss::triangle() {
    for (int i = 0; i < n; i++) {
        divisionrow(i);
        subtraction(i);
    }
}

// Обратный ход Гаусса: нахождение корней (или обратной матрицы)
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

// Полный процесс метода Гаусса (прямой + обратный ход)
void default_gauss::reverse() {
    triangle();
    obrat();
}

// Решает СЛАУ для вектора b и возвращает вектор x
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

// Решение СЛАУ без выделения памяти под ответ (для ускорения тестов)
void default_gauss::SolveForTests(double *b) {
    for (int i = 0; i < n; i++) {
        conmatrix[n * i] = b[i];
    }

    triangle();
    obrat();
}

// Инкапсулирует вызов reverse()
void default_gauss::TakeReverse() { reverse(); }

// Геттеры для матрицы и её элементов
double *default_gauss::GetMatrix() const { return this->conmatrix; }

double default_gauss::GetElement(int i, int j) const {
    return matrix[n * i + j];
}
