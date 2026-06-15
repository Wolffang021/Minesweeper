#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/*
Boredr: ' '
Unopened: '-'
Opened: ' ', '1-8'
Mark: 'x'
Mine: '+'
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
    char border = ' ';

    printf("\n");
    for (int i = y - 1; i >= -2; i--) {
        if (i == -1) {
            printf("%c %c ", border, border);
            for (int j = 0; j < x; j++)
                printf("%c ", border);
            printf("\n");
            continue;
        }

        if (i == -2) {
            printf("  %c ", border);
            for (int j = 0; j < x; j++)
                printf("%d ", j);
            continue;
        }

        printf("%d %c ", i, border);
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
            
            if (coX < 0 || coX >= x || coY < 0 || coY >= y) {
                printf("\n!!INVALID COORDINATES!!\n");
                continue;
            }
            
            if (display[coY][coX] == '-') {
                display[coY][coX] = 'x';
                printf("\nMarked %d, %d\n", coX, coY);
            }
            else {
                display[coY][coX] = '-';
                printf("\nUnmarked %d, %d\n", coX, coY);
            }

            return;
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

bool openCell(int x, int y, int grid[][x], char display[][x], int coX, int coY) {
    if (grid[coY][coX] == 1)
        return false;
    
    int mines = 0;
    for (int i = coY - 1; i <= coY + 1; i++) {
        for (int j = coX - 1; j <= coX + 1; j++) {
            if (i < 0 || i >= y || j < 0 || j >= x)
                continue;
            
            if (grid[i][j] == 1)
                mines++;
        }
    }

    if (mines > 0)
        display[coY][coX] = mines + '0';
    else {
        display[coY][coX] = ' ';
        for (int i = coY - 1; i <= coY + 1; i++) {
            for (int j = coX - 1; j <= coX + 1; j++) {
                if (i < 0 || i >= y || j < 0 || j >= x)
                    continue;
                
                if (display[i][j] != ' ')
                    openCell(x, y, grid, display, j, i);
            }
        }
    }
    return true;
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
        printf("\nOpen cell: [x-coord]<space>[y-coord]");
        printf("\nMark cell: [m]");
        printf("\nExit: [x]");
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

            if (coX < 0 || coX >= lengthX || coY < 0 || coY >= lengthY) {
                printf("\n!!INVALID COORDINATES!!\n");
                continue;
            }
            
            if (display[coY][coX] == '-') {
                if(!openCell(lengthX, lengthY, grid, display, coX, coY)) {
                    printf("\nGame Over!!\n");
                    exit = true;
                }
            }
            else
                printf("\nAlready opened!\n");

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
        char choice[1024];
        printf("\nMINESWEEPER vAlpha-1");
        printf("\n\tby Shourjo");
        printf("\nPLAY [Press '1']");
        printf("\nEXIT [Press '0']");
        printf("\nInput: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        switch (choice[0]) {
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