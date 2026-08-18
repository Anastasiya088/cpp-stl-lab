#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const std::string filename = "data13.txt";

    // Створюємо тестовий текстовий файл для перевірки
    {
        std::ofstream out(filename);
        out << "10 5 20 5 30 15 30 2";
        out.close();
        std::cout << "Файл " << filename << " з елементами (10 5 20 5 30 15 30 2) створено.\n\n";
    }

    // --- Варіант 1: З використанням допоміжної множини (std::set) ---
    {
        std::ifstream in(filename);
        if (!in.is_open()) return 1;

        // Використовуємо greater<int>, щоб множина одразу сортувала за спаданням
        std::set<int, std::greater<int>> unique_set;
        int num;
        while (in >> num) {
            unique_set.insert(num);
        }
        in.close();

        std::cout << "--- Спосіб 1 (з допоміжною множиною std::set) ---\n";
        if (unique_set.size() >= 3) {
            // Видаляємо максимальний (перший) та мінімальний (останній)
            unique_set.erase(unique_set.begin());
            unique_set.erase(--unique_set.end());

            for (int val : unique_set) {
                std::cout << val << " ";
            }
            std::cout << "\n\n";
        }
        else {
            std::cout << "У файлі менше ніж 3 різні числа.\n\n";
        }
    }

    // --- Варіант 2: Без використання допоміжної множини (лише std::vector) ---
    {
        std::ifstream in(filename);
        if (!in.is_open()) return 1;

        std::vector<int> V;
        int num;
        while (in >> num) {
            V.push_back(num);
        }
        in.close();

        // 1. Сортуємо за спаданням
        std::sort(V.begin(), V.end(), std::greater<int>());

        // 2. Видаляємо повторення
        auto last = std::unique(V.begin(), V.end());
        V.erase(last, V.end());

        std::cout << "--- Спосіб 2 (без допоміжної множини) ---\n";
        if (V.size() >= 3) {
            // Видаляємо перший (максимальний) та останній (мінімальний)
            V.erase(V.begin());
            V.pop_back();

            for (int val : V) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "У файлі менше ніж 3 різні числа.\n";
        }
    }

    return 0;
}