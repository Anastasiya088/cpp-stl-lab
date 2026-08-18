#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    std::cout << "Введіть кількість слів у векторі V: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<std::string> V(n);
    std::cout << "Введіть " << n << " англійських слів:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> V[i];
    }

    std::map<char, int> M;             // Ключ: літера, Значення: кількість слів
    std::map<char, size_t> lengthMap;  // Ключ: літера, Значення: сумарна довжина слів

    // Заповнення без умовних конструкцій (if)
    for (const auto& word : V) {
        char first_letter = static_cast<char>(std::tolower(static_cast<unsigned char>(word[0])));

        M[first_letter]++;                 // Збільшуємо кількість
        lengthMap[first_letter] += word.length(); // Додаємо довжину
    }

    std::cout << "\nРезультат (Літера, сумарна довжина, кількість слів):\n";
    for (const auto& [letter, count] : M) {
        std::cout << letter << " " << lengthMap[letter] << " (кількість: " << count << ")\n";
    }

    return 0;
}