#ifndef FUNCTION_H
#define FUNCTION_H

// Структура для хранения информации о командах
typedef struct Command {
    char name[20];
    char description[100];
    void (*function)(char *arg[]); // Указатель на функцию-обработчик
} Command;

void print_command(char *arg[]);
void lang_command(char *arg[]);
void help_command(char *arg[]);
void time_command(char *arg[]);
void date_command(char *arg[]);
void version_command(char *arg[]);
void execute_command(char *first_word, char **args);

#endif
