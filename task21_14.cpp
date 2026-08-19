#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>
#include <windows.h>

const std::vector<std::string> MONTH_NAMES = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Функція для визначення номера місяця (1-12) з числа або рядка
int parseMonth(const std::string& str) {
    if (std::isdigit(str[0])) {
        return std::stoi(str);
    }
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);

    for (int i = 0; i < 12; ++i) {
        std::string mName = MONTH_NAMES[i];
        std::transform(mName.begin(), mName.end(), mName.begin(), ::tolower);
        if (mName.find(lowerStr) == 0 || lowerStr.find(mName.substr(0, 3)) == 0) {
            return i + 1;
        }
    }
    return 1;
}

struct Date14 {
    int day;
    int month;
    int year;

    bool operator==(const Date14& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо вхідний файл dates14.txt з тестовими даними
    std::ofstream outFile("dates14.txt");
    outFile << "15 May 2023, 01 Jan 2021, 15 May 2023, 10 12 2019, 05 August 2020";
    outFile.close();

    // 2. Зчитуємо дати з файлу
    std::ifstream inFile("dates14.txt");
    if (!inFile) {
        std::cerr << "Помилка відкриття файлу dates14.txt\n";
        return 1;
    }

    std::vector<Date14> dates;
    int d, y;
    std::string mStr;
    char sep;

    while (inFile >> d >> mStr >> y) {
        int m = parseMonth(mStr);
        dates.push_back({ d, m, y });
        inFile >> sep; // зчитуємо кому між датами
    }
    inFile.close();

    // 3. Сортуємо дати за зростанням
    std::sort(dates.begin(), dates.end(), [](const Date14& a, const Date14& b) {
        if (a.year != b.year) return a.year < b.year;
        if (a.month != b.month) return a.month < b.month;
        return a.day < b.day;
        });

    // 4. Видаляємо дублікати
    auto last = std::unique(dates.begin(), dates.end());
    dates.erase(last, dates.end());

    // 5. Записуємо результат у файл sorted_dates14.txt та виводимо в консоль
    std::ofstream resultFile("sorted_dates14.txt");
    std::cout << "Дати без повторень за зростанням (формат: рік/місяць/число):\n";

    for (size_t i = 0; i < dates.size(); ++i) {
        std::string formatted = std::to_string(dates[i].year) + "/" +
            MONTH_NAMES[dates[i].month - 1] + "/" +
            (dates[i].day < 10 ? "0" : "") + std::to_string(dates[i].day);

        std::cout << "  - " << formatted << "\n";
        resultFile << formatted << (i + 1 < dates.size() ? ", " : "");
    }
    resultFile.close();

    std::cout << "\nРезультати успішно збережено у файл sorted_dates14.txt\n";

    return 0;
}