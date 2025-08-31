#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef int Etype;

typedef struct {
    Etype elem[MAX];
    int count;
} List;

typedef List* EPtr;

void initialize(EPtr L);
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, int data);
int retrieve(EPtr L, int position);
void insertSorted(EPtr L, int data);
void display(EPtr L);
void makeNULL(EPtr L);
void insertFirst(EPtr L, int data);
void insertLast(EPtr L, int data);
void deleteFirst(EPtr L);
void deleteLast(EPtr L);

int main() {
    List myList;
    EPtr L = &myList;

    initialize(L);
    insertFirst(L, 1);
    insertLast(L, 3);
    insertPos(L, 2, 1);
    display(L);

    deleteFirst(L);
    display(L);

    deleteLast(L);
    display(L);

    insertSorted(L, 5);
    insertSorted(L, 10);
    insertSorted(L, 8);
    display(L);

    makeNULL(L);
    display(L);

    return 0;
}

void initialize(EPtr L) {
    L->count = 0;
}

void insertPos(EPtr L, int data, int position) {
    if (L->count == MAX) return;
    if (position < 0 || position > L->count) return;
    for (int i = L->count; i > position; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[position] = data;
    L->count++;
}

void deletePos(EPtr L, int position) {
    if (position < 0 || position >= L->count) return;
    for (int i = position; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
}

int locate(EPtr L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elem[i] == data) return i;
    }
    return -1;
}

int retrieve(EPtr L, int position) {
    if (position < 0 || position >= L->count) return -1;
    return L->elem[position];
}

void insertSorted(EPtr L, int data) {
    if (L->count == MAX) return;
    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) pos++;
    insertPos(L, data, pos);
}

void display(EPtr L) {
    printf("List: ");
    for (int i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\nCount: %d\n", L->count);
}

void makeNULL(EPtr L) {
    L->count = 0;
}

void insertFirst(EPtr L, int data) {
    insertPos(L, data, 0);
}

void insertLast(EPtr L, int data) {
    insertPos(L, data, L->count);
}

void deleteFirst(EPtr L) {
    deletePos(L, 0);
}

void deleteLast(EPtr L) {
    deletePos(L, L->count - 1);
}
