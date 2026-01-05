#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

// Assuming studtype structure (you may need to adjust this based on your actual studtype definition)
typedef struct {
    int ID;
    char name[50];
    float grade;
} studtype;

typedef struct {
    studtype *elemPtr;
    int count;
    int max;
} List;

// Function prototypes
void initialize(List *L);
void insertPos(List *L, studtype elem, int pos);
void deletePos(List *L, int pos);
void locate(List *L, int ID);
studtype retrieve(List *L, int pos);
void insertSorted(List *L, studtype elem);
void makeNULL(List *L);
void resize(List *L);

// Initialize the list
void initialize(List *L) {
    L->max = LENGTH;
    L->count = 0;
    L->elemPtr = (studtype *)malloc(L->max * sizeof(studtype));
    if (L->elemPtr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// Insert element at specific position
void insertPos(List *L, studtype elem, int pos) {
    if (pos < 0 || pos > L->count) {
        printf("Invalid position!\n");
        return;
    }
    
    // Check if resize is needed
    if (L->count == L->max) {
        resize(L);
    }
    
    // Shift elements to make space
    for (int i = L->count; i > pos; i--) {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }
    
    // Insert element
    L->elemPtr[pos] = elem;
    L->count++;
    printf("Element inserted at position %d\n", pos);
}

// Delete element at specific position
void deletePos(List *L, int pos) {
    if (pos < 0 || pos >= L->count) {
        printf("Invalid position!\n");
        return;
    }
    
    // Shift elements to fill the gap
    for (int i = pos; i < L->count - 1; i++) {
        L->elemPtr[i] = L->elemPtr[i + 1];
    }
    
    L->count--;
    printf("Element deleted from position %d\n", pos);
}

// Locate element by ID
void locate(List *L, int ID) {
    for (int i = 0; i < L->count; i++) {
        if (L->elemPtr[i].ID == ID) {
            printf("Student with ID %d found at position %d\n", ID, i);
            printf("Name: %s, Grade: %.2f\n", L->elemPtr[i].name, L->elemPtr[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found\n", ID);
}

// Retrieve element from specific position
studtype retrieve(List *L, int pos) {
    studtype emptyStudent = {0, "", 0.0};
    
    if (pos < 0 || pos >= L->count) {
        printf("Invalid position! Returning empty student.\n");
        return emptyStudent;
    }
    
    return L->elemPtr[pos];
}

// Insert element in sorted order (assuming sorting by ID)
void insertSorted(List *L, studtype elem) {
    // Check if resize is needed
    if (L->count == L->max) {
        resize(L);
    }
    
    // Find the correct position
    int pos = 0;
    while (pos < L->count && L->elemPtr[pos].ID < elem.ID) {
        pos++;
    }
    
    // Insert at the found position
    insertPos(L, elem, pos);
}

// Make the list empty
void makeNULL(List *L) {
    L->count = 0;
    printf("List cleared. Count set to 0.\n");
}

// Resize the list to accommodate more elements
void resize(List *L) {
    int newSize = L->max * 2; // Double the size
    studtype *newPtr = (studtype *)realloc(L->elemPtr, newSize * sizeof(studtype));
    
    if (newPtr == NULL) {
        printf("Memory reallocation failed!\n");
        return;
    }
    
    L->elemPtr = newPtr;
    L->max = newSize;
    printf("List resized to %d elements\n", newSize);
}

// Utility function to display all elements
void displayList(List *L) {
    printf("\n=== List Contents (Count: %d, Max: %d) ===\n", L->count, L->max);
    for (int i = 0; i < L->count; i++) {
        printf("Position %d: ID=%d, Name=%s, Grade=%.2f\n", i, L->elemPtr[i].ID, L->elemPtr[i].name, L->elemPtr[i].grade);
    }
    printf("===================================\n\n");
}

// Main function to demonstrate usage
int main() {
    List myList;
    
    // Initialize the list
    initialize(&myList);
    
    // Create some sample students
    studtype s1 = {101, "John Doe", 85.5};
    studtype s2 = {103, "Jane Smith", 92.0};
    studtype s3 = {102, "Bob Johnson", 78.5};
    studtype s4 = {105, "Alice Brown", 88.0};
    studtype s5 = {104, "Charlie Wilson", 95.5};
    
    // Test insertSorted
    printf("Inserting students in sorted order...\n");
    insertSorted(&myList, s1);
    insertSorted(&myList, s2);
    insertSorted(&myList, s3);
    insertSorted(&myList, s4);
    insertSorted(&myList, s5);
    
    displayList(&myList);
    
    // Test insertPos
    studtype s6 = {100, "David Lee", 82.0};
    printf("Inserting at position 0...\n");
    insertPos(&myList, s6, 0);
    displayList(&myList);
    
    // Test deletePos
    printf("Deleting at position 2...\n");
    deletePos(&myList, 2);
    displayList(&myList);
    
    // Test locate
    printf("Locating student with ID 103...\n");
    locate(&myList, 103);
    
    printf("Locating student with ID 999...\n");
    locate(&myList, 999);
    
    // Test retrieve
    printf("Retrieving student at position 3...\n");
    studtype retrieved = retrieve(&myList, 3);
    printf("Retrieved: ID=%d, Name=%s, Grade=%.2f\n", retrieved.ID, retrieved.name, retrieved.grade);
    
    // Test resize by adding more elements
    printf("\nTesting resize functionality...\n");
    for (int i = 200; i < 220; i++) {
        studtype newStudent = {i, "Test Student", 75.0};
        insertSorted(&myList, newStudent);
    }
    displayList(&myList);
    
    // Test makeNULL
    printf("Clearing the list...\n");
    makeNULL(&myList);
    displayList(&myList);
    
    // Clean up
    free(myList.elemPtr);
    
    return 0;
}