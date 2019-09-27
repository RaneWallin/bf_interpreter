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
void 		fuckItUp(char code, char *cPtr, int *dPtr);

// constants
const int 	COMMANDS 		= 8;
const char 	VALID_CODE[] 	= {';', ':', '<', '>', '[', ']', '+', '-'};

// Errors
const char  *NO_FILE_MSG 	= "No such file exists!";
const char	bEOF			= 255;
const int 	NO_FILE_ERROR 	= -2;


// File handling
const int 	FILENAME      	= 1;
const char	*READONLY		= "r";

int main(int argc, char **argv)
{
	int Data[1000],
		*dPtr = Data,
		fsz,
		i;
		
	char *Code,
		 *cPtr;
		 
	FILE *fileBF; 
	
	if(argc == 1) {
		printf("No commands\n");
		return -1;
	}
	
	// Verify and open file
	if((fileBF = fopen(argv[FILENAME], READONLY)) == NULL) {
		// File doesn't exist
		printf("%s\n", NO_FILE_MSG);
		return NO_FILE_ERROR;
	}
	
	// Determine file size and allocate memory for the Code
	// array based on it
	fseek(fileBF, 0L, SEEK_END);
	fsz = ftell(fileBF);
	rewind(fileBF);
	Code = (char *) malloc((fsz + 1) * sizeof(char));

	// Get each character from the file, validate it, and put it
	// into the Code array
	addCode(fileBF, Code);
	

	cPtr = Code;

	fuckItUp(*cPtr, cPtr,dPtr);
	
	printf("\n");
	
	return 0;
}

// Perform current command `code`
void fuckItUp(char code, char *cPtr, int *dPtr) {
	//int *Data = (int *) malloc(10 * sizeof(int))

		
	switch(code) {
		case ';':
			printf("? ");
			scanf("%d", &*dPtr);
			break;
		case ':':
			printf("%d ", *dPtr);
			break;
		case '<':
			if (dPtr - 1 < 0)
				printf("Point out of bounds, quitting.\n");
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
						printf("[ Loop conditions out of bound.\n");
						return;
					}
					cPtr++;
				} 
				cPtr++;
			}
				
			break;
		case ']':
			while(*cPtr != '[') {
				if (cPtr < 0) {
					printf("] Loop conditions out of bound.\n");
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
	
	if(*cPtr != '\0') 
		fuckItUp(*cPtr, cPtr, dPtr); 
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
