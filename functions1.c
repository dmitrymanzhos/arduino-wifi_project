// функции для работы с файлом

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

const char *COMMANDNAMES[] = {"write_to_file", "print", "rewrite_to_file", "get"};
const int MAXSIZE = 1024;

// создание новой бд
int create_db_file(char name[], char *field_names){
    FILE* fp = fopen(name, "w"); // --dlib full
    // FILE *fopen(), "w");
    fprintf(fp, "time %s\n", field_names);
    fclose(fp);
    return 0;
}
// удаление бд
int delete_db_file(char *name){
    return remove(name);
}

// обработчик команд
// обработчик команд
int handle_command(char *command, char filename[], int tmp){
    if (strncmp(command, COMMANDNAMES[0], 5) == 0){
        printf("yes\n");
        char *cmname = malloc(1024);
        // char *filename = malloc(1024);
        char *time = malloc(1024);
        float field_value;
        // if (sscanf(command, "%s %s %s %f", cmname, filename, time, &field_value) == 4) printf("ok-scanf\n");
        // if (sscanf(command, "%s %s %s %f", cmname, filename, time, &field_value) == 4 && check_time_format(time)){
        if (sscanf(command, "%s %s %f", cmname, time, &field_value) == 3 && check_time_format(time)){

            if (tmp)
                ;
                // return write_to_file_tmp(command, 0);
            else{
                printf("ok\n");
            
                return write_to_file(filename, time, field_value);
            }
        }

        free(cmname);
        free(time);
    // else if (strncmp(command, COMMANDNAMES[1], 5) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     if (sscanf(command, "%s %s", filename, time) == 2 && check_time_format(time)){
    //         if (tmp)
    //             return write_to_file_tmp(command);
    //         else
    //             return write_to_file(filename, time);
    //     }
    //     return print();
    // }
    //     else if (strncmp(command, COMMANDNAMES[2], 7) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     float field_value;
    //     if (sscanf(command, "%s %s %f", filename, time, &field_value) == 3 && check_time_format(time)){
    //         if (tmp)
    //             return write_to_file_tmp(command);
    //         else
    //             return write_to_file(filename, time, field_value);
    //     }
    //     return rewrite_to_file();
    // }
    //     else if (strncmp(command, COMMANDNAMES[3], 5) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     if (sscanf(command, "%s %s", filename, time) == 3 && check_time_format(time)){
    //         if (tmp)
    //             return write_to_file_tmp(command);
    //         else
    //             return write_to_file(filename, time, field_value);
    //     }
    //     return get(filename, time);
    // }
}
}


// int write_to_file_tmp(char *command, char* buf);

int write_to_file(char filename[], char *time, float field_value){
    FILE* fp = fopen(filename, "a");
    printf(">>>>>>>>>>>>>>%p\n", fp);
    fprintf(fp, "%s, %f\n", time, field_value);
    fclose(fp);
    return 0;
}

int check_time_format(char *time){
    int s = 0;
    if (sscanf(time, "%d", &s ) == 1){
        return 1;
    }
    else return 0;
}

void clear_buf(){
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
    return;
}
