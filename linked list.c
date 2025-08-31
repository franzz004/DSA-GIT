#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List* initialize() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->count = 0;
    return list;
}

void empty(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

void insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count) return;
    
    if (index == 0) {
        insertFirst(list, data);
        return;
    }
    if (index == list->count) {
        insertLast(list, data);
        return;
    }
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    list->count++;
}

void deleteStart(List *list) {
    if (list->head == NULL) return;
    
    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list) {
    if (list->head == NULL) return;
    
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        list->count--;
        return;
    }
    
    Node *current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    list->count--;
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count) return;
    
    if (index == 0) {
        deleteStart(list);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
}

int retrieve(List *list, int index) {
    if (index < 0 || index >= list->count) return -1;
    
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int locate(List *list, int data) {
    Node *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void display(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}