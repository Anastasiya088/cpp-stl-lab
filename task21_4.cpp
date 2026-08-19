#define NOMINMAX
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <windows.h>

// 1. Функтор-генератор для отримання значення clock()
struct ClockGenerator {
    clock_t operator()() const {
        return clock();
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::list<clock_t> clock_list;
    const size_t count = 10;

    // 2. Заповнення списку за допомогою генератора та std::generate_n
    std::generate_n(std::back_inserter(clock_list), count, ClockGenerator());

    std::cout << "Початковий список значень clock():\n";
    std::copy(clock_list.begin(), clock_list.end(), std::ostream_iterator<clock_t>(std::cout, " "));
    std::cout << "\n\n";

    // 3. Видалення дублікатів
    // Для std::list::unique список повинен бути попередньо відсортований
    clock_list.sort();
    clock_list.unique();

    std::cout << "Список після видалення дублікатів (за допомогою std::copy):\n";
    std::copy(clock_list.begin(), clock_list.end(), std::ostream_iterator<clock_t>(std::cout, " "));
    std::cout << "\n";

    return 0;
}