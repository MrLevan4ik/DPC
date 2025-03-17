#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>
#include "function.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Russian_Russia.UTF8");
    char input[100]; // Переменная для ввода
    char *args[10];  // Массивnn аргументов
    bool state = true;

    // Цикл для постоянного ожидания ввода от пользователя
    while (state) {
        printf("DPC < "); // Вывод приглашения
        fgets(input, sizeof(input), stdin); // Чтение строки
        input[strcspn(input, "\n")] = '\0'; // Удаление символа новой строки

        // Разделение строки на команду и аргументы
        char *first_word = strtok(input, " ");
        if (first_word != NULL) {
            int i = 0;
            args[i++] = first_word;
            while ((args[i] = strtok(NULL, " ")) != NULL) {
                i++;
            }
            args[i] = NULL; // Завершаем массив аргументов

            execute_command(first_word, args);
        } else {
            printf("Пустой ввод\n");
        }
    }
    return 0;
}
