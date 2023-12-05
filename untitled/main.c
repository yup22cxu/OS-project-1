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
    char* dupe = strdup(userInput);
    char* ifBin = strtok(userInput, "/");
    char inBin[1000] = {"/bin/"};
    printf("ifBin: %s\n", ifBin);
    int i = 0;
    printf("User input: %s\n",userInput);
    token = strtok(dupe, " ");

    while (token != NULL) {
        printf("UI: %s, Token: %s, Index : %d\n", dupe,token,i);
        // Pass NULL to get next token
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    char *envp[] = {NULL};
    if (strcmp(ifBin, "bin") == 0){
        printf("exec: %d\n", execve(argv[0], argv, envp));
        exit(0);
    }
    else {
        strcat(inBin,argv[0]);
        printf("exec: %d\n", execve(inBin, argv, envp));
        exit(0);
    }



}

void processCommand(char userInput[]) {
    int pid = getpid(); // parent pid
    pid_t cpid = fork();
    pid_t cppid = getppid(); // childs parent pid

    printf("cpid: %d, cppid: %d, pid: %d\n",cpid, cppid, pid);
    if (cppid == pid) {
        execCommand(userInput);
        exit(1);
    }
    int status;
    waitpid(cpid, &status,0);
}

int main() {

    char userInput[1000];// = "/bin/ls -al main.c";

    do {
        printf(">>>");

        fgets(userInput,1000,stdin);

        size_t newline_pos = strcspn(userInput, "\n");
        printf("Newline pos: %d\n", newline_pos);
        userInput[newline_pos] = '\0';
        // check if exit first
        if (strcmp("exit",userInput) == 0) {
            break;
        }
        else {
        // check cd


            processCommand(userInput);
        }
    }
    while (1 == 1);
    printf("Successfully exited");

}


/*
*    char *command;
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

 */