#include <stdio.h>
#include <string.h>



int main() {
    char userInput[6];
    char exit[6] = "exit\n";
    char exit2[] = "";
    int length;
    int x = 1;
    char *token;
    int y = 1;
    do {
        printf(">>>");
        fgets(userInput,50,stdin);

        token = strtok(userInput, " ");

    }
    while (strcmp(exit,userInput) != 0);
    printf("Successfully exited");

}
