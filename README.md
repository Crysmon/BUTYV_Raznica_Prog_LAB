# BUTYV_Raznica_Prog_LAB
 
Поскольку CodeBlock плохо показал себя в работе совместно с win11 на моём ноутбуке, я писал код в VisualStudio 2022. 
Также при личной встрече было указано, что необходимо писать код на C, но по лабораторной работе используется C++. Из-за этой неопределённости использовались методы, которые в теории возможно реализовать в обычном C. Также из-за того, что не был указан конкретный вариант я взял несколько задач из различных вариантов.

Основная программа - mainTEST. main_back - backup одной из прошлых версий программы.

В данной программе реализован вывод вертикальной гистограммы с выравниванием по строкам и столбцам. Выравнивание предусмотрено с учётом максимального значения числа в целочисленном типе integer.
Реализована возможность задания символов для осей и самой гистограммы.
Не реализована обработка и "откидывание" пользователя при несовпадении заданного количества элементов и актуального количества. 

Вдоль дополнительной оси Y выводится количество элементов в столбце, то есть количество отдельных уникальных элементов среди введённых значений. 
По оси X выводятся те самые значения этих уникальных элементов, то есть среди введённых значений мы находим все отличающиеся друг от друга элементы.


Для проверки автоматическим тестом возможно обратиться к папке debug:

C:\...\x64\Debug> mainTEST.exe < example.input.txt > example.actual.txt

ниже приведён код программы:

// mainTEST.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <cmath>
#include <cstdlib>

using namespace std;

void Sortirovka(int *A, int N)// сортировка по возрастанию
{
    for (int i = 1; i < N; i++)
    {
        int j = i - 1, t;
        while (j >= 0 && A[j] > A[j+1]) 
        {
            t = A[j];
            A[j] = A[j + 1];
            A[j + 1] = t;
            j--;
        }
    }
}

int NumDigits(int x)//определение разряда 
{
    return (x < 10 ? 1 :
        (x < 100 ? 2 :
            (x < 1000 ? 3 :
                (x < 10000 ? 4 :
                    (x < 100000 ? 5 :
                        (x < 1000000 ? 6 :
                            (x < 10000000 ? 7 :
                                (x < 100000000 ? 8 :
                                    (x < 1000000000 ? 9 :
                                        10)))))))));
}

void PrintSpaces(int N)// функция для выравнивания гистограммы
{
    for (int i = 0; i < N; i++) {
        printf(" ");
    }
}
//функция для вывода оси Y
void Y_Axis(int* A, int* B, int M, int N, char O, int P) {
    for (int k = 0; k < M; k++) {
        if (A[k] == P) {
            PrintSpaces(N - B[k]);
            printf("%d", A[k]);
            printf("%c", O);
            break;
        }
        else if (M - 1 == k) {
            PrintSpaces(N);
            printf("%c", O);
        }
    }
}


