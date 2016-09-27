#ifndef EXEC_BIN_H_
#define EXEC_BIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int output_detector(char **, char *);
int exec_bin ( char **);

#endif
