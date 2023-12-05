#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>


char currentDirectory[PATH_MAX] = "";

void setcwd(){
        if (getcwd(currentDirectory, sizeof(currentDirectory)) == NULL) {
            perror("getcwd() error");
        }
};

void changeCwd(char param1[]){
    printf("param 1 %s\n", param1);

}

void execCommand(char userInput[]){
    char* argv[100] = {};
    char*token;
    int i;

    token = strtok(userInput, " ");
    //processCommand(userInput);
    while (token != NULL) {
        printf("Token: %s\n", token);
        // Pass NULL to get next token
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    // add less then 100 parameters validation

    char* envp[] = {NULL};
    execve(argv[0], argv, envp);
    exit(0);

}

void processCommand(char userInput[]) {

    int cpid = fork();
    if (cpid == 0) {
        execCommand(userInput);
    }
    wait(&cpid);
    char *command;
    char *param1;
    //setcwd();
    //printf("this is the cwd %s\n", currentDirectory);
    printf("%s\n", userInput);
    command = strtok(userInput, " ");
    param1 = strtok(NULL, " ");
    printf("%s\n", command);
    if (strcmp(command, "cd") == 0) {
        printf("we made it\n");
        changeCwd(param1);
    }
}

int main() {
    char userInput[] = "/bin/ls -al main.c";
    char exit[6] = "exit\n";
    processCommand(userInput);
      //  system("ls");
    //system("cat main.c");
    return 0;

    do {
        printf(">>>");
        fgets(userInput,1000,stdin);

        if (strcmp(exit,userInput) == 0) {
            break;
        }



    }
    while (1 == 1);
    printf("Successfully exited");

}


