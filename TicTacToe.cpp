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

/* To check whether or not the current move is better than the best move, we take
the help of minimax() function which will consider all the possible ways the game 
can go and returns the best value for that move, assuming the opponent also plays
optimally.
*/
int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    //if game is over
    if (gameOver(board) == true)
    {
        /*isAI --> current chance. If the current chance is of COMPUTER, the previous
        chance was of HUMAN, the game got over in the previous move itself, therefore
        the HUMAN wins and we return -10 as score == -10 if HUMAN wins
        */
        if (isAI == true)
            return -10;
        /*isAI --> current chance. If the current chance is of HUMAN, the previous
        chance was of COMPUTER, the game got over in the previous move itself, 
        therefore the COMPUTER wins and we return +10 as score == +10 if COMPUTER wins.
        */
        if (isAI == false)
            return +10;
    }
    // if game is not over
    else
    {
        //the moveIndex is not out of bounds
        if(depth < 9)
        {
            //if turn is of COMPUTER
            /*Maximiser: The code for maximiser is similar to bestMove(), the only
            difference is, instead of returning a move (position), it will return a 
            value(bestScore).
            */
            if(isAI == true)
            {
                bestScore = -999;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if(score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            //turn is of HUMAN
            /*Minimiser: The code for minimiser is similar to bestMove(), the only
            difference is, instead of returning a move (position), it will return a 
            value(bestScore).
            */
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        /*If the moveIndex goes out of bounds (depth>9) this implies that no one
        won and the game is a draw. Therefore we return 0 as score == 0 if the game
        is draw
        */
        else
        {
            return 0;
        }
    }
}

/* It's a function to check for the optimal move of the COMPUTER. It calls the 
function minimax to calculate the score of the current move that COMPUTER made 
and compares with the score of the previously made move. It basically evaluates
all the available moves using minimax() and return the best move the maximiser
can make.
*/
int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            //if the position is vacant
            if (board[i][j] == '*') 
            {
                //place 'O' at that position
                board[i][j] = COMPUTERMOVE;
                // calculate score of the move that we did
                //if score == -10 --> HUMAN wins
                //if score == 0 --> It's a draw
                //if score == 10 --> COMPUTER wins
                score = minimax(board, moveIndex+1, false);
                //backtracking to check for more optimal moves
                board[i][j] = '*';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y; //position
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE]; //side is defined to be 3 by default
    int moveIndex = 0, x = 0, y = 0;
    //calling the function "initialise()" to initialise the empty TicTacToe board
    initialise(board);
    //calling the function "showInstructions()" to display the instructions to the
    //user
    showInstructions();
    //run the game until the game is not over {!gameOver(board)} and the index which
    //we are using to plot the 'X' does not go out of the board.
    while (gameOver(board) == false && moveIndex != SIDE*SIDE)
    {
        int n;
        //if the turn is of computer
        if (whoseTurn == COMPUTER)
        {
            //to get the optimal best move for computer
            n = bestMove(board, moveIndex); 
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE; //COMPUTERMOVE = O
            printf("COMPUTER has put a %c in cell %d\n\n", COMPUTERMOVE,n+1);
            showBoard(board);
            moveIndex ++;
            whoseTurn = HUMAN;
        }
        //If the turn is of human
        else if (whoseTurn == HUMAN)
        {
            printf("You can insert in the following positions : ");
                for(int i=0; i<SIDE; i++)
                    for (int j = 0; j < SIDE; j++)
                        if (board[i][j] == '*')
                            //converting indexes of the board into position number
                            printf("%d ", (i * 3 + j) + 1);
            printf("\n\nEnter the position = ");
            scanf("%d",&n);
            n--;//0-based indexing
            x = n / SIDE;//to get the x-coordinate
            y = n % SIDE;//to get the y-coordinate
            if(board[x][y] == '*' && n<9 && n>=0)
            {
                board[x][y] = HUMANMOVE; //HUMANMOVE = X
                printf ("\nHUMAN has put a %c in cell %d\n\n", HUMANMOVE,n+1);
                showBoard(board);
                moveIndex ++;
                whoseTurn = COMPUTER;
            }
            else if(board[x][y] != '*' && n<9 && n>=0)
            {
                printf("\nPosition is occupied, select any one place from the available places\n\n");
            }
            else if(n<0 || n>8)
            {
                printf("Invalid position\n");
            }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else
    {
        /*If the current chance is of COMPUTER and the game is over, this means
        that previous player won, the previous player was HUMAN, therefore we set
        whoseTurn to HUMAN and call the function declareWinner() to print it on the
        screen.
        */
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        /*If the current chance is of HUMAN and the game is over, this means
        that previous player won, the previous player was COMPUTER, therefore we set
        whoseTurn to COMPUTER and call the function declareWinner() to print it on the
        screen.
        */
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn);
    }
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