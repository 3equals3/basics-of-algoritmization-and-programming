/*
1. Составить программу для определения значения y. Обязательно выводить сообщения о том, по какой ветви происходило вычисление значения переменной х
2. Вычислить значение y в зависимости от выбранной функции
F(x): 2x, x2, х/3, аргумент которой x определяется в зависимости от переменной z. Обязательно выводить сообщения, показывающие, при каком условии и с какой функцией производились вычисления у.
При вводе данных использовать проверку на ввод нечисловых данных.
Организовать проверку исключительных ситуаций: деление на нуль, вычисление корня из отрицательного числа, выход значений аргументов используемых функций за допустимые значения
*/

#define PROBLEM 1
#if PROBLEM == 1

#include <iostream> // Импорт библиотек (ввод/вывод, математические функции)
#include <cmath>
double getXFromZ(double z) { // функция, которая проверяет значение X из числа Z по условию
    if (z > 1) // Условие из задачи. Если Z > 1, то должно использоваться первое выражение, иначе второе
        return exp(z) + z;
    else
        return pow(z, 2) + 1;
}
int main() { //Главная функция, с которой начинается выполнение программы
    double z, n = 1, m = 1, k = 1; //Объявление переменных
    std::cout << "Enter z = "; //Вывод в консоль текст запроса на ввод
    while (!(std::cin >> z)) { //Цикл, который запрашивает ввод до тех пор, пока не удастся удачно записать double в переменную z.
        std::cin.clear(); //В случае неудачи оно очищает предыдущий ввод из буфера и игнорирует прошлый ввод.
        std::cin.ignore();
    }
    std::cout << "Branch #" << (z > 1 ? 1 : 2) << std::endl; //Вывод в консоль ветки. Использован тернарный оператор: Если z > 1, то выведет 1, иначе 2
    double y = sin(n * getXFromZ(z)) + cos(k * getXFromZ(z)) + log(m * getXFromZ(z)); //Вычисление выражений. В аргументах использована своя функция на X
    std::cout << "y = " << y; //Вывод в консоль ответ
    return 0; //Успешное завершение программы
}

#elif PROBLEM == 2

#include <iostream>// Импорт библиотек (ввод/вывод, математические функции и строчки)
#include <cmath>
#include <string>
double getXFromZ(double z) { // Функция, которая проверяет значение X из числа Z по условию, сказанному в задаче.
    if (z > 1) // Условие из задачи. Если Z > 1, то должно использоваться первое выражение, иначе второе
        return z;
    else
        return pow(z, 2) + 1;
}
double fun(int mode, double x) { // Функция, которая подставляет математическое выражение, исходя из выбранного mode (режима)
    switch (mode) { // Использован switch как оператор ветвления. Аналогичен лесенке из if else
    case 0:
        return 2 * x;
    case 1:
        return x * x;
    case 2:
        return x / 3;
    default: // В случае если ни одно из определенных условий не сработает, выведет 0.0 в ответ. Но такого не должно случиться
        return 0.0;
    }
}

int main() { //Главная функция, с которой начинается выполнение программы
    int mode = 0;
    double z, n = 1, m = 1, k = 1; //Определение переменных
    std::cout << "#0 : 2*x\n#1 : x*x\n#2 : x/3\nSelect function (0-2): "; // Вывод в консоль возможных функций
    while (!(std::cin >> mode)) { // Запрос на ввод номера функций
        std::cin.clear();
        std::cin.ignore();
    }
label_restart: //Сюда перейдет в случае ошибки.
    std::cout << "Enter z = ";
    while (!(std::cin >> z)) { //Цикл, который запрашивает ввод до тех пор, пока не удастся удачно записать double в переменную z.
        std::cin.clear(); //В случае неудачи (!) оно очищает предыдущий ввод из буфера и игнорирует прошлый ввод.
        std::cin.ignore();
    }
    mode %= 3; //чтобы брать каждый 3. ноль один и два нормально определит, а 3 будет как 0, 4 как 1 и так далее
    std::string selected = "something broken!"; //Переменная std::string, в которую мы затем запишем саму функцию для вывода в консоль
    switch (mode) { // Использован switch как оператор ветвления. Аналогичен лесенке из if else
    case 0:
        selected = "2 * x";
        break;
    case 1:
        selected = "x * x";
        break;
    case 2:
        selected = "x / 3";
        break;
    }
    std::cout << "Branch #" << ((z > 1) + 1) << std::endl; //Вывод в консоль выбранной ветки. Можно использовать тернарный оператор, я использовал true как 1 и false как 0
    std::cout << "Function: " << selected << std::endl; //Вывод выбранного выражения в консоль
    if (log(m * getXFromZ(z)) == NAN) { //Проверка на то, чтобы логарифм был вычислен успешно. Иначе запросит новый Z
        std::cerr << "Bad input format! (log == NAN)" << std::endl;
        goto label_restart; //возврат в начало 
    }
  
    double y = sin(n * fun(mode, getXFromZ(z))) + cos(k * getXFromZ(z)) + log(m * getXFromZ(z)); //вычисление выражения
    std::cout << "y = " << y; //вывод ответа
    return 0;// успешное завершение программы
}

#endif
