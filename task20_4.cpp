#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <numeric>
#include <windows.h>

struct Point {
    long long x, y;
};

struct Line {
    long long a, b, c;
    bool operator<(const Line& other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }
};

Line getLine(Point p1, Point p2) {
    long long a = p2.y - p1.y;
    long long b = p1.x - p2.x;
    long long c = -(a * p1.x + b * p1.y);
    long long g = std::gcd(std::gcd(a, b), c);
    if (g != 0) { a /= g; b /= g; c /= g; }
    if (a < 0 || (a == 0 && b < 0)) { a = -a; b = -b; c = -c; }
    return { a, b, c };
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    std::cout << "Введіть кількість точок: ";
    if (!(std::cin >> n) || n < 2) return 0;

    std::vector<Point> pts(n);
    std::cout << "Введіть координати точок (X Y):\n";
    for (int i = 0; i < n; ++i) std::cin >> pts[i].x >> pts[i].y;

    std::map<Line, std::set<std::pair<long long, long long>>> line_points;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Line L = getLine(pts[i], pts[j]);
            line_points[L].insert({ pts[i].x, pts[i].y });
            line_points[L].insert({ pts[j].x, pts[j].y });
        }
    }

    std::multimap<size_t, Line> lines_by_count;
    for (const auto& [line, points] : line_points) {
        if (points.size() > 1) {
            lines_by_count.insert({ points.size(), line });
        }
    }

    std::ofstream out("lines_output.txt");
    for (const auto& [count, line] : lines_by_count) {
        out << "Пряма: " << line.a << "x + " << line.b << "y + " << line.c
            << " = 0 проходить через " << count << " точок.\n";
    }
    out.close();
    std::cout << "Результати збережено в lines_output.txt\n";
    return 0;
}