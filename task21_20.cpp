#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <windows.h>

struct Contact {
    std::string lastName;
    std::string firstName;
    std::string prefix;
    std::string number;
    std::string oldPrefix; // Зберігаємо старий префікс, якщо змінювали

    // Оператор порівняння: спочатку за прізвищем, потім за іменем
    bool operator<(const Contact& other) const {
        if (lastName != other.lastName)
            return lastName < other.lastName;
        return firstName < other.firstName;
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо вхідний файл phonebook.txt з тестовими даними
    std::ofstream outFile("phonebook.txt");
    outFile << "Petrov Petro 253 2619\n";
    outFile << "Ivanov Ivan 222 8945\n";
    outFile << "Ivanov Petro 379 2530\n";
    outFile << "Sydorov Ivan 222 8432\n";
    outFile << "Ivanov Anna 756 3920\n";
    outFile.close();

    // 2. Зчитуємо дані з файлу
    std::ifstream inFile("phonebook.txt");
    if (!inFile) {
        std::cerr << "Помилка відкриття файлу phonebook.txt\n";
        return 1;
    }

    std::vector<Contact> contacts;
    Contact c;
    while (inFile >> c.lastName >> c.firstName >> c.prefix >> c.number) {
        // Заміна 222 -> 863 із збереженням старого префікса
        if (c.prefix == "222") {
            c.oldPrefix = "222";
            c.prefix = "863";
        }
        contacts.push_back(c);
    }
    inFile.close();

    // 3. Сортування (первинний ключ — прізвище, вторинний — ім'я)
    std::sort(contacts.begin(), contacts.end());

    std::cout << "=== Відсортована телефонна книга (із зміненими номерами 222 -> 863) ===\n";
    for (const auto& item : contacts) {
        std::cout << std::left << std::setw(12) << item.lastName
            << std::setw(10) << item.firstName
            << item.prefix << "-" << item.number;
        if (!item.oldPrefix.empty()) {
            std::cout << " (старий префікс: " << item.oldPrefix << ")";
        }
        std::cout << "\n";
    }

    // 4. Пошук за прізвищем за допомогою std::equal_range
    std::string searchLastName = "Ivanov";
    std::cout << "\n=== Пошук усіх контактів з прізвищем '" << searchLastName << "' (через std::equal_range) ===\n";

    Contact dummyKey;
    dummyKey.lastName = searchLastName;
    dummyKey.firstName = ""; // Мур для нижнього порогу

    // Компаратор для порівняння лише за прізвищем під час range-пошуку
    auto comp = [](const Contact& a, const Contact& b) {
        return a.lastName < b.lastName;
        };

    auto range = std::equal_range(contacts.begin(), contacts.end(), dummyKey, comp);

    if (range.first != range.second) {
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << "  Знайдено: " << it->lastName << " " << it->firstName
                << " -> " << it->prefix << "-" << it->number << "\n";
        }
    }
    else {
        std::cout << "  Контактів з таким прізвищем не знайдено.\n";
    }

    return 0;
}