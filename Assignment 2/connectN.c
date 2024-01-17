#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int InitializeBoard(int **connectNBoard, int numRowsInBoard);
int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen);
int DisplayBoard(int **connectNBoard, int numRowsInBoard);
int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID);
int fullBoard(int **connectNBoard, int numRowsInBoard);
int isInteger(double number);
int emptyElements(int **connectNBoard, int numRowsInBoard, int columnChosen);
void free2DArray(int **connectNBoard, int numRowsInBoard);
void clear(void);

const int MINSIZE = 8;
const int MAXSIZE = 25;
const int MINCONNECTNUM = 4;
const int NUMBEROFATTEMPTS = 3;
const int RED = 1;
const int BLACK = 2;

int main(void)
{
    /*
      This program is similar to the game of Connect 4, where two players play against each other to see
      who can first line up their pieces in a line of specified length chosen by the user. The user
      specifies the board size and each user is given three attempts to enter their choice for each turn.
      The program exits once a player has won or the board is full.
      
      Author Evan Law July 2, 2023;
    */

    double numRows; // Stored as double data type to ensure floating point numbers are caught with isInteger function
    double numToConnect;
    int scanf_return_value; // Stores the return value of scanf calls

    // Prompts user for the number of rows for the size of the board
    while (1)
    {
        printf("Enter the number of squares along each edge of board\n");
        scanf_return_value = scanf("%lf", &numRows);
        
        if (scanf_return_value != 1 || !isInteger(numRows)) // Checks if user entered correct input
        {
            printf("ERROR: The value provided was not an integer\n");
            numRows = 0;
        }
        else if (numRows >= MINSIZE && numRows <= MAXSIZE)
        {
            break; // Valid number of rows received
        }
        else if (numRows > MAXSIZE)
        {
            printf("ERROR: Board size too large (>%d)\n", MAXSIZE);
        }
        else if (numRows < MINSIZE)
        {
            printf("ERROR: Board size too small (<%d)\n", MINSIZE);
        }
        clear(); // Clears the input buffer from invalid input
    }    

    // Prompts user for the number of game pieces to line up to win
    while (1)
    {
        printf("Enter the number of pieces that must form a line to win\n");
        scanf_return_value = scanf("%lf", &numToConnect);
        
        if (scanf_return_value != 1 || !isInteger(numToConnect)) // Checks if user entered correct input
        {
            printf("ERROR: The value provided was not an integer\n");
            numToConnect = 0;
        }
        else if (numToConnect >= MINCONNECTNUM && numToConnect <= numRows-MINCONNECTNUM)
        {
            break; // Valid number of number of game pieces to line up received
        }
        else if (numToConnect > (int) numRows-MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too large (>%d)\n", (int) numRows-MINCONNECTNUM);
        }
        else if (numToConnect < MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too small (<%d)\n", MINCONNECTNUM);
        }
        clear(); // Clears the input buffer from invalid input
    }

    // Dynamically allocating a 2-D integer array
    int **myConnectNBoard;
    myConnectNBoard = (int **) malloc(numRows * sizeof(int*));
    for (int i = 0; i < numRows; i++)
    {
        myConnectNBoard[i] = (int *) malloc(numRows * sizeof(int));
    }

    if (!InitializeBoard(myConnectNBoard, numRows)) // If error was caught, exit the program
    {
        printf("ERROR: Could not initialize the game board\n");
        free2DArray(myConnectNBoard, numRows);
        return 1;
    }

    int turn; // Stores a number indicating which player's turn it is to move
    int result; // Stores the return value of the CheckWinner function to check if there is a winner
    int attempts; // Counter that keeps track of the number of attempts by the user
    double chosenColumn;

    turn = RED; // Red moves first

    // Plays the game until the entire board is full or a player wins
    while (!fullBoard(myConnectNBoard, numRows))
    {
        printf("\n\n"); // Prints two blank lines
        if (!DisplayBoard(myConnectNBoard, numRows))
        {
            printf("ERROR: Could not display the game board\n");
            continue;
        }
        if (turn == RED)
        {
            printf("Red moves\n");
        }
        else
        {
            printf("Black moves\n");
        }

        attempts = 0; // Resets the counter of attempts

        while (attempts < NUMBEROFATTEMPTS)
        {
            printf("Enter the column number where you want to put your piece\n");
            scanf_return_value = scanf("%lf", &chosenColumn);

            if (scanf_return_value != 1 || !isInteger(chosenColumn)) // Checks if user entered correct input
            {
                printf("ERROR: The value provided was not a number\n");
                clear();
                chosenColumn = 0;
                attempts++;
                continue;
            }
            else if ((int) chosenColumn >= (int) numRows || (int) chosenColumn < 0)
            {
                printf("ERROR: Column %d is not on the board: try again\n", (int) chosenColumn);
                printf("ERROR: Column number should be >= 0 and < %d\n", (int) numRows);
                clear();
                attempts++;
                continue;
            }
            else if (!emptyElements(myConnectNBoard, numRows, chosenColumn))
            {
                printf("ERROR: Column %d is already completely full try again\n", (int) chosenColumn);
                clear();
                attempts++;
                continue;
            }

            if (!MakeMove(myConnectNBoard, numRows, turn, chosenColumn))
            {
                attempts++;
                continue;
            }
            else
            {
                break;
            }
        }
        if (attempts == NUMBEROFATTEMPTS)
        {
            if (turn == RED)
            {
                printf("TOO MANY ILLEGAL MOVES\n");
                printf("Red has forfeited a turn\n");
                turn = BLACK;
            }
            else
            {
                printf("TOO MANY ILLEGAL MOVES\n");
                printf("Black has forfeited a turn\n");
                turn = RED;
            }
            continue;
        }
        else
        {
            result = CheckWinner(myConnectNBoard, numRows, numToConnect, chosenColumn, turn);
            if (result != 0) // If the result variable value is zero, there is no winner yet
            {
                if (result == RED) // Checks which player won
                {
                    printf("Red has won\n");
                    DisplayBoard(myConnectNBoard, numRows);
                    break;
                }
                else
                {
                    printf("Black has won\n");
                    DisplayBoard(myConnectNBoard, numRows);
                    break;
                }
            }
        }
        if (turn == RED)
        {
            turn = BLACK; // Black moves next turn
        }
        else
        {
            turn = RED; // Red moves next turn
        }
    }

    if (result == 0 && fullBoard(myConnectNBoard, numRows)) // result == 0 condition checks the case if on the last turn, there are still no winners
    {
        printf("The board is full. It's a tie.\n");
        DisplayBoard(myConnectNBoard, numRows);
    }
    free2DArray(myConnectNBoard, numRows);
    return 0;
}

