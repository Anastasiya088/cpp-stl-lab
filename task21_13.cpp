#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

struct Date {
    int day, month, year;

    // Отримання повного року для порівняння (1951-2049)
    int fullYear() const {
        return (year >= 51 && year <= 99) ? (1900 + year) : (2000 + year);
    }

    // Оператор для видалення дублікатів через std::unique / std::sort
    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо вхідний файл dates.txt з тестовими даними
    std::ofstream outFile("dates.txt");
    outFile << "15/05/23, 01/01/99, 15/05/23, 10/12/55, 05/08/04, 10/12/55, 20/02/48";
    outFile.close();

    // 2. Зчитуємо дати з файлу
    std::ifstream inFile("dates.txt");
    if (!inFile) {
        std::cerr << "Помилка відкриття файлу dates.txt\n";
        return 1;
    }

    std::vector<Date> dates;
    int d, m, y;
    char s1, s2, sep;

    // Формат зчитування: чч/мм/рр
    while (inFile >> d >> s1 >> m >> s2 >> y) {
        dates.push_back({ d, m, y });
        inFile >> sep; // зчитуємо кому між датами
    }
    inFile.close();

    // 3. Сортуємо дати за спаданням
    std::sort(dates.begin(), dates.end(), [](const Date& a, const Date& b) {
        if (a.fullYear() != b.fullYear()) return a.fullYear() > b.fullYear();
        if (a.month != b.month) return a.month > b.month;
        return a.day > b.day;
        });

    // 4. Видаляємо повторення (дублікати)
    auto last = std::unique(dates.begin(), dates.end());
    dates.erase(last, dates.end());

    // 5. Записуємо результат у файл sorted_dates.txt
    std::ofstream resultFile("sorted_dates.txt");
    std::cout << "Дати без повторень за спаданням:\n";

    for (size_t i = 0; i < dates.size(); ++i) {
        char buf[30];
        snprintf(buf, sizeof(buf), "%02d/%02d/%02d", dates[i].day, dates[i].month, dates[i].year);

        std::cout << "  - " << buf << " (Повний рік: " << dates[i].fullYear() << ")\n";
        resultFile << buf << (i + 1 < dates.size() ? ", " : "");
    }
    resultFile.close();

    std::cout << "\nРезультати успішно збережено у файл sorted_dates.txt\n";

    return 0;
}