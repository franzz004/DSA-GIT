#include <stdio.h>
#include <stdbool.h>

#define MAX 4

typedef struct{
    int elem;
    int next;
}Cell, HeadSpace[MAX];

typedef struct{
    HeadSpace H;
    int avail;
}VHeap;

typedef int List;

void initialize(VHeap *V){
    int i;
    
    for(i = 0; i < MAX - 1; i++){
        V->H[i].next = i + 1;
    }
    
    V->H[MAX - 1].next = -1;
    V->avail = 0;
}

int allocSpace(VHeap *V){
    int index = V->avail;
    
    if(index != -1){
        V->avail = V->H[index].next;
    }
    
    return index;
}

void deallocSpace(VHeap *V, int index){
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int *L, VHeap *V, int elem){
    int newCell = allocSpace(V);
    
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = *L;
        *L = newCell;
    }
}

void insertLast(int *L, VHeap *V, int elem){
    int newCell = allocSpace(V);
    
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = -1;
        
        if(*L == -1) *L = newCell;
		else {
            int curr;
            
			for(curr = *L; V->H[curr].next != -1; curr = V->H[curr].next){}
			
            V->H[curr].next = newCell;
        }
    }
}

void deleteElem(int *L, VHeap *V, int elem){
    int curr;
    
    for(curr = *L;
		curr != -1 && V->H[curr].elem != elem;
        curr = V->H[curr].next){
	}
    
    if(curr != -1){
        *L = V->H[curr].next;
        deallocSpace(V, curr);
    }
}

void display(int L, VHeap V){
    while(L != -1){
        printf("%d", V.H[L].elem);
        if(V.H[L].next != -1) printf(" -> ");
        L = V.H[L].next;
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    VHeap V;
    List L = -1;
    initialize(&V);

    insertFirst(&L, &V, 5);
    insertFirst(&L, &V, 10);
    insertLast(&L, &V, 15);

    display(L, V);
	
	deleteElem(&L, &V, 10);
    
    insertFirst(&L, &V, 25);
    insertFirst(&L, &V, 30);

    display(L, V);

    return 0;
}