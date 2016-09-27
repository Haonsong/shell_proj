#ifndef SHELL_LOOP_H_
#define  SHELL_LOOP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exec_buildin.h"
#include "exec_bin.h"

#ifndef CMD_MAX_LEN
#define CMD_MAX_LEN 2048
#endif

#ifndef ARGU_MAX_NUM
#define ARGU_MAX_NUM 10
#endif

typedef struct command_list{
    char command[CMD_MAX_LEN+1];
    struct command_list * next_command;
}command_list;

void add_command(command_list *, char * );

void print_command(command_list *);

void batch_loop(char * );
// help .py to run
void python_adder(char ** argus);
// Divide the string command into command and arguments
char ** read_CMD(char * );

// Get the whole line of command with its arguments as a string
char * get_CMD();

// Here is the loop keep printing "myshell>" & deal with the command and its arguments
void shell_loop(char * );


#endif
