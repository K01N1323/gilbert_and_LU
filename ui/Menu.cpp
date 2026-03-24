#include <iostream>

#include "BitSequence.cpp"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "menu.h"
#include "tests.h"

using namespace std;

// Умножает число на 10
int MultiplyBy10(const int& x) { 
    return x * 10; 
}

// Проверяет, является ли число четным
bool IsEven(const int& x) { 
    return x % 2 == 0; 
}

// Складывает два числа
int Sum(const int& x, const int& y) { 
    return x + y; 
}

// Функция для красивого вывода последовательности на экран
template <typename T>
void PrintSequence(Sequence<T>* seq) {
    cout << "[ ";
    
    for (int index = 0; index < seq->GetLength(); index++) {
        cout << seq->Get(index) << " ";
    }
    
    cout << "]\n";
}

// Тестирование изменяемой последовательности на основе массива
void TestArraySequence() {
    MutableArraySequence<int>* arr = new MutableArraySequence<int>();
    int choice = -1;
    
    while (choice != 0) {
        cout << "\nMutableArraySequence<int>\n";
        cout << "Текущий массив: ";
        PrintSequence(arr);
        cout << "1. Добавить в конец \n";
        cout << "2. Добавить в начало \n";
        cout << "3. Проверить Map (Умножить все на 10)\n";
        cout << "4. Проверить Where (Оставить только четные)\n";
        cout << "5. Проверить Reduce (Сумма элементов)\n";
        cout << "0. Назад\nВыбор: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int val; 
            cout << "Введи число: "; 
            cin >> val;

            if (choice == 1) {
                arr->Append(val);
            } else {
                arr->Prepend(val);
            }
        } 
        else if (choice == 3) {
            Sequence<int>* mapped = arr->Map(MultiplyBy10);

            cout << "Результат Map: "; 
            PrintSequence(mapped);
            delete mapped;
        } 
        else if (choice == 4) {
            Sequence<int>* filtered = arr->Where(IsEven);
            
            cout << "Результат Where: "; 
            PrintSequence(filtered);
            delete filtered;
        } 
        else if (choice == 5) {
            if (arr->GetLength() == 0) {
                cout << "Массив пуст!\n";
            } else {
                cout << "Сумма (Reduce): " << arr->Reduce(Sum, 0) << "\n";
            }
        }
    }
    
    delete arr;
}

// Тестирование изменяемой последовательности на основе списка
void TestListSequence() {
    MutableListSequence<int>* list = new MutableListSequence<int>();
    int choice = -1;
    
    while (choice != 0) {
        cout << "\nMutableListSequence<int>\n";
        cout << "Текущий список: ";
        PrintSequence(list);
        cout << "1. Добавить в конец (Append)\n";
        cout << "2. Добавить в начало (Prepend)\n";
        cout << "3. Получить подпоследовательность \n";
        cout << "0. Назад\nВыбор: ";
        cin >> choice;

        if (choice == 1) {
            int val; 
            cout << "Введи число: "; 
            cin >> val;

            list->Append(val);
        } else if (choice == 2) {
            int val; 
            cout << "Введи число: "; 
            cin >> val;

            list->Prepend(val);
        } else if (choice == 3) {
            int start, end;
            cout << "Введи start_index: "; 
            cin >> start;
            cout << "Введи end_index: "; 
            cin >> end;
            
            try {
                Sequence<int>* sub = list->GetSubsequence(start, end);
                cout << "Подсписок: "; 
                PrintSequence(sub);
                delete sub;
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        }
    }
    
    delete list;
}

// Тестирование последовательности битов
void TestBitSequence() {
    BitSequence* bits1 = new BitSequence();
    BitSequence* bits2 = new BitSequence();
    
    bits1->Append(1); bits1->Append(0); bits1->Append(1); 
    bits2->Append(1); bits2->Append(1); bits2->Append(0);

    int choice = -1;
    while (choice != 0) {
        cout << "\nBitSequence1\n";
        cout << "Маска 1: "; 
        PrintSequence(bits1);
        cout << "Маска 2: "; 
        PrintSequence(bits2);
        cout << "1. Добавить бит в Маску 1\n";
        cout << "2. Побитовое И (AND)\n";
        cout << "3. Побитовое ИЛИ (OR)\n";
        cout << "4. Инверсия Маски 1 (NOT)\n";
        cout << "0. Назад\nВыбор: ";
        cin >> choice;

        if (choice == 1) {
            int val; 
            cout << "Введи 0 или 1: "; 
            cin >> val;
            
            bits1->Append(val);
        } else if (choice == 2) {
            BitSequence* res = bits1->And(bits2);
            cout << "Результат AND: "; 
            PrintSequence(res);
            delete res;
        } else if (choice == 3) {
            BitSequence* res = bits1->Or(bits2);
            cout << "Результат OR: "; 
            PrintSequence(res);
            delete res;
        } else if (choice == 4) {
            BitSequence* res = bits1->Not();
            cout << "Результат NOT: "; 
            PrintSequence(res);
            delete res;
        }
    }
    
    delete bits1; 
    delete bits2;
}

// Запуск главного меню программы
void RunMenu() {
    int main_choice = -1;
    
    while (main_choice != 0) {
        cout << "\nГЛАВНОЕ МЕНЮ\n";
        cout << "1. Тестирование MutableArraySequence\n";
        cout << "2. Тестирование MutableListSequence\n";
        cout << "3. Тестирование BitSequence\n";
        cout << "4. Запустить все автотесты\n";
        cout << "0. Выход из программы\n";
        cout << "\n";
        cout << "Введи номер пункта: ";
        cin >> main_choice;

        switch (main_choice) {
            case 1: 
                TestArraySequence(); 
                break;
            case 2: 
                TestListSequence(); 
                break;
            case 3: 
                TestBitSequence(); 
                break;
            case 4: 
                run_all_tests(); 
                break;
            case 0: 
                break;
            default: 
                cout << "Неверный ввод!\n";
        }
    }
}