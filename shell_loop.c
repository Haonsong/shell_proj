
#include "shell_loop.h"
int background = 0;


// Fun feature for python

void python_adder(char ** argus){
    if(argus[1] == NULL){
        char * py_copy = (char*) malloc(100*sizeof(char));
        strcpy(py_copy,argus[0]);
        int py_len = strlen(py_copy);
        if (py_copy[py_len-1] == 'y' &&
            py_copy[py_len-2] == 'p' &&
            py_copy[py_len-3] == '.'){
            argus[2] = NULL;
            argus[1] = argus[0];
            argus[0] = "python";
        }
        free(py_copy);
    }
}

char ** read_CMD(char * command_in_string){
    // Counter may be ouputed in later work
    int cur_position = 0;
    char * space = " ";
    char * phaser = strtok(command_in_string,space);
    char ** arguments = (char **) malloc( (ARGU_MAX_NUM + 1) * sizeof(char *));
    // char * command_temp;
    // Make sure command array is successfully created
    if ( !arguments ){
        fprintf(stderr, "Can't malloc space for phasing command" );
        exit(1);
    }

    // Read through command_in_string get the command and argus out
    while(phaser != NULL){

        if(cur_position >= ARGU_MAX_NUM - 1){
            fprintf(stderr, "Number of arguments exceeding limitation: %d", ARGU_MAX_NUM );
            exit(1);
        }
        // if (cur_position == 0) {
        //     command_temp = phaser;
        // }else{
        //     arguments[cur_position-1] = phaser;
        // }
        arguments[cur_position] = phaser;
        phaser = strtok(NULL, space);
        cur_position++ ;
    }

    arguments[cur_position] = NULL;
    // strcpy(command_in_string, command_temp);
    // free(command_in_string);
    return arguments;
}

char * get_CMD(){
    char * command = (char *) malloc((CMD_MAX_LEN + 1) * sizeof(char));
    int position = 0;
    // Test the malloc is successful or not
    if (!command){
        fprintf(stderr, "Can't malloc for reading input command\n" );
        exit(1);
    }

    // Get every char in line
    while(position < CMD_MAX_LEN - 1){
        char c = getchar();

        // Reach the end of line
        if (c == EOF || c == '\n') {
            command[position] = '\0';
            return command;
        }

        command[position] = c ;
        position++ ;

    }

    fprintf(stderr, "Command size exceeds the buff size: %d Bytes \n", CMD_MAX_LEN );
    free(command);
    exit(1);

}

void shell_loop() {
    // char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    while(1)
    {
        printf("mysh> ");
        char * filename = (char * ) malloc(100*sizeof(char));
        char * command  = get_CMD();
        char ** argus = read_CMD(command);

        // ============ get the > =================
        int position_in_argus = 0;
        while(argus[position_in_argus] != NULL){
            if(strcmp(argus[position_in_argus], ">") == 0){
                if(argus[position_in_argus+2] ==NULL){
                    strcpy(filename, argus[position_in_argus+1]);
                    output_file = 1;
                    argus[position_in_argus] = NULL;
                }
            }
            position_in_argus++;
        }

        printf("filename %s output_file: %d\n",filename,output_file );
        // ========================================

        if (output_file)
        {

                int fd1;
                if ((fd1 = creat(filename, 0644)) < 0) {
                        perror("Couldn't open the output file");
                        exit(1);
                }

                dup2(fd1, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
                output_file = 0;
                close(fd1);
        }


        python_adder(argus);

        // int position = 0;
        // while(argus[position] != NULL){
        //     printf("%d.%s\n",position +1,argus[position] );
        //     position++;
        // }

        int buildin = exec_buildin(argus);
        if(!buildin){
            if (exec_bin(argus)){
                // wait(NULL);
                fprintf(stderr, "Unknown error happened when executing %s\n", argus[0]);
            }
        }
        // if(output_file){
        //     output_file = 0;
        //     close(fd1);
        // }
        // testing the cmd reader
        // printf("Got command: %s build-in?: %d\n",command, buildin );
        // int position = 0;
        // while(argus[position] != NULL){
        //     printf("%d.%s\n",position +1,argus[position] );
        //     position++;
        // }
        // while (position > -1){
        //     free (argus[position] );
        //     position--;
        // }
        free(argus);
        // free(command);
    }
}
