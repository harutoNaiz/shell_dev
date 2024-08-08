#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define BUFFER_SIZE 1024

void main_loop(){
    char *line;
    char **args;
    int binary_result;

    do{
        line = read_line(); //the input to the shell
        args = split_line(line); //gets all the attributes by splittinf the input to the command line
        //the following line updates the status of the shell until exit called  
        binary_result =  runner(args);
        free(line);
        free (args);

    } while(binary_result);
}

char* read_line(){

    int buff_size = BUFFER_SIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char)* buff_size);

    if(!buffer){
        printf("allocation error for inputs \n");
        exit(1);
    }

    //now we need to read the line until the we reach EOF or an escape sequence
    

}

int main(int argc, char **argv){

    main_loop();

    return EXIT_SUCCESS;

}