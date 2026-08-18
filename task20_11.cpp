#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::string name;
    std::cout << "Введіть ім'я файлу (name): ";
    std::cin >> name;

    int n;
    std::cout << "Введіть парну кількість елементів вектора V: ";
    if (!(std::cin >> n) || n <= 0 || n % 2 != 0) {
        std::cout << "Кількість елементів повинна бути додатним парним числом.\n";
        return 0;
    }

    std::vector<int> V(n);
    std::cout << "Введіть " << n << " чисел вектора V: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> V[i];
    }

    // 1. Розділення вектору на дві рівні частини
    size_t half = V.size() / 2;
    std::vector<int> first_half(V.begin(), V.begin() + half);
    std::vector<int> second_half(V.begin() + half, V.end());

    // 2. Створення впорядкованих множин унікальних елементів для кожної половини
    std::set<int> set1(first_half.begin(), first_half.end());
    std::set<int> set2(second_half.begin(), second_half.end());

    // 3. Знаходження елементів з другої половини, яких немає в першій (set_difference)
    // Алгоритм set_difference(set2 - set1) автоматично зберігає результат за зростанням
    std::vector<int> result;
    std::set_difference(
        set2.begin(), set2.end(),
        set1.begin(), set1.end(),
        std::back_inserter(result)
    );

    // 4. Запис у файл, кожне число на новому рядку
    std::ofstream outFile(name);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття файлу для запису!\n";
        return 1;
    }

    for (int num : result) {
        outFile << num << "\n";
    }
    outFile.close();

    std::cout << "\nРезультат успішно збережено у файл " << name << std::endl;

    return 0;
}