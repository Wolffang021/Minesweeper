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

void initializeGrid(int x, int y, int grid[][x], char display[][x], int* mines, int* safe) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (rand() % 5 == 0) {
                grid[i][j] = 1;
                (*mines)++;
            }
            else {
                grid[i][j] = 0;
                (*safe)++;
            }

            display[i][j] = '-';
        }
    }

    // for (int i = 0; i < y; i++) {
    //     printf("\n");
    //     for (int j = 0; j < x; j++) {
    //         printf("%d ", grid[i][j]);
    //     }
    // }
}
        
void displayGrid(int x, int y, int grid[][x], char display[][x], bool gameOver) {
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
            printf("%c ", gameOver && grid[i][j] == 1 ? '+' : display[i][j]);
        
        printf("\n");
    }
    printf("\n");
}

void markCell(int x, int y, int grid[][x], char display[][x], int* marked) {
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
                (*marked)++;
                printf("\nMarked %d, %d\n", coX, coY);
            }
            else if (display[coY][coX] == 'x') {
                display[coY][coX] = '-';
                (*marked)--;
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

bool openCell(int x, int y, int grid[][x], char display[][x], int coX, int coY, int* mines, int* opened) {
    if (grid[coY][coX] == 1)
        return false;
    
    int detected = 0;
    for (int i = coY - 1; i <= coY + 1; i++) {
        for (int j = coX - 1; j <= coX + 1; j++) {
            if (i < 0 || i >= y || j < 0 || j >= x)
                continue;
            
            if (grid[i][j] == 1)
                detected++;
        }
    }

    if (detected > 0)
        display[coY][coX] = detected + '0';
    else {
        display[coY][coX] = ' ';
        for (int i = coY - 1; i <= coY + 1; i++) {
            for (int j = coX - 1; j <= coX + 1; j++) {
                if (i < 0 || i >= y || j < 0 || j >= x)
                    continue;
                
                if (display[i][j] == '-')
                    openCell(x, y, grid, display, j, i, &(*mines), &(*opened));
            }
        }
    }

    // printf("(%d,%d)", coX, coY);
    (*opened)++;
    return true;
}

void play() {
    srand(time(0));
    int lengthX = 8, lengthY = 6;
    int mines = 0, marked = 0, opened = 0, safe = 0;
    int grid[lengthY][lengthX];
    char display[lengthY][lengthX];
    time_t startTime = time(0);

    initializeGrid(lengthX, lengthY, grid, display, &mines, &safe);

    bool exit = false;
    do {
        char choice[1024];
        displayGrid(lengthX, lengthY, grid, display, false);
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
                if(!openCell(lengthX, lengthY, grid, display, coX, coY, &mines, &opened)) {
                    displayGrid(lengthX, lengthY, grid, display, true);
                    printf("\nGame Over!!\n");
                    exit = true;
                }

                // printf("mines: %d, safe: %d, opened: %d, marked: %d, x * y: %d", mines, safe, opened, marked, lengthX * lengthY);
                
                if (opened == safe) {
                    double playtime = difftime(time(0), startTime);
                    printf("\nCongratulations, You Won!!\nIt took you %.2lf seconds\n", playtime);
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
                markCell(lengthX, lengthY, grid, display, &marked);
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
        printf("\nMINESWEEPER");
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