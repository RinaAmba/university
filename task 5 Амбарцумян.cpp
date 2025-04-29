#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int size;
    std::cout << "Введите размер векторов: ";
    std::cin >> size;

    vector<double> vec1(size);
    vector<double> vec2(size);

    cout << "Введите элементы первого вектора:\n";
    for (int i = 0; i < size; ++i) {
        cin >> vec1[i];
    }

    cout << "Введите элементы второго вектора:\n";
    for (int i = 0; i < size; ++i) {
        cin >> vec2[i];
    }
  
    double dot_sum = 0.0;

    #pragma omp parallel for reduction(+:dot_sum) num_threads(12)
    for (int i = 0; i < size; ++i) {
        dot_sum += vec1[i] * vec2[i];
    }

    cout << "\nПервый вектор: ";
    for (double num : vec1) {
        cout << num << " ";
    }

    cout << "\nВторой вектор: ";
    for (double num : vec2) {
        cout << num << " ";
    }

    cout << "\nСкалярное произведение: " << dot_sum << endl;

    return 0;
}
