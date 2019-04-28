/*---------------------------------------------------------------------------*\

   Source code:  ValidateMain.c
        Author:  Marcel Riera

      Language:  C
   Compile/Run: make build
          ./ValidateDates.out < dates.dat [*] | ./ConvertDates.out > output.dat

                NOTE: Items with asterisk correspond to user input:
                [*]: Positive integer to specify how many valid dates to output
                     from range 0 to INT_MAX.

   Alternative: gcc ValidateMain.c DateFunctions.c -o ValidateDates.out
                gcc ConvertMain.c DateFunctions.c -o ConvertDates.out
                PokerFunctions.c -o PokerHands.out
          ./ValidateDates.out < dates.dat [*] | ./ConvertDates.out > output.dat

  Dependencies: This program requires the following files in the same
                directory for proper compilation
                - Dates.h
                - ValidateMain.c
                - DateFunctions.c

  --------------------------------------------------------------------

  Description:  This program retrieves input dates from the user through stdin
                and checks if it is in a valid date format MM/DD/YYYY and if so
                outputs the date, else it dismisses it. The process is repeated
                until the expected amount of valid dates specified by the user
                has been reached. This program is suposed to be used as input
                for ConvertDate.out by pipelining the output to convert the
                dates format, altough its not required.
                NOTE: If used by itself, the user has to enter an EOF char to
                exit early the program (before the amount of valid dates
                specified by argument input has been reached)

        Input:  There are two main inputs:
                Argument input - The argument should specify the amount of
                valid dates to output, and should be a positive integer from
                range 0 to INT_MAX. An input of 0 is interpreted as output
                all valid dates possible.
                Stdin input - The user should enter a string line for the
                program to later check if its a valid date. This input is
                supposed to be received as a redirection from a file when
                executing the program. If not using redirection, to exit
                the program the user should enter a EOF char (CTRL-D in UNIX
                or CTRL-Z in Windows).


       Output:  The program outputs a number of dates that are considered
                valid dates in the format MM/DD/YYYY in accordance to the
                input argument amount of dates to output.

      Process:  The program's steps are as follows
                1. Validate input argument
                2. Start loop up to input argument with EOF sentinel
                3. Get a date line from stdin
                4. Validate date line
                5. If valid, display and increase loop counter
                7. Continue loop (step 2)
                16. Terminate


\*---------------------------------------------------------------------------*/

#include "Dates.h"    // Required program header

int main(int argc, char *argv[]) {
    /* Variable Initialization */
    const int expectedDates = validateArguments(argc, argv);
    char inputLine[BUFFER_SIZE] = {};
    int validDatesFound = 0;
    int hasData = TRUE;

    /* Argument Validation */
    if (expectedDates == INVALID_ARGUMENTS) {
        reportError();
        return INVALID_ARGUMENTS;
    } // endif

    /* Process and Output */
    while (validDatesFound < expectedDates && hasData) {
        if (getNextLine(inputLine, BUFFER_SIZE) == NO_DATA) {
            hasData = FALSE;
        } // endif
        if (isValidDate(inputLine) && hasData) {
            printf("%s\n", inputLine);
            validDatesFound++;
        } // endif
    } // endwhile

    /* Terminate */
    return NO_ERRORS;
} // endmain
