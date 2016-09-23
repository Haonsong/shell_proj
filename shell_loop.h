#ifndef SHELL_LOOP_H_
#define  SHELL_LOOP_H_

#include <stdlib.h>
#include <stdio.h>

#ifndef CMD_MAX_LEN
#define CMD_MAX_LEN 5
#endif


// Here is the loop keep printing "myshell>" & deal with the command and its arguments
char * read_CMD(char * command);
char * get_CMD();
void shell_loop();


#endif
