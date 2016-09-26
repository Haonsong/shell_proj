#include "exec_buildin.h"


// if the command is build in function then execute it and return 1 (true), else 0 (false)
int exec_buildin (char ** argus){

    if (!argus[0] || argus[0] == NULL){
        // fprintf(stderr, "Command is empty!");
        return 1;
    }

    if (strcmp(argus[0], "cd") == 0){
        char * path;
        if(argus[1] == NULL){
            // printf("This is cd HOME\n");
            path = getenv("HOME");
        } else {
            // need to consider the error of no such directory
            path  = argus[1];
        }
        if(chdir(path) != 0){
            fprintf(stderr, "No such directory%s\n", argus[1]);
        }
    }else if (strcmp(argus[0], "pwd") == 0){
        if(argus[1] != NULL){
            fprintf(stderr, "Can't find this usage of pws: %s\n", argus[1] );
        } else {
            char path [1000];
            getcwd(path, sizeof(path));
            fprintf(stdout,"%s\n",path);
            // free(path);
        }
    }else if (strcmp(argus[0], "exit") == 0){
        exit(0);
    }else{
        return 0;
    }
    return 1;
}
