/* 
1. Составить программу для расчета двух значений z1 и z2, результаты которых должны совпадать. Значения исходных данных вводить с клавиатуры, π = 3.1415926, α и β  - в радианах
2. Составить программу для расчета заданных выражений с проверкой исключительных ситуаций: деление на нуль, вычисление корня из отрицательного числа и т. п. При вводе данных использовать проверку на ввод числовых данных.
3. Составить программу для расчета заданного значения с проверкой исключительных ситуаций: деление на нуль, выход значений аргументов используемых функций за допустимые пределы и т. п. При вводе данных использовать проверку на ввод нечисловых данных.
*/

#define PROBLEM 1

#if PROBLEM == 1
#include <iostream>
#include <cmath>

double solve1(double a) { //Отдельная функция с записью первого выражения, которая возвращает ответ
    return sqrt((3 * a + 2) * (3 * a + 2) - 24 * a) / (3 * sqrt(a) - 2 / sqrt(a));
}
double solve2(double a) { //Функция для решения второго уравнения
    return sqrt(a);
}
int main() {
    double a; //Объявление переменной
    std::cout << "Enter a=";
    std::cin >> a; //Запись ввода консоли в переменную
    std::cout << "r1=" << solve1(a) << std::endl << "r2=" << solve2(a); //Решение и вывод ответа в консоль
    return 0;
}

#elif PROBLEM == 2

#include <iostream>
#include <cmath>
#define PI 3.1415926535

double solve1(double a) { //отдельная функция с записью первого выражения, которая возвращает ответ
    return cos(a) + sin(a) + cos(3 * a) + sin(3 * a);
}
double solve2(double a) { //функция для решения второго уравнения
    return 2 * sqrt(2) * cos(a) * sin(PI / 4 + 2 * a);
}
int main() {
    double a;
    std::cout << "Enter a=";
    while (!(std::cin >> a)) { //пробуем записать строчку до тех пор, пока не получится
        std::cin.clear(); //если неудачный ввод, очищаем и запрашиваем снова
        std::cin.ignore();
        std::cout << "Incorrect input. 'a' should be a number!\n";
    };
    std::cout << "r1=" << solve1(a) << std::endl << "r2=" << solve2(a);
    return 0;
}

#elif PROBLEM == 3

#include <iostream>
#include <cmath>

double pow_check(double x, double y) { //функция замены возведения в степень с проверкой на корректность и экстренное закрытие программы
    if (x < 0 && y < 1 && y > 0) throw "negative number under root!";
    return pow(x, y);
}
double solve(double x, double y, double z) { //отдельная функция с записью выражения, которая возвращает ответ при подстановке х и у
    if (sin(z) * sin(z) + tan(z) == 0) throw "dividing by zero!";
    return pow_check(y + pow(x - 1, 1. / 3.), 0.25) / abs(x - y) / (sin(z) * sin(z) + tan(z));
}

int main() {
    double x, y, z; //текст для проверки - 17.421 0.010365 82800
    std::cout << "Enter x y z, splitted with space:";

    while (!(std::cin >> x >> y >> z)) { //пробуем записать строчку до тех пор, пока не получится
        std::cin.clear(); //если неудачный ввод, очищаем
        std::cin.ignore();
    };
    std::cout << "r=" << solve(x, y, z);
    return 0;
}

#endif
