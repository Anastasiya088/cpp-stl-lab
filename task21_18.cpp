#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <windows.h>

// 1. Перерахування для погоди
enum Weather { RAINY, SNOWY, CLOUDY, SUNNY };

// 2. Клас Місто (Town)
class Town {
private:
    std::string name;
    int population;
    int altitude; // висота у футах
    Weather weather;

public:
    Town(std::string n, int pop, int alt, Weather w)
        : name(n), population(pop), altitude(alt), weather(w) {
    }

    std::string getName() const { return name; }

    std::string getWeatherString() const {
        switch (weather) {
        case RAINY:  return "ДОЩИТЬ";
        case SNOWY:  return "СНІЖНО";
        case CLOUDY: return "ХМАРНО";
        case SUNNY:  return "ЯСНО";
        default:     return "НЕВІДОМО";
        }
    }

    void print() const {
        std::cout << "Місто: " << std::left << std::setw(12) << name
            << " | Популяція: " << std::setw(8) << population
            << " | Висота: " << std::setw(5) << altitude << " фт"
            << " | Погода: " << getWeatherString() << "\n";
    }
};

// 3. Клас-генератор об'єктів Town
class TownGenerator {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> popDist;
    std::uniform_int_distribution<int> altDist;
    std::uniform_int_distribution<int> weatherDist;
    std::set<std::string> usedNames;

    std::vector<std::string> baseNames = {
        "kyiv", "lviv", "odesa", "kharkiv", "dnipro",
        "poltava", "vinnytsia", "sumy", "chernihiv", "rivne"
    };

public:
    TownGenerator()
        : rng(1337), // стабільний зерновий генератор для відтворення
        popDist(100, 1000000),
        altDist(0, 8000),
        weatherDist(0, 3) {
    }

    Town generateNext() {
        std::string name;

        // Гарантуємо унікальність та нижній регістр назв міст
        for (const auto& baseName : baseNames) {
            std::string lowerName = baseName;
            std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

            if (usedNames.find(lowerName) == usedNames.end()) {
                name = lowerName;
                usedNames.insert(lowerName);
                break;
            }
        }

        if (name.empty()) {
            name = "town_" + std::to_string(usedNames.size() + 1);
            usedNames.insert(name);
        }

        int pop = popDist(rng);
        int alt = altDist(rng);
        Weather w = static_cast<Weather>(weatherDist(rng));

        return Town(name, pop, alt, w);
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    TownGenerator gen;
    std::vector<Town> towns;

    // Генеруємо 6 унікальних міст
    for (int i = 0; i < 6; ++i) {
        towns.push_back(gen.generateNext());
    }

    std::cout << "Згенерований список міст (Towns):\n";
    std::cout << "---------------------------------------------------------\n";
    for (const auto& town : towns) {
        town.print();
    }
    std::cout << "---------------------------------------------------------\n";

    return 0;
}