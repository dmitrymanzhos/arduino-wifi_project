// #include <stdio.h>
// #include <math.h>
// #include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

const char *COMMANDNAMES[] = {"write", "print", "rewrite", "get"};
const int MAXSIZE = 1024;

// int main(int argc, char *argv[]){
//     while (1){
//         char *command = malloc(1024);
//         // if (scanf("%s", command) && check_command(command) == 1) handle_command(command);
//         if(fgets(command, 1024, stdin) && check_command(command) == 1) handle_command(command, 0);
//     }
//     return 0;
// }

// создание новой бд
int create_db_file(char *name, char *field_names){
    FILE* fp = fopen(name, "a"); // --dlib full
    // FILE *fopen(), "w");
    fprintf(fp, "time %s", field_names);
    return 0;
}

// удаление бд
int delete_db_file(char *name){
    return remove(name);
}

// обработчик команд
int handle_command(char *command, int tmp){
    if (strncmp(command, COMMANDNAMES[0], 5) == 0){
        printf("yes\n");
        char *cmname = malloc(1024);
        char *filename = malloc(1024);
        char *time = malloc(1024);
        float field_value;
        // if (sscanf(command, "%s %s %s %f", cmname, filename, time, &field_value) == 4) printf("ok-scanf\n");
        if (sscanf(command, "%s %s %s %f", cmname, filename, time, &field_value) == 4 && check_time_format(time)){

            if (tmp)
                ;
                // return write_tmp(command, 0);
            else{
                printf("ok\n");
            
                return write(filename, time, field_value);
            }
        }
    // else if (strncmp(command, COMMANDNAMES[1], 5) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     if (sscanf(command, "%s %s", filename, time) == 2 && check_time_format(time)){
    //         if (tmp)
    //             return write_tmp(command);
    //         else
    //             return write(filename, time);
    //     }
    //     return print();
    // }
    //     else if (strncmp(command, COMMANDNAMES[2], 7) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     float field_value;
    //     if (sscanf(command, "%s %s %f", filename, time, &field_value) == 3 && check_time_format(time)){
    //         if (tmp)
    //             return write_tmp(command);
    //         else
    //             return write(filename, time, field_value);
    //     }
    //     return rewrite();
    // }
    //     else if (strncmp(command, COMMANDNAMES[3], 5) == 0){
    //     char *filename = malloc(1024);
    //     char *time = malloc(1024);
    //     if (sscanf(command, "%s %s", filename, time) == 3 && check_time_format(time)){
    //         if (tmp)
    //             return write_tmp(command);
    //         else
    //             return write(filename, time, field_value);
    //     }
    //     return get(filename, time);
    // }
}
}

int write(char *filename, char *time, float field_value){
    FILE* fp = fopen(filename, "a");
    fprintf(fp, "%s, %f\n", time, field_value);
    fclose(fp);
    return 0;
}

char* read(char *filename, char *time){
    FILE* fp = fopen(filename, "r");
    fclose(fp);

}

int rewrite(char *filename, char *time, float *field_values){
    return 0;
}

int get(char *filename, char *time){
    return 0;
}

int check_time_format(char *time){
    // hh.mm.ss.msms
    int h, m, s, ms = 0;
    printf("strlen=%ld\n", strlen(time));
    if (strlen(time) == 11 && sscanf(time, "%d.%d.%d.%d", &h, &m, &s, &ms) == 4 && (0 <= h <= 99) && (0 <= m <= 99) && (0 <= s <= 99) && (0 <= ms <= 99)){
        return 1;
    }
    else return 0;
}


//------------------------------------------------------------------------------------------------------------------
// обработка данных

float* find_medium(char *filename){}

int show_grapth(char * filename){}

/*!
Очищает буфер
*/
void clear_buf()
    {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n')
        ;
    return;
    }

