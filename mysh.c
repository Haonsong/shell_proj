#include "shell_loop.h"

int main(int argc, char *agrv[])
{

	if(agrv[1] == NULL){
		shell_loop(NULL);
	}else{
		batch_loop(agrv[1]);
	}

	exit(0);
	return 0;
}
