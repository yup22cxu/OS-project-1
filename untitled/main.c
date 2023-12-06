#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>


char currentDirectory[PATH_MAX] = "";

void setcwd(){
    // checks to make sure currentDirectory isn't null
        if (getcwd(currentDirectory, sizeof(currentDirectory)) == NULL) {
            perror("getcwd() error");
        }
        // returns current directory (the new changed one)
        else{
            printf("%s\n",currentDirectory);
        }
};

void changeCwd(char* pathTo[]){
    //chdir changes the directory to the parameter
    chdir(pathTo);
    //calls setcwd
    setcwd();
}

void execCommand(char *argv[]){

    char* dupe2 = strdup(argv[0]);
    char* ifBin = strtok(dupe2, "/");
    char inBin[1000] = {"/bin/"};
    //printf("ifBin: %s\n", ifBin);
    char *envp[] = {NULL};
    char *fullPath;
    //makes a full path if they put /bin or not
    if (strcmp(ifBin, "bin") == 0){
        fullPath = argv[0];
    }
    else{
        fullPath = strcat(inBin,argv[0]);
    }
    //validates that it is a valid command found in /bin
    if (access(fullPath, F_OK) == 0){
        printf("exec with bin: %d \n", execve(fullPath,argv, envp));
        exit(0);
    }
    else{
        printf("Invalid command or command not found %s \n", fullPath);
        exit(-1);
    }

}

void processCommand(char* argv[]) {
    int pid = getpid(); // parent pid
    //forks the process to make an identical child process
    pid_t cpid = fork();
    pid_t cppid = getppid(); // childs parent pid

    //printf("cpid: %d, cppid: %d, pid: %d\n",cpid, cppid, pid);
    //checks it is the child process then calls execCommand
    if (cppid == pid) {
        execCommand(argv);
        exit(1);
    }
    int status;
    //makes the parent process wait for the child process to complete so it doesn't crash the child
    waitpid(cpid, &status,0);
}

int main() {

    char userInput[1000];// = "/bin/ls -al main.c";

    do {
        printf(">>>");

        fgets(userInput,1000,stdin);

        size_t newline_pos = strcspn(userInput, "\n");
        //printf("Newline pos: %d\n", newline_pos);
        userInput[newline_pos] = '\0';
        // check if exit first

        char*token;
        char* dupe = strdup(userInput);
        char* argv[100] = {};
        int i = 0;
        //gets the intial token eg /bin/ls
        token = strtok(dupe, " ");
        //loops through the rest of the tokens adding them to a string array
        while (token != NULL) {
            //printf("UI: %s, Token: %s, Index : %d\n", dupe,token,i);
            // Pass NULL to get next token
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        // finds what the command is and sends it to the respective procedure
        if (argv[0] != NULL) {
            if (strcmp(argv[0], "exit") == 0) {
                break;
            } else if (strcmp(argv[0], "cd") == 0) {
                // check cd
                changeCwd(argv);
            } else {
                processCommand(argv);
            }
        }
    }
    while (1 == 1);
    // Displays when exited correctly using exit condition rather than crashing
    printf("Successfully exited");

}
