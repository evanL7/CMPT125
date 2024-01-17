#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define ARRAY_SIZE 6

// Function prototypes
int all_digits(const char *seed);
int check_guess(const int *answer_array, const int *user_array);
void copy_array(int *array_copy, const int *array_source);
void fill_zero(int *arr);
void generate_random_nums(int *arr);
int get_guess(int *arr);
char *get_seed(char *seed);
void print_guess(const int *arr);

int main(void)
{
    int answer_nums[ARRAY_SIZE]; // Stores the answer digits
    int user_nums[ARRAY_SIZE]; // Stores the user's digits

    char seed[MAX_SIZE];

    get_seed(seed);
    srand(atoi(seed));

    generate_random_nums(answer_nums);
    
    printf("For each turn enter %d digits 0 <= digit <= 9\n", ARRAY_SIZE);
    printf("Spaces or tabs in your response will be ignored.\n");
    
    while (1)
    {
        fill_zero(user_nums);

        if (get_guess(user_nums))
        {
            if (check_guess(answer_nums, user_nums))
            {
                printf("YOU DID IT!!\n");
                break;
            }
        }
    }
    return 0;
}

// Gets user input for the current seed
char *get_seed(char *seed)
{
    while (1)
    {
        printf("Enter the integer value of the seed for the game: ");
        fgets(seed, MAX_SIZE, stdin);
        seed[strcspn(seed, "\r\n")] = '\0'; // Removes end of line character
        
        if (*(seed) != '\0' && all_digits(seed)) // *(seed) != '\0' condition applies if user accidentially pressed enter
        {
            return seed;
        }
        printf("Try again you made an error\n");
    }
}

// Checks whether the string of characters are all digits
int all_digits(const char *seed)
{
    for (int i = 0, length = strlen(seed); i < length; i++)
    {
        if (!isdigit(*(seed + i)))
        {
            return 0;
        }
    }
    return 1; // Exiting the loop implies all the characters are digits
}

// Generates a pseudo random sequence of digits between 0 and 9 inclusive
void generate_random_nums(int *arr)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        *(arr + i) = rand() % (9 + 1 - 0) + 0; // Applying pointer arithmetic
    }
}

// Gets guess from the user
int get_guess(int *arr)
{
    char user_input[MAX_SIZE]; // Temporarily stores user input until sufficient digits received
    char current_char = '\0';
    char single_digit[2] = {current_char, '\0'}; // This array stores the single digit to process into the atoi() function

    int digit_count = 0; // Keeps track of the number of digits in the user's guess

    printf("\nEnter your guess, %d digits\n", ARRAY_SIZE);
    while (1)
    {
        fgets(user_input, MAX_SIZE, stdin);
        user_input[strcspn(user_input, "\r\n")] = '\0'; // Removes end of line character

        for (int i = 0, j = strlen(user_input); i < j; i++)
        {
            current_char = *(user_input + i); 
            *(single_digit) = current_char; // Points to the first element
            if (isdigit(current_char))
            {
                *(arr + digit_count) = atoi(single_digit); // Applying pointer arithmetic
                digit_count++;
            }
            else if (isalpha(current_char))
            {
                printf("ERROR: A character in your guess was not a digit or a white space\n");
                return 0;
            }
            if (digit_count == ARRAY_SIZE)
            {
                return 1;
            }
        }
        printf("You need to enter %d more digits to complete your guess\n", (ARRAY_SIZE - digit_count));
    }
}

// Compares the answer to the user's guess 
int check_guess(const int *answer_array, const int *user_array)
{
    int copy_answer[ARRAY_SIZE]; // Stores a copy of the answer digits
    int copy_user[ARRAY_SIZE]; // Stores a copy of the user's digits

    int perfect_match = 0; // Correct letter and correct index location
    int partial_match = 0; // Correct letter but incorrect index location

    // Copy both arrays to pair matches in order to find the partial matches
    copy_array(copy_answer, answer_array);
    copy_array(copy_user, user_array);

    for (int K = 0; K < ARRAY_SIZE; K++) // Finds perfect matches
    {
        if (*(answer_array + K) == *(user_array + K))
        {
            // Assign -1 to copy array indexes that have perfect matches
            *(copy_answer + K) = -1;
            *(copy_user + K) = -1;
            perfect_match++;
        }
    }
    for (int Q = 0; Q < ARRAY_SIZE; Q++) // Finds partial matches
    {
        if (*(copy_answer + Q) != -1) // If the value being indexed is already a perfect match, ignore that index
        {
            for (int H = 0; H < ARRAY_SIZE; H++)
            {
                // Need to check if user's guess is not already an existing perfect nor partial match
                if (*(copy_user + H) != -1 && *(copy_user + H) != -2 && *(copy_answer + Q) == *(copy_user + H))
                {
                    *(copy_answer + Q) = -2;
                    *(copy_user + H) = -2;
                    partial_match ++;
                }
            }
        }
    }
    if (perfect_match == ARRAY_SIZE)
    {
        return 1; // Correct guess received
    } 
    print_guess(user_array);
    printf("My response was\n");
    printf("%d matches %d partial matches\n", perfect_match, partial_match);
    return 0;
}

// Prints user's guess to console
void print_guess(const int *arr)
{
    printf("Your guess was\n");
    for (int i = 0, j = ARRAY_SIZE - 1; i < j; i++)
    {
        printf("%d ", *(arr + i));
    }
    // To avoid unnecessarily printing additional space at the end
    printf("%d\n", *(arr + ARRAY_SIZE - 1));
}

// Deep copies the values in the source array to the copy array
void copy_array(int *array_copy, const int *array_source)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        *(array_copy + i) = *(array_source + i);
    }
}

// Fills the array passed in with zeros using pointer arithmetic
void fill_zero(int *arr)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        *(arr + i) = 0;
    }
}