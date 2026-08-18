#define NOMINMAX
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <windows.h>

// 1. Перевантаження для std::set
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    bool first = true;
    for (const auto& elem : s) {
        if (!first) os << ",";
        os << elem;
        first = false;
    }
    return os;
}

// 2. Перевантаження для std::multiset
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    bool first = true;
    for (const auto& elem : s) {
        if (!first) os << ",";
        os << elem;
        first = false;
    }
    return os;
}

// 3. Перевантаження для std::map
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    bool first = true;
    for (const auto& [key, value] : m) {
        if (!first) os << "; ";
        os << key << "=" << value;
        first = false;
    }
    return os;
}

// 4. Перевантаження для std::multimap
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::multimap<K, V>& m) {
    bool first = true;
    for (const auto& [key, value] : m) {
        if (!first) os << "; ";
        os << key << "=" << value;
        first = false;
    }
    return os;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Приклад використання з умови
    std::set<int> testSet{ 1, 3 };
    std::map<int, std::string> testMap;
    testMap[1] = "123";
    testMap[2] = "456";

    std::cout << testMap << std::endl;
    std::cout << testSet << std::endl;

    // Додаткова перевірка для multiset та multimap
    std::multiset<int> testMultiSet{ 5, 5, 10 };
    std::multimap<std::string, int> testMultiMap{ {"a", 1}, {"a", 2} };

    std::cout << "\nДодаткова перевірка multiset: " << testMultiSet << std::endl;
    std::cout << "Додаткова перевірка multimap: " << testMultiMap << std::endl;

    return 0;
}