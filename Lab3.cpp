/*
1. Составить программу для определения всех значений функции у в произвольном диапазоне [a, b] изменения аргумента х с произвольным шагом h. Значения a, b, h вводятся с клавиатуры. Результат должен содержать следующие столбцы: 
порядковый номер, значение аргумента x и значение функции у. Определить максимальное и минимальное значения функции у.
2. Для каждого x, изменяющегося от a до b с шагом h, найти значения функ-
ции Y(x), суммы S(x) и |Y(x) – S(x)| и вывести в виде таблицы. Значения a, b, h и n вводятся с клавиатуры. Так как значение S(x) является рядом разложения функции Y(x), при правильном решении значения S и Y для заданного аргумента x 
(для тестовых значений исходных данных) должны совпадать в целой части и в первых двух-четырех позициях после десятичной точки. Работу программы проверить для a = 0,1; b = 1,0; h = 0,1; значение параметра n выбрать так, чтобы |Y(x) – S(x)| < 0.001 (0.0001, 0.00001).
3. Составить программу по заданию из п. 3.3.2, в которой нахождение суммы S(x) и функции Y(x) организовать в виде отдельных функций, причем расчет функции выполнять не по заданному значению n, а до тех пор пока разница
очередного значения суммы не будет отличаться от значения функции на некоторую величину (погрешность) E, равную, например, 0.001 (0.0001), т. е. до тех пор пока |S(x) – Y(x)| >= E. Определить количество шагов вычисления суммы, при которых был достигнут указанный результат.
*/

#define PROBLEM 2

#if PROBLEM == 1 

#include <iostream> // Импорт библиотек (ввод/вывод, математические функции)
#include <cmath>

double solve_y(double x) {
    return (1 - x * x / 4) * cos(x) - x / 2 * sin(x);
}

int main(void) { //Главная функция, с которой начинается выполнение программы
    double a, b, h; //Определение переменных из условия
    double max_y = -DBL_MAX, min_y = DBL_MAX; //для рассчета мы берем самые максимальные и минимальные значения. Все равно перезапишутся

    std::cout << "Enter a, b, h (write each one separated by a space): "; // Вывод в консоль возможных функций //-0.9 2.7 0.3
    while (!(std::cin >> a >> b >> h)) { // Запрос на ввод значений a, b, h. Запрашивает до тех пор, пока не будет корректный ввод
        std::cin.clear();
        std::cin.ignore();
    }
    std::cout << "Num:\t\tX:\t\tY:\n";

    double x;
    int i;
    for (x = a, i = 1; x <= b; x += h, i++) { //Одновременно считаем индекс и перебираем x
        double y = solve_y(x);
        std::cout << i << "\t\t" << x << "\t\t" << y << std::endl;
        if (y > max_y) max_y = y;
        if (y < min_y) min_y = y;
    }
    std::cout << "Maximal Y: " << max_y << std::endl;
    std::cout << "Minimal Y: " << min_y << std::endl;
    return 0;// успешное завершение программы
}

#elif PROBLEM == 2



#include <iostream> // Импорт библиотек (ввод/вывод, математические функции)
#include <cmath>
#include <iomanip> // Для std::setw(), Чтобы таблица была красивой

int fac(int number) { //функция факториала
    int result = 1;
    for (int i = number; i > 0; i--) {
        result *= i;
    }
    return result;
}

double S(int n, double x) {
    double result = 0;
    for (int k = 1; k <= n; k++) {
        result += pow(-1, (double)k) * pow(2 * x, 2 * ((double)k)) / fac((int)(2 * k));
    }
    return result;
}

double Y(double x) {
    return 2 * cos(x) * cos(x) - 2;
}


int main(void) { // Главная функция, с которой начинается выполнение программы
    double a, b, h, n; // Определение переменных из условия

    std::cout << "Enter a, b, h, n (write each one separated by a space): "; // Вывод в консоль возможных функций //0.1 1.0 0.1 6
    while (!(std::cin >> a >> b >> h >> n)) { // Запрос на ввод значений a, b, h. Запрашивает до тех пор, пока не будет корректный ввод
        std::cin.clear();
        std::cin.ignore();
    }
    std::cout << std::setw(20) << "Y(x):" << std::setw(20) << "S(x):" << std::setw(20) << "|Y(x) - S(x)|" << std::endl;

    for (double x = a; x <= b; x += h) { // Перебираем x
        double y = Y(x), s = S(n, x);
        std::cout << std::setw(20) << y << std::setw(20) << s << std::setw(20) << std::abs(y - s) << std::endl;
    }
    return 0;// успешное завершение программы
}


#elif PROBLEM == 3

#include <iostream>
#include <cmath>
#include <iomanip>

int fac(int number) {
    int result = 1;
    for (int i = number; i > 0; i--) {
        result *= i;
    }
    return result;
}

double S(double x, double E, int& steps) { //Указатель на steps чтобы в него записать.
    double result = 0;
    int k = 1;
    double term = 1;
    while (std::abs(term) >= E) {
        term = pow(-1, k) * pow(2 * x, 2 * k) / fac(2 * k);
        result += term;
        k++;
        steps++;
    }
    return result;
}

double Y(double x) {
    return 2 * cos(x) * cos(x) - 2;
}

int main(void) {
    double a, b, h, E;
    std::cout << "Enter a, b, h, E (write each one separated by a space): ";
    while (!(std::cin >> a >> b >> h >> E)) {
        std::cin.clear();
        std::cin.ignore();
    }
    std::cout << std::setw(20) << "Y(x):" << std::setw(20) << "S(x):" << std::setw(20) << "|Y(x) - S(x)|" << std::setw(20) << "Steps:" << std::endl;

    for (double x = a; x <= b; x += h) {
        int steps = 0;
        double y = Y(x), s = S(x, E, steps); //мы из функции s возвращаем steps чтобы вывести
        std::cout << std::setw(20) << y << std::setw(20) << s << std::setw(20) << std::abs(y - s) << std::setw(20) << steps << std::endl;
    }
    return 0;
}

#endif
