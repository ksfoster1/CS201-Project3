#pragma once
//binheap.h
#include "CDLL.h"
#include "node.h"

typedef struct binheap
{
	int count;
	int(*comparator)(void *, void *);
	CDLL *root;
	Node *extreme; 
} Binheap;

extern Binheap *newBinheap(int(*)(void *, void *));
extern Node *insertHeap(Binheap *, void *);
extern void decreaseKey(Binheap *, Node *, void *);
extern Node *bubbleUp(Binheap *, Node *);
extern void *extractMin(Binheap *);
extern void consolidate(Binheap *);
extern void updateConsolidationArray(Binheap *, Node **, Node *);
extern Node *combine(Binheap *, Node *, Node *);
extern void displayHeap(Binheap *);