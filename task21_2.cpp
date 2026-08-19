#define NOMINMAX
#include <iostream>
#include <list>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n;
    std::cout << "Введіть кількість елементів списку: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Некоректний розмір.\n";
        return 0;
    }

    std::list<int> lst;
    std::cout << "Введіть " << n << " цілих чисел:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        lst.push_back(val);
    }

    int X;
    std::cout << "Введіть число X: ";
    std::cin >> X;

    std::cout << "\nПочатковий список: ";
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // std::partition переставляє елементи in-place (без змін розміру та без допоміжних об'єктів):
    // елементи, що задовольняють умову (<= X), переміщуються на початок, інші (> X) — у кінець
    std::partition(lst.begin(), lst.end(), [X](int val) {
        return val <= X;
        });

    std::cout << "Список після перегрупування (спочатку <= " << X << ", потім > " << X << "): ";
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}