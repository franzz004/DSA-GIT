#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
	int items[MAX];
	int count;
}List;

typedef struct{
	List list;
	int front;
	int rear;
}Queue;

Queue* initialize(){
	Queue *q = malloc(sizeof(Queue));
	q->list.count = 0;
	q->front = q->rear = -1;
	
	return q;
}

bool isFull(Queue *q){
	if(q->list.count == MAX) return true;
	else return false;
}

bool isEmpty(Queue *q){
	if(q->list.count == 0) return true;
	else return false;
}

void enqueue(Queue* q, int value){
	if(isFull(q)) return;
	
	else if(isEmpty(q)){
		q->front = q->rear = 0;
	}
	else{
		q->rear = (q->rear + 1) % MAX;
	}
	q->list.items[q->rear] = value;
	q->list.count++;
}

int dequeue(Queue* q){
	if(isEmpty(q)) printf("Queue is empty\n");
	
	int value = q->list.items[q->front];
	
	if(q->list.count == 1){
		q->front = q->rear = -1;
	}
	else{
		q->front = (q->front + 1) % MAX;
	}
	q->list.count--;
	
	return value;
}

int front(Queue* q){
	
}

void display(Queue* q){
	if(isEmpty(q)) return;

	int i, ndx;
	for(i = q->front; i != q->rear; i = (i + 1) % MAX){
		printf("%d ", q->list.items[i]);
	}
	printf("%d\n", q->list.items[q->rear]);
}

int main(int argv, char *arch[]){
	Queue *queue = initialize();
	
	enqueue(queue, 1);
	enqueue(queue, 3);
	enqueue(queue, 2);
	enqueue(queue, 5);
	
	display(queue);
	
	enqueue(queue, 4);
	
	display(queue);
	
	return 0;
}