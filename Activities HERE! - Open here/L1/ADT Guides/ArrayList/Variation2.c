#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
	int elem[MAX];
	int count;
}Etype, *Eptr;

void initialize(Eptr L){
	L->count = 0;
}

void insertPos(Eptr L, int data, int position){
	int ndx, count;
	
	for(ndx = 0; ndx < L->count, ndx != position; ndx++){}
	
	memcpy(&(L->elem[ndx]), &(L->elem[ndx-1]), sizeof(L->elem[0]) * (L->count - ndx + 1));

	L->elem[ndx] = data;
	L->count++;	
}

void deletePos(Eptr L, int position){
	int ndx, count;
	
	for(ndx = position, count = 1; ndx < L->count; ndx++, count++){}
	
	memcpy(&(L->elem[position]), &(L->elem[position+1]), sizeof(L->elem[0]) * count);
	
	L->count--;
}

int locate(Eptr L, int data){
	int ndx;
	
	for(ndx = 0; L->elem[ndx] != data; ndx++){}
	
	if(ndx >= L->count){
		return -1;
	}
	
	return ndx;
}

int retrieve(Eptr L, int position){
	
	if(position >= L->count){
		return -1;
	}
	
	return L->elem[position];
}

void insertSorted(Eptr L, int data){
	int ndx;
	
	for(ndx = 0; ndx < L->count && L->elem[ndx] <= data; ndx++) {}
	
	memcpy(&(L->elem[ndx]), &(L->elem[ndx-1]), sizeof(L->elem[0]) * (L->count - ndx + 1));
	
	L->elem[ndx] = data;
	L->count++;
}

void makeNULL(Eptr L){
	free(L);
}

void display(Eptr L){
	int ndx = 0;
	
	while(ndx < L->count){
		printf("Index: %d Element: %d", ndx, L->elem[ndx]);
		if(ndx < L->count-1){
			printf("\n");
		}
		ndx++;
	}
}

int main(int argv, char *argc[]){
	Eptr L;
	
	initialize(L);
	
	L->elem[0] = 1;
	L->elem[1] = 3;
	L->elem[2] = 2;
	L->elem[3] = 5;
	
	L->count = 4;

	
	//insertPos
	printf("\n\nInsert Position\n\n");
	display(L);
	printf("\n\n");
	insertPos(L, 4, 2);
	display(L);


	//deletePos
	L->elem[0] = 1;
	L->elem[1] = 3;
	L->elem[2] = 2;
	L->elem[3] = 5;
	
	L->count = 4;

	printf("\n\nDelete Position\n\n");
	display(L);
	printf("\n\n");
	deletePos(L, 1);
	display(L);


	//locate
	L->elem[0] = 1;
	L->elem[1] = 3;
	L->elem[2] = 2;
	L->elem[3] = 5;
	
	L->count = 4;
	
	printf("\n\nSearch Data\n\n");
	display(L);
	printf("\n\n");
	int position = locate(L, 5);
	printf("Data is at Index: %d", position);
	
	//retrieve
	L->elem[0] = 1;
	L->elem[1] = 3;
	L->elem[2] = 2;
	L->elem[3] = 5;
	
	L->count = 4;
	
	printf("\n\nFind Position\n\n");
	display(L);
	printf("\n\n");
	int ndx = 1;
	int data = retrieve(L, ndx);
	printf("Index: %d is Element: %d", ndx, data);
	
	//Insert Sorted
	
	L->elem[0] = 1;
	L->elem[1] = 3;
	L->elem[2] = 5;
	L->elem[3] = 10;
	
	L->count = 4;
	
	printf("\n\nInsert Sorted\n\n");
	display(L);
	printf("\n\n");
	insertSorted(L, 4);
	display(L);
	
	return 0;
}
