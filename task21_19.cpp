#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Генерація випадкових чисел у масив (вектор)
    const size_t N = 10;
    std::vector<int> arr(N);
    std::mt19937 rng(42); // Фіксований seed для відтворюваності
    std::uniform_int_distribution<int> dist(1, 100);

    for (size_t i = 0; i < N; ++i) {
        arr[i] = dist(rng);
    }

    std::cout << "Початковий масив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n\n";

    // 2. Сортування виділенням (Selection Sort) з використанням std::max_element
    // На кожному кроці шукаємо максимум у діапазоні [arr.begin(), endIt) та міняємо його з елементом у *(endIt - 1)
    for (auto endIt = arr.end(); endIt != arr.begin(); --endIt) {
        auto maxIt = std::max_element(arr.begin(), endIt);
        std::iter_swap(maxIt, endIt - 1);
    }

    std::cout << "Відсортований масив (Selection Sort): ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}