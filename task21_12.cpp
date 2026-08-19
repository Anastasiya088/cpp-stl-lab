#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

struct WeightedPoint {
    int x, y;
    double mass;

    // Обчислення важеля сили: m1 * (x1 + x2)
    double leverage() const {
        return mass * (x + y);
    }
};

struct Segment {
    WeightedPoint p1, p2;
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо вхідний файл weighted_points.txt з тестовими даними
    std::ofstream outFile("weighted_points.txt");
    outFile << "(1, 2): 3.5, (4, 0): 1.2, (2, 2): 2.0, (0, 1): 5.0";
    outFile.close();

    // 2. Зчитуємо точки з файлу
    std::ifstream inFile("weighted_points.txt");
    if (!inFile) {
        std::cerr << "Помилка відкриття файлу weighted_points.txt\n";
        return 1;
    }

    std::vector<WeightedPoint> points;
    char p1, comma, p2, colon, sep;
    int x, y;
    double m;

    // Формат зчитування: (x, y): m,
    while (inFile >> p1 >> x >> comma >> y >> p2 >> colon >> m) {
        points.push_back({ x, y, m });
        inFile >> sep; // зчитуємо кому між точками, якщо вона є
    }
    inFile.close();

    // 3. Сортуємо точки за важелем сили (m1 * (x1 + x2))
    std::sort(points.begin(), points.end(), [](const WeightedPoint& a, const WeightedPoint& b) {
        return a.leverage() < b.leverage();
        });

    // 4. Формуємо відрізки з відсортованих точок та записуємо у файл weighted_segments.txt
    std::ofstream resultFile("weighted_segments.txt");
    std::cout << "Точки, відсортовані за важелем сили m*(x1+x2):\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << i + 1 << ") Точка (" << points[i].x << ", " << points[i].y
            << ") маса: " << points[i].mass
            << " | Важіль сили: " << points[i].leverage() << "\n";
    }

    std::cout << "\nЗгенеровані відрізки з відсортованих точок:\n";
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            std::string line = "((" + std::to_string(points[i].x) + "," + std::to_string(points[i].y) + ") - (" +
                std::to_string(points[j].x) + "," + std::to_string(points[j].y) + "))";
            resultFile << line << "\n";
            std::cout << "  - " << line << "\n";
        }
    }
    resultFile.close();

    std::cout << "\nРезультати успішно збережено у файл weighted_segments.txt\n";

    return 0;
}