#define NOMINMAX
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <optional>
#include <cmath>
#include <windows.h>

struct Point { double x, y; };
struct Segment { Point p1, p2; };

std::optional<Point> getIntersection(Segment s1, Segment s2) {
    double a1 = s1.p2.y - s1.p1.y, b1 = s1.p1.x - s1.p2.x, c1 = a1 * s1.p1.x + b1 * s1.p1.y;
    double a2 = s2.p2.y - s2.p1.y, b2 = s2.p1.x - s2.p2.x, c2 = a2 * s2.p1.x + b2 * s2.p2.y;
    double det = a1 * b2 - a2 * b1;
    if (std::abs(det) < 1e-9) return std::nullopt;

    double x = (b2 * c1 - b1 * c2) / det;
    double y = (a1 * c2 - a2 * c1) / det;

    Point pt{ x, y };

    double min_x1 = (std::min)(s1.p1.x, s1.p2.x), max_x1 = (std::max)(s1.p1.x, s1.p2.x);
    double min_y1 = (std::min)(s1.p1.y, s1.p2.y), max_y1 = (std::max)(s1.p1.y, s1.p2.y);
    double min_x2 = (std::min)(s2.p1.x, s2.p2.x), max_x2 = (std::max)(s2.p1.x, s2.p2.x);
    double min_y2 = (std::min)(s2.p1.y, s2.p2.y), max_y2 = (std::max)(s2.p1.y, s2.p2.y);

    bool on_s1 = (x >= min_x1 - 1e-9 && x <= max_x1 + 1e-9 && y >= min_y1 - 1e-9 && y <= max_y1 + 1e-9);
    bool on_s2 = (x >= min_x2 - 1e-9 && x <= max_x2 + 1e-9 && y >= min_y2 - 1e-9 && y <= max_y2 + 1e-9);

    if (on_s1 && on_s2) return pt;
    return std::nullopt;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    std::cout << "Введіть кількість відрізків N: ";
    if (!(std::cin >> n) || n < 2) return 0;

    std::vector<Segment> segs(n);
    std::cout << "Введіть координати відрізків (x1 y1 x2 y2):\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> segs[i].p1.x >> segs[i].p1.y >> segs[i].p2.x >> segs[i].p2.y;
    }

    std::map<double, double> intersections;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto pt = getIntersection(segs[i], segs[j]);
            if (pt) intersections[pt->x] = pt->y;
        }
    }

    if (!intersections.empty()) {
        auto min_elem = intersections.begin();
        std::cout << "Точка перетину з мінімальною абсцисою: (" << min_elem->first << ", " << min_elem->second << ")\n";
    }
    else {
        std::cout << "Перетинів відрізків не знайдено.\n";
    }
    return 0;
}