// Initializes the board elements to zero
int InitializeBoard(int **connectNBoard, int numRowsInBoard)
{
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (numRowsInBoard < MINSIZE || numRowsInBoard > MAXSIZE)
    {
        printf("ERROR: illegal number of rows in board");
        return 0;
    }
    for (int i = 0; i < numRowsInBoard; i++)
    {
        for (int j = 0; j < numRowsInBoard; j++)
        {
            connectNBoard[i][j] = 0; // Initializes elements to zero
        }
    }
    return 1;
}

// Updates the board to reflect the user's chosen column
int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen)
{
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (columnChosen >= numRowsInBoard || columnChosen < 0 || !emptyElements(connectNBoard, numRowsInBoard, columnChosen))
    {
        printf("Illegal move\n");
        return 0;
    }

    for (int i = numRowsInBoard-1; i >= 0; i--) // Begins at bottom of column
    {
        if (connectNBoard[i][columnChosen] == 0)
        {
            connectNBoard[i][columnChosen] = playerID;
            break;
        }
    }
    if (playerID == RED)
    {
        printf("Red has moved\n");
    }
    else
    {
        printf("Black has moved\n");
    }
    return 1;
}

int DisplayBoard(int **connectNBoard, int numRowsInBoard)
{
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (numRowsInBoard < MINSIZE || numRowsInBoard > MAXSIZE)
    {
        printf("ERROR: illegal number of rows in board");
        return 0;
    }
    
    // Prints and formats the top row of the board
    printf("%3c", ' ');
    int i = 0;
    for (i = 0; i < numRowsInBoard; i++)
    {
        printf("%3d", i); // Prints the column numbers of the board
    }
    printf("\n");

    // Prints the row numbers and board values
    for (i = 0; i < numRowsInBoard; i++)
    {
        printf("%3d", i); // Prints the row numbers of the board
        for (int j = 0; j < numRowsInBoard; j++)
        {
            if (connectNBoard[i][j] == 0)
            {
                printf("%3c", 'o');
            }
            else if (connectNBoard[i][j] == RED)
            {
                printf("%3c", 'R');
            }
            else if (connectNBoard[i][j] == BLACK)
            {
                printf("%3c", 'B');
            }
        }
        printf("\n");
    }
    return 1;
}

