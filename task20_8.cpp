#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <windows.h>

// Функція для очищення слова від розділових знаків та зведення до нижнього регістру
std::string cleanAndLowercase(const std::string& word) {
    std::string result = "";
    for (char ch : word) {
        if (!std::ispunct(static_cast<unsigned char>(ch))) {
            result += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return result;
}

// Читання слів з файла у впорядковану множину (std::set)
std::set<std::string> readWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::set<std::string> words;
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return words;
    }
    std::string word;
    while (file >> word) {
        std::string cleaned = cleanAndLowercase(word);
        if (!cleaned.empty()) {
            words.insert(cleaned);
        }
    }
    file.close();
    return words;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Створюємо два тестові файли прямо з програми для зручності перевірки
    std::ofstream f1("file1.txt");
    f1 << "apple banana cherry date";
    f1.close();

    std::ofstream f2("file2.txt");
    f2 << "banana date elderberry fig";
    f2.close();

    std::cout << "Файли file1.txt та file2.txt створено для тестування.\n\n";

    // 1. Зчитуємо слова з обох файлів
    std::set<std::string> set1 = readWordsFromFile("file1.txt");
    std::set<std::string> set2 = readWordsFromFile("file2.txt");

    // 2. Пошук спільних слів через std::set_intersection
    std::vector<std::string> common_words;
    std::set_intersection(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(common_words)
    );

    std::cout << "--- Спільні слова (set_intersection) ---\n";
    for (const auto& w : common_words) {
        std::cout << w << " ";
    }
    std::cout << "\n\n";

    // 3. Пошук неспільних слів через std::set_symmetric_difference
    std::vector<std::string> unique_words;
    std::set_symmetric_difference(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(unique_words)
    );

    std::cout << "--- Неспільні слова (set_symmetric_difference) ---\n";
    for (const auto& w : unique_words) {
        std::cout << w << " ";
    }
    std::cout << std::endl;

    return 0;
}