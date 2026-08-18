#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n1, n2;
    std::cout << "Введіть кількість елементів першого вектора V1: ";
    if (!(std::cin >> n1) || n1 < 0) return 0;

    std::vector<std::string> V1(n1);
    std::cout << "Введіть елементи вектора V1:\n";
    for (int i = 0; i < n1; ++i) {
        std::cin >> V1[i];
    }

    std::cout << "Введіть кількість елементів другого вектора V2: ";
    if (!(std::cin >> n2) || n2 < 0) return 0;

    std::vector<std::string> V2(n2);
    std::cout << "Введіть елементи вектора V2:\n";
    for (int i = 0; i < n2; ++i) {
        std::cin >> V2[i];
    }

    // 1. Сортуємо вектори за незростанням (спаду) перед застосуванням set_union
    std::sort(V1.begin(), V1.end(), std::greater<std::string>());
    std::sort(V2.begin(), V2.end(), std::greater<std::string>());

    // 2. Об'єднання через std::set_union
    std::vector<std::string> result;
    std::set_union(
        V1.begin(), V1.end(),
        V2.begin(), V2.end(),
        std::back_inserter(result),
        std::greater<std::string>()
    );

    // 3. Вивід результату
    std::cout << "\nРезультат об'єднання (за незростанням):\n";
    for (const auto& s : result) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    return 0;
}