#include "menu.h"
#include "tests.h"

// Точка входа в программу
int main() {
    // Выполняем автоматические тесты
    run_all_tests();
    
    // Запускаем пользовательское меню
    RunMenu();
    
    return 0;
}
