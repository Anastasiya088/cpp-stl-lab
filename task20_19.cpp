#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

struct Record {
    int client_code;
    int year;
    int month;
    int hours;
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const std::string filename = "data19.txt";

    // 1. Створюємо тестовий файл
    {
        std::ofstream out(filename);
        out << "101 2023 5 12\n";
        out << "102 2023 6 8\n";
        out << "103 2024 1 8\n";
        out << "104 2024 2 15\n";
        out.close();
        std::cout << "Тестовий файл " << filename << " створено.\n\n";
    }

    // 2. Зчитуємо дані з файлу
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Помилка відкриття файлу!\n";
        return 1;
    }

    std::vector<Record> records;
    Record rec;
    while (in >> rec.client_code >> rec.year >> rec.month >> rec.hours) {
        records.push_back(rec);
    }
    in.close();

    if (records.empty()) {
        std::cout << "Файл порожній.\n";
        return 0;
    }

    // 3. Знаходимо мінімальну тривалість занять за допомогою std::min_element
    auto min_it = std::min_element(records.begin(), records.end(),
        [](const Record& a, const Record& b) {
            return a.hours < b.hours;
        });

    int min_hours = min_it->hours;

    // 4. Виводимо всі записи, що мають мінімальну тривалість
    std::cout << "Елементи з мінімальною тривалістю занять (" << min_hours << " год):\n";
    std::cout << "<Кількість занять> <Рік> <Номер місяця>\n";

    for (const auto& r : records) {
        if (r.hours == min_hours) {
            std::cout << r.hours << " " << r.year << " " << r.month << "\n";
        }
    }

    return 0;
}