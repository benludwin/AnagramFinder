#include <stdio.h>
#include <string.h>

void func(char * temp){
	char * name;
	name = strtok(temp, ":");
	char *s = name;
	while (*s) {
		*s = tolower(*s);
		s++;
	}
}

void quickSortChar(char a[], int left, int right)
{
    int j;
    if (left < right)
    {
        j = partition(a, left, right);
        quickSortChar(a, left, j - 1);
        quickSortChar(a, j + 1, right);
    }
}

int partition(char a[], int left, int right)
{
    int pivot, i, j, t;
    pivot = a[left];
    i = left; j = right + 1;

    while (1)
    {
        do i++; while (a[i] <= pivot && i <= right);
        do j--; while (a[j] > pivot);
        if (i >= j) break;
        t = a[i]; a[i] = a[j]; a[j] = t;
    }
    t = a[left]; a[left] = a[j]; a[j] = t;
    return j;
}

void applyBoth(char *word){
	func(word);
	quickSortChar(word, 0, strlen(word) - 1);
}

int main(){
	char s[] = "SIDFBGSKDFILNKJpqmlzknxjcsbehvrgyrvchuejiwsaqplazkmxnscjbGTBYRVUCNEIMXWalmxcnkdjbvr";
	char *r = strdup(s);
	applyBoth(r);
	fprintf(stderr, "%s\n", s);
	fprintf(stderr, "%s\n", r);
	return 1;
}

