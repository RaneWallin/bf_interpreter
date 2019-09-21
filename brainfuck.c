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
#include <strings.h>

// function prototypes
void addData(int data, int *Data);
void addCode(char code, char *Code);
void growCharArray(char *arr);
void growIntArray(int *arr);
int  isValidCode(char code);

// constants
const int COMMANDS = 8;
const char VALID_CODE[8] = {';', ':', '<', '>', '[', ']', '+', '-'};

int main(int argc, char **argv)
{
	int Data[100], i;
	char Code[100];
	
	if(argc == 1) {
		 printf("No commands\n");
		 return -1;
	 }
	
	for(i = 1; i < argc; i++) {
		printf("%s is %s valid\n", 	argv[i],
									isValidCode(*argv[i]) ? "" : "not");
	}
	
	return 0;
}

// Add integer to Data
void addData(int data, int *Data) {
	
}

// Add char to Code
void addCode(char code, char *Code) {
	
}

// increase the length of a char array
void growCharArray(char *arr) {
	
}

// increase the length of an int array
void growIntArray(int *arr) {
	
}

// verify code char is a valid command
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
