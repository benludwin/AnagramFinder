#include "anagram.h"
/*
 * BenLudwin, 951510335, CIS415 Project 0
 * This is my own work except that I used code I found online for quicksort. Link Below.
 * https://www.geeksforgeeks.org/quick-sort/
 */
void wordToLower(char *word){
        while (*word) {
                *word = tolower(*word);
                word++;
	}
}
void swap(char* a, char* b){ 
	char t = *a; 
    	*a = *b; 
	*b = t; 
} 
int partition(char arr[], int left, int right){ 
	int pivot = arr[right], i = left - 1, j;
	for (j = left; j <= right - 1; j++){ 
	        if (arr[j] <= pivot){ 
		        i++;
	        	swap(&arr[i], &arr[j]); 
        	} 
	} 
	swap(&arr[i + 1], &arr[right]); 
	return i + 1; 
}
void quickSortChar(char a[], int left, int right){
	int j;
	if (left < right){
	        j = partition(a, left, right);
        	quickSortChar(a, left, j - 1);
        	quickSortChar(a, j + 1, right);
    	}
}
void wordFormat(char *word){
	wordToLower(word);
	quickSortChar(word, 0, strlen(word)-1);
}
void AppendSList(struct StringList **head, struct StringList *node){
	struct StringList *current = *head;
	while (current->Next){
		current = current->Next;
	}
	current->Next = node;
}
void PrintSList(FILE *file,struct StringList *node){
	struct StringList *current = node;
	while (current->Next){
		fprintf(file, "\t%s\n", current->Word);	
		current = current->Next;
	}
	fprintf(file, "\t%s\n", current->Word);	
}

void PrintAList(FILE *file,struct AnagramList *node){
	struct AnagramList *current = node;
	while (current->Next){
		if (SListCount(current->Words) > 1){
			fprintf(file, "%s:%d\n", current->Anagram, SListCount(current->Words));	
			PrintSList(file, current->Words);
		}
		current = current->Next;
	}
}
int SListCount(struct StringList *node){
	if (!node->Next){
		return 1;
	} else {
		int count = 1;
		struct StringList *current = node;
		while (current->Next){
			current = current->Next;
			count++;
		}
		return count;
	}
}
struct StringList *MallocSList(char *word){
	struct StringList *newStringList;
	char *temp = strdup(word);
	newStringList = (struct StringList *)malloc(sizeof(struct StringList));
	newStringList->Word = temp;
	newStringList->Next = NULL;
	return newStringList;
}
struct AnagramList* MallocAList(char *word){
	struct AnagramList *newAnagramList;
	newAnagramList = (struct AnagramList *)malloc(sizeof(struct AnagramList));
	char *anagram = strdup(word);
	wordFormat(anagram);		
	newAnagramList->Anagram = anagram;
	newAnagramList->Words = MallocSList(word);
	newAnagramList->Next = NULL;
	return newAnagramList;
}
void FreeSList(struct StringList **node){
	struct StringList *current = *node;
	struct StringList *prev;
	if (!current->Next){
		free(current->Word);
		free(current);
	} else {
		while (current->Next){
			prev = current;
			current = current->Next;
			free(prev->Word);
			free(prev);
		}
		free(current->Word);
		free(current);
	}
}
void FreeAList(struct AnagramList **node){
	struct AnagramList *current = *node;
	struct AnagramList *prev = *node;
	if (!current->Next){
		FreeSList(&current->Words);
		free(current->Anagram);
		free(current);
	} else {
		while(current->Next){
			prev = current;
			current = current->Next;
			FreeSList(&prev->Words);
			free(prev->Anagram);
			free(prev);
		}
		FreeSList(&current->Words);
		free(current->Anagram);
		free(current);
	}
}
void AddWordAList(struct AnagramList **node, char *word){
	if (*node == NULL){
		*node = MallocAList(word);
	} else {
		int added = 0;
		struct AnagramList *current = *node;
		char *anagram = strdup(word);
		wordFormat(anagram);		
		if (strcmp(current->Anagram, anagram) == 0){
			AppendSList(&current->Words, MallocSList(word));
			free(anagram);
			return;
		}
		while (current->Next){
			current = current->Next;
			if (strcmp(current->Anagram, anagram) == 0){
				AppendSList(&current->Words, MallocSList(word));
				added = 1;
				break;
			}
		}
		if (added == 0){ current->Next = MallocAList(word); }
		free(anagram);
	}
}
