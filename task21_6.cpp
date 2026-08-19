#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

// Шаблонний функціональний об'єкт для накопичення суми
template <typename T>
struct Sum {
    T total;

    // Конструктор за замовчуванням
    Sum() : total(T()) {}

    // Перевантажений оператор () для сумування елементів
    void operator()(const T& value) {
        total += value;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Тестування з цілими числами (int)
    std::vector<int> intVec = { 10, 20, 30, 40, 50 };
    Sum<int> intSum = std::for_each(intVec.begin(), intVec.end(), Sum<int>());

    std::cout << "Елементи int: ";
    for (int x : intVec) std::cout << x << " ";
    std::cout << "\nСума int: " << intSum.total << "\n\n";

    // 2. Тестування з дійсними числами (double)
    std::vector<double> doubleVec = { 1.5, 2.3, 3.7, 4.1 };
    Sum<double> doubleSum = std::for_each(doubleVec.begin(), doubleVec.end(), Sum<double>());

    std::cout << "Елементи double: ";
    for (double x : doubleVec) std::cout << x << " ";
    std::cout << "\nСума double: " << doubleSum.total << "\n";

    return 0;
}