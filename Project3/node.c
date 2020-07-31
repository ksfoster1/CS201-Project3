//node.c
#include "node.h"
#include "CDLL.h"

Node *newNode(void *v)
{
	Node *p = malloc(sizeof(Node));                         
	p->next = NULL;
	p->parent = NULL;
	p->previous = NULL;
	p->value = v;
	p->children = NULL;
	return p;
}

//void displayVoid(void *v)
//{
	//int *x = (int)v;
	//printf("%d", x);
//}


