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
int  		isValidCode(char code);
void 		addCode(FILE *file, char *code);
void 		fuckItUp(char code, 
					 char *cPtr, 
					 int *dPtr, 
					 int *Data, 
					 char *Code, 
					 char flag);
					 
// colors
const char *BRIGHT_RED  	= "\033[31;1m";
const char *DARK_CYAN    	= "\033[36m";
const char *BRIGHT_CYAN  	= "\033[36;1m";
const char *BRIGHT_WHITE 	= "\033[37;1m";
const char *CLEAR_COLOR  	= "\033[0m";


// constants
const int 	COMMANDS 		= 8;
const char 	VALID_CODE[] 	= {';', ':', '<', '>', '[', ']', '+', '-'};

// Errors
const char  *NO_FILE_MSG 	= "No such file exists!";
const char  *USAGE 			= "Usage: brain <filename>\n";
const char 	*BAD_LOOP		= "Loop conditions out of bounds.\n";
const char	*BAD_POINTER	= "Pointer out of bounds.\n";
const char	bEOF			= 255;
const int 	NO_FILE_ERROR 	= -2;
const int 	USAGE_ERROR		= -1;


// File handling
const int 	FILENAME      	= 1;
const char	*READONLY		= "r";

int main(int argc, char **argv)
{
	int *Data,
		*dPtr,
		fsz,
		i;
		
	char *Code,
		 *cPtr;
		 
	FILE *fileBF; 
	
	if(argc == 1) {
		printf(USAGE);
		return USAGE_ERROR;
	}
	
	// Verify and open file
	if((fileBF = fopen(argv[FILENAME], READONLY)) == NULL) {
		// File doesn't exist
		printf("%s\n", NO_FILE_MSG);
		return NO_FILE_ERROR;
	}
	
	// Allocate data
	Data = (int *) calloc(1000, sizeof(int));
	
	// Determine file size and allocate memory for the Code
	// array based on it
	fseek(fileBF, 0L, SEEK_END);
	fsz = ftell(fileBF);
	rewind(fileBF);
	if(fsz < 10) fsz = 10;
	Code = (char *) calloc((fsz + 1), sizeof(char));

	// Get each character from the file, validate it, and put it
	// into the Code array
	addCode(fileBF, Code);
	

	// Set pointers
	cPtr = Code;
	dPtr = Data;
	
	
	fuckItUp(*cPtr, cPtr, dPtr, Data, Code, 'v');
	
	printf("\n");
	
	return 0;
}

// Perform current command `code`
void fuckItUp(char code, char *cPtr, int *dPtr, int *Data, char *Code, char flag) {
	int i, j;
	
	
	// Print Code and Data info in verbose mode
	if(flag == 'v') {
		// pause
		for(i = 0; i < 10000; i++)
			for(j = 0; j < 10000; j++);
			
		printf("Data: ");
		for(i = 0; i < 10; i++) {
			printf("%s%d ", (&Data[i] == dPtr) ? 
								BRIGHT_CYAN : CLEAR_COLOR,
							  Data[i]);
		}
		
		printf("\n");
		printf("Code: ");
		for(i = 0; i < 10; i++) {
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
			printf("%s%d%s ", (flag == 'v' ? BRIGHT_RED : CLEAR_COLOR), 
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
				while(*cPtr != ']') {
					if (*cPtr == '\0') {
						printf("[ %s", BAD_LOOP);
						return;
					}
					cPtr++;
				} 
			}
				
			break;
		case ']':
			while(*cPtr != '[') {
				if (cPtr < 0) {
					printf("] %s", BAD_LOOP);
					return;
				}
			
				cPtr--;	
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
	
	if(flag == 'v')
		printf("\n");
	
	if(*cPtr != '\0') 
		fuckItUp(*cPtr, cPtr, dPtr, Data, Code, flag); 
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
