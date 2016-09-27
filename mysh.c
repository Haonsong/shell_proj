#define CMD_MAX_LENGTH 512

#include "shell_loop.h"

// #include <stdio.h>
// #include <stdlib.h>

// #include <error.h> // this libary defines the integer variable 'errno'

// requirement 512 + NULL = 513

int main(int argc, char *agrv[])
{
	// printf("mysh is starting...\n" );
	shell_loop();
	exit(0);

	// 		if(errno) printError(); // print out the error message

	return 0;
}
