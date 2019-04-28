/*---------------------------------------------------------------------------*\

   Source code:  DateFunctions.c
        Author:  Marcel Riera

   Description:  Source code containing a collection of functions required for
                 programs ValidateMain.c and ConvertMain.c

                 This program is required for compilation and must be in the
                 same folder as:
                - Dates.h
                - ValidateMain.c
                - ConvertMain.c

\*---------------------------------------------------------------------------*/

#include "Dates.h"    // Required program header

/**
 * Function isValidDate
 * Checks whether the input string is a valid date in format MM/DD/YY
 * @param date  Input string to check if is valid date
 * @return      TRUE if string is a valid date, FALSE otherwise
 */

int isValidDate(const char *date) {
    int year = 0;
    int month = 0;
    int day = 0;

    if (parseDateOverflow(date, &month, &day, &year) == INVALID_DATE) {
        return FALSE;
    } // endif
    if (isValidMonth(month) && isValidDay(day, month, year)) {
        return TRUE;
    } // endif
    return FALSE;
} // endfunction


/**
 * Function isValidMonth
 * Checks whether the given month number is a valid month.
 * @param date  Input integer to be test if is valid month
 * @return      TRUE if integer is a valid month, FALSE otherwise
 */

int isValidMonth(int month) {
    return (month > 0) && (month <= MONTHS_AMOUNT);
}

/**
 * Function isValidDay
 * Checks whether the given day is valid for a particular month and year.
 * @param day   Input day of the given date to validate
 * @param month Input month of the given date to validate
 * @param year  Input year of the given date to validate
 * @return      TRUE if the day is valid for the date, FALSE otherwise
 */

int isValidDay(int day, int month, int year) {
    int daysAmount = DAYS[month];
    if (month == FEBRUARY && isLeapYear(year)) {
        daysAmount++;
    } // endif
    return (day > 0) && (day <= daysAmount);
} // endfunction

/**
 * Function parseIntOverflow
 * Receives an input string, and if posible parses it to an integer. It also
 * checks if the input results in integer overflow, or if string does not
 * represent a valid integer value.
 *
 * FORMULA
 *   currentValue = (currentValue * 10) + (input[index] - MIN_CHAR_INTEGER)
 *  The formula multiplies the current value by 10 to make space for the new
 *  digit to be included. The rest of the formula parses the digit from char
 *  and adds it to the result.
 *
 * @param toParse Input string to parse to integer
 * @return        Integer representation of input, INPUT_OVERFLOW otherwise.
 */

long long int parseIntOverflow(const char *toParse) {
    const long long int MAX_VALUE = INT_MAX; // To cast INT_MAX as a long.
    long long int currentValue = 0;
    int isNegative = FALSE;
    int index = 0;

    if (toParse[index] == '-') {
        isNegative = TRUE;
        index++;
    } // endif

    for (; toParse[index] != END_OF_STRING; index++) {
        if (!isCharValidInteger(toParse[index])) {
            return INTEGER_OVERFLOW;
        } // endif
        currentValue = (currentValue * 10) + (toParse[index] - MIN_CHAR_INTEGER);
         /* ^ formula in documentation */
        if (currentValue > (MAX_VALUE + isNegative)) {
            return INTEGER_OVERFLOW;
        } // endif
    } // endfor

    if (isNegative) {
        currentValue = currentValue * -1;
    } // endif
    return currentValue;
} // endfunction

/**
 * Function isCharValidInteger
 * Checks whether the input char represents a numeric digit.
 * @param testChar  Character to test if represents a digit.
 * @return          TRUE if character represents a digits, FALSE otherwise
 */

int isCharValidInteger(char testChar) {
    if ((testChar < MIN_CHAR_INTEGER) || (testChar > MAX_CHAR_INTEGER)) {
        return FALSE;
    } // endif
    return TRUE;
} // end function

/**
 * Function parseDateOverflow
 * Parses a non validated input string date to day, month and year. It splits
 * the input in three parts expecting the format MM/DD/YYYY. In the process it
 * validates if the input has three date fields, and if any result in overflow.
 * This function uses function 'strtok' from the string.h library, covered in
 * chapter 8.8.7 of D/D class book, to split the date into tokens or fields.
 * @param date   Input string date to parse from.
 * @param month  A pointer to an int variable to save the resulting month
 * @param day    A pointer to an int variable to save the resulting day
 * @param year   A pointer to an int variable to save the resulting year
 * @return       VALID_DATE if parsed succesfully, INVALID_DATE otherwise
 */

