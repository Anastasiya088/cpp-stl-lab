#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string sentence;

    // Якщо речення передано через аргументи командного рядка
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            sentence += argv[i];
            if (i < argc - 1) sentence += " ";
        }
    }
    else {
        std::cout << "Увага: аргумент командного рядка не передано.\n";
        std::cout << "Введіть речення для генерації перестановок слів: ";
        std::getline(std::cin, sentence);
    }

    // Розбиваємо речення на слова
    std::stringstream ss(sentence);
    std::string word;
    std::vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }

    std::cout << "\nПерестановки слів для речення: \"" << sentence << "\"\n";

    // Сортуємо вектор слів для std::next_permutation
    std::sort(words.begin(), words.end());

    int count = 0;
    do {
        std::cout << ++count << ") ";
        for (size_t i = 0; i < words.size(); ++i) {
            std::cout << words[i] << (i + 1 < words.size() ? " " : "");
        }
        std::cout << "\n";
    } while (std::next_permutation(words.begin(), words.end()));

    std::cout << "\nУсього перестановок: " << count << "\n";

    return 0;
}