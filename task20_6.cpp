#define NOMINMAX
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <windows.h>

// Функція для очищення слова від розділових знаків по краях
std::string cleanWord(const std::string& word) {
    size_t start = 0;
    while (start < word.length() && std::ispunct(static_cast<unsigned char>(word[start]))) {
        start++;
    }
    if (start == word.length()) return "";

    size_t end = word.length() - 1;
    while (end > start && std::ispunct(static_cast<unsigned char>(word[end]))) {
        end--;
    }
    return word.substr(start, end - start + 1);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string text;
    int target_count;

    std::cout << "Введіть речення: ";
    std::getline(std::cin, text);

    std::cout << "Введіть кількість разів (K) для видалення слів: ";
    if (!(std::cin >> target_count) || target_count <= 0) {
        std::cout << "Некоректна кількість.\n";
        return 0;
    }

    // 1. Рахуємо частоту кожного слова
    std::stringstream ss1(text);
    std::string word;
    std::map<std::string, int> freq;

    while (ss1 >> word) {
        std::string cleaned = cleanWord(word);
        if (!cleaned.empty()) {
            freq[cleaned]++;
        }
    }

    // 2. Формуємо відредаговане речення
    std::stringstream ss2(text);
    std::string result = "";
    bool first = true;

    while (ss2 >> word) {
        std::string cleaned = cleanWord(word);
        if (cleaned.empty() || freq[cleaned] != target_count) {
            if (!first) result += " ";
            result += word;
            first = false;
        }
    }

    std::cout << "\nВідредаговане речення:\n" << result << std::endl;

    return 0;
}