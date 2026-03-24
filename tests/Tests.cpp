#include <iostream>
#include <stdexcept>

#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "tests.h"

using namespace std;

static int tests_passed = 0;
static int tests_failed = 0;

// Вспомогательная функция для проверки условий в тестах
static void check(bool condition, const char *test_name) {
    if (condition) {
        cout << "  Успешно: " << test_name << "\n";
        tests_passed++;
    } else {
        cout << "  Провалено: " << test_name << "\n";
        tests_failed++;
    }
}

// Вспомогательная функция для Map (умножение на 2)
static int double_val(const int &x) { 
    return x * 2; 
}

// Вспомогательная функция для Where (проверка на четность)
static bool is_even(const int &x) { 
    return x % 2 == 0; 
}

// Вспомогательная функция для Reduce (сумма элементов)
static int sum(const int &acc, const int &x) { 
    return acc + x; 
}

// Тестирование изменяемой последовательности на основе массива
void test_mutable_array_sequence() {
    cout << "\n--- Тестирование MutableArraySequence ---\n";

    {
        MutableArraySequence<int> seq;
        check(seq.GetLength() == 0, "Длина пустой последовательности равна 0");
    }

    {
        int data[] = {10, 20, 30};
        MutableArraySequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Создание из массива: длина корректна");
        check(seq.Get(0) == 10, "Получение элемента по индексу 0");
        check(seq.Get(2) == 30, "Получение элемента по индексу 2");
        check(seq.GetFirst() == 10, "Получение первого элемента");
        check(seq.GetLast() == 30, "Получение последнего элемента");
        check(seq[1] == 20, "Перегрузка оператора индексации работает");
    }

    {
        MutableArraySequence<int> seq;
        seq.Append(1);
        seq.Append(2);
        seq.Append(3);
        check(seq.GetLength() == 3, "Добавление элементов в конец (Append)");
        check(seq.GetFirst() == 1, "Первый элемент после Append корректен");
        check(seq.GetLast() == 3, "Последний элемент после Append корректен");
    }

    {
        MutableArraySequence<int> seq;
        seq.Append(2);
        seq.Prepend(1);
        check(seq.GetFirst() == 1, "Добавление элемента в начало (Prepend)");
        check(seq.GetLength() == 2, "Длина после Prepend корректна");
    }

    {
        int data[] = {1, 3};
        MutableArraySequence<int> seq(data, 2);
        seq.InsertAt(2, 1);
        check(seq.Get(1) == 2, "Вставка элемента по индексу (InsertAt)");
        check(seq.GetLength() == 3, "Длина после вставки корректна");
    }

    {
        int data[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(data, 5);
        Sequence<int> *sub = seq.GetSubsequence(1, 3);
        check(sub->GetLength() == 3, "Получение подпоследовательности работает");
        check(sub->Get(0) == 20, "Первый элемент подпоследовательности корректен");
        check(sub->Get(2) == 40, "Последний элемент подпоследовательности корректен");
        delete sub;
    }

    {
        int data[] = {1, 2, 3};
        MutableArraySequence<int> seq(data, 3);
        bool threw = false;
        try {
            seq.GetSubsequence(2, 1);
        } catch (const out_of_range &) {
            threw = true;
        }
        check(threw, "Исключение при невалидных индексах в GetSubsequence");
    }

    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        MutableArraySequence<int> a(d1, 2);
        MutableArraySequence<int> b(d2, 2);
        Sequence<int> *c = a.Concat(&b);
        check(c->GetLength() == 4, "Конкатенация двух последовательностей работает");
        check(c->Get(0) == 1, "Первый элемент конкатенации корректен");
        check(c->Get(3) == 4, "Последний элемент конкатенации корректен");
        delete c;
    }

    {
        int data[] = {1, 2, 3};
        MutableArraySequence<int> seq(data, 3);
        Sequence<int> *mapped = seq.Map(double_val);
        check(mapped->Get(0) == 2 && mapped->Get(2) == 6, "Функция Map работает корректно");
        delete mapped;
    }

    {
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        Sequence<int> *filtered = seq.Where(is_even);
        check(filtered->GetLength() == 2 && filtered->Get(0) == 2, "Функция Where работает корректно");
        delete filtered;
    }

    {
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Функция Reduce работает корректно");
    }
}

