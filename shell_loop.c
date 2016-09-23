
#include "shell_loop.h"

char ** read_CMD(char * command_in_string){
    // Counter may be ouputed in later work
    int cur_position = 0;
    char * space = " ";
    char * phaser = strtok(command_in_string,space);
    char ** command = (char **) malloc( ARGU_MAX_NUM * sizeof(char *));

    // Make sure command array is successfully created
    if ( !command ){
        fprintf(stderr, "Can't malloc space for phasing command" );
        exit(1);
    }

    // Read through command_in_string get the command and argus out
    while(phaser != NULL){

        if(cur_position >= ARGU_MAX_NUM - 2){
            fprintf(stderr, "Number of arguments exceeding limitation: %d", ARGU_MAX_NUM - 2);
            exit(1);
        }

        command[cur_position] = phaser;
        phaser = strtok(NULL, space);
        cur_position++ ;
    }
    command[cur_position] = NULL;
    // free(command_in_string);
    return command;
}

char * get_CMD(){
    char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    int position = 0;
    // Test the malloc is successful or not
    if (!command){
        fprintf(stderr, "Can't malloc for reading input command\n" );
        exit(1);
    }

    // Get every char in line
    while(position < CMD_MAX_LEN - 2){
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
    printf("myshell>");
    char * input  = get_CMD();
    printf("Got command: %s\n",input );
    char ** command = read_CMD(input);

    // testing the cmd reader
    int position = 0;
    while(command[position] != NULL){
        printf("%d.%s\n",position +1,command[position] );
        position++;
    }


    free(input);
    free(command);
}
