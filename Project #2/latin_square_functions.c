/******************************************************************************
 * @file: latin_square_functions.c
 *
 * sdanda
 * Sreeram
 * 9081904576
 *
 * @creator: Sreeram Danda (sdanda@wisc.edu)
 * @modified: 11/10/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0
// before submitting!
#define DEBUG 0
#define dbgprintf(...)       \
    if (DEBUG)               \
    {                        \
        printf(__VA_ARGS__); \
    }
#define dbgprint_latin_square(n, LS) \
    if (DEBUG)                       \
    {                                \
        Print_Latin_Square(n, LS);   \
    }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/
int Count_Occurence(char find, const size_t n, char **latin_square)
{
    int occurences = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            char value = *(*(latin_square + r) + c);
            if (value == find)
            {
                occurences++;
            }
        }
    }

    return occurences;
}
// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename,
                            char ***latin_square_in,
                            size_t *n)
{
    /* BEGIN MODIFYING CODE HERE */
    //Opening the file
    FILE *latin_square = fopen(filename, "r");

    char buffer;
    int rows = 0;
    int num_chars = 0;

    //Read the file and count lines
    while (1)
    {
        if (feof(latin_square))
        {
            break;
        }

        //reading the file
        buffer = fgetc(latin_square);

        //counting the lines
        if (buffer >= 33 && buffer <= 126)
        {
            num_chars++;
        }
    }

    for (int i = 1; i <= 1000; i++)
    {
        if (i * i == num_chars)
        {
            rows = i;
            break;
        }
    }

    //Reserving memeory for the latin square
    char **square = malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; i++)
    {
        *(square + i) = malloc(sizeof(char) * rows);
    }

    rewind(latin_square);
    //Fill in latin square from file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            fscanf(latin_square, " %c", &(*(*(square + i) + j)));
        }
    }

    *n = rows;
    *latin_square_in = square;

    fclose(latin_square);
    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square)
{
    if (latin_square == NULL)
    {
        printf("Verify_Alphabet - latin_square is NULL\n");
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    int occurence = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            char value = *(*(latin_square + r) + c);
            occurence = Count_Occurence(value, n, latin_square);
            if (occurence != n)
            {
                return 0;
            }
        }
    }
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Rows_and_Columns(const size_t n, char **latin_square)
{
    if (latin_square == NULL)
    {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n");
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    int r, c, i, j;
    int invalid_row = 0;
    int invalid_col = 0;
    int breaker = 0;
    //CHECKING ALL ROWS
    for (r = 0; r < n; r++) //for every row
    {
        for (i = 0; i < n; i++) //for each value in the row
        {
            for (j = i + 1; j < n; j++)
            {
                char compare_to = *(*(latin_square + r) + i); //locked value (changed after compared to every char past itself)
                char comparee = *(*(latin_square + r) + j);   //free value (every value after locked value)
                breaker = 0;

                if (compare_to == comparee)
                {
                    printf("Error in row %d\n", r);
                    invalid_row = 1;
                    breaker = 1;
                    break;
                }
            }
            if (breaker == 1)
            {
                break;
            }
        }
    }

    //CHECKING ALL COLUMNS
    for (c = 0; c < n; c++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                char compare_to = *(*(latin_square + i) + c); //locked value (changed after compared to every char past itself)
                char comparee = *(*(latin_square + j) + c);   //free value (every value after locked value)
                breaker = 0;

                if (compare_to == comparee)
                {
                    printf("Error in column %d\n", c);
                    invalid_col = 1;
                    breaker = 1;
                    break;
                }
            }
            if (breaker == 1)
            {
                break;
            }
        }
    }

    if (invalid_row || invalid_col)
    {
        return 0;
    }

    // printf("Error in row %d\n", i);
    // printf("Error in column %d\n", i);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */
void Free_Memory(const size_t n, char **latin_square)
{
    /* BEGIN MODIFYING CODE HERE */
    for (int i = 0; i < n; i++)
    {
        free(*(latin_square + i));
    }
    free(latin_square);
    /* END MODIFYING CODE HERE */
}
