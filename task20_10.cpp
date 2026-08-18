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

    std::string filename;
    std::cout << "Введіть ім'я файлу для запису (наприклад, output10.txt): ";
    std::cin >> filename;

    int n;
    std::cout << "Введіть кількість елементів вектора V: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Некоректна кількість елементів.\n";
        return 0;
    }

    std::vector<int> V(n);
    std::cout << "Введіть " << n << " чисел вектора V: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> V[i];
    }

    // 1. Поділ вектора на дві половини
    size_t half = V.size() / 2;
    std::vector<int> first_half(V.begin(), V.begin() + half);
    std::vector<int> second_half(V.begin() + half, V.end());

    // 2. Створення впорядкованих множин для алгоритму set_intersection
    std::set<int> set1(first_half.begin(), first_half.end());
    std::set<int> set2(second_half.begin(), second_half.end());

    std::vector<int> common_nums;
    std::set_intersection(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(common_nums)
    );

    // 3. Збереження порядку відносно початкового вектора V та виключення дублікатів
    std::vector<int> result;
    std::set<int> added;
    for (int num : V) {
        if (std::find(common_nums.begin(), common_nums.end(), num) != common_nums.end() && !added.count(num)) {
            result.push_back(num);
            added.insert(num);
        }
    }

    // 4. Запис у файл з додаванням пробілу після кожного числа
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Помилка відкриття файлу для запису!\n";
        return 1;
    }

    for (int num : result) {
        outFile << num << " ";
    }
    outFile.close();

    std::cout << "\nРезультат успішно збережено у файл " << filename << std::endl;

    return 0;
}