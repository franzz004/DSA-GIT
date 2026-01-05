// Code Not Mine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Node structure for linked list
typedef struct Node {
    int key;
    char value[50];
    struct Node* next;
} Node;

// Hash Table structure
typedef struct {
    Node* buckets[TABLE_SIZE];
    int size;
} OpenHashTable;

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Create a new node
Node* createNode(int key, const char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;
    return newNode;
}

// Initialize hash table
void initOpenHashTable(OpenHashTable* ht) {
    ht->size = TABLE_SIZE;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

// Insert key-value pair
void insertOpenHash(OpenHashTable* ht, int key, const char* value) {
    int index = hashFunction(key);
    Node* newNode = createNode(key, value);
    
    // Insert at the beginning of the chain
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    
    printf("Inserted key %d at bucket %d\n", key, index);
}

// Search for a key
char* searchOpenHash(OpenHashTable* ht, int key) {
    int index = hashFunction(key);
    Node* current = ht->buckets[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// Delete a key
int deleteOpenHash(OpenHashTable* ht, int key) {
    int index = hashFunction(key);
    Node* current = ht->buckets[index];
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                // First node in chain
                ht->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Deleted key %d\n", key);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0; // Key not found
}

// Display hash table
void displayOpenHashTable(OpenHashTable* ht) {
    printf("\nOpen Hashing Table (Separate Chaining):\n");
    printf("========================================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* current = ht->buckets[i];
        while (current != NULL) {
            printf("[%d: %s] -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

// Clean up memory
void freeOpenHashTable(OpenHashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Demo function
void demoOpenHashing() {
    OpenHashTable ht;
    initOpenHashTable(&ht);
    
    printf("=== Open Hashing (Separate Chaining) Demo ===\n");
    
    // Insert some values
    insertOpenHash(&ht, 10, "Alice");
    insertOpenHash(&ht, 20, "Bob");
    insertOpenHash(&ht, 30, "Charlie");
    insertOpenHash(&ht, 40, "David");
    insertOpenHash(&ht, 11, "Eve");  // Collision with key 1
    
    displayOpenHashTable(&ht);
    
    // Search operations
    int searchKey = 20;
    char* result = searchOpenHash(&ht, searchKey);
    if (result != NULL) {
        printf("Found key %d: %s\n", searchKey, result);
    } else {
        printf("Key %d not found\n", searchKey);
    }
    
    // Delete operation
    deleteOpenHash(&ht, 20);
    displayOpenHashTable(&ht);
    
    // Free memory
    freeOpenHashTable(&ht);
}