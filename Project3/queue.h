#pragma once
#include "node.h"

typedef struct queue
{
	struct node *front;
	struct node *rear;
	int count;
} Queue;

extern Queue *createQueue(); //creates empty queue
extern void enqueue(Queue *, void *);
extern Node *dequeue(Queue *);
