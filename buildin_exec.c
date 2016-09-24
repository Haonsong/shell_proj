#include "buildin_exec.h"



int buildin_exe (char * command, char ** argus){

    if (!command || command == NULL){
        fprintf(stderr, "Buildin command is empty!");
    }

    if (strcmp(input, "cd") == 0){
        if(argus == NULL){
            getenv("HOME");
        } else {
            // need to consider the error of no such directory
            chdir(argus);
        }
    }else if (strcmp(input, "pwd") == 0){
        if(argus != NULL){
            fprintf(stderr, "Can't find this usage of pws: %s\n", argus[0] );
        } else {
            getcwd();
        }
    }else if (strcmp(input, "exit") == 0){
        exit(0);
    }else{
        return 0;
    }
    return 1;
}
