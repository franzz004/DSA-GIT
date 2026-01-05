#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct{
	int elem[MAX];
	int count;
}List;

List initialize(List L){
	L.count = 4;
	
	return L;
}

List insertPos(List L, int data, int position){
	int ndx, count;
	
	for(ndx = L.count, count = 1; ndx != position; ndx--, count++){}
	
	//memcpy dest, src, size of an array you want to copy
	memcpy(&L.elem[ndx], &L.elem[ndx-1], sizeof(L.elem[0]) * count);
	
	L.elem[ndx] = data;
	L.count++;
	
	return L;
}

List deletePos(List L, int position){
	int ndx, count;
	
	for(ndx = position, count = 1; ndx < L.count; ndx++, count++){}
	
	memcpy(&L.elem[position], &L.elem[position+1], sizeof(L.elem[0]) * count);
	
	L.count--;
	
	return L;
}

int locate(List L, int data){
	int ndx;
	
	for(ndx = 0; ndx < L.count && L.elem[ndx] != data; ndx++){}
	
	if(ndx >= L.count){
		return -1;
	}
	
	return ndx;
}

List insertSorted(List L, int data){
	int ndx, count;
	
	for(ndx = L.count, count = 1; L.elem[ndx] < data; ndx--, count++){}
	
	memcpy(&(L.elem[ndx]), &(L.elem[ndx-1]), sizeof(L.elem[0]) * count);
	
	L.elem[ndx] = data;
	L.count++;
	
	return L;
}

void display(List L){
	int ndx = 0;
	
	while(ndx < L.count){
		printf("Index: %d Element: %d", ndx, L.elem[ndx]);
		if(ndx < L.count-1){
			printf("\n");
		}
		ndx++;
	}
}

int main(int argv, char *argc[]){
	List L;
	
	initialize(L);
	
	L.elem[0] = 1;
	L.elem[1] = 3;
	L.elem[2] = 2;
	L.elem[3] = 5;
	
	L.count = 4;


	display(L);
	
	//insertPos
	printf("\n\nInsert Position\n\n");
	List insert = insertPos(L, 4, 2);
	display(insert);


	//deletePos
	printf("\n\nDelete Position\n\n");
	List deletes = deletePos(L, 1);
	display(deletes);


	//locate
	printf("\n\nSearch Data\n\n");
	int search = locate(L, 5);
	printf("Data is at Index: %d", search);
	
	L.elem[0] = 1;
	L.elem[1] = 3;
	L.elem[2] = 5;
	L.elem[3] = 10;
	
	L.count = 4;
	
	//Insert Sorted
	printf("\n\nInsert Sorted\n\n");
	List sorted = insertSorted(L, 5);
	display(sorted);
	
	return 0;
}