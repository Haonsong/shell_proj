#include "exec_bin.h"

int output_detector(char ** argus,char * filename){
    int cur_position = 0;
    while(argus[cur_position] != NULL){
        if(strcmp(argus[cur_position], ">") == 0){
            if(argus[cur_position+2] ==NULL){
                strcpy(filename, argus[cur_position+1]);
                argus[cur_position] = NULL;
                return 1;
            }
        }
        cur_position++;
    }
    return 0;
}

int background_dectector( char** argus){
    int cur_position = 0;
    while(argus[cur_position] != NULL){
        if(strcmp(argus[cur_position], "&") == 0){
            argus[cur_position] = NULL;
            return 1;
        }
        cur_position++;
    }
    return 0;
}

int exec_bin( char ** argus){
    char * filename = (char * ) malloc(100*sizeof(char));
    int output_file = output_detector(argus,filename);
    int background = background_dectector(argus);
    int status ;
    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Forking error while executing %s\n", argus[0]);
        return 1;
    } else if(pid == 0){
        if(output_file){
            int output_file;
            if ((output_file = creat(filename, 0644)) < 0) {
                perror("Couldn't open the output file");
                exit(1);
            }

            dup2(output_file, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
            output_file = 0;
            close(output_file);
        }
        if(execvp(argus[0],argus) < 0){
            fprintf(stderr, "Execution failed: %s\n", argus[0]);
            exit(1);
            // return 1;
        }
        exit(0);
    }
    else{
        if(!background){
             while (!(wait(&status) == pid)) ;
        }

    }

    // exit(0);
    output_file = 0;
    background = 0;
    return 0;
}
