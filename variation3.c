#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List initialize();
List insertAt(List L, int data, int position);
List deleteAt(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);
List insertFirst(List L, int data);
List insertLast(List L, int data);
List deleteFirst(List L);
List deleteLast(List L);
List deleteByValue(List L, int data);

List initialize() {
    List L;
    L.elemPtr = (int *)malloc(LENGTH * sizeof(int));
    if (L.elemPtr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    L.count = 0;
    L.max = LENGTH;
    return L;
}

List insertAt(List L, int data, int position) {
    if (position < 0 || position > L.count) {
        printf("Invalid position!\n");
        return L;
    }
    
    if (L.count == L.max) {
        L = resize(L);
    }
    
    for (int i = L.count; i > position; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }
    
    L.elemPtr[position] = data;
    L.count++;
    
    return L;
}

List deleteAt(List L, int position) {
    if (position < 0 || position >= L.count) {
        printf("Invalid position!\n");
        return L;
    }
    
    for (int i = position; i < L.count - 1; i++) {
        L.elemPtr[i] = L.elemPtr[i + 1];
    }
    
    L.count--;
    
    return L;
}

int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    if (L.count == L.max) {
        L = resize(L);
    }
    
    int i;
    for (i = L.count - 1; i >= 0 && L.elemPtr[i] > data; i--) {
        L.elemPtr[i + 1] = L.elemPtr[i];
    }
    
    L.elemPtr[i + 1] = data;
    L.count++;
    
    return L;
}

void display(List L) {
    if (L.count == 0) {
        printf("List is empty!\n");
        return;
    }
    
    printf("List elements: ");
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("\n");
}

List resize(List L) {
    int newMax = L.max * 2;
    int *newArray = (int *)malloc(newMax * sizeof(int));
    
    if (newArray == NULL) {
        printf("Memory allocation failed during resize!\n");
        return L;
    }
    
    for (int i = 0; i < L.count; i++) {
        newArray[i] = L.elemPtr[i];
    }
    
    free(L.elemPtr);
    L.elemPtr = newArray;
    L.max = newMax;
    
    printf("List resized to %d elements\n", newMax);
    return L;
}

List insertFirst(List L, int data) {
    return insertAt(L, data, 0);
}

List insertLast(List L, int data) {
    return insertAt(L, data, L.count);
}

List deleteFirst(List L) {
    return deleteAt(L, 0);
}

List deleteLast(List L) {
    return deleteAt(L, L.count - 1);
}

List deleteByValue(List L, int data) {
    int position = locate(L, data);
    if (position != -1) {
        return deleteAt(L, position);
    }
    printf("Value not found!\n");
    return L;
}

int main() {
    List myList = initialize();
    
    myList = insertLast(myList, 10);
    myList = insertLast(myList, 20);
    myList = insertLast(myList, 30);
    myList = insertFirst(myList, 5);
    
    display(myList);
    
    myList = insertAt(myList, 15, 2);
    display(myList);
    
    myList = deleteAt(myList, 1);
    display(myList);
    
    int pos = locate(myList, 20);
    printf("Position of 20: %d\n", pos);
    
    List sortedList = initialize();
    sortedList = insertSorted(sortedList, 25);
    sortedList = insertSorted(sortedList, 15);
    sortedList = insertSorted(sortedList, 35);
    sortedList = insertSorted(sortedList, 5);
    
    printf("Sorted list: ");
    display(sortedList);
    
    free(myList.elemPtr);
    free(sortedList.elemPtr);
    
    return 0;
}