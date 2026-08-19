#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <windows.h>

// Допоміжна функція для зчитування слів з файлу в відсортовану множину std::set
std::set<std::string> readWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::set<std::string> words;
    std::string word;
    while (file >> word) {
        words.insert(word);
    }
    return words;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо два тестові файли
    std::ofstream f1("file1.txt");
    f1 << "apple banana cherry date elderberry";
    f1.close();

    std::ofstream f2("file2.txt");
    f2 << "banana date fig grape elderberry";
    f2.close();

    // 2. Зчитуємо слова у впорядковані множини
    std::set<std::string> set1 = readWordsFromFile("file1.txt");
    std::set<std::string> set2 = readWordsFromFile("file2.txt");

    // 3. Пошук спільних слів через std::set_intersection
    std::vector<std::string> intersection_result;
    std::set_intersection(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(intersection_result)
    );

    std::cout << "Спільні слова (std::set_intersection):\n";
    for (const auto& w : intersection_result) {
        std::cout << "  - " << w << "\n";
    }

    // 4. Пошук неспільних слів через std::set_symmetric_difference
    std::vector<std::string> diff_result;
    std::set_symmetric_difference(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(diff_result)
    );

    std::cout << "\nНеспільні слова (std::set_symmetric_difference):\n";
    for (const auto& w : diff_result) {
        std::cout << "  - " << w << "\n";
    }

    return 0;
}