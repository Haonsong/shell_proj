#include "exec_bin.h"

int exec_bin( char ** argus){

    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Forking error while executing %s\n", argus[0]);
        return 1;
    } else if(pid == 0){
        if(execvp(argus[0],argus) < 0){
            fprintf(stderr, "Execution failed: %s\n", argus[0]);
            exit(1);
            // return 1;
        }
        exit(0);
    }
    wait(NULL);
    // exit(0);
    return 0;
}
