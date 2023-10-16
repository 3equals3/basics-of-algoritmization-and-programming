/*
1.Для одномерного массива, состоящего из n вводимых с клавиатуры элементов (n – не больше 20), вычислить указанное в задании значение. Сумму модулей элементов массива, расположенных после первогоотрицательного элемента
2.Для одномерного массива, состоящего из n значений (n – не больше 20), решить поставленную задачу. Предусмотреть ввод значений массива как с клавиатуры, так и с помощью заполнения случайными числами. Выводить сообщения в случае невозможности выполнения поставленного задания: Вычислить произведение элементов массива, расположенных послепоследнего нулевого элемента и не превышающих среднее арифметическое
3.Для решения поставленной задачи использовать динамический массив. Решение задачи организовать в виде отдельной функции. В основной функции организовать ввод исходных данных, обращение к созданной функции и вывод результатов. При вводе исходных данных использовать обработку ввода нечисловых значений: Расположить в обратном порядке элементы массива, находящиесямежду первым и последним нулевым элементами.
*/

#define NUMBER 1

#include <iostream> // Импорт библиотек (ввод/вывод, математические функции)
#include <cmath>
#include <cstring> // Для memcpy

#if NUMBER == 1 

void askForValue(int* arr, int i) {
    while (true) {
        std::cout << "Enter value array[" << i << "] = ";
        std::cin >> arr[i];
        if (!std::cin.good()) {
            std::cout << "Invalid input! This value should be a number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
}

int main(void) { //Главная функция, с которой начинается выполнение программы
    unsigned int length, sum = 0; // нам нужна длина от 0 и сумма всегда будет положительной
    int negative_index = -1; // изначально -1, так ка индекс от 0 минимум

    while (true) {
        std::cout << "Enter positive length = ";
        std::cin >> length;
        if (!std::cin.good() || length <= 0 || length > 20) {
            std::cout << "Invalid input! Length should be positive and from 1 to 20." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    int* arr = new int[length]; //там в условии сказано про одномерный массив. Но ничего про динамический

    for (int i = 0; i < length; i++) {
        askForValue(arr, i); // Запрос значений в массиве
        if (arr[i] < 0 && negative_index == -1) {
            negative_index = i;
        }
        if (negative_index != i && negative_index != -1) sum += abs(arr[i]);
    }
    std::cout << "Sum of all elements after first negative is " << sum;

    delete[] arr;
    return 0;// успешное завершение программы
}

#elif NUMBER == 2

int getAverage(int* arr, int length) {
    long result = 0;
    for (int i = 0; i < length; i++) {
        result += arr[i];
    }
    result = (long) round((double) result / (double) length); // Да, целочисленное деление, но его тут достаточно
    return result; // Считаем в long чтобы можно было выйти за рамки массива
}

int askForValue(int* arr, int i) {
    while (true) {
        std::cout << "Enter value array[" << i << "] = ";
        std::cin >> arr[i];
        if (!std::cin.good()) {
            std::cout << "Invalid input! This value should be a number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break;//return arr[i]; // Иначе выходим из цикла
    }
    //std::cout << "[DEBUG] askForValue=" << arr[i] << " " << i << std::endl;
    return arr[i];
}

int main(void) { // Главная функция, с которой начинается выполнение программы
    srand(time(nullptr)); // Устанавливаем начальную точку генерирования случайности. nullptr вместо NULL это C-Lang tidy
    int length, mul = 1 /*равно 1 потому что иначе умножение ломается*/, null_index = -1, average = 0, count = 0;//, less_than_average_count = 0;
    int* arr = nullptr; // нет указателя

    while (true) {
        std::cout << "Enter length (if length <= 0 it will create random number in interval 0..20 and fill it) = ";
        std::cin >> length;
        if (!std::cin.good() || length > 20) {
            std::cout << "Invalid input! Length should be not more than 20 and be a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    if (length <= 0) { // Если делаем все случайно
        std::cout << "Filling with random numbers! Output may vary!" << std::endl;
        length = abs(rand() % (20 + 1)); // 20 + 1 потому что нас интересует лишь числа от 0 до 20. а 21 будет как 0
        arr = new int[length]; // Создаем массив. Так как указатель не "умный", он останется. Да-да
        for (int i = 0; i < length; i++) {
            arr[i] = rand() % 11; // Я решил сделать ограничение, чтобы числа были от -10 до 10. Конечно, можно больше, но иначе почти всегда будет срабатывать null_index == -1
            if (arr[i] == 0) null_index = i;
        }
    } else { // все что ниже это если мы сами заполняем нужное количество элементов
        arr = new int[length];
        for (int i = 0; i < length; i++) {
            //std::cout << "[DEBUG] " << askForValue(arr, i) << std::endl; // Запрос значений в массиве
            if (askForValue(arr, i) == 0) null_index = i;
        }
    }
    average = getAverage(arr, length);
    //std::cout << "[DEBUG] average=" << average << " null_index=" << null_index << std::endl;
    if (null_index == -1) { // Есть ли у нас нули или если этот 0 единственное число
        std::cout << "There is no 0's in array or 0 is one number in array! Aborting.";
        goto label_end;
    }
    for (int i = null_index + 1; i < length; i++) { // Начинаем со следующего после последнего нуля элемента
        if (arr[i] <= average) {
            count++;
            //std::cout << "[DEBUG] arr[i]=" << arr[i] << " i=" << i << std::endl;
            mul *= arr[i];
        }
    }
    if (count == 0) {
        std::cout << "There is no numbers after 0 and less than average! Aborting.";
        goto label_end;
    }
    std::cout << "Result: " << mul;

    delete[] arr;
    return 0;// успешное завершение программы

label_end:
    delete[] arr;
    return 1;// не успешное завершение программы! 1 это плохо
}


#elif NUMBER == 3

int askForValue(int* arr, int i) {
    while (true) {
        std::cout << "Enter value array[" << i << "] = ";
        std::cin >> arr[i];
        if (!std::cin.good()) {
            std::cout << "Invalid input! This value should be a number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break;
    }
    return arr[i];
}

void modifyArray(int* arr, int start, int end) {
    int length = end - start + 1; // увеличиваем размер на 1
    int* temp_arr = new int[length];
    for (int i = end, j = 0; i >= start; i--, j++) {
        temp_arr[j] = arr[i];
    }
    memcpy((int*)arr + start, temp_arr, length * sizeof(int));
    delete[] temp_arr;
}

int main(void) {
    unsigned int length = 0;
    int first_zero = -1, last_zero = -1;
    while (true) {
        std::cout << "Enter length = ";
        std::cin >> length;
        if (!std::cin.good()) {
            std::cout << "Invalid input! Length should be a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    int* arr = new int[length]; // создаем динамический массив
    for (int i = 0; i < length; i++) {
        //std::cout << "[DEBUG] " << askForValue(arr, i) << std::endl; // Запрос значений в массиве
        int value = askForValue(arr, i);
        if (value == 0) {
            last_zero = i;
            if (first_zero == -1) first_zero = i; //сработает только один раз.
        }
    }
    if (first_zero == last_zero || first_zero == -1) {
        std::cout << "First zero index equals to last or there is no 0! Aborting";
        goto label_end;
    }
    std::cout << "Array = {";
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << (i == length - 1 ? "" : ",");
    }
    std::cout << "} (Before)" << std::endl;
    modifyArray(arr, first_zero, last_zero);

    std::cout << "Array = {";
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << (i == length - 1 ? "" : ",");
    }
    std::cout << "} (After)" << std::endl;
    delete[] arr;
    return 0;
label_end:
    delete[] arr;
    return 0;
}

#endif
