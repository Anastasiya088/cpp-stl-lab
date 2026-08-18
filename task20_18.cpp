#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <windows.h>

// Функція для отримання першої значущої цифри числа
int getFirstDigit(double num) {
    std::string str = std::to_string(std::abs(num));
    for (char ch : str) {
        if (ch >= '1' && ch <= '9') {
            return ch - '0';
        }
    }
    return 0; // Для 0.0
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    std::cout << "Введіть кількість елементів вектора V: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<double> V(n);
    std::cout << "Введіть " << n << " дійсних чисел:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> V[i];
    }

    // 1. Групування елементів за початковою цифрою
    std::map<int, std::vector<double>> groups;
    for (double num : V) {
        int digit = getFirstDigit(num);
        groups[digit].push_back(num);
    }

    // 2. Обчислення сум без першого елемента
    std::vector<std::pair<int, double>> result;
    for (const auto& [digit, vec] : groups) {
        double sum = 0.0;
        // Додаємо елементи починаючи з другого (індекс 1)
        for (size_t i = 1; i < vec.size(); ++i) {
            sum += vec[i];
        }
        result.push_back({ digit, sum });
    }

    // 3. Сортування: по зростанню цифр, а потім по зростанню сум
    std::sort(result.begin(), result.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second < b.second;
        });

    // 4. Вивід результату
    std::cout << "\nРезультат (Цифра - Сума):\n";
    for (const auto& p : result) {
        std::cout << "Цифра " << p.first << ": сума = " << p.second << "\n";
    }

    return 0;
}