// Тестирование неизменяемой последовательности на основе массива
void test_immutable_array_sequence() {
    cout << "\n--- Тестирование ImmutableArraySequence ---\n";

    {
        ImmutableArraySequence<int> seq;
        check(seq.GetLength() == 0, "Длина пустой последовательности равна 0");
    }

    {
        int data[] = {5, 10, 15};
        ImmutableArraySequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Создание из массива: длина корректна");
        check(seq.Get(0) == 5, "Получение элемента по индексу");
        check(seq.GetFirst() == 5, "Получение первого элемента");
        check(seq.GetLast() == 15, "Получение последнего элемента");
        check(seq[1] == 10, "Перегрузка оператора индексации работает");
    }

    {
        int data[] = {1, 2};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int> *appended = original.Append(3);
        check(original.GetLength() == 2, "Append не изменяет исходную последовательность");
        check(appended->GetLength() == 3, "Append возвращает новую корректную последовательность");
        check(appended->GetLast() == 3, "Последний элемент после Append корректен");
        delete appended;
    }

    {
        int data[] = {2, 3};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int> *prepended = original.Prepend(1);
        check(original.GetLength() == 2, "Prepend не изменяет исходную последовательность");
        check(prepended->GetLength() == 3, "Prepend возвращает новую корректную последовательность");
        check(prepended->GetFirst() == 1, "Первый элемент после Prepend корректен");
        delete prepended;
    }

    {
        int data[] = {1, 3};
        ImmutableArraySequence<int> original(data, 2);
        Sequence<int> *inserted = original.InsertAt(2, 1);
        check(original.GetLength() == 2, "InsertAt не изменяет исходную последовательность");
        check(inserted->Get(1) == 2, "InsertAt возвращает новую корректную последовательность");
        check(inserted->GetLength() == 3, "Длина после вставки корректна");
        delete inserted;
    }

    {
        int data[] = {10, 20, 30, 40};
        ImmutableArraySequence<int> seq(data, 4);
        Sequence<int> *sub = seq.GetSubsequence(1, 2);
        check(sub->GetLength() == 2, "Получение подпоследовательности работает");
        check(sub->Get(0) == 20 && sub->Get(1) == 30, "Элементы подпоследовательности корректны");
        delete sub;
    }

    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        ImmutableArraySequence<int> a(d1, 2);
        ImmutableArraySequence<int> b(d2, 2);
        Sequence<int> *c = a.Concat(&b);
        check(c->GetLength() == 4, "Конкатенация двух последовательностей работает");
        check(c->Get(2) == 3, "Элементы конкатенации корректны");
        delete c;
    }

    {
        int data[] = {3, 6, 9};
        ImmutableArraySequence<int> seq(data, 3);
        Sequence<int> *mapped = seq.Map(double_val);
        check(mapped->Get(0) == 6 && mapped->Get(2) == 18, "Функция Map работает корректно");
        delete mapped;
    }

    {
        int data[] = {1, 2, 3, 4};
        ImmutableArraySequence<int> seq(data, 4);
        Sequence<int> *filtered = seq.Where(is_even);
        check(filtered->GetLength() == 2 && filtered->Get(0) == 2, "Функция Where работает корректно");
        delete filtered;
    }

    {
        int data[] = {10, 20, 30};
        ImmutableArraySequence<int> seq(data, 3);
        int result = seq.Reduce(sum, 0);
        check(result == 60, "Функция Reduce работает корректно");
    }
}

// Тестирование изменяемой последовательности на основе связного списка
void test_mutable_list_sequence() {
    cout << "\n--- Тестирование MutableListSequence ---\n";

    {
        MutableListSequence<int> seq;
        check(seq.GetLength() == 0, "Длина пустой последовательности равна 0");
    }

    {
        int data[] = {7, 14, 21};
        MutableListSequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Создание из массива: длина корректна");
        check(seq.Get(0) == 7, "Получение элемента по индексу");
        check(seq.GetFirst() == 7, "Получение первого элемента");
        check(seq.GetLast() == 21, "Получение последнего элемента");
        check(seq[1] == 14, "Перегрузка оператора индексации работает");
    }

    {
        MutableListSequence<int> seq;
        seq.Append(100);
        seq.Append(200);
        check(seq.GetLength() == 2, "Добавление элементов в конец (Append)");
        check(seq.GetFirst() == 100 && seq.GetLast() == 200, "Элементы после Append корректны");
    }

    {
        MutableListSequence<int> seq;
        seq.Append(2);
        seq.Prepend(1);
        check(seq.GetFirst() == 1, "Добавление элемента в начало (Prepend)");
        check(seq.GetLength() == 2, "Длина после Prepend корректна");
    }

    {
        int data[] = {1, 3};
        MutableListSequence<int> seq(data, 2);
        seq.InsertAt(2, 1);
        check(seq.Get(1) == 2, "Вставка элемента по индексу (InsertAt)");
        check(seq.GetLength() == 3, "Длина после вставки корректна");
    }

    {
        int data[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(data, 5);
        Sequence<int> *sub = seq.GetSubsequence(1, 3);
        check(sub->GetLength() == 3, "Получение подпоследовательности работает");
        check(sub->Get(0) == 20 && sub->Get(2) == 40, "Элементы подпоследовательности корректны");
        delete sub;
    }

    {
        int data[] = {1, 2, 3};
        MutableListSequence<int> seq(data, 3);
        bool threw = false;
        try {
            seq.GetSubsequence(3, 1);
        } catch (const out_of_range &) {
            threw = true;
        }
        check(threw, "Исключение при невалидных индексах в GetSubsequence");
    }

    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        MutableListSequence<int> a(d1, 2);
        MutableListSequence<int> b(d2, 2);
        Sequence<int> *c = a.Concat(&b);
        check(c->GetLength() == 4, "Конкатенация двух последовательностей работает");
        check(c->Get(0) == 1 && c->Get(3) == 4, "Элементы конкатенации корректны");
        delete c;
    }

    {
        int data[] = {5, 10, 15};
        MutableListSequence<int> seq(data, 3);
        Sequence<int> *mapped = seq.Map(double_val);
        check(mapped->Get(0) == 10 && mapped->Get(2) == 30, "Функция Map работает корректно");
        delete mapped;
    }

    {
        int data[] = {1, 2, 3, 4, 5, 6};
        MutableListSequence<int> seq(data, 6);
        Sequence<int> *filtered = seq.Where(is_even);
        check(filtered->GetLength() == 3 && filtered->Get(2) == 6, "Функция Where работает корректно");
        delete filtered;
    }

    {
        int data[] = {1, 2, 3, 4, 5};
        MutableListSequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Функция Reduce работает корректно");
    }
}

