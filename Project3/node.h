//node.h
#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//struct CDLL;

typedef struct node
{
	struct node *next;
	struct node *previous;
	struct node *parent;
	void *value;
	struct cdll *children;
} Node;

extern Node *newNode(void *);
//extern void displayVoid(void *);
