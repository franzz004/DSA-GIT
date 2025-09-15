/* 
void initialize (VHeap);
int allocSpace(Vheap* V);
void deallocSpace(Vheap* V, int index);
void insertFirst(int* L, Vheap* V, int elem);
void insertLast(int* L, Vheap* V, int elem);
void insertSorted(int* L, VHeap* V, int elem);
void delete(int* L, VHeap* V, int elem);
void deleteAllOccurrence(int* L, VHeap* V, int elem);
void display(int L, VHeap V);
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct{
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;


typedef int List;

void initialize(VHeap *V);
int allocSpace(VHeap* V);


void main(){
    VHeap V;
    initialize(&V);

    int x;
    for(x=0;x<MAX;x++){
        printf("%d \n", V.H[x].next);
    }
}

void initialize (VHeap *V){
    int trav = 0;
    for(trav; trav < MAX-1; trav++){
        V -> H[trav].next=trav+1;
    }
    V->H[MAX-1].next=-1;
    V->avail=0;
}

