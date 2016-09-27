#define CMD_MAX_LEN 512

#include "shell_loop.h"

// #include <stdio.h>
// #include <stdlib.h>

// #include <error.h> // this libary defines the integer variable 'errno'

// requirement 512 + NULL = 513

int main(int argc, char *agrv[])
{
	// printf("mysh is starting with %s\n",agrv[1] );
	if(agrv[1] == NULL){
		shell_loop(NULL);
	}else{
		batch_loop(agrv[1]);
	}

	exit(0);

	// 		if(errno) printError(); // print out the error message

	return 0;
}
