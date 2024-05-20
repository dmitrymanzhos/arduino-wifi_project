#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#ifndef __COMMANDNAMES__
#define __COMMANDNAMES__

#endif

// typedef struct _info {
//     char **filenames;
//     int y;
// } info;

// создание новой бд
int create_db_file(char *name, char *field_names);

// удаление бд
int delete_db_file(char *name);

// обработчик команд
int handle_command(char *command, char* filename, int tmp);


// int write_to_file_tmp(char *command, char* buf);

int write_to_file(char *filename, char *time, float field_value);

int check_time_format(char *time);

void clear_buf();

#endif