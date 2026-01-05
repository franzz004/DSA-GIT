#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

// Function prototypes
Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
bool push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

// Initialize stack with top = MAX (indicating empty)
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    s->top = MAX;  // Initialize top to MAX (empty stack)
    return s;
}

// Check if stack is full
bool isFull(Stack* s) {
    return s->top == 0;  // Stack is full when top reaches index 0
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return s->top == MAX;  // Stack is empty when top is at MAX
}

// Push operation
bool push(Stack* s, int value) {
    // Check if stack is full
    if (isFull(s)) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return false;
    }
    
    // Decrement top first (since we start from MAX-1)
    s->top--;
    
    // Place the value at the new top position
    s->items[s->top] = value;
    
    return true;
}

// Pop operation
int pop(Stack* s) {
    // Check if stack is empty
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1;  // Return -1 to indicate error
    }
    
    // Get the value at current top
    int value = s->items[s->top];
    
    // Increment top (move toward MAX)
    s->top++;
    
    return value;
}

// Peek operation - view top element without removing
int peek(Stack* s) {
    // Check if stack is empty
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    return s->items[s->top];
}

// Display stack contents
void display(Stack* s) {
    // Check if stack is empty
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack contents (top to bottom): ");
    
    // Iterate from top down to MAX-1 (top is at the "beginning" of valid data)
    for (int i = s->top; i < MAX; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
    printf("Current top index: %d\n", s->top);
}

// Main function to demonstrate the stack operations
int main() {
    Stack* myStack = initialize();
    
    printf("=== Stack Implementation (Variation 2) ===\n\n");
    
    // Test initial state
    printf("Initial state:\n");
    display(myStack);
    printf("Is empty: %s\n", isEmpty(myStack) ? "true" : "false");
    printf("Is full: %s\n\n", isFull(myStack) ? "true" : "false");
    
    // Push elements
    printf("Pushing elements 10, 20, 30, 40, 50:\n");
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);
    display(myStack);
    
    // Peek at top element
    printf("Peek at top: %d\n\n", peek(myStack));
    
    // Push more elements
    printf("Pushing more elements 60, 70, 80, 90, 100:\n");
    push(myStack, 60);
    push(myStack, 70);
    push(myStack, 80);
    push(myStack, 90);
    push(myStack, 100);
    display(myStack);
    printf("Is full: %s\n\n", isFull(myStack) ? "true" : "false");
    
    // Try to push when full
    printf("Trying to push 110 (stack should be full):\n");
    push(myStack, 110);
    printf("\n");
    
    // Pop elements
    printf("Popping elements:\n");
    printf("Popped: %d\n", pop(myStack));
    printf("Popped: %d\n", pop(myStack));
    printf("Popped: %d\n", pop(myStack));
    display(myStack);
    
    // Push after popping
    printf("Pushing 95 after popping:\n");
    push(myStack, 95);
    display(myStack);
    
    // Pop remaining elements
    printf("Popping all remaining elements:\n");
    while (!isEmpty(myStack)) {
        printf("Popped: %d\n", pop(myStack));
    }
    printf("\n");
    
    // Try to pop from empty stack
    printf("Trying to pop from empty stack:\n");
    pop(myStack);
    
    free(myStack);
    return 0;
}