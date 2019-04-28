#---------------------------------------------------------------#
#  Makefile for ValidateDates.out and ConverDates.out programs  #
#      	Author:  Marcel Riera	      						    #
#---------------------------------------------------------------#

# Files required for compilation:
VALIDATE_FILES = ValidateMain.c DateFunctions.c
CONVERT_FILES = ConvertMain.c DateFunctions.c

# Name for executable:
VALIDATE_OUT = ValidateDates.out
CONVERT_OUT = ConvertDates.out

# Compile all
build: buildValidateDates buildConvertDates

# Compile ValidateDates.out	
buildValidateDates:
	gcc $(VALIDATE_FILES) -o $(VALIDATE_OUT)
	
# Compile ConvertDates.out
buildConvertDates:
	gcc $(CONVERT_FILES) -o $(CONVERT_OUT)
	
# Remove Object files	
clean: 
	rm -f *.o core

# Remove and recompile
rebuild: clean build