/*
1 Ввести строку символов. Определить длину введенной строки L, и если длина L кратна 4, то первая часть строки меняется местами со второй.
2 Дана строка, состоящая из слов, разделенных пробелами. Разбить исходную строку на две подстроки, причем первая длиной k символов, если
  на k-ю позицию попадает слово, то его следует отнести ко второй строке. Значение k вводится с клавиатуры.
3 Ввести с клавиатуры строку символов, представляющую собой некоторое предложение. Обрезать предложение так, чтобы оно содержало только
  второе, третье и четвертое слова. Результирующую строку вывести на экран.
*/
#define PROBLEM 1
#define STR_SIZE 128

#include <iostream>
#include <cstring>
#include <malloc.h>


#if PROBLEM == 1

int main(void) {
    char text[STR_SIZE];
    size_t len = 0;

    std::cout << "Enter string: ";
    std::cin.getline(text, STR_SIZE);

    
    if ((len = strlen(text)) % 4 == 0) { // сразу записываю переменную как размер и проверяю кратно ли 4
        for (int i = 0; i < len / 2; i++) { // перебираю половину
            text[i] ^= text[i + len / 2] ^= text[i] ^= text[i + len / 2]; // a ^= b ^= a ^= b поменяет местами переменные без необходимости вводить третью
        }
    }
    std::cout << text;

    return 0;
}

#elif PROBLEM == 2

int main(void) {
    char text[STR_SIZE] = "The quick brown fox jumps over the lazy dog";
    unsigned short k;

    while (true) {
        std::cout << "Enter K = ";
        std::cin >> k;
        if (!std::cin.good() || k >= strlen(text)) {
            std::cout << "Invalid input! This value should be a positive number and less than " << strlen(text) << "!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем предыдущий ввод чтобы не было зацикливания
        }
        else break; // Иначе выходим из цикла
    }
    while (text[k] != 0x20 && k > 0) {  // 0x20 - пробел
        k--; //ищем начало слова если не пробел
    }

    char t1[STR_SIZE + 1], t2[STR_SIZE + 1];
    memcpy(t1, text, k);
    memcpy(t2, text + k, strlen(text) - k); // мы можем прибавить k так как это указатель на массив по 1 байту, иначе надо было бы делить на sizeof 
    t1[k] = 0x0; t2[strlen(text) - k] = 0x0;
    std::cout << "First: "  << t1 << std::endl;
    std::cout << "Second: " << t2 << std::endl;

    return 0;
}


#elif PROBLEM == 3

int main(void) {
    char text[STR_SIZE];

    std::cout << "Enter string: ";
    std::cin.getline(text, STR_SIZE);
    
    size_t length = strlen(text);
    int count = 0, startIdx = 0, endIdx = 0;

    for (int i = 0; i < length; i++) {
        if ((i + 1) == length || (text[i] != 0x20 && text[i + 1] == 0x20)) {
            count++;
            if (count == 1) {
                startIdx = i + 1;
                continue; // пропустит следующую проверку
            }
            if (count == 4) {
                endIdx = i + 1;
                break;
            }
        }
    }

    if (count != 4) {
        std::cout << "Could not find 2nd, 3rd, and 4th words in the string." << std::endl;
    } else {
        char substr[STR_SIZE];
        memcpy(substr, text + startIdx, endIdx - startIdx);
        substr[endIdx - startIdx] = '\0';
        std::cout << "Substring: " << substr << std::endl;
    }
    return 0;
}

#endif
