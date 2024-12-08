#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "function.h"
#include <string.h>

char programVersion[] = "0.1";

// Список команд
Command commands[] = {
    {"help", "Выводит список команд", help_command},
    {"print", "Выводит текст после команды", print_command},
    {"time", "Выводит время в формате часы:минуты:секунды", time_command},
    {"date", "Выводит дату в формате дни/месяцы/годы", date_command},
    {"V", "Выводит версию программы", version_command}
};

// Функция-обработчик для команды "print"
void print_command(char *arg[]) {
    if (arg != NULL) {
        int i = 0;
        while (arg[i] != NULL) {
            printf("%s ", arg[i]);
            i++;
        }
        printf("\n");
    } else {
        printf("Не указан текст для print\n");
    }
}

// Функция для вывода справки о командах
void help_command(char *arg[]) {
    size_t command_count = sizeof(commands) / sizeof(Command);

    printf("Доступные команды:\n");
    for (size_t i = 0; i < command_count; i++) {
        printf("- %s: %s\n", commands[i].name, commands[i].description);
    }
}

// Функция-обработчик для команды "time"
void time_command(char *arg[]) {
    if (arg == NULL || arg[0] == NULL) {
        time_t t = time(NULL);
        struct tm *aTm = localtime(&t);
        printf("%02d:%02d:%02d\n", aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    } else {
        printf("Неверный ввод\n");
    }
}

// Функция-обработчик для команды "date"
void date_command(char *arg[]) {
    if (arg == NULL || arg[0] == NULL) {
        time_t t = time(NULL);
        struct tm *aTm = localtime(&t);
        printf("%02d/%02d/%04d\n", aTm->tm_mday, aTm->tm_mon + 1, aTm->tm_year + 1900);
    } else {
        printf("Неверный ввод\n");
    }
}

void version_command(char *arg[]) {
    if (arg == NULL || arg[0] == NULL) {
        printf("%s\n", programVersion);    
    } else {
        printf("Неверный ввод\n");
    }
}

// Функция для поиска команды
void execute_command(char *first_word, char **args) {
    // Поиск команды
    int i;
    for (i = 0; i < sizeof(commands) / sizeof(Command); i++) {
        if (strcmp(first_word, commands[i].name) == 0) {
            commands[i].function(args + 1); // Передаем аргументы
            break;
        }
    }
    if (i == sizeof(commands) / sizeof(Command)) {
        printf("Команды %s не существует\n", first_word);
    }
}
