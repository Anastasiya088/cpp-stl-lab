#define NOMINMAX
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <string>
#include <windows.h>

// --- Частина 1: Ієрархія класів та std::for_each ---
class B {
public:
    virtual void f() const {
        std::cout << "Викликанo B::f()\n";
    }
    virtual ~B() = default;
};

class D : public B {
public:
    void f() const override {
        std::cout << "Викликано D::f()\n";
    }
};

// --- Частина 2: Генератор для послідовності чисел ---
class SequenceGenerator {
private:
    int current;
public:
    SequenceGenerator(int start = 1) : current(start) {}
    int operator()() {
        return current++;
    }
};

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=== Частина 1: Поліморфізм та std::for_each ===\n";
    std::vector<B*> objects;
    objects.push_back(new B());
    objects.push_back(new D());
    objects.push_back(new B());
    objects.push_back(new D());

    // Виклик віртуальної функції f() через std::for_each
    std::for_each(objects.begin(), objects.end(), [](B* obj) {
        obj->f();
        });

    // Звільнення пам'яті
    for (B* obj : objects) {
        delete obj;
    }

    std::cout << "\n=== Частина 2: Обчислення факторіалів через std::partial_sum ===\n";

    int n = 7; // Значення за замовчуванням
    if (argc > 1) {
        n = std::stoi(argv[1]);
    }
    else {
        std::cout << "Аргумент командного рядка не передано. Використовуємо N = " << n << "\n";
    }

    std::vector<int> numbers(n);
    // Заповнюємо вектор послідовними числами: 1, 2, ..., N
    std::generate(numbers.begin(), numbers.end(), SequenceGenerator(1));

    std::vector<int> factorials(n);
    // Обчислюємо часткові добутки (факторіали) за допомогою std::partial_sum та std::multiplies
    std::partial_sum(numbers.begin(), numbers.end(), factorials.begin(), std::multiplies<int>());

    std::cout << "Таблиця факторіалів від 1! до " << n << "!:\n";
    for (size_t i = 0; i < factorials.size(); ++i) {
        std::cout << "  " << (i + 1) << "! = " << factorials[i] << "\n";
    }

    return 0;
}