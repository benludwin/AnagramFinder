#include <stdio.h>
#include <stdlib.h>
#include "anagram.h"
/*
 * BenLudwin, 951510335, CIS415 Project 0
 * This is my own work except Roscoe provided the code for determining the input/output file in lab.
 */
int main(int argc, char* argv[])
{
	FILE* input = stdin;	
	FILE* output = stdout;
	if (argc > 1){ input = fopen(argv[1], "r"); }
	if (argc > 2){ output = fopen(argv[2], "w"); }
	if (input == NULL || output == NULL){
		exit(1);
	}
	char line[32];
	struct AnagramList *head = NULL;	
	while (fgets(line, sizeof(line), input) != NULL){
		line[strcspn(line, "\n")] = 0;
		AddWordAList(&head, line);
	}
	PrintAList(output, head);
	FreeAList(&head);
	if (input != stdin){ fclose(input); }	
	if (output != stdout){ fclose(output); }	
	return 0;
}

