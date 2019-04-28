/*---------------------------------------------------------------------------*\

   Source code:  ConvertMain.c
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
                - ConvertMain.c
                - DateFunctions.c

  --------------------------------------------------------------------

  Description:  This program retrieves input validated dates in format
                MM/DD/YYYY from standard input, and outputs the converted
                date in format DD MMM YYYY, where MMM is a three character
                string representing the month. The process is repeated until
                a EOF character is read from standard input.

        Input:  Stdin input - The program expects to receive valid dates from
                the standard input (format MM/DD/YYYY). The program is supposed
                to work in a pipeline with ValidateDates.out to ensure valid
                dates are received. If not using redirection, to exit
                the program the user should enter a EOF char (CTRL-D in UNIX
                or CTRL-Z in Windows).


       Output:  Outputs the input date in a new format DD MMM YYYY, where MMM
                is the three character representation of the month.

      Process:  The program's steps are as follows
                1. Start loop until EOF is found
                2. Get a date from stdin
                3. Split date into day, month and year
                4. Output date into new format DD MM YYYY
                5. Continue loop (to step 1)
                6. Open file dates.dat
                7. Output the file contents
                8. Close dates.dat
                9. Terminate

\*---------------------------------------------------------------------------*/

#include "Dates.h"    // Required program header

int main() {
    /* Variable Initialization */
    FILE *datesFile = NULL;
    char currentDate[BUFFER_SIZE] = {};
    int hasData = TRUE;

    /* Process and output */
    while (hasData) {
        if (scanf("%s", currentDate) == NO_DATA) {
            hasData = FALSE;
        } // endif
        else {
            printf("%s", convertDate(currentDate));
        } // endelse
    } // endwhile

    /* Output file contents*/
    datesFile = fopen(INPUT_FILENAME, "r");
    displayFileContents(datesFile);
    fclose(datesFile);

    /* Terminate */
    return NO_ERRORS;
} // endmain
