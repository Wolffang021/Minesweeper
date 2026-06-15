#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
Unopened: -
Opened: 0-8
Mark: x
Mine: +
*/

void initializeGrid(int x, int y, int grid[][x]) {
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
            grid[i][j] = rand() % 5 == 0 ? 1 : 0;
}
        
void displayGrid(int x, int y, int grid[][x]) {
    printf("\n");
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void play() {
    srand(time(0));
    int lengthX = 8, lengthY = 6;
    int grid[lengthY][lengthX];

    initializeGrid(lengthX, lengthY, grid);
    displayGrid(lengthX, lengthY, grid);
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