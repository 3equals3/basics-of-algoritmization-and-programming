/*
1  Написать программу по обработке двухмерного динамического массива. Размеры массива n, m и значения его элементов вводятся с клавиатуры. 
1.1 Определить номер первого из столбцов, содержащих хотя бы один нулевой элемент
1.2 В квадратной матрице найти максимальный среди элементов, лежащих ниже побочной диагонали

2. Для динамического двухмерного массива решить поставленную задачу, алгоритм которой реализовать в виде отдельной функции. При вводе исходных данных выполнить проверку ввода нечисловых значений. В действительной квадратной матрице порядка n найти сумму и произведение элементов, расположенных в заштрихованной области (рис. 5.1, б).
*/

#define PROBLEM 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>


#define PTR_ARRAY(n, m) \
    int** arr = new int*[n]; \
    for (int count = 0; count < n; count++) arr[count] = new int[m];
#define CLR_ARRAY(n) \
    for (int i = 0; i < n; i++) delete[] arr[i]; \
    delete[] arr;
#define PRINT_ARRAY(n, m) \
    for (int i = 0; i < n; i++) { \
        for (int j = 0; j < m; j++) { \
            std::cout << std::setw(6) << arr[i][j]; \
        } \
        std::cout << std::endl; \
    }
/* 
PTR_ARRAY - Макрос для создания массива который при компиляции
создаст двумерный динамический массив N x M 
CLR_ARRAY - Очистка того массива
PRINT_ARRAY - Вывод в консоль всех значений
*/

void askForValue(int** arr, int i, int j) {
    while (true) {
        std::cout << "Enter value array[" << i << "][" << j << "] = ";
        std::cin >> arr[i][j];
        if (!std::cin.good()) {
            std::cout << "Invalid input! This value should be a number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
}
/*
   Порядок элементов в массиве arr[n][m]
            M
    (0, 0) --->
       |
     N |
       v
*/

#if PROBLEM == 1

int main(void) {
    unsigned int n, m;
    int index = -1, max_column = INT_MAX;
    while (true) {
        std::cout << "Enter positive lengths n and m (separate with space) = ";
        std::cin >> n >> m;
        if (!std::cin.good() || n <= 0 || m <= 0) {
            std::cout << "Invalid input! n and m should be a positive number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    PTR_ARRAY(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            askForValue(arr, i, j);
            if (arr[i][j] == 0 && j < max_column) {
                index = j; //Сразу запишем
                max_column = j;
            }
        }
    } 
    PRINT_ARRAY(n, m);
    if (max_column <= n)
        std::cout << "First column with 0 is " << index;
    else
        std::cout << "There is no 0's in array!";
    CLR_ARRAY(n);
    return 0;
}

#elif PROBLEM == 2

int main(void) {
    unsigned int length;
    int max_num = INT_MIN;
    while (true) {
        std::cout << "Enter positive length = ";
        std::cin >> length;
        if (!std::cin.good() || length <= 0) {
            std::cout << "Invalid input! Length should be a positive number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    PTR_ARRAY(length, length);
    for (int i = 0; i < length; i++)  // Запрашиваем
        for (int j = 0; j < length; j++) 
            askForValue(arr, i, j);

    PRINT_ARRAY(length, length);
   
    for (int i = 1; i < length; i++) // Начинаем с правого верхнего + 1. Так как все равно будет ниже чем диагональ которая на 0
        for (int j = length - 1; j > (length - (i + 1)); j--) // Идем лесенкой. Если необходимо, можно включить отображение какой элемент мы перебираем
            if (arr[i][j] > max_num) 
                max_num = arr[i][j];
    if (max_num != INT_MIN)
        std::cout << "Maximum number under secondary diagonal is " << max_num;
    else
        std::cout << "Something went wrong! Array is too small!";
    CLR_ARRAY(length);
    return 0;
}


#elif PROBLEM == 3

long* solve(int** arr, int length) { // Вернет указатель на ответ Типа Long (чтобы можно было с уверенностью умножать Int если они большие
    long mul = 1, sum = 0;
    // Если я правильно понял, та пограничная диагональная зона учитывает сами диагонали. Я считал вместе с ними
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (!(i < j && i + j < length - 1) && !(i > j && i + j > length - 1)) { // Какой страх божий. Но на деле нет, просто хитрая математика которая отсекает все что над и под диагоналями
                //std::cout << arr[i][j] << std::endl;
                sum += arr[i][j];
                mul *= arr[i][j];
            }
        }
    }
    long* pointer = new long[2] {sum, mul};
    return pointer;
}

int main(void) {
    unsigned int length;
    while (true) {
        std::cout << "Enter positive length = ";
        std::cin >> length;
        if (!std::cin.good() || length <= 0) {
            std::cout << "Invalid input! Length should be a positive number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }

    PTR_ARRAY(length, length);
    for (int i = 0; i < length; i++)  // Запрашиваем
        for (int j = 0; j < length; j++)
            askForValue(arr, i, j);

    PRINT_ARRAY(length, length);

    long* result = solve(arr, length);
    std::cout << "Sum is " << result[0] << std::endl << "Mul is " << result[1];

    CLR_ARRAY(length);
    delete[] result;
    return 0;
}

#endif