int main() {
    int N, symbol_count_X = 0, symbol_count_Y = 0;      // N - количество исследуемых элементов,symbol... - значение максимального количества символов в записи массива quantity
    char bar_char, axisX_char, axisY_char;              //символы столбцов и "осей"
    int max_value;                                      // max_value - максимальное значение в количестве уникальных цифр/чисел

    printf ("Insert the number of meanings: ");         // мы заранее должны определить количество элементов для массива, N - количесво значений на вход
    scanf ("%d", &N);
    printf ("%d \n",N);
    printf ("Insert the meanings: ");                   //ввод значений, позже будет заменён на импорт из файла

    int *numbers = new int[N];                          // "динамический" массив значений
    for (int i = 0; i < N; i++) {
        scanf ("%d", &numbers[i]);
    }

    Sortirovka(numbers, N);                             // сортируем элементы по возрастанию
    int count_of_unique_elements = 1;
    //подсчёт количества уникальных элементов
    for (int i = 0; i < N-1; i++) {
        if (numbers[i] != numbers[i + 1]) {
            count_of_unique_elements++;
        }
    }

    int* quantity = new int[count_of_unique_elements];  // динамический массив для записи количества уникальных элементов из массива numbers
    int* digit_Y = new int[count_of_unique_elements];   // динамический массив для записи длины чисел из массива quantity
    int* X_table = new int[count_of_unique_elements];   // массив для отсортированных элементов массива numbers
    int* digit_X = new int[count_of_unique_elements];   // динамический массив для записи длины чисел из массива numbers
    for (int i = 0; i < count_of_unique_elements; i++) quantity[i] = 0;
    for (int i = 0; i < count_of_unique_elements; i++) X_table[i] = 0;
    //заполнение quantity
    int totalizer = 0;
    for (int i = 0; i < N - 1; i++) {
            quantity[totalizer] ++;
            if (numbers[i] != numbers[i + 1]) {
                totalizer += 1;
            }
    }
    quantity[count_of_unique_elements - 1] ++;
    //проверка
    printf("\nUnique elements: ");
    for (int i = 0; i < count_of_unique_elements; i++) {
        printf ("%d ", quantity[i]);
    }
    //Ищем максимальное значение по массиву уникальных элементов
    max_value = quantity[0];
    for (int x=0; x < count_of_unique_elements; x++) {
        if (quantity[x] > max_value) {
            max_value = quantity[x];
        }
    }

    printf ("\nThe symbol of COLUMN: ");
    scanf (" %c", &bar_char);
    printf ("The symbol of X AXIS: ");
    scanf (" %c", &axisX_char);
    printf("The symbol of Y AXIS: ");
    scanf(" %c", &axisY_char);
    printf("\n");
    //Записываем уникальные элементы массива numbers в новый массив
    totalizer = 0;
    for (int i = 0; i < N - 1; i++) {
        if (numbers[i] != numbers[i + 1]) {
            X_table[totalizer] = numbers[i];
            totalizer += 1;
        }
    }
    X_table[count_of_unique_elements - 1] = numbers[N - 1];
  
        //вычисления "разрядности" в количестве подсчитанных элементов (от quantity)
        for (int i = 0; i < count_of_unique_elements; i++) {
            digit_Y[i] = NumDigits(quantity[i]);
        }
        //вычисления "разрядности" элементов (от numbers)
        for (int i = 0; i < count_of_unique_elements; i++) {
            digit_X[i] = NumDigits(X_table[i]);
        }
        //определение максимального количества символов в выписанных элементах (от numbers)
        for (int x = 0; x < count_of_unique_elements; x++) {
            if (digit_X[x] > symbol_count_X) {
                symbol_count_X = digit_X[x];
            }
        }
        //определение максимального количества символов в записанном количестве элементов (от quantity)
        for (int x = 0; x < count_of_unique_elements; x++) {
            if (digit_Y[x] > symbol_count_Y) {
                symbol_count_Y = digit_Y[x];
            }
        }
        // Выводим гистограмму
        for (int i = max_value; i > 0; i--) {
                Y_Axis(quantity, digit_Y, count_of_unique_elements, symbol_count_Y, axisY_char, i);// вывод оси Y
            for (int j = 0; j < count_of_unique_elements; j++) {
                // Если значение в данных больше или равно текущей высоте, выводим символ столбца, иначе пробел
                if (quantity[j] >= i) {
                    printf("%c", bar_char);
                }
                else {
                    printf(" ");
                }
                PrintSpaces(symbol_count_X);
            }
            printf("\n"); // Переход на новую строку для следующего уровня гистограммы
        }
        // Выводим линию оси X
        PrintSpaces(symbol_count_Y + 1);
        for (int i = 0; i < count_of_unique_elements * (symbol_count_X + 1); i++) {
            printf("%c", axisX_char);
        }
        //выводим элементы к соответствующей оси Х
        printf("\n");
        PrintSpaces(symbol_count_Y + 1);
        for (int i = 0; i < count_of_unique_elements; i++) {
            printf("%d", X_table[i]);//здесь менял
            int t = (symbol_count_X + 1) - digit_X[i];
            PrintSpaces(t);
        }
        printf("\n");
        
    delete[] numbers;
    delete[] quantity;
    delete[] digit_Y;
    delete[] digit_X;
    delete[] X_table;

    return 0;
}