#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

struct Person {
    std::string lastName;
    int age;
};

void printList(const std::vector<Person>& people, const std::string& title) {
    std::cout << title << ":\n";
    for (const auto& p : people) {
        std::cout << "  - " << p.lastName << ", вік: " << p.age << "\n";
    }
    std::cout << "\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Зразок списку людей (прізвище, вік)
    std::vector<Person> people = {
        {"Шевченко", 28},
        {"Коваленко", 42},
        {"Бондаренко", 19},
        {"Мельник", 35},
        {"Ткаченко", 31},
        {"Кравченко", 50},
        {"Олійник", 24},
        {"Бойко", 38}
    };

    printList(people, "Початковий список");

    // 1. Розділяємо вектор: ті, кому < 35 років — на початок
    auto it = std::stable_partition(people.begin(), people.end(), [](const Person& p) {
        return p.age < 35;
        });

    // 2. Сортуємо першу частину (< 35 років) від наймолодшого до найстаршого
    std::sort(people.begin(), it, [](const Person& a, const Person& b) {
        return a.age < b.age;
        });

    // 3. Сортуємо другу частину (>= 35 років) за прізвищем за алфавітом
    std::sort(it, people.end(), [](const Person& a, const Person& b) {
        return a.lastName < b.lastName;
        });

    printList(people, "Оброблений список (перша частина <35 за віком, друга >=35 за прізвищем)");

    return 0;
}