// Тестирование неизменяемой последовательности на основе связного списка
void test_immutable_list_sequence() {
    cout << "\n--- Тестирование ImmutableListSequence ---\n";

    {
        ImmutableListSequence<int> seq;
        check(seq.GetLength() == 0, "Длина пустой последовательности равна 0");
    }

    {
        int data[] = {3, 6, 9};
        ImmutableListSequence<int> seq(data, 3);
        check(seq.GetLength() == 3, "Создание из массива: длина корректна");
        check(seq.Get(0) == 3 && seq.GetFirst() == 3 && seq.GetLast() == 9, "Получение элементов работает");
        check(seq[1] == 6, "Перегрузка оператора индексации работает");
    }

    {
        int data[] = {1, 2};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int> *appended = original.Append(3);
        check(original.GetLength() == 2, "Append не изменяет исходную последовательность");
        check(appended->GetLength() == 3 && appended->GetLast() == 3, "Append возвращает корректную новую последовательность");
        delete appended;
    }

    {
        int data[] = {2, 3};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int> *prepended = original.Prepend(1);
        check(original.GetLength() == 2, "Prepend не изменяет исходную последовательность");
        check(prepended->GetLength() == 3 && prepended->GetFirst() == 1, "Prepend возвращает корректную новую последовательность");
        delete prepended;
    }

    {
        int data[] = {1, 3};
        ImmutableListSequence<int> original(data, 2);
        Sequence<int> *inserted = original.InsertAt(2, 1);
        check(original.GetLength() == 2, "InsertAt не изменяет исходную последовательность");
        check(inserted->GetLength() == 3 && inserted->Get(1) == 2, "InsertAt возвращает корректную новую последовательность");
        delete inserted;
    }

    {
        int data[] = {5, 10, 15, 20};
        ImmutableListSequence<int> seq(data, 4);
        Sequence<int> *sub = seq.GetSubsequence(0, 2);
        check(sub->GetLength() == 3 && sub->Get(0) == 5, "Получение подпоследовательности работает");
        delete sub;
    }

    {
        int d1[] = {1, 2};
        int d2[] = {3, 4};
        ImmutableListSequence<int> a(d1, 2);
        ImmutableListSequence<int> b(d2, 2);
        Sequence<int> *c = a.Concat(&b);
        check(c->GetLength() == 4 && c->Get(3) == 4, "Конкатенация двух последовательностей работает");
        delete c;
    }

    {
        int data[] = {1, 2, 3};
        ImmutableListSequence<int> seq(data, 3);
        Sequence<int> *mapped = seq.Map(double_val);
        check(mapped->Get(0) == 2 && mapped->Get(2) == 6, "Функция Map работает корректно");
        delete mapped;
    }

    {
        int data[] = {2, 3, 4, 5, 6};
        ImmutableListSequence<int> seq(data, 5);
        Sequence<int> *filtered = seq.Where(is_even);
        check(filtered->GetLength() == 3 && filtered->Get(0) == 2, "Функция Where работает корректно");
        delete filtered;
    }

    {
        int data[] = {1, 2, 3, 4, 5};
        ImmutableListSequence<int> seq(data, 5);
        int result = seq.Reduce(sum, 0);
        check(result == 15, "Функция Reduce работает корректно");
    }
}

// Запуск всех подготовленных тестов
void run_all_tests() {
    tests_passed = 0;
    tests_failed = 0;

    test_mutable_array_sequence();
    test_immutable_array_sequence();
    test_mutable_list_sequence();
    test_immutable_list_sequence();

    cout << "\n=========================\n";
    cout << "=== Результаты тестов ===\n";
    cout << "Пройдено: " << tests_passed << "\n";
    cout << "Провалено: " << tests_failed << "\n";
    
    if (tests_failed == 0) {
        cout << "Все тесты успешно пройдены!\n";
    } else {
        cout << "Были обнаружены ошибки.\n";
    }
    cout << "=========================\n\n";
}
