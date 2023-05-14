#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для решения системы линейных алгебраических уравнений методом Зейделя
vector<double> solveSystem(vector<vector<double>>& A, vector<double>& b, double epsilon, int maxIterations) {
    int n = A.size();
        vector<double> x(n, 0.0); // Инициализируем начальное приближение нулевым вектором
        vector<double> xPrev(n, 0.0); // Предыдущее значение вектора x
        int iteration = 0;
        
        while (iteration < maxIterations) {
            xPrev = x;
            
            for (int i = 0; i < n; ++i) {
                double sum1 = 0.0;
                double sum2 = 0.0;
                
                for (int j = 0; j < i; ++j)
                    sum1 += A[i][j] * x[j];
                
                for (int j = i + 1; j < n; ++j)
                    sum2 += A[i][j] * xPrev[j];
                
                x[i] = (b[i] - sum1 - sum2) / A[i][i];
            }
            
            // Проверка критерия остановки
            double error = 0.0;
            for (int i = 0; i < n; ++i)
                error += abs(x[i] - xPrev[i]);
            
            if (error < epsilon)
                break;
            
            iteration++;
        }

    return x;
}

// Функция для заполнения матрицы случайными числами
void fillMatrixRandom(vector<vector<double>>& A) {
    srand(time(0)); // Инициализация генератора случайных чисел

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            A[i][j] = rand() % 10; // Генерация случайного числа от 0 до 9
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(const vector<vector<double>>& A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int choice;
    vector<vector<double>> A;
    vector<double> b;
    double epsilon = 1e-6; // Точность
    int maxIterations = 100; // Максимальное количество итераций
    
    while (true) {
        cout << "Меню:\n";
        cout << "1. Ввести данные в матрицу с клавиатуры\n";
        cout << "2. Заполнить матрицу случайными числами\n";
        cout << "3. Выход\n";
        cout << "Введите выбор (1, 2 или 3): ";
        cin >> choice;
        cout << endl;
        
        if (choice == 1) {
            int size;
            cout << "Введите размерность матрицы: ";
            cin >> size;
            
            A.resize(size, vector<double>(size));
            b.resize(size);
            
            cout << "Введите элементы матрицы A:\n";
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cin >> A[i][j];
                }
            }
            
            cout << "Введите элементы вектора b:\n";
            for (int i = 0; i < size; ++i) {
                cin >> b[i];
            }
            
            // Решение системы уравнений и вывод результата
            vector<double> solution = solveSystem(A, b, epsilon, maxIterations);
            cout << "Решение:\n";
            for (int i = 0; i < solution.size(); ++i) {
                cout << "x" << i + 1 << " = " << solution[i] << endl;
            }
        } else if (choice == 2) {
            int size;
            cout << "Введите размерность матрицы: ";
            cin >> size;
            
            A.resize(size, vector<double>(size));
            b.resize(size);
            
            // Заполнение матрицы случайными числами
            fillMatrixRandom(A);
            
            // Заполнение вектора b случайными числами
            srand(time(0));
            for (int i = 0; i < size; ++i) {
                b[i] = rand() % 10; // Генерация случайного числа от 0 до 9
            }
            
            cout << "Матрица A:\n";
            printMatrix(A);
            
            cout << "Вектор b:\n";
            for (int i = 0; i < size; ++i) {
                cout << b[i] << " ";
            }
            cout << endl;
            
            // Решение системы уравнений и вывод результата
            vector<double> solution = solveSystem(A, b, epsilon, maxIterations);
            cout << "Решение:\n";
            for (int i = 0; i < solution.size(); ++i) {
                cout << "x" << i + 1 << " = " << solution[i] << endl;
            }
        } else if (choice == 3) {
            cout << "Выход из программы.\n";
            break;
        } else {
            cout << "Такого пункта меню не существует.\n";
        }
        cout << endl;
    }
}
