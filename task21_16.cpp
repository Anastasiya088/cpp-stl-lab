#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

// Власна реалізація алгоритму transform_if у стилі STL
template <typename InputIterator, typename OutputIterator, typename UnaryPredicate, typename UnaryOperation>
OutputIterator transform_if(InputIterator first, InputIterator last,
    OutputIterator result,
    UnaryPredicate pred, UnaryOperation op) {
    while (first != last) {
        if (pred(*first)) {
            *result = op(*first);
            ++result;
        }
        ++first;
    }
    return result; // повертаємо новий кінцевий ітератор
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> squared_evens;

    // Застосовуємо transform_if:
    // Предикат: перевірка на парність (x % 2 == 0)
    // Операція: піднесення до квадрата (x * x)
    transform_if(numbers.begin(), numbers.end(),
        std::back_inserter(squared_evens),
        [](int x) { return x % 2 == 0; },
        [](int x) { return x * x; });

    std::cout << "Початковий вектор: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    std::cout << "Квадрати лише парних чисел (transform_if): ";
    for (int n : squared_evens) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}