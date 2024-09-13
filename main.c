#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

// Структура для хранения информации о командах
typedef struct Command {
    char name[20];
    char description[100];
    void (*function)(char *arg); // Указатель на функцию-обработчик
} Command;

// Функция-обработчик для команды "print"
void print_command(char *arg) {
    if (arg != NULL) {
        printf("%s\n", arg);
    } else {
        printf("Не указан текст для print\n");
    }
}

// Функция-обработчик для команды "lang"
void lang_command(char *arg) {
    if (arg != NULL) {
        setlocale(LC_ALL, arg);
        printf("Язык изменен на %s.\n", arg);
    } else {
        printf("Не указан язык.\n");
    }
}

// Функция для вывода справки о командах
void help_command(char *arg) {
    printf("Доступные команды:\n");
    printf("- help\n");
    printf("- print [текст]\n");
    //printf("- lang [язык]\n");
    //printf("- system [команда]\n"); // Добавленная команда
}

// Список команд
Command commands[] = {
    {"help", "Выводит список команд", help_command},
    {"print", "Выводит текст после команды", print_command},
    //{"lang", "Изменяет язык системы", lang_command},
    //{"system", "Выполняет системную команду", system_command}
};

int main() {
  // Список всех переменных
  char input[100]; // Создаём переменную которая будет принимать ввод от пользователя
  char *start_print; // Указатель на начало слова "print"
  char *first_word;
  char *start_lang;
  bool state = true;
  char *arg; // Переменная для аргумента команды
  int i; // Переменная для индекса в цикле


  // Создаём цикл для постоянного ожидания ввода от пользователя
  while (state) {
    printf("DPC < "); // Выводим в строку название программы

    fgets(input, 100, stdin); // Читаем текст с консоли
    input[strcspn(input, "\n")] = '\0'; // Удаляем символ новой строки из ввода

    // Получаем первое слово
    first_word = strtok(input, " ");

    // Проверяем, есть ли первое слово
    if (first_word != NULL) {
        // Поиск команды в списке
        for (i = 0; i < sizeof(commands) / sizeof(Command); i++) {
            if (strcmp(first_word, commands[i].name) == 0) {
                // Получаем аргумент
                arg = strtok(NULL, " ");
                // Вызываем функцию-обработчик команды
                commands[i].function(arg);
                break;
            }
        }

        if (i == sizeof(commands) / sizeof(Command)) {
            printf("Команды %s не существует\nВведите команду help для получения всех существующих команд\n", first_word);
        }
    } else {
        printf("Пустой ввод\n");
    }
  }
  return 0;
}
