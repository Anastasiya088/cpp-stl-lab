#define NOMINMAX
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string text = "Hello, World! C++ STL Algorithms.";

    std::cout << "Початковий рядок: " << text << "\n";

    // Один виклик std::transform для перетворення всіх літер на великі
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return std::toupper(c);
        });

    std::cout << "Результат:         " << text << "\n";

    return 0;
}