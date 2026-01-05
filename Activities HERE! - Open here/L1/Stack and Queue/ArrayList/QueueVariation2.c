#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// Function prototypes
Queue* initialize();
bool isEmpty(Queue* q);
bool isFull(Queue* q);
bool enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);
int getSacrificialSpace(Queue* q);

// Initialize queue with front = 1 and rear = 0
Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    q->front = 1;  // Front starts at position 1
    q->rear = 0;   // Rear starts at position 0
    return q;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    // Queue is empty when front is one position ahead of rear (circularly)
    return q->front == (q->rear + 1) % MAX;
}

// Check if queue is full
bool isFull(Queue* q) {
    // Queue is full when front is two positions ahead of rear (circularly)
    return q->front == (q->rear + 2) % MAX;
}

// Get the sacrificial space index
int getSacrificialSpace(Queue* q) {
    // Sacrificial space is always the space before front
    return (q->front - 1 + MAX) % MAX;
}

// Enqueue operation
bool enqueue(Queue* q, int value) {
    // Check if queue is full
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return false;
    }
    
    // Increment rear circularly
    q->rear = (q->rear + 1) % MAX;
    
    // Insert the new element at the new rear position
    q->items[q->rear] = value;
    
    printf("Enqueued %d. Front=%d, Rear=%d\n", value, q->front, q->rear);
    return true;
}

// Dequeue operation
int dequeue(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue from empty queue\n");
        return -1;  // Return -1 to indicate error
    }
    
    // Get the element at the front of the queue
    int value = q->items[q->front];
    
    // Increment front circularly
    q->front = (q->front + 1) % MAX;
    
    printf("Dequeued %d. Front=%d, Rear=%d\n", value, q->front, q->rear);
    return value;
}

// Get front element without removing it
int front(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty! No front element.\n");
        return -1;
    }
    
    return q->items[q->front];
}

// Display queue contents
void display(Queue* q) {
    // Check if queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue contents: ");
    
    // Start from front and go to rear (circularly)
    int i = q->front;
    while (true) {
        printf("%d ", q->items[i]);
        
        // If we've reached the rear, break
        if (i == q->rear) {
            break;
        }
        
        // Move to next position circularly
        i = (i + 1) % MAX;
    }
    
    printf("\n");
    printf("Front index: %d, Rear index: %d\n", q->front, q->rear);
    printf("Sacrificial space index: %d\n", getSacrificialSpace(q));
}

// Main function to demonstrate the queue operations
int main() {
    Queue* myQueue = initialize();
    
    printf("=== Queue Implementation (Variation 2 - With Sacrificial Space) ===\n\n");
    
    // Test initial state
    printf("Initial state:\n");
    display(myQueue);
    printf("Is empty: %s\n", isEmpty(myQueue) ? "true" : "false");
    printf("Is full: %s\n\n", isFull(myQueue) ? "true" : "false");
    
    // Enqueue elements
    printf("Enqueuing elements 10 to 80:\n");
    for (int i = 10; i <= 80; i += 10) {
        enqueue(myQueue, i);
    }
    display(myQueue);
    printf("Is empty: %s, Is full: %s\n\n", 
           isEmpty(myQueue) ? "true" : "false", 
           isFull(myQueue) ? "true" : "false");
    
    // Try to enqueue when full
    printf("Trying to enqueue 90 (queue should be full):\n");
    enqueue(myQueue, 90);
    printf("\n");
    
    // Dequeue some elements
    printf("Dequeuing 3 elements:\n");
    for (int i = 0; i < 3; i++) {
        dequeue(myQueue);
    }
    display(myQueue);
    printf("\n");
    
    // Enqueue more elements
    printf("Enqueuing 90 and 100:\n");
    enqueue(myQueue, 90);
    enqueue(myQueue, 100);
    display(myQueue);
    printf("Is full: %s\n\n", isFull(myQueue) ? "true" : "false");
    
    // Get front element
    printf("Front element: %d\n\n", front(myQueue));
    
    // Enqueue more elements (wrap around)
    printf("Enqueuing 110 (will wrap around):\n");
    enqueue(myQueue, 110);
    display(myQueue);
    printf("\n");
    
    // Dequeue all elements
    printf("Dequeuing all elements:\n");
    while (!isEmpty(myQueue)) {
        dequeue(myQueue);
    }
    display(myQueue);
    printf("\n");
    
    // Try to dequeue from empty queue
    printf("Trying to dequeue from empty queue:\n");
    dequeue(myQueue);
    
    free(myQueue);
    return 0;
}