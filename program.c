#include <stdio.h>
#include <stdbool.h>

void play() {
    //
}

void main() {
    bool exit = false;
    
    do {
        char choice;
        printf("\nMINESWEEPER");
        printf("\n\tby Shourjo");
        printf("\nPLAY [Press '1']");
        printf("\nEXIT [Press '0']");
        printf("\n\nInput: ");
        scanf(" %c", &choice);

        switch (choice) {
            default:
                printf("\n!!INVALID INPUT!!\n");
                break;
            
            case '0':
                exit = true;
                break;

            case '1':
                play();
                break;
        }
    } while (!exit);

    printf("\nHope you had fun! <3\n");
}