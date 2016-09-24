
#include "shell_loop.h"

char ** read_CMD(char * command_in_string){
    // Counter may be ouputed in later work
    int cur_position = 0;
    char * space = " ";
    char * phaser = strtok(command_in_string,space);
    char ** arguments = (char **) malloc( (ARGU_MAX_NUM + 1) * sizeof(char *));
    char * command_temp;
    // Make sure command array is successfully created
    if ( !arguments ){
        fprintf(stderr, "Can't malloc space for phasing command" );
        exit(1);
    }

    // Read through command_in_string get the command and argus out
    while(phaser != NULL){

        if(cur_position >= ARGU_MAX_NUM - 1){
            fprintf(stderr, "Number of arguments exceeding limitation: %d", ARGU_MAX_NUM - 2);
            exit(1);
        }
        if (cur_position == 0) {
            command_temp = phaser;
        }else{
            arguments[cur_position-1] = phaser;
        }
        phaser = strtok(NULL, space);
        cur_position++ ;
    }

    arguments[cur_position-1] = NULL;
    strcpy(command_in_string, command_temp);
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

    fprintf(stderr, "Command size exceeds the buff size: %d\n", CMD_MAX_LEN );
    free(command);
    exit(1);

}

void shell_loop() {
    // char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    while(1)
    {
        printf("mysh>");
        char * command  = get_CMD();

        char ** argus = read_CMD(command);

        // execute the command

        int buildin = buildin_exec(command, argus);
        // testing the cmd reader
        printf("Got command: %s build-in?: %d\n",command, buildin );
        int position = 0;
        while(argus[position] != NULL){
            printf("%d.%s\n",position +1,argus[position] );
            position++;
        }

        // while (position > -1){
        //     free (argus[position] );
        //     position--;
        // }
        free(argus);
        free(command);
    }
}
