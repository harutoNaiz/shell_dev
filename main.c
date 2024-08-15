#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include <sys/types.h>

#define BUFF_TOKEN_LEN 64
#define BUFFER_SIZE 1024
#define TOK_ESC " \n\r\a\t" //these are the escape sequneces

void main_loop(void){

    char *line;
    char **args;
    int binary_result = 1;

    do{
        printf("< ");  
        line = read_line(); //the input to the shell
        args = split_line(line); //gets all the attributes by splittinf the input to the command line
        //the following line updates the status of the shell until exit called  
        // binary_result= 1; //testing the loop
        binary_result =  runner(args);
        free(line);
        free (args);

    } while(binary_result);
}

char* read_line(){

    int buff_size = BUFFER_SIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char)* buff_size);
    char holder;

    if(!buffer){
        fprintf(stderr ,"allocation error for inputs \n");
        exit(EXIT_FAILURE);
    }
    //now we need to read the line until the we reach EOF or an escape sequence
    while(1){

        holder = getchar();
        if(holder == EOF || holder == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else{
            buffer[position] = holder;
        }  position++;

        if(position >= buff_size){

            buff_size += BUFFER_SIZE;
            buffer = realloc(buffer, buff_size);
            if(!buffer){
                fprintf(stderr,"allocation error \n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

//we will use the string tokeniser (strtok) to tokenise the stdin line
char **split_line(char *line){

    int buff_size = BUFF_TOKEN_LEN;
    int position = 0;

    // this desscribes one token 
    char **tokens = malloc(buff_size * sizeof(char));
    //this is the pointer tokens
    char *token;

    if(!tokens){
        printf('allocation error !!');
        exit(EXIT_FAILURE);
    }
    //defineing the individual tokens
    token = strtok(line, TOK_ESC);

    while(token != NULL){
        tokens[position]=  token;
        position++;

        //edge cases
        //here we reallocate
        if(position> buff_size){
            buff_size += BUFFER_SIZE;
            buff_size = realloc(buff_size, sizeof(char*)*buff_size);
            if(!tokens){
                printf('realloc error !!');
                exit(EXIT_FAILURE);
            }
        }
        //now we can retokenise
        token = strtok(line, TOK_ESC);
    }

    // add a null pointer the the EOF
    tokens[position] = NULL;
    return tokens; //return the tokens array
}

//the code tokenised is passed into the runner which invokes the call
int runner(char** args){

    pid_t child;
    int flag;

    if(strcmp(args[0], "exit")==0){
        return exit_shell(args);
    }
    // creates the child process
    child = fork();
    
    if(child == 0){
        if(execvp(args[0], args) <0){
            printf("command not found :(\n");
        }
        exit(EXIT_FAILURE);

    } else if(child <0){
        
        printf("fork failed :(");
        exit(EXIT_FAILURE);
    
    } else{
        // waity for the child to complete exec
        waitpid(child, &flag, WUNTRACED);
    }
    return 1;

}

//the code to exit the shell
char** exit_shell(char **args){

    return 0;
}

int main(int argc, char **argv){

    main_loop();
    return EXIT_SUCCESS;
}

