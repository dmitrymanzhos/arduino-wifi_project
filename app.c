#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"


// const char *FILENAME = "onegin.txt";
// typedef struct _info {
//     char **filenames;
//     int y;
// } info;

int main(int argc, char *argv[]){
    create_db_file("new.txt", "volts");
    while (1){
        char *command = malloc(1024);
        // if (scanf("%s", command) && check_command(command) == 1) handle_command(command);
        // if(fgets(command, 1024, stdin) && check_command(command) == 1) handle_command(command, 0);
        if(fgets(command, 1024, stdin)) handle_command(command, 0);
        printf("%s", command);
    }
    // free(command);
    return 0;
}


// extern char* buf = calloc(MAXSIZE, sizeof(char));

// int write_tmp(char *command, char* buf){
//     // char* buf = calloc(MAXSIZE, sizeof(char));

//     fread(buf, sizeof(char), fsize + 1, fp);
//     fclose(fp);
//     return (char*)buf;
//     return 0;
// }


// проверка валидности вводимой команды
// int check_command(char* command){
//     if (sscanf("b", &command_name, &file_name, &, &) == 4 && ....){
//         // запись во временный файл
//         FILE* tmp = fopen("tmp.txt", "a"); // --dlib full
//         fprintf(tmp, "%s\n", command);
//         return 0;
//     }
//     else return -1;
// }

