#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define HALF_MAX 50

// Function prototypes
void FillZero(int **my2DArray, int M, int N);
void CopyArray(int **my2DArray, int **myNextGenArray, int M, int N);
void NextGen(int **board, int M, int N);
void PrintGen(int **my2DArray, FILE* output_file, int M, int N);
int isInteger(long double number);
int catchSpaces(char *user_input);

int main(void)
{
    FILE *output_file = NULL;
    FILE *input_file = NULL;
    char output_filename[MAX];
    char input_filename[MAX];

    /* 
      Rows and columns intially strings will be converted to floats
      to ensure correct input
    */
    char numRows[HALF_MAX];
    char numCols[HALF_MAX];
    long double rows = 0;
    long double cols = 0;

    /*
      Number of generations and generation increment initially strings
      will be converted to int using atoi()
    */
    char numGen[HALF_MAX];
    char numIncrem[HALF_MAX];

    int **board;

    printf("Enter the name of the output file: ");
    fgets(output_filename, MAX, stdin); // Reads input from user
    output_filename[strcspn(output_filename, "\r\n")] = '\0'; // Removes end of line character

    printf("Enter the name of the input file: ");
    fgets(input_filename, MAX, stdin);
    input_filename[strcspn(input_filename, "\r\n")] = '\0';    

    output_file = fopen(output_filename, "w");
    input_file = fopen(input_filename, "r");

    if (output_file == NULL)
    {
        printf("ERROR: Output file not opened correctly.\n");
        fclose(output_file);
        fclose(input_file);
        return 1;
    }
    else if (input_file == NULL)
    {
        printf("ERROR: Input file not opened correctly.\n");
        fclose(output_file);
        fclose(input_file);
        return 2;
    }

    // Prompts user for the number of rows in the game board
    printf("Enter the number of rows in the board (0<number<40) ");
    while (1)
    {
        fgets(numRows, HALF_MAX, stdin);
        numRows[strcspn(numRows, "\r\n")] = '\0'; // Removes end of line character

        rows = atof(numRows);
        // Checks if number has decimals which is therefore not an integer
        if (!isInteger(rows))
        {
            printf("ERROR: The value of numRows is not an integer\n");
            fclose(output_file);
            fclose(input_file);
            return 3;
        }

        if (!catchSpaces(numRows) && rows > 0 && rows < 40)
        {
            break; // Valid number of rows received
        }
        else
        {
            printf("ERROR: Read an illegal number of rows for the board\n");
            printf("TRY AGAIN, 0 < number of rows < 40 ");
        }
    }

    // Prompts user for the number of columns in the game board
    printf("Enter the number of columns in the board (0<number<80) ");
    while (1)
    {
        fgets(numCols, HALF_MAX, stdin);
        numCols[strcspn(numCols, "\r\n")] = '\0'; // Removes end of line character

        cols = atof(numCols);
        // Checks if number has decimals other than zero which is therefore not an integer
        if (!isInteger(cols))
        {
            printf("ERROR: The value of numCols is not an integer\n");
            fclose(output_file);
            fclose(input_file);
            return 4;
        }

        if (!catchSpaces(numCols) && cols > 0 && cols < 80)
        {
            break; // Valid number of columns received
        }
        else
        {
            printf("ERROR: Read an illegal number of columns for the board\n");
            printf("TRY AGAIN, 0 < number of columns < 80 ");
        }
    }

    // Reads the number of generations from the input file
    if (fgets(numGen, HALF_MAX, input_file) == NULL)
    {
        printf("ERROR: Could not read the number of generations\n");
        fclose(output_file);
        fclose(input_file);
        return 5;
    }
    numGen[strcspn(numGen, "\r\n")] = '\0'; // Removes end of line character

    if (atof(numGen) == 0 || !isInteger(atof(numGen)))
    {
        printf("ERROR: number of generations is not an integer\n");
        fclose(output_file);
        fclose(input_file);
        return 6;
    }

    if (atof(numGen) < 1) 
    {
        printf("ERROR: Read an illegal number of generations\n");
        fclose(output_file);
        fclose(input_file);
        return 7;
    }
    
    // Reads the generation increment from the input file
    if (fgets(numIncrem, HALF_MAX, input_file) == NULL)
    {
        printf("ERROR: Could not read the generation increment\n");
        fclose(output_file);
        fclose(input_file);
        return 8;
    }
    numIncrem[strcspn(numIncrem, "\r\n")] = '\0'; // Removes end of line character

    if (atof(numIncrem) == 0 || !isInteger(atof(numIncrem)))
    {
        printf("ERROR: generation increment is not an integer\n");
        fclose(output_file);
        fclose(input_file);
        return 9;
    }

    if (atof(numIncrem) < 1 || atof(numGen) < atof(numIncrem))
    {
        printf("ERROR: Read an illegal generation increment\n");
        fclose(output_file);
        fclose(input_file);
        return 10;
    }

    int numGenerations = atoi(numGen);
    int genIncrem = atoi(numIncrem);

    // Dynamically allocating a 2-D integer array
    board = (int **) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
    {
        *(board + i) = (int *) malloc(cols * sizeof(int)); // Applying pointer arithmetic
    }
    FillZero(board, rows, cols);

    // To avoid segmentation fault error, rows must be >= 2 and columns must be >= 4
    if (rows >= 2 && cols >= 4) 
    {
        board[1][3] = 1;
    }

    for (int P = 1; P <= numGenerations; P++)
    {
        NextGen(board, rows, cols);

        if (P == 1 || (P - 1) % genIncrem == 0 || P == numGenerations)
        {
            // Prints generation to output file
            fprintf(output_file, "Sierpinski gameboard: generation %d\n", P);
            PrintGen(board, output_file, rows, cols);
            
            // Prints generation to console
            printf("Sierpinski gameboard: generation %d\n", P);
            PrintGen(board, stdout, rows, cols);
        }
    }

    for (int i = 0; i < rows; i++) 
    {
        free(*(board + i)); // Applying pointer arithmetic
    }
    free(board);

    fclose(output_file);
    fclose(input_file);

    return 0;
}

