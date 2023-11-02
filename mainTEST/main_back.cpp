// mainTEST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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

int NumDigits(int x)
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

int main() {
    int N, symbol_count = 0; // N - количество исследуемых элементов,symbol... - значение максимального количества символов в записи массива B
    char bar_char, axis_char; //символы столбцов и "оси"
    int max_value, min_value, max_digit = 0;// max_value, min_value - максимальное и минимальное значение в

    printf ("Insert the number of meanings: "); // мы заранее должны определить количество элементов для массива, N - количесво значений на вход
    scanf ("%d", &N);
    printf ("%d \n",N);
    printf ("Insert the meanings: ");//ввод значений, позже будет заменён на импорт из файла

    int *A = new int[N]; // "динамический" массив значений


    for (int i = 0; i < N; i++) {
        scanf ("%d", &A[i]);
    }

    // 4 5 4 3 4 5 4 3 4 4 4 5 4 4 4 6 4  
    // 3 3 4 4 4 4 4 4 4 4 4 4 4 5 5 5 6
    
    Sortirovka(A, N);
    
    int count_of_unique_elements = 1;

    for (int i = 0; i < N-1; i++) {
        if (A[i] != A[i + 1]) {
            count_of_unique_elements++;
        }
    }

    int* B = new int[count_of_unique_elements];// динамический массив для записи количества уникальных элементов из массива А
    int* C = new int[count_of_unique_elements];// динамический массив для записи длины чисел из массива B
    for (int i = 0; i < count_of_unique_elements; i++) B[i] = 0;

    int totalizer = 0;
    for (int i = 0; i < N - 1; i++) {
            B[totalizer] ++;
            if (A[i] != A[i + 1]) {
                totalizer += 1;
            }
    }
    B[count_of_unique_elements - 1] ++;

    for (int i = 0; i < N; i++) {
        printf ("%d ", A[i]);
    }
    printf ("\n");
    for (int i = 0; i < count_of_unique_elements; i++) {
        printf ("%d ", B[i]);
    }

    min_value = B[0];
    max_value = B[0];

    for (int x=0; x < count_of_unique_elements; x++) {
        if (B[x] < min_value) {
            min_value = B[x];
        }
        else if (B[x] > max_value) {
            max_value = B[x];
        }
    }

    printf ("\nInsert the symbol of stolbec: ");
    scanf (" %c", &bar_char);

    printf ("Insert the symbol of axis: ");
    scanf (" %c", &axis_char);

    
    for (int i = 0; i < count_of_unique_elements; i++) {
        C[i] = NumDigits(B[i]);
    }

    for (int x = 0; x < count_of_unique_elements; x++) {
        if (C[x] > symbol_count) {
            symbol_count = C[x];
        }
    }
    // Выводим гистограмму
    for (int i = max_value; i > 0; i--) {
        for (int j = 0; j < count_of_unique_elements; j++) {
            int t = symbol_count;
            
            // Если значение в данных больше или равно текущей высоте, выводим символ столбца, иначе пробел
            if (B[j] >= i) {
                printf ("%c ", bar_char);
            }
            else { 
                printf ("  ");
            }
            while (t > 1) {
                printf(" ");
                t--;
            }
        }
        printf ("\n"); // Переход на новую строку для следующего уровня гистограммы
    }
    // Выводим линию оси X
    for (int i = 0; i < (count_of_unique_elements * 3)/2 ; i++) {
        int t = symbol_count;
        while (t > 1) {
            printf ("%c", axis_char);
            t --;
        }
        printf("%c", axis_char);
    }
    //выводим количество элементов к соответствующей оси
    printf("\n");
    /*for (int i = 0; i < count_of_unique_elements - 2; i++) {
        symbol_count += 1;
    }
    */
    for (int i = 0; i < count_of_unique_elements; i++) {
        printf("%d ", B[i]);
        if (C[i] != symbol_count) {
            printf("  ");
            symbol_count--;
        }
        else printf(" ");
    }
    printf("\n");

    for (int i = 0; i < count_of_unique_elements; i++) B[i] = 0;
    totalizer = 0;
    for (int i = 0; i < N - 1; i++) { 
        if (A[i] != A[i + 1]) {
            B[totalizer] = A[i];
            totalizer += 1;
        }
    }
    B[count_of_unique_elements-1] = A[N-1];


    // Выводим подписи значений
    printf ("Meanings: ");
    for (int i = 0; i < count_of_unique_elements; i++) {
        printf ("%d ", B[i]);
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
// 4 5 4 3 4 5 4 3 4 4 4 5 4 4 4 6 4
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
