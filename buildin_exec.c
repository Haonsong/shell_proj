#include "buildin_exec.h"


// if the command is build in function then execute it and return 1 (true), else 0 (false)
int buildin_exec (char * command, char ** argus){

    if (!command || command == NULL){
        fprintf(stderr, "Buildin command is empty!");
    }

    if (strcmp(command, "cd") == 0){
        char * path;
        if(argus[0] == NULL){
            // printf("This is cd HOME\n");
            path = getenv("HOME");
        } else {
            // need to consider the error of no such directory
            path  = argus[0];
        }
        if(chdir(path) != 0){
            fprintf(stderr, "No such directory%s\n", argus[0]);
        }
    }else if (strcmp(command, "pwd") == 0){
        if(argus[0] != NULL){
            fprintf(stderr, "Can't find this usage of pws: %s\n", argus[0] );
        } else {
            char path [1000];
            getcwd(path, sizeof(path));
            fprintf(stdout,"%s\n",path);
            // free(path);
        }
    }else if (strcmp(command, "exit") == 0){
        exit(0);
    }else{
        return 0;
    }
    return 1;
}
