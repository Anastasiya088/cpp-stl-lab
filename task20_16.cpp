#define NOMINMAX
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    std::cout << "Введіть кількість елементів вектора V: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<int> V(n);
    std::cout << "Введіть " << n << " цілих чисел:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> V[i];
    }

    std::map<int, std::vector<int>> M;

    // Групування за останньою цифрою (std::abs використовуємо для від'ємних чисел)
    for (int num : V) {
        int last_digit = std::abs(num) % 10;
        M[last_digit].push_back(num);
    }

    std::cout << "\nРезультат групування:\n";
    for (const auto& [digit, group] : M) {
        std::cout << digit << ": ";
        for (size_t i = 0; i < group.size(); ++i) {
            std::cout << group[i];
            if (i + 1 < group.size()) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}