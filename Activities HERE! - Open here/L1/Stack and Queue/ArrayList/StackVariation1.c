#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
	int items[MAX];
	int top;
}Stack;

Stack* initialize(){
	
	Stack *s = malloc(sizeof(Stack));
	s->top = -1;
	return s;
}

bool isFull(Stack *s){
	if(s->top == MAX-1) return true;
	else return false;
}

bool isEmpty(Stack *s){
	if(s->top == -1) return true;
	else return false;
}

void push(Stack* s, int value){
	if(!isFull(s)){
		s->top++;
		s->items[s->top] = value;
	}
	else{
		printf("Stack Overflow\n");
	}
}

int pop(Stack* s){
	if(!isEmpty(s)){
		s->top--;
	}
	else{
		printf("Stack Underflow\n");
	}

	return s->items[s->top+1];
}

int peek(Stack* s){
	if(!isEmpty(s)){
		return s->items[s->top];
	}
	else{
		printf("Stack is empty\n");
		return -1;
	}
}

void display(Stack* s){
	if(!isEmpty(s)){
		printf("S = ");
		for(int i=s->top; i>=0; i--){
			printf("%d", s->items[i]);
			if(i > 0) printf(", ");
		}
		printf("\n");
	}
	else{
		printf("Stack is empty\n");
	}
}

int main(int argv, char *arch[]){
	Stack* stack = initialize();

	push(stack, 10);
	push(stack, 20);
	push(stack, 30);
	
	display(stack);
	
	printf("Top element is %d\n", peek(stack));
	printf("Popped element is %d\n", pop(stack));
	
	display(stack);
	
	
	
	return 0;
}