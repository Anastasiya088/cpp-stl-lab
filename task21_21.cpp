#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const size_t N = 1'000'000;
    const size_t K = 100; // Потрібно знайти 100 найменших елементів

    std::vector<int> data(N);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 10'000'000);
    for (size_t i = 0; i < N; ++i) data[i] = dist(rng);

    auto v1 = data, v2 = data, v3 = data;

    // 1. Тест std::sort
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v1.begin(), v1.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> t_sort = end - start;

    // 2. Тест std::partial_sort (перші K)
    start = std::chrono::high_resolution_clock::now();
    std::partial_sort(v2.begin(), v2.begin() + K, v2.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> t_partial = end - start;

    // 3. Тест std::nth_element
    start = std::chrono::high_resolution_clock::now();
    std::nth_element(v3.begin(), v3.begin() + K, v3.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> t_nth = end - start;

    std::cout << "=== Порівняння продуктивності (" << N << " елементів, K = " << K << ") ===\n";
    std::cout << "1. std::sort          : " << t_sort.count() << " ms\n";
    std::cout << "2. std::partial_sort  : " << t_partial.count() << " ms\n";
    std::cout << "3. std::nth_element   : " << t_nth.count() << " ms\n";

    std::cout << "\nВисновок: Використання 'слабких' сортувань (partial_sort, nth_element) "
        << "суттєво прискорює виконання, якщо нам не потрібен повний порядок усередині всього масиву.\n";

    return 0;
}