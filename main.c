//----------------------------------	Tic tac too Game   -----------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char board[3][3];
} GameBoard;

char PLAYER1 = ' ';
char PLAYER2 = ' ';
char COMPUTER = ' ';

// Function prototypes
void resetBoard(GameBoard *gb);
void printBoard(const GameBoard *gb);
int checkFreeSpaces(const GameBoard *gb);
void playerMove(GameBoard *gb, char player);
void computerMove(GameBoard *gb, char playerSymbol);
void computerMoveRecursively(GameBoard *gb, char playerSymbol);
char checkWinner(const GameBoard *gb);
void printWinner(char winner);
int getGameMode();

int main() {
    GameBoard gb;
    char winner = ' ';
    char response = ' ';
    int gameMode;

    srand(time(0)); // Seed for random number generation

    // Welcome message
    printf("***Welcome to Tic-Tac-Toe!***\n\n");

    do {
        gameMode = getGameMode(); // Get the game mode from the user
        PLAYER1 = ' ';
        PLAYER2 = ' ';

        printf("Choose 'X' or 'O' for Player 1: ");
        scanf(" %c", &PLAYER1);
        PLAYER1 = toupper(PLAYER1);

        // Validate input
        while (PLAYER1 != 'X' && PLAYER1 != 'O') {
            printf("Invalid choice. Please enter 'X' or 'O' for Player 1: ");
            scanf(" %c", &PLAYER1);
            PLAYER1 = toupper(PLAYER1);
        }

        // Assign the opposite symbol to Player 2
        PLAYER2 = (PLAYER1 == 'X') ? 'O' : 'X';

        resetBoard(&gb);
        winner = ' ';
        response = ' ';

        // Main game loop
        while (winner == ' ' && checkFreeSpaces(&gb) != 0) {
            printBoard(&gb);

            playerMove(&gb, PLAYER1); // Player 1's move
            winner = checkWinner(&gb);
            if (winner != ' ' || checkFreeSpaces(&gb) == 0) {
                break;
            }

            if (gameMode == 1) {
                playerMove(&gb, PLAYER2); // Player 2's move in Player vs Player mode
            } else {
                computerMove(&gb, PLAYER1); // Computer's move in Player vs Computer mode
            }

            winner = checkWinner(&gb);
            if (winner != ' ' || checkFreeSpaces(&gb) == 0) {
                break;
            }
        }

        printBoard(&gb);
        printWinner(winner);

        // Ask the user if they want to play again
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response); // Space before %c to catch newline
        response = toupper(response);
    } while (response == 'Y');

    printf("Thanks for playing!\n");

    return 0;
}


// Get game mode from the user
int getGameMode() {
    int mode;
    char buffer[100]; // Buffer to handle invalid input

    printf("Choose game mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    printf("Enter your choice (1 or 2): ");

    // Validate input
    while (1) {
        if (scanf("%d", &mode) == 1) {
            // Input is an integer
            if (mode == 1 || mode == 2) {
                break; // Valid input, exit loop
            } else {
                printf("Invalid choice. Please enter 1 or 2: ");
            }
        } else {
            // Input is not an integer, clear the input buffer
            scanf("%s", buffer);
            printf("Invalid choice. Please enter 1 or 2: ");
        }
    }

    return mode;
}

// Modify playerMove function to accept player symbol as an argument
void playerMove(GameBoard *gb, char player) {
    int x, y;
    printf("Player %c, make your move.\n", player);
    do {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || gb->board[x][y] != ' ') {
            printf("Invalid move!\n");
        } else {
            gb->board[x][y] = player;
            break;
        }
    } while (1);
}

// Reset the game board
void resetBoard(GameBoard *gb) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gb->board[i][j] = ' ';
        }
    }
}

// Print the game board
void printBoard(const GameBoard *gb) {
    printf(" %c | %c | %c \n", gb->board[0][0], gb->board[0][1], gb->board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", gb->board[1][0], gb->board[1][1], gb->board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", gb->board[2][0], gb->board[2][1], gb->board[2][2]);
}

// Check for free spaces on the board
int checkFreeSpaces(const GameBoard *gb) {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gb->board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

// Handle computer's move
void computerMove(GameBoard *gb, char playerSymbol) {
    if (checkFreeSpaces(gb) > 0) {
        computerMoveRecursively(gb, playerSymbol);
    }
}

// Computer move using recursion
void computerMoveRecursively(GameBoard *gb, char playerSymbol) {
    int x = rand() % 3;
    int y = rand() % 3;

    if (gb->board[x][y] == ' ') {
        gb->board[x][y] = playerSymbol == PLAYER1 ? PLAYER2 : PLAYER1; // Use the opposite symbol of the player
    } else {
        computerMoveRecursively(gb, playerSymbol); // Recur if the spot is taken
    }
}

// Check the winner of the game
char checkWinner(const GameBoard *gb) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (gb->board[i][0] == gb->board[i][1] && gb->board[i][0] == gb->board[i][2] && gb->board[i][0] != ' ')
            return gb->board[i][0];
        if (gb->board[0][i] == gb->board[1][i] && gb->board[0][i] == gb->board[2][i] && gb->board[0][i] != ' ')
            return gb->board[0][i];
    }

    if (gb->board[0][0] == gb->board[1][1] && gb->board[0][0] == gb->board[2][2] && gb->board[0][0] != ' ')
        return gb->board[0][0];
    if (gb->board[0][2] == gb->board[1][1] && gb->board[0][2] == gb->board[2][0] && gb->board[0][2] != ' ')
        return gb->board[0][2];

    // Check if the board is full (tie)
    int boardFull = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gb->board[i][j] == ' ') {
                boardFull = 0;
                break;
            }
        }
    }

    if (boardFull) {
        return 'T'; // Tie
    }

    return ' '; // No winner yet
}


// Print the winner of the game
void printWinner(char winner) {
    if (winner == PLAYER1) {
        printf("Player 1 WINS!\n");
    } else if (winner == PLAYER2) {
        printf("Player 2 WINS!\n");
    } else if (winner == COMPUTER) {
        printf("COMPUTER WINS!\n");
    } else {
        printf("IT'S A TIE!\n");
    }
}

CODE EXPLANATION :

This C program creates a fun, console-based Tic-Tac-Toe game where you can challenge a friend or go head-to-head with a computer. The game uses a simple 3x3 grid, stored in a `GameBoard` structure, to keep track of moves. When you start, the program welcomes you and asks whether you'd like to play against another player or the computer, along with your choice of symbol—either 'X' or 'O'. 

As the game unfolds, players take turns making moves, with the program ensuring that each move is valid. After every turn, it checks for a winner or if the game ends in a tie, updating the board for everyone to see. The computer makes random moves, although it doesn't always play strategically just yet. Once a game wraps up, the program announces the winner or declares a tie, and it invites you to play again. The structure of the program includes various functions to reset the board, display it, check for available spaces, and determine the winner, making for an engaging and interactive gaming experience!
--------------------------------------------------------------------------------------------------------------