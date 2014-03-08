//
//  tic_tac_toe.c
//  Tic Tac Toe
//
//  Created by Joseph Miller on 3/2/14.
//  Copyright (c) 2014 Joseph Miller. All rights reserved.
//

#include <stdio.h>
#define ROWS 3
#define COLS 3
#define BLANK '_'
#define TRUE 0
#define FALSE 1

void start();
void takeTurn(char mark, char board[ROWS][COLS]);
void displayBoard(char board[ROWS][COLS]);
char *getCoordinates();
int moveValid(char mark, int x, int y, char board[ROWS][COLS]);
char winner(char board[ROWS][COLS]);
char diagonalWinner(char board[ROWS][COLS]);
char rowWinner(char board[ROWS][COLS]);
char colWinner(char board[ROWS][COLS]);

int main(int argc, const char * argv[])
{
    // Tic Tac Toe
    printf("Welcome to Tic Tac Toe!\n");
    start();
    
    return 0;
}

void start()
{
    char board[ROWS][COLS] = { BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK };
    char player1 = 'x';
    char player2 = 'o';
    char players[2] = { player1, player2 };
    int currentPlayer = 0;
    int moves = 0;
    int numPlayers = sizeof(players);
    int maxMoves = (ROWS * COLS);
    char winnerMark;
    
    // Show blank board
    displayBoard(board);
    
    // Game loop
    do {
        // Take turn
        takeTurn(players[currentPlayer], board);
        moves++;
        
        // Check if winner
        winnerMark = winner(board);
        if (winnerMark != BLANK) {
            printf("%c won!\n", winnerMark);
            return;
        }
        
        // Switch players
        currentPlayer++;
        currentPlayer %= numPlayers;
    } while (moves < maxMoves);
    printf("It is a tie.");
}

void takeTurn(char mark, char board[ROWS][COLS])
{
    char *coords;
    int x, y;
    int validSpace;
    
    printf("Player %c's turn.\n", mark);
    coords = getCoordinates();
    x = coords[0];
    y = coords[1];
    validSpace = moveValid(mark, x, y, board);
    if (validSpace == TRUE) {
        board[x][y] = mark;
        displayBoard(board);
    } else {
        printf("Invalid move, try again.\n");
        takeTurn(mark, board);
    }
}

void displayBoard(char board[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) { printf("|"); }
        }
        printf("\n");
    }
}

char *getCoordinates()
{
    int x, y;
    static char coords[2];
    char *coordPointer;
    printf( "Please input coordinates: " );
    scanf( "%d", &x );
    scanf( "%d", &y );
    coords[0] = x;
    coords[1] = y;
    coordPointer = coords;
    return coordPointer;
}

int moveValid(char mark, int x, int y, char board[ROWS][COLS])
{
    // check if space off board
    if (x >= ROWS || y >= COLS || x < 0 || y < 0) {
        return FALSE;
    }
    // check if board space is available
    if (board[x][y] == BLANK) {
        return TRUE;
    } else {
        return FALSE;
    }
}

char winner(char board[ROWS][COLS]) {
    char diagonalWin;
    char rowWin;
    char colWin;
    
    // Diagonals
    diagonalWin = diagonalWinner(board);
    if (diagonalWin != BLANK) {
        return diagonalWin;
    }
    // Rows
    rowWin = rowWinner(board);
    if (rowWin != BLANK) {
        return rowWin;
    }
    // Cols
    colWin = colWinner(board);
    if (colWin != BLANK) {
        return colWin;
    }
    return BLANK;
}

char diagonalWinner(char board[ROWS][COLS]) {
    char diagonal1;
    char diagonal2;
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] ) {
        diagonal1 = board[1][1];
        return diagonal1;
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2] ) {
        diagonal2 = board[1][1];
        return diagonal2;
    }
    return BLANK;
}

char rowWinner(char board[ROWS][COLS]) {
    char rowMark;
    int row, col;
    for (row = 0; row < ROWS; row++) {
        rowMark = board[row][0];
        for (col = 0; col < COLS; col++) {
            if (board[row][col] != rowMark) {
                rowMark = BLANK;
                break;
            }
        }
        if (rowMark != BLANK) {
            return rowMark;
        }
    }
    return BLANK;
}

char colWinner(char board[ROWS][COLS]) {
    char colMark;
    int col, row;
    for (col = 0; col < COLS; col++) {
        colMark = board[0][col];
        for (row = 0; row < ROWS; row++) {
            if (board[row][col] != colMark) {
                colMark = BLANK;
                break;
            }
        }
        if (colMark != BLANK) {
            return colMark;
        }
    }
    return BLANK;
}