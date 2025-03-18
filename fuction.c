#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "function.h"
#include <string.h>
#include <dirent.h>
#include <unistd.h> // Для chdir и getcwd
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_LINES 100
#define LINE_LENGTH 256

char programVersion[] = "0.4";

// Список команд
Command commands[] = {
    {"help", "Выводит список команд", help_command},
    {"hello", "Приветствие", greeting_command},
    {"print", "Выводит текст после команды", print_command},
    {"time", "Выводит время в формате часы:минуты:секунды", time_command},
    {"date", "Выводит дату в формате дни/месяцы/годы", date_command},
    {"v", "Выводит версию программы", version_command},
    {"clear", "Очищает консоль", clear_command},
    {"cd", "Переходит в указанную директорию", cd_command},
    {"mkdir", "Создает новую папку", mkdir_command},
    {"create", "Создает новый файл", create_file_command},
    {"rm", "Удаляет файл или папку", rm_command},
    {"ls", "Отображает список файлов и папок в текущей директории", ls_command},
    {"read", "Читает содержимое файла", read_file_command},
    {"pwd", "Отображает текущий путь", pwd_command},
    {"exit", "Завершает работу программы", exit_command},
    {"title", "Изменяет заголовок окна консоли", title_command}
};

// Функция-обработчик для команды "print"
void print_command(char *arg[]) {
    if (arg != NULL) {
        int i = 0;
        while (arg[i] != NULL) {
            printf("%s", arg[i]);
            if (arg[i + 1] != NULL) {
                printf(" ");
            }
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

// Очистка консоли
void clear_command(char *arg[]) {
    system("clear || cls");
}

// Перемещение по директории
void cd_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        struct stat st;
        if (stat(arg[0], &st) == 0 && S_ISDIR(st.st_mode)) {
            if (chdir(arg[0]) == 0) {
                printf("Перешли в директорию: %s\n", arg[0]);
            } else {
                perror("Ошибка при переходе");
            }
        } else {
            printf("Директория не существует: %s\n", arg[0]);
        }
    } else {
        printf("Не указана директория.\n");
    }
}

// Создание папки
void mkdir_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        if (mkdir(arg[0]) == 0) {
            printf("Папка %s создана.\n", arg[0]);
        } else {
            perror("Ошибка при создании папки");
        }
    } else {
        printf("Не указано имя папки.\n");
    }
}

// Создание файла
void create_file_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        struct stat st;
        if (stat(arg[0], &st) != 0) {
            FILE *file = fopen(arg[0], "w");
            if (file) {
                printf("Файл %s создан.\n", arg[0]);
                fclose(file);
            } else {
                perror("Ошибка при создании файла");
            }
        } else {
            printf("Файл уже существует: %s\n", arg[0]);
        }
    } else {
        printf("Не указано имя файла.\n");
    }
}

// Удаление папки/файла
void rm_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        struct stat st;
        if (stat(arg[0], &st) == 0) {
            if (remove(arg[0]) == 0) {
                printf("Файл или папка %s удалены.\n", arg[0]);
            } else {
                perror("Ошибка при удалении");
            }
        } else {
            printf("Файл или папка не существуют: %s\n", arg[0]);
        }
    } else {
        printf("Не указано имя файла или папки.\n");
    }
}

// Отображение файлов в текущей директории
void ls_command(char *arg[]) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir) {
        printf("Содержимое текущей директории:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf("- %s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("Ошибка при открытии директории");
    }
}

// Чтение файла
void read_file_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        FILE *file = fopen(arg[0], "r");
        if (file) {
            char line[LINE_LENGTH];
            printf("Содержимое файла %s:\n", arg[0]);
            while (fgets(line, sizeof(line), file)) {
                printf("%s", line);
            }
            fclose(file);
        } else {
            perror("Ошибка при открытии файла");
        }
    } else {
        printf("Не указано имя файла.\n");
    }
}

// Показать текущий путь
void pwd_command(char *arg[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("Текущая директория: %s\n", cwd);
    } else {
        perror("Ошибка получения текущей директории");
    }
}

// Приветствие
void greeting_command(char *arg[]) {
    if (arg == NULL || arg[0] == NULL) {
        printf("Привет, это DPC(Digit Personal Console).\n");
        printf("Созданная в обучающих целях и является\n"); 
        printf("самой базовой и премитивной моделью консоли.\n");
        printf("Это версия: %s. Введи help чтобы получить список доступных команд\n", programVersion);    
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

// Функция для выхода из программы
void exit_command(char *arg[]) {
    if (arg == NULL || arg[0] == NULL) {
        printf("Завершение работы программы...\n");
        exit(0);
    } else {
        printf("Неверный ввод\n");
    }
}

// Функция для изменения заголовка окна
void title_command(char *arg[]) {
    if (arg != NULL && arg[0] != NULL) {
        // Объединяем все аргументы в одну строку
        char title[256] = "";
        int i = 0;
        while (arg[i] != NULL) {
            strcat(title, arg[i]);
            if (arg[i + 1] != NULL) {
                strcat(title, " ");
            }
            i++;
        }
        
        // Конвертируем ANSI строку в UTF-16
        wchar_t wtitle[256];
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 256);
        
        // Устанавливаем заголовок окна
        SetConsoleTitleW(wtitle);
        printf("Заголовок окна изменен на: %s\n", title);
    } else {
        printf("Не указан текст для заголовка.\n");
    }
}
