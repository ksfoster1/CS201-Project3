#pragma once
//CDLL.h
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "node.h"


typedef struct cdll
{
	struct node *head;
	struct node *tail;
	int count;
} CDLL;

extern CDLL *newCDLL();
extern void insertCDLL(CDLL *, Node *);
extern void deleteCDLL(CDLL *, Node *);
extern void displayCDLL(CDLL *);
extern CDLL *merge(CDLL *, CDLL *);

