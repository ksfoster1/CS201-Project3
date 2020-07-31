#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
#include "node.h"

Queue *createQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	q->count = 0;
	return q;
}

void enqueue(Queue *q, void *v)
{
	Node *n = newNode(v);

	if (q->front == NULL)
			q->front = q->rear = n;
	else
		{
			q->rear->next = n;
			q->rear = n;
		}

	q->count+=1;
}

Node *dequeue(Queue *q)
{
	Node *tempValue;

	if (q->front == NULL)
	{
		printf("\n Error: Trying to display elements from empty queue");
		return NULL;
	}

	else
	{
			tempValue = q->front;
			q->front = q->front->next;
			q->count--;
			return tempValue;
	}

	q->count--;
}

