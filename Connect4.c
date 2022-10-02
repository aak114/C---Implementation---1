#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int board[6][7]; //connect 4 board
char players[2][20]; //list of player names
int startingPlayerIndex;
int numberOfMoves;
int moves[2][22];

void resetGame();
void drawBoard();
void promptPlayers();
int randomIndex();
int getRow(int col);
int checkWin(int lastMoveRow, int lastMoveCol);
int manageTurns();
void manageGame();
int getTokenInt(int turn);



int main(){
    resetGame();
    printf("Welcome to Connect 4!\n");
    promptPlayers();
    startingPlayerIndex = randomIndex();
    printf("%s starts with Red (1)\n", players[startingPlayerIndex]);
    manageGame();
}

void resetGame(){

    numberOfMoves = 0;

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

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 22; j++){
            moves[i][j] = NULL;
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

int getRow(int col){
    int row = 5;
    while (board[row][col] != 0){
        row--;
    }
    return row;
}

int manageTurns(){
    if (startingPlayerIndex == 0){
        if (numberOfMoves%2==0) return 0;
        else return 1;
    } else {
        if (numberOfMoves%2==0) return 1;
        else return 0;
    }
    
}

void manageGame(){
    int turn;
    int col;
    int row;
    do {
        turn = manageTurns();
        drawBoard();
        printf("\n%s's turn (%d) . Enter col (1-7): ", players[turn], numberOfMoves);
        scanf("%d", &col);
        col--;
        row = getRow(col);
        if (row >= 0){
        board[row][col] = getTokenInt(turn);
        moves[turn][numberOfMoves % 22] = col-1;
        numberOfMoves++;
        } else {
        printf("\nInvalid move! try again.");
        manageGame();
        }
    } while (checkWin(row, col) == 0);

    drawBoard();
    printf("%s wins!", &players[turn]);
}

int getTokenInt(int turn){
    if (startingPlayerIndex == turn) return 1;
    return 2;
}

int checkWin(int lastMoveRow, int lastMoveCol) {
    //  For checking whether any win or lose condition is reached. Returns 1 if win or lose is reached. else returns 0
    //  board[][] is the game matrix(can be any number of rows and columns between 4 and 40)
    //  colNum is the column number where the last token was placed
    //  rowNum is the row number where the last token was placed
    //  maxRow is the number of rows in my grid
    //  maxCol is the number of columns in my grid

    // int board[6][7] = board;
    
    int rowNum = lastMoveRow;
    int colNum = lastMoveCol;
    int maxRow = 6;
    int maxCol = 7;
    int player = board[rowNum][colNum]; //player ID
    int count=0;

    // Horizontal check
    for (int i=0;i<maxCol;i++)
    {
        if (board[rowNum][i]==player)
            count++;
        else
            count=0;

        if (count>=4)
            return 1;
    }
    //Vertical check
    for (int i=0;i<maxRow;i++)
    {
        if (board[i][colNum]==player)
            count++;
        else
            count=0;

        if (count>=4)
            return 1;
    } 
    count=0;
    // 4 in a row diagonally
    for(int i=colNum+1,j=rowNum+1;i<maxRow && j<maxCol;i++,j++) 
    { 
        if(board[j][i]!=player)
        {
            count=1;
            break;        
        }
        count++;
    }
    // 4 in a row diagonally
    for(int i=colNum-1,j=rowNum-1;i>=0 && j>=0;i--,j--) 
    { 
        if(board[j][i]!=player)
        {
            count=1;
            break;        
        }
        count++;
    }
    // 4 in a row diagonally
    for(int i=colNum+1,j=rowNum-1;i<maxRow && j>=0;i++,j--) 
    { 
        if(board[j][i]!=player)
        {
            count=1;
            break;        
        }
        count++;
    }

    for(int i=colNum-1,j=rowNum+1;i>=0 && j<maxCol;i--,j++) 
    { // 4 in a row diagonally
        if(board[j][i]!=player)
        {
            count=1;
            break;        
        }
        count++;
    }

    if(count>=4)
        return 1;

    return 0;
}