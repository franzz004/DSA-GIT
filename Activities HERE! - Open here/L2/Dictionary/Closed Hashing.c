// Code Not Mine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define DELETED_KEY -1

// Entry structure
typedef struct {
    int key;
    char value[50];
    int isOccupied;
    int isDeleted;  // For lazy deletion
} Entry;

// Hash Table structure
typedef struct {
    Entry* entries;
    int size;
    int count;  // Number of occupied slots
} ClosedHashTable;

// Hash function 1
int hashFunction1(int key) {
    return key % TABLE_SIZE;
}

// Hash function 2 (for double hashing)
int hashFunction2(int key) {
    return 7 - (key % 7);  // Must be relatively prime to TABLE_SIZE
}

// Initialize hash table
void initClosedHashTable(ClosedHashTable* ht) {
    ht->size = TABLE_SIZE;
    ht->count = 0;
    ht->entries = (Entry*)malloc(TABLE_SIZE * sizeof(Entry));
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->entries[i].key = 0;
        ht->entries[i].isOccupied = 0;
        ht->entries[i].isDeleted = 0;
        strcpy(ht->entries[i].value, "");
    }
}

// Linear Probing
int linearProbing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i) % TABLE_SIZE;
}

// Quadratic Probing
int quadraticProbing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i * i) % TABLE_SIZE;
}

// Double Hashing
int doubleHashing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i * hashFunction2(key)) % TABLE_SIZE;
}

// Insert using specified probing method
void insertClosedHash(ClosedHashTable* ht, int key, const char* value, int (*probingFunc)(ClosedHashTable*, int, int)) {
    if (ht->count >= ht->size) {
        printf("Hash table is full!\n");
        return;
    }
    
    int i = 0;
    int index;
    
    do {
        index = probingFunc(ht, key, i);
        
        // If slot is empty or marked as deleted
        if (!ht->entries[index].isOccupied || ht->entries[index].isDeleted) {
            ht->entries[index].key = key;
            strcpy(ht->entries[index].value, value);
            ht->entries[index].isOccupied = 1;
            ht->entries[index].isDeleted = 0;
            ht->count++;
            printf("Inserted key %d at index %d\n", key, index);
            return;
        }
        
        // If key already exists, update value
        if (ht->entries[index].key == key) {
            strcpy(ht->entries[index].value, value);
            printf("Updated key %d at index %d\n", key, index);
            return;
        }
        
        i++;
    } while (i < TABLE_SIZE);
    
    printf("Failed to insert key %d (table full after probing)\n", key);
}

// Search using specified probing method
Entry* searchClosedHash(ClosedHashTable* ht, int key, int (*probingFunc)(ClosedHashTable*, int, int)) {
    int i = 0;
    int index;
    
    do {
        index = probingFunc(ht, key, i);
        
        // If we find an empty slot that was never occupied
        if (!ht->entries[index].isOccupied && !ht->entries[index].isDeleted) {
            return NULL;
        }
        
        // If we find the key and it's not marked as deleted
        if (ht->entries[index].isOccupied && 
            !ht->entries[index].isDeleted && 
            ht->entries[index].key == key) {
            return &ht->entries[index];
        }
        
        i++;
    } while (i < TABLE_SIZE);
    
    return NULL;
}

// Delete using lazy deletion
int deleteClosedHash(ClosedHashTable* ht, int key, int (*probingFunc)(ClosedHashTable*, int, int)) {
    Entry* entry = searchClosedHash(ht, key, probingFunc);
    
    if (entry != NULL) {
        entry->isDeleted = 1;
        ht->count--;
        printf("Marked key %d as deleted\n", key);
        return 1;
    }
    
    printf("Key %d not found for deletion\n", key);
    return 0;
}

// Display hash table
void displayClosedHashTable(ClosedHashTable* ht) {
    printf("\nClosed Hashing Table (Open Addressing):\n");
    printf("========================================\n");
    printf("Index\tKey\tValue\tOccupied\tDeleted\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (ht->entries[i].isOccupied && !ht->entries[i].isDeleted) {
            printf("%d\t%s\t", ht->entries[i].key, ht->entries[i].value);
        } else if (ht->entries[i].isDeleted) {
            printf("%d\t%s\t", DELETED_KEY, "[DELETED]");
        } else {
            printf("-\t-\t");
        }
        printf("%s\t\t%s\n", 
               ht->entries[i].isOccupied ? "Yes" : "No",
               ht->entries[i].isDeleted ? "Yes" : "No");
    }
    printf("Total entries: %d/%d\n\n", ht->count, ht->size);
}

// Clean up memory
void freeClosedHashTable(ClosedHashTable* ht) {
    free(ht->entries);
    ht->entries = NULL;
}

// Demo function for Linear Probing
void demoLinearProbing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Linear Probing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", linearProbing);
    insertClosedHash(&ht, 20, "Bob", linearProbing);
    insertClosedHash(&ht, 30, "Charlie", linearProbing);
    insertClosedHash(&ht, 40, "David", linearProbing);
    insertClosedHash(&ht, 11, "Eve", linearProbing);  // Potential collision
    
    displayClosedHashTable(&ht);
    
    // Search operation
    Entry* found = searchClosedHash(&ht, 30, linearProbing);
    if (found != NULL) {
        printf("Found key 30: %s\n", found->value);
    }
    
    // Delete operation
    deleteClosedHash(&ht, 20, linearProbing);
    displayClosedHashTable(&ht);
    
    // Insert after deletion
    insertClosedHash(&ht, 21, "Frank", linearProbing);
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}

// Demo function for Quadratic Probing
void demoQuadraticProbing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Quadratic Probing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", quadraticProbing);
    insertClosedHash(&ht, 20, "Bob", quadraticProbing);
    insertClosedHash(&ht, 30, "Charlie", quadraticProbing);
    insertClosedHash(&ht, 40, "David", quadraticProbing);
    insertClosedHash(&ht, 11, "Eve", quadraticProbing);
    
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}

// Demo function for Double Hashing
void demoDoubleHashing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Double Hashing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", doubleHashing);
    insertClosedHash(&ht, 20, "Bob", doubleHashing);
    insertClosedHash(&ht, 30, "Charlie", doubleHashing);
    insertClosedHash(&ht, 40, "David", doubleHashing);
    insertClosedHash(&ht, 11, "Eve", doubleHashing);
    
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}

// Main function to demonstrate both implementations
int main() {
    printf("Hash Table Implementations in C\n");
    printf("===============================\n");
    
    // Demo Open Hashing
    demoOpenHashing();
    
    // Demo Closed Hashing with different probing methods
    demoLinearProbing();
    demoQuadraticProbing();
    demoDoubleHashing();
    
    return 0;
}