// Prints the current generation to the specified output file
void PrintGen(int **my2DArray, FILE* output_file, int M, int N)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (*(*(my2DArray + i) + j) == 1)
            {
                fprintf(output_file, "%d", *(*(my2DArray + i) + j)); // Applying pointer arithmetic
            }
            else // Print empty spaces if not one
            {
                fprintf(output_file, " ");
            }
        }
        fprintf(output_file, "\n");
    }
    fprintf(output_file, "\n");
}

// Sets all elements in the array to zero
void FillZero(int **my2DArray, int M, int N)
{
    for (int i = 0; i < M; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            *(*(my2DArray + i) + j) = 0; // Applying pointer arithmetic
        }
    }
}

// Generates the next board generation using pointer arithmetic
void NextGen(int **board, int M, int N)
{
    int **nextGenBoard;
    // Dynamically allocating 2-D integer array
    nextGenBoard = (int **) malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++)
    {
        *(nextGenBoard + i) = (int *) malloc(N * sizeof(int)); // Applying pointer arithmetic
    }
    FillZero(nextGenBoard, M, N);

    // Since board initialized at row 2, we can start from row 2 where k = 1 for optimization
    for (int k = 1; k < M; k++) 
    {
        // Since board initialized at column 4, we can start from column 4 where j = 3 for optimization
        for (int j = 3; j < N; j++)
        {
            if (k == 0 || j == 0)
            {
                *(*(nextGenBoard + k) + j) = 0; // Applying pointer arithmetic
            }
            else
            {
                *(*(nextGenBoard + k) + j) = (*(*(board + k) + j) + *(*(board + k-1) + j) + *(*(board + k) + j-1)) % 2; // Applying pointer arithmetic
            } 
        }
    }
    CopyArray(board, nextGenBoard, M, N);

    for (int i = 0; i < M; i++) 
    {
        free(*(nextGenBoard + i)); // Applying pointer arithmetic
    }
    free(nextGenBoard);
}

// Deep copies the values in 2-D array myNextGenArray to 2-D array my2DArray
void CopyArray(int **my2DArray, int **myNextGenArray, int M, int N)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *(*(my2DArray + i) + j) = *(*(myNextGenArray + i) + j); // Applying pointer arithmetic
        }
    }
}

// Checks if number is an integer or a decimal number by truncating the decimals
int isInteger(long double number)
{
    int trunc_number = (int) number;
    return number == trunc_number;
}

// Checks if user's input has spaces in their input which should be rejected
// This function is used to read the number of rows and columns
int catchSpaces(char *user_input)
{
    for (int i = 0, j = strlen(user_input); i < j; i++)
    {
        if (isspace(user_input[i]) != 0)
        {
            return 1; // Spaces are in user's input
        }
    }
    return 0; // Spaces are not in user's input
}