
#include "shell_loop.h"
int background = 0;

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
        perror ("Error opening file");
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
    // char * one_command = strtok(buffer,"\n\r");
    // command_list * list_head = malloc(sizeof(command_list));
    // strcpy(list_head->command,one_command);
    // list_head->next_command = NULL;
    // one_command = strtok(NULL,"\n\r");
    // while(one_command != NULL){
    //     add_command(list_head, one_command);
    //     one_command = strtok(NULL,"\n\r");
    // }
    // print_command(list_head);
    //printf("list: %s\n", list_head->command);
    while(list_head != NULL){
        write(STDOUT_FILENO, list_head->command, strlen(list_head->command) );
        write(STDOUT_FILENO, "\n", 1 );
        shell_loop(list_head->command);
        list_head = list_head->next_command;
    }

}

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

void shell_loop(char * cmd_line) {
    // char * command = (char *) malloc(CMD_MAX_LEN* sizeof(char));
    do
    {
        char * command ;
        if(cmd_line == NULL){
        // char * filename = (char * ) malloc(100*sizeof(char));
            printf("mysh> ");
            command  = get_CMD();
        }else{
            command = cmd_line;
        }
        char ** argus = read_CMD(command);

        python_adder(argus);

        // int position = 0;
        // while(argus[position] != NULL){
        //     printf("%d.%s\n",position +1,argus[position] );
        //     position++;
        // }

        int buildin = exec_buildin(argus);
        if(!buildin){
            if (exec_bin(argus)){

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
    }while(cmd_line == NULL);
}
