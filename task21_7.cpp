#define NOMINMAX
#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string word;

    // Якщо слово передане через аргументи командного рядка — використовуємо його,
    // інакше запитуємо з консолі
    if (argc > 1) {
        word = argv[1];
    }
    else {
        std::cout << "Увага: аргумент командного рядка не передано.\n";
        std::cout << "Введіть слово для генерації анаграм: ";
        std::cin >> word;
    }

    std::cout << "\nАнаграми для слова \"" << word << "\":\n";

    // Для генерації ВСІХ перестановок слово має бути відсортоване
    std::sort(word.begin(), word.end());

    int count = 0;
    do {
        std::cout << ++count << ") " << word << "\n";
    } while (std::next_permutation(word.begin(), word.end()));

    std::cout << "\nУсього анаграм: " << count << "\n";

    return 0;
}