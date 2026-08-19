#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <windows.h>

// а) Сума k найбільших чисел
int sumOfKMax(std::vector<int> vec, size_t k) {
    // Якщо k перевищує розмір вектору або дорівнює 0 — повертаємо 0
    if (k > vec.size() || k == 0) {
        return 0;
    }

    // Переставляємо елементи так, щоб перші k елементів були найбільшими (за допомогою std::greater)
    std::nth_element(vec.begin(), vec.begin() + k, vec.end(), std::greater<int>());

    // Рахуємо суму перших k елементів
    return std::accumulate(vec.begin(), vec.begin() + k, 0);
}

// б) Масив з k найменших чисел
std::vector<int> getKMin(std::vector<int> vec, size_t k) {
    // Якщо k перевищує розмір вектору або дорівнює 0 — повертаємо порожній вектор
    if (k > vec.size() || k == 0) {
        return {};
    }

    // Частково сортуємо масив, щоб у перших k позиціях були найменші елементи за зростанням
    std::partial_sort(vec.begin(), vec.begin() + k, vec.end());

    // Повертаємо підвектор із перших k елементів
    return std::vector<int>(vec.begin(), vec.begin() + k);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::vector<int> data = { 12, 3, 45, 7, 19, 8, 2, 33 };

    std::cout << "Початковий масив: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n\n";

    // Тест 1: Корректне значення k
    size_t k1 = 3;
    std::cout << "=== Тест 1 (k = " << k1 << ") ===\n";
    std::cout << "а) Сума " << k1 << " найбільших чисел: " << sumOfKMax(data, k1) << "\n";

    auto minArr1 = getKMin(data, k1);
    std::cout << "б) " << k1 << " найменших чисел: ";
    for (int x : minArr1) std::cout << x << " ";
    std::cout << "\n\n";

    // Тест 2: k перевищує розмір масиву
    size_t k2 = 15;
    std::cout << "=== Тест 2 (k = " << k2 << ", де k > size) ===\n";
    std::cout << "а) Сума: " << sumOfKMax(data, k2) << " (очікується 0)\n";

    auto minArr2 = getKMin(data, k2);
    std::cout << "б) Розмір результату: " << minArr2.size() << " (порожній масив)\n";

    return 0;
}