int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID)
{
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot print the board because the pointer to the board is NULL\n");
        return 0;
    }
    if (columnChosen >= numRowsInBoard || columnChosen < 0)
    {
        printf("ERROR: invalid column chosen, cannot check for winner\n");
        return 0;
    }

    int resultingRow = 0; // Stores the value of the most recent row from the most recent column chosen
    int i = 0;
    for (i = 0; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] == playerID)
        {
            resultingRow = i;
            break;
        }
    }
    
    int beforeCount = 0;
    int afterCount = 0;

    // Checks to the left of the row of the column chosen
    for (i = columnChosen - 1; i >= 0 && connectNBoard[resultingRow][i] == playerID; i--) 
    {
        beforeCount++;
    }
    // Checks to the right of the row of the column chosen
    for (i = columnChosen + 1; i < numRowsInBoard && connectNBoard[resultingRow][i] == playerID; i++) 
    {
        afterCount++;
    }   
    if (beforeCount + afterCount + 1 >= numConnect)
    {
        return playerID; // We have a winner, return which colour won
    }

    beforeCount = 0;
    afterCount = 0;

    // Checks downwards of the column chosen
    for (i = resultingRow - 1; i >= 0 && connectNBoard[i][columnChosen] == playerID; i--) 
    {
        beforeCount++;
    }
    // Checks upwards of the column chosen
    for (i = resultingRow + 1; i < numRowsInBoard && connectNBoard[i][columnChosen] == playerID; i++) 
    {
        afterCount++;
    }
    if (beforeCount + afterCount + 1 >= numConnect)
    {
        return playerID; // We have a winner, return which colour won
    }

    beforeCount = 0;
    afterCount = 0;

    // Checks diagonally upper left of the column chosen
    for (i = 1; resultingRow - i >= 0 && columnChosen - i >= 0 && connectNBoard[resultingRow-i][columnChosen-i] == playerID; i++)
    {
        beforeCount++;
    }
    // Checks diagonally lower right of the column chosen
    for (i = 1; resultingRow + i < numRowsInBoard && columnChosen + i < numRowsInBoard && connectNBoard[resultingRow+i][columnChosen+i] == playerID; i++)
    {
        afterCount++;
    }
    if (beforeCount + afterCount + 1 >= numConnect)
    {
        return playerID; // We have a winner, return which colour won
    }

    beforeCount = 0;
    afterCount = 0;

    // Checks diagonally lower left of the column chosen
    for (i = 1; resultingRow + i < numRowsInBoard && columnChosen - i >= 0 && connectNBoard[resultingRow+i][columnChosen-i] == playerID; i++)
    {
        beforeCount++;
    }
    // Checks diagonally upper right of the column chosen
    for (i = 1; resultingRow - i >= 0 && columnChosen + i < numRowsInBoard && connectNBoard[resultingRow-i][columnChosen+i] == playerID; i++)
    {
        afterCount++;
    }
    if (beforeCount + afterCount + 1 >= numConnect)
    {
        return playerID; // We have a winner, return which colour won
    }

    return 0; // No winner yet
}

// Checks if the entire board is full
int fullBoard(int **connectNBoard, int numRowsInBoard)
{
    for (int i = 0; i < numRowsInBoard; i++)
    {
        if (connectNBoard[0][i] == 0) // Only need to check the first row for optimization
        {
            return 0;
        }
    }
    return 1; // Exiting the loop implies the entire board is full
}

// Checks if the column has empty elements, returning true if the column has empty elements
int emptyElements(int **connectNBoard, int numRowsInBoard, int columnChosen)
{
    for (int i = 0; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] == 0)
        {
            return 1;
        }
    }
    return 0; // Exiting the loop implies the column is full
}

// Checks if number is an integer or a decimal number by truncating the decimals
int isInteger(double number)
{
    int trunc_number = (int) number; // Type casting a double to an int
    return number == trunc_number;
}

// Frees a 2D array
void free2DArray(int **connectNBoard, int numRowsInBoard)
{
    for (int i = 0; i < numRowsInBoard; i++)
    {
        free(connectNBoard[i]);
    }
    free(connectNBoard);
}

// Clears the input buffer
void clear(void)
{
    while (getchar() != '\n');
}