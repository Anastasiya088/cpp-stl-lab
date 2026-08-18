#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <map>
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

    std::multimap<char, std::string> M;

    // Заповнення multimap
    for (const auto& word : V) {
        // Якщо слово має довжину > 1, беремо другу літеру (індекс 1), інакше першу (індекс 0)
        char key = (word.length() > 1) ? word[1] : word[0];
        M.insert({ key, word });
    }

    std::cout << "\nРезультат (Ключ - Слово):\n";
    for (const auto& [key, value] : M) {
        std::cout << key << ": " << value << "\n";
    }

    return 0;
}