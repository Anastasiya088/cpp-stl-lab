#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string NameT, NameS;
    std::cout << "Введіть ім'я вхідного файлу (NameT, наприклад, input14.txt): ";
    std::cin >> NameT;
    std::cout << "Введіть ім'я вихідного файлу (NameS, наприклад, output14.txt): ";
    std::cin >> NameS;

    // Створюємо тестовий файл для перевірки
    {
        std::ofstream testFile(NameT);
        testFile << "Hello, world! Program test: aaa bbb cc d.";
        testFile.close();
        std::cout << "Тестовий файл " << NameT << " створено.\n\n";
    }

    // 1. Зчитуємо файл та підраховуємо малі латинські літери
    std::ifstream inFile(NameT);
    if (!inFile.is_open()) {
        std::cerr << "Помилка відкриття вхідного файлу!\n";
        return 1;
    }

    std::map<char, int> freq;
    char ch;
    while (inFile.get(ch)) {
        if (ch >= 'a' && ch <= 'z') {
            freq[ch]++;
        }
    }
    inFile.close();

    // 2. Переносимо дані у вектор для сортування за власним правилом
    std::vector<std::pair<char, int>> vec(freq.begin(), freq.end());

    // 3. Сортування:
    // - за спаданням кількості повторень
    // - при однаковій кількості — за зростанням коду літери
    std::sort(vec.begin(), vec.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second; // за спаданням частоти
        }
        return a.first < b.first;       // за зростанням коду
        });

    // 4. Запис у вихідний файл NameS
    std::ofstream outFile(NameS);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття вихідного файлу!\n";
        return 1;
    }

    for (const auto& p : vec) {
        outFile << p.first << " - " << p.second << "\n";
    }
    outFile.close();

    std::cout << "Результат обробки успішно збережено у файл " << NameS << std::endl;

    return 0;
}