#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
//Displays the updated board after each move.
void showBoard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}
//Displays the board configuration with indexes at which 'X' can be placed.
void showInstructions()
{
    printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}
// Initially sets the board to '*' which implies that those spaces are empty.
void initialise(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
            board[i][j] = '*';
    }
}
//Declares the winner.
void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
}
//We check for every row, if elements are same we return true else false.
bool rowCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
        board[i][1] == board[i][2] &&
        board[i][0] != '*')
            return (true);
    }
    return(false);
}
//We check for every column, if elements are same we return true else false.
bool columnCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
        board[1][i] == board[2][i] &&
        board[0][i] != '*')
            return (true);
    }
    return(false);
}
//We check for every diagonal, if elements are same we return true else false.
bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] &&
    board[1][1] == board[2][2] &&
    board[0][0] != '*')
        return(true);
    if (board[0][2] == board[1][1] &&
    board[1][1] == board[2][0] &&
    board[0][2] != '*')
        return(true);
    return(false);
}
/* If we are given the board, it simply checks if all the elements in the row are
same (rowCrossed) or if all the elements in the column are same (columnCrossed) or
if all the elements in the diagonal are same (diagonalCrossed). 
*/
bool gameOver(char board[][SIDE])
{
    return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

//main function
int main()
{
    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    char cont='y';
    do {
        char choice;
        printf("Do you want to start first?(y/n) : ");
        scanf(" %c", &choice);
        if(choice=='n')
            /*If user does not start first, we call the function playTicTacToe for 
            COMPUTER.
            */
            playTicTacToe(COMPUTER);
        else if(choice=='y')
            /*If user decides to start first, we call the function playTicTacToe for 
            HUMAN.
            */
            playTicTacToe(HUMAN);
        else
            printf("Invalid choice\n");
            printf("\nDo you want to quit(y/n) : ");
            scanf(" %c", &cont);
    } while(cont=='n'); //we continue the game if the user does not quit
    return (0);
}