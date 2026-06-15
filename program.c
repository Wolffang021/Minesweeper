#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Unopened: -
Opened: 0-8
Mark: x
Mine: +
*/

void initializeGrid(int x, int y, int grid[][x], char display[][x]) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            grid[i][j] = rand() % 5 == 0 ? 1 : 0;
            display[i][j] = '-';
        }
    }
}
        
void displayGrid(int x, int y, char display[][x]) {
    printf("\n");
    for (int i = y - 1; i >= -1; i--) {
        if (i == -1) {
            printf("  ");
            for (int j = 0; j < x; j++)
                printf("%d ", j);
            continue;
        }

        printf("%d ", i);
        for (int j = 0; j < x; j++)
            printf("%c ", display[i][j]);
        
        printf("\n");
    }
    printf("\n");
}

void markCell(int x, int y, int grid[][x], char display[][x]) {
    bool exit = false;
    do {
        char choice[1024];
        printf("\nCell coords: [x-coord]<space>[y-coord]");
        printf("\nBack: [b]");
        printf("\nInput: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        if (strlen(choice) > 1) {
            int coX, coY;
            int matched = sscanf(choice, "%d %d", &coX, &coY);

            if (matched != 2) {
                printf("\n!!INVALID INPUT!!\n");
                continue;
            }

            if (display[coX][coY] != 'x') {
                display[coX][coY] = 'x';
                printf("\nMarked %d, %d\n", coX, coY);
                return;
            }
            else {
                printf("\nAlready marked!\n");
                return;
            }
        }

        switch (choice[0]) {
            default:
                printf("\n!!INVALID INPUT!!\n");
                break;
            
            case 'B':
            case 'b':
                exit = true;
                break;
        }
    } while (!exit);
}

void play() {
    srand(time(0));
    int lengthX = 8, lengthY = 6;
    int grid[lengthY][lengthX];
    char display[lengthY][lengthX];

    initializeGrid(lengthX, lengthY, grid, display);

    bool exit = false;
    do {
        char choice[1024];
        displayGrid(lengthX, lengthY, display);
        printf("\nOpen unopened cell: [x-coord]<space>[y-coord]");
        printf("\nMark cell: [m]");
        printf("\nExit: [x]");
        printf("\nInput: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        if (strlen(choice) > 1) {
            continue;
        }

        switch (choice[0]) {
            default:
                printf("\n!!INVALID INPUT!!\n");
                break;
            
            case 'M':
            case 'm':
                markCell(lengthX, lengthY, grid, display);
                break;
            
            case 'X':
            case 'x':
                exit = true;
                break;
        }
    } while (!exit);
}

void main() {
    bool exit = false;
    
    do {
        char choice;
        printf("\nMINESWEEPER v1");
        printf("\n\tby Shourjo");
        printf("\nPLAY [Press '1']");
        printf("\nEXIT [Press '0']");
        printf("\nInput: ");
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