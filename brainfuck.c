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
#include <stdlib.h>

// function prototypes
int  		isValidCode(char code);
void 		addCode(FILE *file, char *code, int *count);
void 		fuckItUp(char code, char *Code, int *Data, int *dPtr, int *cPtr);

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
		cPtr = 0,
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
	Code[count + 1] = '\0';
	
	while(Code[cPtr] != '\0') {
		fuckItUp(Code[cPtr], Code, Data, &dPtr, &cPtr);
		cPtr++;
	}
	
	printf("\n");
	
	return 0;
}

void fuckItUp(char code, char *Code, int *Data, int *dPtr, int *cPtr) {
	int i, j;

	//for(i = 0; i < 10000; i++)
	//	for(j = 0; j < 10000; j++);
		
	switch(code) {
		case ';':
			printf("? ");
			scanf("%d", &Data[*dPtr]);
			break;
		case ':':
			printf("%d", Data[*dPtr]);
			break;
		case '<':
			if (*dPtr - 1 < 0)
				printf("Point out of bounds, quitting.\n");
			else { 
				(*dPtr)--;
			}
			break;
		case '>':
			(*dPtr)++;
			break;
		case '[':
			if(Data[*dPtr] == 0) {
				while(Code[*cPtr] != ']') {
					if (Code[*cPtr] == '\0') {
						printf("[ Loop conditions out of bound.\n");
						return;
					}
					(*cPtr)++;
				} 
				(*cPtr)++;
			}
				
			break;
		case ']':
			while(Code[*cPtr] != '[') {
				if (*cPtr < 0) {
					printf("] Loop conditions out of bound.\n");
					return;
				}
			
				(*cPtr)--;	
			} 
			
			(*cPtr)--;
			break;
		case '+':
			(Data[*dPtr])++;
			break;
		case '-':
			(Data[*dPtr])--;
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
