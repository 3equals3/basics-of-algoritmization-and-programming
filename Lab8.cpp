#include <iostream>
#include <cmath>


#define PROBLEM 2
#define INPUT_VALUES(string, args) \
    while (true) { \
        std::cout << string; \
        if (!(std::cin >> args)) { \
            std::cout << "Invalid input!" << std::endl;\
            std::cin.clear(); \
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); \
        } else break; \
    } 

#if PROBLEM == 1 

double S(int n, double x) {
    double result = 0;
    double prev_quotient = 1;
    for (int k = 1; k <= n; k++) {
        result += pow(-1, (double)k) * pow(2 * x, 2 * ((double)k)) / (prev_quotient * 2 * k * (2 * k - 1));
        prev_quotient = (prev_quotient * 2 * k * (2 * k - 1));
    }
    return result;
}

double Y(double x) {
    return 2 * cos(x) * cos(x) - 2;
}

double abs_YmS(int n, double x) {
    return std::abs(Y(x) - S(n, x));
}

void Out_Rez(int function, double a, double b, double h, int n) {
    switch (function) {
    case 1: 
        std::cout << "Y(x):\n";
        break;
    case 2:
        std::cout << "S(x):\n";
        break;
    case 3:
        std::cout << "|Y(x) - S(x)|:\n";
        break;
    default:
        std::cout << "Function is not selected.";
        return;
    }
    for (double x = a; x <= b; x += h) {
        std::cout << (function == 1 ? Y(x) : (function == 2 ? S(n, x) : abs_YmS(n, x))) << std::endl;
    }
}


int main(void) {
    double a, b, h;
    int n, function;

    INPUT_VALUES("Enter a, b, h, n (write each one separated by a space): ", a >> b >> h >> n); // 0.1 1.0 0.1 6
    INPUT_VALUES("Enter function number(1 is Y(x), 2 is S(x), 3 is abs()): ", function);

    Out_Rez(function, a, b, h, n);
    return 0;
} 

#elif PROBLEM == 2


double powerRecursive(double x, int n) { // Рекурсивная функция для вычисления y = x^n
    if (n == 0) {
        return 1.0;
    }
    else if (n % 2 == 0) {
        double temp = powerRecursive(x, n / 2);
        return temp * temp;
    }
    else {
        return x * powerRecursive(x, n - 1);
    }
}


double powerNonRecursive(double x, int n) { // Обычная функция для вычисления y = x^n
    double result = 1.0;

    while (n > 0) {
        if (n % 2 == 0) {
            x = x * x;
            n = n / 2;
        }
        else {
            result = result * x;
            n = n - 1;
        }
    }

    return result;
}


int main(void) {
    int n = 5;
    double x;
    INPUT_VALUES("Enter x: ", x);

    double resultRecursive = powerRecursive(x, n);
    std::cout << "Recursive result: " << resultRecursive << std::endl;

    double resultNonRecursive = powerNonRecursive(x, n);
    std::cout << "Non-recursive result: " << resultNonRecursive << std::endl;

    return 0;
}

// Вывод о разности: при выполнении программы никаких отклонений от предполагаемых результатов обнаружены не были. Обе функции работают исправно и выдают один и тот же ответ.

#endif
