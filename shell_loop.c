
#include "shell_loop.h"
#define EXIT 1

void print_error_massage(int exit_code){
    char error_message[30] = "A error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    if(exit_code){
        exit(1);
    }
}

// Must get a non-NULL command_list or will get Core dump.
void add_command(command_list * command_head, char * command){
    command_list * new_command = command_head;
    while(new_command->next_command != NULL){
        new_command = new_command->next_command;
    }
    new_command->next_command = malloc(sizeof(command_list));
    strcpy(new_command->next_command->command,command);
    new_command->next_command->next_command=NULL;
}

void print_command(command_list * command_head){
    command_list * cur_command = command_head;

    do{
        printf("%s ->", cur_command->command);
        cur_command = cur_command->next_command;
    }while(cur_command != NULL);
}

void batch_loop(char * filename){
    // printf("Batch file is: %s\n", filename);

    FILE * file;
    char buffer [100];
    command_list * list_head = malloc(sizeof(command_list));
    file = fopen (filename , "r");
    if (file == NULL)
        print_error_massage(EXIT);
    else {
        if ( fgets (buffer , 100 , file) != NULL ){
            char * one_command = strtok(buffer,"\n\r");
            if(one_command != NULL){
                strcpy(list_head->command,one_command);
                list_head->next_command = NULL;
            }
            while(fgets(buffer,100,file)!= NULL){
                one_command = strtok(buffer,"\n\r");
                if(one_command != NULL){
                    add_command(list_head, one_command);

                }
            }
            fclose (file);
        }
    }

    while(list_head != NULL){
        write(STDOUT_FILENO, list_head->command, strlen(list_head->command) );
        write(STDOUT_FILENO, "\n", 1 );
        shell_loop(list_head->command);
        list_head = list_head->next_command;
    }

}

// Fun feature for python

void python_adder(char ** argus){
    if(argus[0] != NULL && argus[1] == NULL){
        char * py_copy = (char*) malloc(CMD_MAX_LEN*sizeof(char));
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
    char * space = " \t\n\r";
    char * phaser = strtok(command_in_string,space);
    char ** arguments = (char **) malloc( (ARGU_MAX_NUM + 1) * sizeof(char *));

    // Make sure command array is successfully created
    if ( !arguments ){
        fprintf(stderr, "Can't malloc space for phasing command" );
        exit(1);
    }

    // Read through command_in_string get the command and argus out
    while(phaser != NULL){

        if(cur_position >= ARGU_MAX_NUM - 1){
            fprintf(stderr, "Number of arguments exceeding limitation: %d", ARGU_MAX_NUM );
            return NULL;
        }

        arguments[cur_position] = phaser;
        phaser = strtok(NULL, space);
        cur_position++ ;
    }

    arguments[cur_position] = NULL;
    return arguments;
}

char * get_CMD(){
    char * command = (char *) malloc((CMD_MAX_LEN + 1) * sizeof(char));
    int position = 0;
    // Test the malloc is successful or not
    if (!command){
        // Edit error here
        fprintf(stderr, "Can't malloc for reading input command\n" );
        exit(1);
    }

    // Get every char in line
    while(position < CMD_MAX_LEN - 1){
        char c = getchar();


        // Reach the end of line
        if (c == EOF || c == '\n') {//

            if (position == 0) {
                return " ";
            }
            command[position] = '\0';

            return command;
        }

        command[position] = c ;
        position++ ;

    }
    char c;
    do{
        c = getchar();
    } while(c  !=  EOF && c != '\n');
    // fprintf(stderr, "Command size exceeds the buff size: %d Bytes \n", CMD_MAX_LEN );
    free(command);
    print_error_massage(0);
    return NULL;

}

void shell_loop(char * cmd_line) {
    do{
        char * command ;
        if(cmd_line == NULL){
            printf("mysh> ");
            command  = get_CMD();
        }else{
            command = cmd_line;
        }

        // Directly skip this round if empty
        if(command == NULL) continue;
        int whitespace_counter= 0;
        while(  command[whitespace_counter] == ' '||
                command[whitespace_counter] == '\t' ){
            whitespace_counter++;
        }
        if(strcmp(command," ") == 0 || whitespace_counter == strlen(command)) continue;

        // Split up the command with space tab newline
        char ** argus = read_CMD(command);
        if(argus[0] == NULL) continue;

		// add python to .py
        python_adder(argus);

        // execute the command
        int buildin = exec_buildin(argus);
        if(!buildin){
            if (exec_bin(argus)){
                // Print error and exit the child process
                print_error_massage(EXIT);

            }
        }

        free(argus);
    }while(cmd_line == NULL);
}
