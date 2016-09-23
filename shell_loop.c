
#include "shell_loop.h"

char * get_CMD(){
    char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    int position = 0;
    // Test the malloc is successful or not
    if (!command){
        fprintf(stderr, "Can't malloc for command\n" );
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

    fprintf(stderr, "Command exceeds the buff size: %d\n", CMD_MAX_LEN );
    free(command);
    exit(1);

}

void shell_loop() {
    // char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    printf("myshell>");
    char * command  = get_CMD();
    printf("Got command: %s\n",command );
    free(command);
}
