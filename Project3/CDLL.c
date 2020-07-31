//CDLL.c
//#include "node.h"
#include "CDLL.h"
#include "node.h"
#include "prim.h"

CDLL *newCDLL()
{
	CDLL *c = malloc(sizeof(CDLL));
	c->count = 0;
	c->head = c->tail = NULL;
	return c;
}

void insertCDLL(CDLL *c, Node *n)
{
	n->next = n->previous= NULL;

	if ((c->tail == NULL && c->head == NULL) || (c->tail->value == NULL && c->head->value == NULL)) 
		c->tail = c->head = n;
	else
	{
		c->head->previous = n;
		n->next = c->head;
		c->head = n;
	}
	c->count++;
}

void deleteCDLL(CDLL *c, Node *n)
{
	//printf("O");
	if (c->head == NULL) 
	{
		printf("ERROR EMPTY CDLL\n");
		return;
	}

	if (c->head == c->tail)
	{
		c->head = c->tail = NULL;
	}
	else
	{
		if (n == c->head) 
			c->head = n->next; 
		else if (n == c->tail)
		{
			c->tail = n->previous;
			n->previous->next = NULL;
		}
		else
		{
			Node *previousNode = n->previous;
			previousNode->next = n->next;
			n->next->previous = previousNode;
		}
		n->previous = n->next = NULL;
	}

	c->count--;
}

void displayCDLL(CDLL *c)
{
	Node *ptr = c->head;
	if (c->count == 0)
	{
		printf("List Empty");
		return;
	}
	while (ptr)
	{
		printf("%d ", ((Vertex *)ptr->value)->value);
		ptr = ptr->next;
		if (ptr == c->tail->next)
			break;
	}
	printf("\n");
}

CDLL *merge(CDLL *c1, CDLL *c2)
{
	if (c1->count == 0)
	{
		c1->head = c2->head;
		c1->tail = c2->tail;
		c1->count = c2->count;
	}

	else
	{
		c1->tail->next = c2->head;
		c2->head->previous = c1->tail;
		c2->tail->next = c1->head; 
		c1->head->previous = c2->tail; 
		c1->tail = c2->tail;
		c1->count = c1->count + c2->count;
		c2->head = 0;
		c2->tail = 0;
		c2->count = 0;
	}

	return c1;
}