#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <windows.h>

struct Point3D {
    int x, y, z;
};

struct Segment {
    Point3D p1, p2;

    // Обчислення довжини відрізка в 3D
    double length() const {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 1. Створюємо вхідний файл points.txt з тестовими даними
    std::ofstream outFile("points.txt");
    outFile << "0,0,0; 3,4,0; 1,1,1; 5,5,5;";
    outFile.close();

    // 2. Зчитуємо точки з файлу
    std::ifstream inFile("points.txt");
    if (!inFile) {
        std::cerr << "Помилка відкриття файлу points.txt\n";
        return 1;
    }

    std::vector<Point3D> points;
    int x, y, z;
    char ch1, ch2, sep;

    // Формат зчитування: x , y , z ;
    while (inFile >> x >> ch1 >> y >> ch2 >> z >> sep) {
        points.push_back({ x, y, z });
    }
    inFile.close();

    // 3. Формуємо всі можливі відрізки з отриманих точок
    std::vector<Segment> segments;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            segments.push_back({ points[i], points[j] });
        }
    }

    // 4. Сортуємо відрізки за зростанням довжини
    std::sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) {
        return a.length() < b.length();
        });

    // 5. Записуємо відсортовані відрізки у файл segments.txt
    std::ofstream resultFile("segments.txt");
    std::cout << "Результат обробки (відрізки за зростанням довжини):\n";
    for (const auto& seg : segments) {
        std::string line = "((" + std::to_string(seg.p1.x) + "," + std::to_string(seg.p1.y) + "," + std::to_string(seg.p1.z) +
            ") - (" + std::to_string(seg.p2.x) + "," + std::to_string(seg.p2.y) + "," + std::to_string(seg.p2.z) +
            ")) Довжина: " + std::to_string(seg.length());

        resultFile << line << "\n";
        std::cout << line << "\n";
    }
    resultFile.close();

    std::cout << "\nРезультати успішно збережено у файл segments.txt\n";

    return 0;
}