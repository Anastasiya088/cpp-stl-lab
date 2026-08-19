#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <windows.h>

class BoolVector {
private:
    std::vector<bool> vec;

public:
    // Конструктори
    BoolVector() = default;
    BoolVector(const std::vector<bool>& v) : vec(v) {}
    BoolVector(size_t size, bool value = false) : vec(size, value) {}

    // Додавання елементів
    void push_back(bool val) {
        vec.push_back(val);
    }

    size_t size() const {
        return vec.size();
    }

    // Порозрядна кон'юнкція (AND)
    BoolVector operator&(const BoolVector& other) const {
        size_t min_len = (std::min)(vec.size(), other.vec.size());
        BoolVector result(min_len);
        for (size_t i = 0; i < min_len; ++i) {
            result.vec[i] = vec[i] && other.vec[i];
        }
        return result;
    }

    // Порозрядна диз'юнкція (OR)
    BoolVector operator|(const BoolVector& other) const {
        size_t min_len = (std::min)(vec.size(), other.vec.size());
        BoolVector result(min_len);
        for (size_t i = 0; i < min_len; ++i) {
            result.vec[i] = vec[i] || other.vec[i];
        }
        return result;
    }

    // Порозрядне заперечення (NOT)
    BoolVector operator~() const {
        BoolVector result(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            result.vec[i] = !vec[i];
        }
        return result;
    }

    // Підрахунок кількості одиниць (true) за допомогою std::count
    size_t countOnes() const {
        return std::count(vec.begin(), vec.end(), true);
    }

    // Підрахунок кількості нулів (false) за допомогою std::count
    size_t countZeros() const {
        return std::count(vec.begin(), vec.end(), false);
    }

    // Метод для друку
    void print(const std::string& name = "") const {
        if (!name.empty()) std::cout << name << ": ";
        for (bool b : vec) {
            std::cout << (b ? 1 : 0);
        }
        std::cout << "\n";
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    BoolVector v1({ true, false, true, true, false });  // 10110
    BoolVector v2({ true, true,  false, true, true });  // 11011

    v1.print("Вектор 1");
    v2.print("Вектор 2");

    BoolVector andRes = v1 & v2;
    andRes.print("Кон'юнкція (AND)");

    BoolVector orRes = v1 | v2;
    orRes.print("Диз'юнкція (OR) ");

    BoolVector notRes = ~v1;
    notRes.print("Заперечення ~V1");

    std::cout << "\nКількість одиниць у V1: " << v1.countOnes() << "\n";
    std::cout << "Кількість нулів у V1:   " << v1.countZeros() << "\n";

    return 0;
}