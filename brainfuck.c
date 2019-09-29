/*
 * brainfuck.c - Rane Wallin
 * 
 * A brainfuck interpreter that processes code written in brainfuck
 * 
 * Copyright 2019  <SheCodes@pm.me>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * Determine file size: https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function prototypes
int  						isValidCode(char code);
void 						addCode(FILE *file, char *code);
void 						fuckItUp(char code, 
									 char *cPtr, 
									 int *dPtr, 
									 int *Data, 
									 char *Code, 
									 int verbose,
									 int pause);
					 
// colors
const char *BRIGHT_RED		= "\033[31;1m";
const char *DARK_CYAN		= "\033[36m";
const char *BRIGHT_CYAN		= "\033[36;1m";
const char *BRIGHT_WHITE	= "\033[37;1m";
const char *CLEAR_COLOR		= "\033[0m";


// constants
const int 	COMMANDS		= 8;
const char 	VALID_CODE[]	= {';', ':', '<', '>', '[', ']', '+', '-'};

// Errors
const char	*NO_FILE_MSG	= "No such file exists!";
const char	*USAGE			= "Usage: brain <filename> [-v | -r]\n";
const char	*BAD_LOOP		= "Loop conditions out of bounds.\n";
const char	*BAD_POINTER	= "Pointer out of bounds.\n";
const char	bEOF			= 255;
const int	NO_FILE_ERROR	= -2;
const int	USAGE_ERROR		= -1;


// File handling
const char	*READONLY		= "r";

int main(int argc, char **argv)
{
	int *Data,
		*dPtr,
		fsz,
		repeat = 0,
		filename = 1,
		verbose = 0,
		pause = 0,
		i;
		
	char *Code,
		 *cPtr;
		 
	FILE *fileBF; 
	
	if(argc == 1) {
		printf(USAGE);
		return USAGE_ERROR;
	}
	
	if(argc > 2) {
		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-v") == 0) 
				verbose = 1;
			else if (strcmp(argv[i], "-r") == 0)
				repeat = 1;
			else if(strcmp(argv[i], "-p") == 0)
				pause = 1;
			else
				filename = i;
		}
	}
	
	
	// Verify and open file
	if((fileBF = fopen(argv[filename], READONLY)) == NULL) {
		// File doesn't exist
		printf("%s: %s\n", NO_FILE_MSG, argv[filename]);
		return NO_FILE_ERROR;
	}
	
	// Allocate data
	Data = (int *) calloc(1000, sizeof(int));
	
	// Determine file size and allocate memory for the Code
	// array based on it
	fseek(fileBF, 0L, SEEK_END);
	fsz = ftell(fileBF);
	rewind(fileBF);
	if(fsz < 30) fsz = 30;
	Code = (char *) calloc((fsz + 1), sizeof(char));

	// Get each character from the file, validate it, and put it
	// into the Code array
	addCode(fileBF, Code);
	

	// Set pointers
	cPtr = Code;
	dPtr = Data;
	
	printf("Brainfuck interpreter by Rane Wallin\n");
	
	do {
		printf("\nRunning...\n");;
		fuckItUp(*cPtr, cPtr, dPtr, Data, Code, verbose, pause);
		printf("\n");
	} while(repeat);
	
	printf("\n");
	
	return 0;
}

// Perform current command `code`
void fuckItUp(char code, char *cPtr, int *dPtr, int *Data, char *Code, int verbose, int pause) {
	int i, j,
	    lb = 0,
	    rb = 0;
	
	// pause
	if(pause)
		for(i = 0; i < 10000; i++)
			for(j = 0; j < 10000; j++);
	
	
	// Print Code and Data info in verbose mode
	if(verbose) {
			
		printf("Data: ");
		for(i = 0; i < 10; i++) {
			printf("%s%d ", (&Data[i] == dPtr) ? 
								BRIGHT_CYAN : CLEAR_COLOR,
							  Data[i],
							  CLEAR_COLOR);
		}
		
		printf("\n");
		printf("Code: ");
		for(i = 0; i < 50; i++) {
			printf("%s%c%s ", &Code[i] == cPtr ? BRIGHT_CYAN : CLEAR_COLOR,
						      Code[i], CLEAR_COLOR);
		}
		printf("\n");
	}
		
	switch(code) {
		case ';':
			printf("? ");
			scanf("%d", &*dPtr);
			break;
		case ':':
			printf("%s%d%s ", (verbose ? BRIGHT_RED : CLEAR_COLOR), 
					          *dPtr, 
					          CLEAR_COLOR);
			break;
		case '<':
			if (dPtr - 1 < 0)
				printf(BAD_POINTER);
			else { 
				dPtr--;
			}
			break;
		case '>':
			dPtr++;
			break;
		case '[':
			
			if(*dPtr == 0) {
				rb++;
				while(rb != 0) {
					if (*cPtr == '\0') {
						printf("[ %s", BAD_LOOP);
						return;
					}
					cPtr++;
					if(*cPtr == '[') rb++;
					if(*cPtr == ']') rb--;
				} 
			}
				
			break;
		case ']':
			lb++;
			
			while(lb != 0) {
				if (cPtr < 0) {
					printf("] %s", BAD_LOOP);
					return;
				}
				
				cPtr--;
				
				if(*cPtr == ']') lb++;
				
				if(*cPtr == '[') lb--;	
				//cPtr--;
			} 
			
			cPtr--;
			break;
		case '+':
			(*dPtr)++;
			break;
		case '-':
			(*dPtr)--;
			break;
		default:
			printf("If you are seeing this something went extra wrong.\n");
	}
	cPtr++;
	
	if(verbose)
		printf("\n");
	
	if(*cPtr != '\0') 
		fuckItUp(*cPtr, cPtr, dPtr, Data, Code, verbose, pause); 
}

// Add characters to Code array
void addCode(FILE *file, char *code) {
	char c;

	c = fgetc(file);
	
	while(c != bEOF) {
		if(isValidCode(c)) {
			*code = c;
			code++;
		}
		
		c = fgetc(file);
	}

	*code = '\0';
}

// Check if code char is a valid command
int isValidCode(char code) {
	int isValid = 0,
		count = 0;
	
	while(!isValid && count < COMMANDS) {
		if (code == VALID_CODE[count])
			isValid = 1;
		
		count++;
	}
	
	return isValid;
}
