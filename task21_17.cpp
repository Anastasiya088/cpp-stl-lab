#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

// Перевантажена версія for_each для двох діапазонів
template <typename InputIterator1, typename InputIterator2, typename BinaryFunction>
BinaryFunction for_each(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, BinaryFunction f) {
    while (first1 != last1) {
        f(*first1, *first2);
        ++first1;
        ++first2;
    }
    return f;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::vector<std::string> names = { "Анастасія", "Олександр", "Марія" };
    std::vector<int> scores = { 95, 88, 100 };

    std::cout << "Результати роботи двоаргументного for_each:\n";

    // Двійкова функція приймає об'єкт з першого діапазону та відповідний об'єкт з другого
    for_each(names.begin(), names.end(), scores.begin(), [](const std::string& name, int score) {
        std::cout << "  - Студент: " << name << " | Бали: " << score << "\n";
        });

    return 0;
}