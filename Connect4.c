#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int board[6][7]; //connect 4 board
char players[2][20]; //list of player names
int startingPlayerIndex;

void resetGame();
void drawBoard();
void promptPlayers();
int randomIndex();


int main(){
    resetGame();
    printf("Welcome to Connect 4!\n");
    promptPlayers();
    startingPlayerIndex = randomIndex();
    printf("%s starts with Red (1)\n", players[startingPlayerIndex]);
    drawBoard();
    
}

void resetGame(){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 20; j++){
            players[i][j] = NULL;
        }
    }
}

void drawBoard(){
        for (int dash = 0; dash < 15; dash++){
            printf("- ");
        }

        printf("\n");

        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 7; j++){
                printf("| %d ", board[i][j]);
            }
            printf("|\n");
        }

        for (int dash = 0; dash < 15; dash++){
            printf("- ");
        }

}

void promptPlayers(){
    printf("Enter player 1's name: ");
    scanf("%s", &players[0]);
    printf("\n");
    printf("Enter player 2's name: ");
    scanf("%s", &players[1]);
}

int randomIndex(){
    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand() % 2;
    return r;
}