int parseDateOverflow(const char *date, int *month, int *day, int *year) {
    long long int parsedInput = 0;
    char copy[BUFFER_SIZE] = {};
    char *currentPtr = NULL;
    int *handler[] = {month, day, year};    // Handler to unify the process
    int counter = 0;                             // for month, day and year

    strcpy(copy, date);                  // Make a backup of the input date
    currentPtr = strtok(copy, "/");     // Get a pointer to the first field

    while (currentPtr != NULL) {    // Keep retrieving until strtok is done
        parsedInput = parseIntOverflow(currentPtr);
        currentPtr = strtok(NULL, "/");       // Retrieve next field if any

        if (counter >= DATE_FIELDS || parsedInput == INTEGER_OVERFLOW) {
            return INVALID_DATE;
        } // endif
        *handler[counter] = parsedInput;
        counter++;
    } // endwhile
    return VALID_DATE;
} // endfunction

/**
 * Function isLeapYear
 * Checks if the given year is a leap year.
 *
 * FORMULA
 *      (year % 4 == 0 && year % 100 != 0) || year % 400 == 0
 * Formula retrieved from K/R class book, page 48, "2.5 Arithmetic Operations".
 * From book: "a year is a leap year if it is divisible by 4 but not by 100,
 * except that years divisible by 400 are leap years".
 *
 * @param year   Integer year to check if its a leap year.
 * @return       TRUE if given year is a leap year, FALSE otherwise.
 */

int isLeapYear(int year) {
    /* Formula in documentation */
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
} // endfunction

/**
 * Function validateArguments
 * Validates program parameters argc and argv to retrieve how many dates the
 * user requires the program to process.
 * @param argc   Integer argc from main execution
 * @param argv[] Arguments argv from main execution
 * @return       Parsed argument if input is valid, else INVALID_ARGUMENTS
 */

int validateArguments(int argc, char *argv[]) {
    long long int parsedInput = 0;

    if (argc != EXPECTED_ARGUMENTS) {
        return INVALID_ARGUMENTS;
    } // endif

    parsedInput = parseIntOverflow(argv[DATES_ARGUMENT_INDEX]);

    if (parsedInput == INTEGER_OVERFLOW) {
        return INVALID_ARGUMENTS;
    } // endif

    if (parsedInput == VALIDATE_ALL_DATES) {
        return INT_MAX;
    } // endif
    return (int) parsedInput;
} // endfunction

/**
 * Function convertDate
 * Converts a date from format MM/DD/YYYY to DD MM YYYY where the month is
 * a three character month representation. eg 01/01/2000 -> 01 JAN 2000
 * @param date  Validated string date in MM/DD/YYYY format
 * @return      String date in new format DD MM YYYY
 */

char* convertDate(const char *date) {
    static char newDate[BUFFER_SIZE] = {};
    int year = 0;
    int month = 0;
    int day = 0;

    sscanf(date, "%d/%d/%d", &month, &day, &year);
    sprintf(newDate, "%*d %s %d\n", DAY_FORMAT, day, MONTH_STR[month], year);
    return newDate;
} // endfunction

/**
 * Function displayFileContents
 * Displays the contents of a given input file to the standard output.
 * @param file    Pointer to a file to read from.
 */

void displayFileContents(FILE *file) {
    char currentChar = fgetc(file);
    puts("");

    while (currentChar != EOF) {
        printf("%c", currentChar);
        currentChar = fgetc(file);
    } // endwhile
} // endfunction

/**
 * Function getNextLine
 * Retrieves input from standard input until a newline character is found.
 * The function also discards buffer overflow, and replaces newline character
 * for an '\0' end of string character.
 * @param buffer    String to store the input line red from stdin
 * @param maxSize   Maximum buffer size of input buffer
 * @return          NO_ERRORS if red succesfully, NO_DATA if reached EOF
 */

int getNextLine(char *buffer, int maxSize) {
    int index = 0;
    char currentChar = 0;

    do {
        currentChar = getchar();
        if (currentChar == EOF) {
            return NO_DATA;
        } // endif
        if (index < maxSize) {
            buffer[index] = currentChar;
        } // endif
        index++;
    } while (currentChar != NEWLINE);

    buffer[index - 1] = END_OF_STRING;
    return NO_ERRORS;
} // endfunction

/**
 * Function reportError
 * Writes an error message to STDERR explaining the cause of termination,
 * which is due to invalid arguments.
 */

void reportError() {
    fprintf(stderr, "Error: The program started with invalid arguments.\n");
    fprintf(stderr, "The program expects a positive integer argument.");
} // endfunction
