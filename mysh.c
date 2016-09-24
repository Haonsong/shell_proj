
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h> // this libary defines the integer variable 'errno'

#define CMD_MAX_LENGTH 512 // requirement 512 + NULL = 513

int printError(){
	char error message[30] = "An error has occurrednn";
  write(STDERRFILENO, error message, strlen(error message));
	return 0;
}

int main(int argc, char *agrv[])
{
	printf("My shell is starting...\n" );
	char cmdLine[CMD_MAX_LENGTH]; // to store the input string
	const char* space = " ";
	char* input; // to store the string tokens parsed from the input string

	while (1){

    printf("mysh>");
		// use char *fgets(char *str, int n, FILE *stream) to read the input into cmdLine
		// if user doesn't input anything, then continue,
		if (!fgets(cmdLine, CMD_MAX_LENGTH, stdin)) continue;

    // use char *strtok(char *str, const char *delim) to break
		// the cmdLine into tokens and get the first one
		input = strtok(cmdLine, space);

		if(input!=NULL) {

			errno = 0;
      // built-in: cd
			if(strcmp(input, "cd") == 0) {
				char *arg = strtok(NULL, space);
				if(!arg){
					// if no agrument, the working directory should be changed to
					// the path stored in $HOME environment variable
					getenv("HOME"); //can use
				} else {
					chdir(arg); //can use
				}
		  } else if (strcmp(input, "pwd")==0){ // built-in: pwd
				getcwd();
			} else if (strcmp(input, "exit") == 0){ // built-in: exit
				exit(0);
			} else { // executing files

				// first build the array
				char **inputList = malloc(sizeof(char*));
				inputList[0] = malloc(strlen(input)+1); // we need null terminator at each of string agrument
				strcpy(inputList[0], input)
				int num=1; // record how many agruments we have

				while(1){
					input = strtok(NULL, space); // get the next agrument
					if(input!=NULL){
						num++;
						inputList = realloc(inputList, sizeof(char*)*num); // add more space for holding more agruments
						inputList[num-1]=malloc(strlen(input)+1); // allocate space for each agrument string
						strcpy(inputList[num-1], input);
					} else {
						num++;
						inputList = realloc(inputList, sizeof(char*)*num);
						inputList[num-1]=NULL; //according to the hw document, we need to add a null element at the end of this inputList
						break;
					}
				}

				// here we need to add code for file excetuting/wait/redirection

				// free the space for inputList
				for(num=0; num<argc; num++){
					free(inputList[num]);
					inputList[num]=NULL;
				}

			} // end if-else

			if(errno) printError(); // print out the error message

		} // end if

		// we should contine if the user input nothing

	} // end while

	return 0;
}
