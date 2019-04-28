/*---------------------------------------------------------------------------*\

     File Name:  Dates.h
        Author:  Marcel Riera

   Description:  Header file containing libraries, constants and function
                 prototypes required for ValidateMain.c, ConvertMain.c and
                 DateFunctions.c

                 This file is required for compilation and must be in the
                 same folder as:
                - DateFunctions.c
                - ValidateMain.c
                - ConvertMain.c

                NOTE: String buffer size is set to 40, as there are no valid
                formatted dates that can reach this length. Input lines longer
                than 40 characters are immediatelly discarded, not affecting
                the execution of the program.

\*---------------------------------------------------------------------------*/

#include <stdio.h>     // Required for I/O
#include <string.h>    // Required for input validation
#include <limits.h>    // Required for INT_MAX and INT_MIN

    /* Defined constants */

#define TRUE 1                         // True value for boolean expressions
#define FALSE 0                        // False value for boolean expressions
#define NO_ERRORS 0                    // Exit succesful
#define MONTHS_AMOUNT 12               // Total months in a year
#define DAY_FORMAT 2                   // Format for day display (%FORMATs)
#define BUFFER_SIZE 40                 // Buffer size allocated for strings
#define NO_DATA -1                     // No more data to read
#define DATE_FIELDS 3                  // Date fields amount (mm dd yy)
#define END_OF_STRING '\0'             // End of string character
#define NEWLINE '\n'                   // New line character
#define INTEGER_OVERFLOW LLONG_MIN     // Return value when found overflow
#define INVALID_ARGUMENTS -1           // Return for invalid program arguments
#define INVALID_DATE 0                 // Return for an invalid date
#define VALID_DATE 1                   // Return for a valid date
#define MIN_CHAR_INTEGER '0'           // First char representing an integer
#define MAX_CHAR_INTEGER '9'           // Last char representing an integer
#define EXPECTED_ARGUMENTS 2           // Expected value for argc
#define DATES_ARGUMENT_INDEX 1         // Index of dates argument in argv
#define VALIDATE_ALL_DATES 0           // Arg to validate all input dates
#define INPUT_FILENAME "dates.dat"     // Name of dates input file

    /* Enums & constant arrays */

typedef enum month {NONE, JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
                    AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER} Month;

static const int DAYS[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const char *MONTH_STR[] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                     "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    /* Function prototypes */

long long int parseIntOverflow(const char *input);
int isCharValidInteger(char testChar);
int parseDateOverflow(const char *date, int *month, int *day, int *year);
int isValidDate(const char *date);
int isValidMonth(int month);
int isValidDay(int day, int month, int year);
int isLeapYear(int year);
int getNextLine(char *buffer, int maxSize);
int validateArguments(int argc, char *argv[]);
char* convertDate(const char *date);
void displayFileContents(FILE *file);
void reportError();
