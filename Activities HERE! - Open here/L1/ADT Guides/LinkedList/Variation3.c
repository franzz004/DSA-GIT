#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
	int *elemPtr;
	int count;
	int max;
}List;

List initialize(List L){
	
	L.elemPtr = (int *)malloc(LENGTH * sizeof(int));
    if(!L.elemPtr){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    L.count = 0;
    L.max = LENGTH;
	
	return L;
}

List resize(List L){
    int newMax = L.max * 2;
    int *newPtr = (int *)realloc(L.elemPtr, newMax * sizeof(int));
    if(!newPtr){
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    L.elemPtr = newPtr;
    L.max = newMax;
    return L;
}

List insertPos(List L, int data, int position){
    if(L.count == L.max){
        L = resize(L);
    }

    if(position < 0 || position > L.count){
        printf("Invalid position!\n");
        return L;
    }

    for(int i = L.count; i > position; i--){
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position){
    
    if(position < 0 || position >= L.count){
        printf("Invalid position!\n");
        return L;
    }

    for(int i = position; i < L.count - 1; i++){
        L.elemPtr[i] = L.elemPtr[i + 1];
    }

    L.count--;

    if(L.count < L.max / 2){
        L = resize(L);
    }

    return L;
}

int locate(List L, int data){
    for(int i = 0; i < L.count; i++){
        if(L.elemPtr[i] == data){
            return i;
        }
    }
    return -1;
}

void display(List L){
    for(int i = 0; i < L.count; i++){
        printf("%d ", L.elemPtr[i]);
    }
    printf("\n");
}

int main(int argv, char *argc[]){
	List L;
	initialize(L);
	
    insertPos(L, 1, 0);
    insertPos(L, 2, 1);
    insertPos(L, 3, 2);
    insertPos(L, 4, 3);
    insertPos(L, 5, 4);
    insertPos(L, 6, 5);
    insertPos(L, 7, 6);
    insertPos(L, 8, 7);
    insertPos(L, 9, 8);
    insertPos(L, 10, 9);
    insertPos(L, 11, 10);
    
//    display(L);
//    
//    deletePos(L, 5);
//    
//    display(L);
//    
//    printf("%d\n", locate(L, 3));
	
	return 0;
}