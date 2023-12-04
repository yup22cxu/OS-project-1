#include <stdio.h>
#include <string.h>



int main() {
    char userInput[50];
    char exit[] = "exit";
    int length;
    do {
        printf(">>>");
        fgets(userInput,50,stdin);
        //scanf("%[^\n]s", userInput);
        printf("%s", userInput);
        char temp[] = userInput[50];
        //puts(userInput);
        /*for (int i = 0; i < 4; ++i) {
            printf("%c\n", userInput[i]);
        }
        length = sizeof(userInput);
        printf("%d", length);
*/


    }
    while (exit != userInput);
    printf("Successfully exited");

}
