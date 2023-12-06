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
        else{
            printf("%s\n",currentDirectory);
        }
};

void changeCwd(char* pathTo[]){
    chdir(pathTo);
    setcwd();
}

void execCommand(char *argv[]){

    char* dupe2 = strdup(argv[0]);
    char* ifBin = strtok(dupe2, "/");
    char inBin[1000] = {"/bin/"};
    printf("ifBin: %s\n", ifBin);
    char *envp[] = {NULL};
    char *fullPath;
    if (strcmp(ifBin, "bin") == 0){
        fullPath = argv[0];
    }
    else{
        fullPath = strcat(inBin,argv[0]);
    }

    if (access(fullPath, F_OK) == 0){
        printf("exec with bin: %d \n", execve(fullPath,argv, envp));
        exit(0);
    }
    else{
        printf("Invalid command or command not found %s \n", fullPath);
        exit(-1);
    }


    if (strcmp(ifBin, "bin") == 0){
        printf("exec with bin: %d\n", execve(argv[0], argv, envp));
        exit(0);
    }
    else {
        strcat(inBin,argv[0]);
        printf("exec without bin: %d\n", execve(inBin, argv, envp));
        exit(0);
    }



}

void processCommand(char* argv[]) {
    int pid = getpid(); // parent pid
    pid_t cpid = fork();
    pid_t cppid = getppid(); // childs parent pid

    printf("cpid: %d, cppid: %d, pid: %d\n",cpid, cppid, pid);
    if (cppid == pid) {
        execCommand(argv);
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

        char*token;
        char* dupe = strdup(userInput);
        char* argv[100] = {};
        int i = 0;
        token = strtok(dupe, " ");

        while (token != NULL) {
            printf("UI: %s, Token: %s, Index : %d\n", dupe,token,i);
            // Pass NULL to get next token
            argv[i++] = token;
            token = strtok(NULL, " ");
        }

        if (strcmp(argv[0],"exit") == 0) {
            break;
        }
        else if (strcmp(argv[0],"cd") == 0){
        // check cd
            changeCwd(argv);
        }
        else {
            processCommand(argv);
        }
    }
    while (1 == 1);
    printf("Successfully exited");

}
