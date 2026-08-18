#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const std::string filename = "data9.bin";

    // 1. Створюємо тестовий бінарний файл з даними
    {
        std::ofstream out(filename, std::ios::binary);

        // Вектор V0: {1, 2, 2}
        size_t size_v0 = 3;
        out.write(reinterpret_cast<const char*>(&size_v0), sizeof(size_v0));
        int v0_data[] = { 1, 2, 2 };
        out.write(reinterpret_cast<const char*>(v0_data), sizeof(int) * size_v0);

        // Число N = 3
        int N = 3;
        out.write(reinterpret_cast<const char*>(&N), sizeof(N));

        // V1: {1, 2, 2, 3, 4} -> Містить {1, 2, 2} (Підходить)
        size_t size_v1 = 5;
        out.write(reinterpret_cast<const char*>(&size_v1), sizeof(size_v1));
        int v1_data[] = { 1, 2, 2, 3, 4 };
        out.write(reinterpret_cast<const char*>(v1_data), sizeof(int) * size_v1);

        // V2: {1, 2, 5} -> Не містить другої двійки (Не підходить)
        size_t size_v2 = 3;
        out.write(reinterpret_cast<const char*>(&size_v2), sizeof(size_v2));
        int v2_data[] = { 1, 2, 5 };
        out.write(reinterpret_cast<const char*>(v2_data), sizeof(int) * size_v2);

        // V3: {2, 4, 2, 1, 9} -> Містить {1, 2, 2} у невідсортованому вигляді (Підходить)
        size_t size_v3 = 5;
        out.write(reinterpret_cast<const char*>(&size_v3), sizeof(size_v3));
        int v3_data[] = { 2, 4, 2, 1, 9 };
        out.write(reinterpret_cast<const char*>(v3_data), sizeof(int) * size_v3);

        out.close();
        std::cout << "Бінарний файл " << filename << " успішно створено.\n\n";
    }

    // 2. Зчитуємо дані з бінарного файла та перевіряємо їх
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Помилка відкриття файла!\n";
        return 1;
    }

    size_t size_v0;
    in.read(reinterpret_cast<char*>(&size_v0), sizeof(size_v0));
    std::vector<int> V0(size_v0);
    in.read(reinterpret_cast<char*>(V0.data()), sizeof(int) * size_v0);

    int N;
    in.read(reinterpret_cast<char*>(&N), sizeof(N));

    // Сортуємо V0 для алгоритму std::includes
    std::sort(V0.begin(), V0.end());

    int count = 0;
    for (int i = 0; i < N; ++i) {
        size_t size_vi;
        in.read(reinterpret_cast<char*>(&size_vi), sizeof(size_vi));
        std::vector<int> Vi(size_vi);
        in.read(reinterpret_cast<char*>(Vi.data()), sizeof(int) * size_vi);

        // Сортуємо Vi для std::includes
        std::sort(Vi.begin(), Vi.end());

        // Перевіряємо, чи всі елементи V0 входять у Vi з урахуванням повторень
        if (std::includes(Vi.begin(), Vi.end(), V0.begin(), V0.end())) {
            count++;
        }
    }
    in.close();

    std::cout << "Кількість векторів, що містять усі елементи V0: " << count << std::endl;

    return 0;
}