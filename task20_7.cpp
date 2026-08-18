#define NOMINMAX
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <windows.h>

using Point = std::pair<int, int>;
using Figure = std::vector<Point>;

Point rotate90(const Point& p) {
    return { p.second, -p.first };
}

Figure getCanonicalForm(Figure fig) {
    Figure best_form;

    for (int rot = 0; rot < 4; ++rot) {
       
        int min_x = fig[0].first;
        int min_y = fig[0].second;
        for (const auto& p : fig) {
            min_x = (std::min)(min_x, p.first);
            min_y = (std::min)(min_y, p.second);
        }

       
        Figure normalized = fig;
        for (auto& p : normalized) {
            p.first -= min_x;
            p.second -= min_y;
        }

        std::sort(normalized.begin(), normalized.end());

        if (rot == 0 || normalized < best_form) {
            best_form = normalized;
        }

        for (auto& p : fig) {
            p = rotate90(p);
        }
    }

    return best_form;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int rows, cols;
    std::cout << "Введіть розміри сітки (рядки та стовпчики): ";
    if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0) return 0;

    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
    std::cout << "Введіть матрицю (1 - зафарбована клітина, 0 - порожня):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::multiset<Figure> figures_multiset;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

   
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                Figure current_fig;
                std::queue<Point> q;

                q.push({ i, j });
                visited[i][j] = true;

                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    current_fig.push_back({ r, c });

                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dx[d];
                        int nc = c + dy[d];

                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                            if (grid[nr][nc] == 1 && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({ nr, nc });
                            }
                        }
                    }
                }

                
                figures_multiset.insert(getCanonicalForm(current_fig));
            }
        }
    }

    std::set<Figure> unique_figures(figures_multiset.begin(), figures_multiset.end());

    std::cout << "\nЗагальна кількість знайдених фігур: " << figures_multiset.size() << std::endl;
    std::cout << "Кількість різних (унікальних) фігур: " << unique_figures.size() << std::endl;

    return 0;
}