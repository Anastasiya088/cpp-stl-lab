#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <cstring>
#include <windows.h>

// Фіксована структура для збереження у бінарному файлі
struct StudentRecord {
    char surname[50];
    char initials[10];
    int grade_class;
    char subject[50];
    int score;
};

// Структура для обчислення сум оцінок та їх кількості
struct SubjectStats {
    int algebra_sum = 0, algebra_count = 0;
    int geometry_sum = 0, geometry_count = 0;
    int info_sum = 0, info_count = 0;
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const std::string filename = "data20.bin";

    // 1. Створення тестового бінарного файлу
    {
        std::ofstream out(filename, std::ios::binary);
        if (out.is_open()) {
            StudentRecord records[] = {
                {"Ivanov", "I.I.", 10, "Алгебра", 10},
                {"Ivanov", "I.I.", 10, "Алгебра", 12},
                {"Ivanov", "I.I.", 10, "Геометрія", 8},
                {"Petrov", "P.P.", 11, "Інформатика", 11},
                {"Petrov", "P.P.", 11, "Інформатика", 9},
                {"Sidorov", "S.S.", 9, "Алгебра", 7}
            };

            for (const auto& rec : records) {
                out.write(reinterpret_cast<const char*>(&rec), sizeof(StudentRecord));
            }
            out.close();
            std::cout << "Тестовий бінарний файл " << filename << " створено.\n\n";
        }
    }

    // 2. Зчитування даних із бінарного файлу
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Помилка відкриття файлу!\n";
        return 1;
    }

    // Ключ: pair<Прізвище, Ініціали> — забезпечує автоматичне сортування за алфавітом
    std::map<std::pair<std::string, std::string>, SubjectStats> student_map;

    StudentRecord rec;
    while (in.read(reinterpret_cast<char*>(&rec), sizeof(StudentRecord))) {
        std::string surname = rec.surname;
        std::string initials = rec.initials;
        std::string subj = rec.subject;

        auto key = std::make_pair(surname, initials);
        auto& stats = student_map[key];

        if (subj == "Алгебра") {
            stats.algebra_sum += rec.score;
            stats.algebra_count++;
        }
        else if (subj == "Геометрія") {
            stats.geometry_sum += rec.score;
            stats.geometry_count++;
        }
        else if (subj == "Інформатика") {
            stats.info_sum += rec.score;
            stats.info_count++;
        }
    }
    in.close();

    // 3. Форматований вивід результатів
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Результати оцінювання (Алгебра, Геометрія, Інформатика):\n\n";

    for (const auto& [student, stats] : student_map) {
        double avg_alg = (stats.algebra_count > 0) ? static_cast<double>(stats.algebra_sum) / stats.algebra_count : 0.0;
        double avg_geo = (stats.geometry_count > 0) ? static_cast<double>(stats.geometry_sum) / stats.geometry_count : 0.0;
        double avg_inf = (stats.info_count > 0) ? static_cast<double>(stats.info_sum) / stats.info_count : 0.0;

        std::cout << student.first << " " << student.second << " "
            << avg_alg << " " << avg_geo << " " << avg_inf << "\n";
    }

    return 0;
}