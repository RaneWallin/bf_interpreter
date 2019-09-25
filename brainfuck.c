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
 * 
 */


#include <stdio.h>
#include <string.h>

// function prototypes
int  		isValidCode(char code);
void 		addCode(FILE *file, char *code, int *count);
void 		fuckItUp(char code, int *data, int *p);

// constants
const int 	COMMANDS 		= 8;
const char 	VALID_CODE[] 	= {';', ':', '<', '>', '[', ']', '+', '-'};

// Errors
const char *NO_FILE_MSG 	= "No such file exists!";
const char	bEOF			= 255;
const int 	NO_FILE_ERROR 	= -2;


// File handling
const int 	FILENAME      	= 1;
const char	*READONLY		= "r";

int main(int argc, char **argv)
{
	int Data[100],
		count = 0,
		dPtr = 0,
		tCode = 0,
		i;
		
	char Code[100],
		 c;
		 
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

	// Get each character from the file, validate it, and put it
	// into the Code array
	addCode(fileBF, Code, &count);
	
	for(i = 0; i < count; i++) {
		fuckItUp(Code[i], Data, &dPtr);
	}
	
	return 0;
}

void fuckItUp(char code, int *data, int *p) {
	switch(code) {
		case ';':
			printf("? ");
			scanf("%d", &data[*p]);
			break;
		case ':':
			printf("%d\n", data[*p]);
			break;
		case '<':
			if (*p - 1 < 0)
				printf("Point out of bounds, quitting.\n");
			else 
				(*p)--;
			break;
		case '>':
			(*p)++;
			break;
		case '[':
			break;
		case ']':
			break;
		case '+':
			break;
		case '-':
			break;
		default:
			printf("You are seeing this something went extra wrong.\n");
	}
}

// Add characters to Code array
void addCode(FILE *file, char *code, int *count) {
	char c;

	c = fgetc(file);
	
	while(c != bEOF) {
		if(isValidCode(c)) {
			code[*count] = c;
			(*count)++;
		}
		
		c = fgetc(file);
	}
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
