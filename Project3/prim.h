#pragma once
//prim.h
#include "node.h"
#include "binheap.h"

typedef struct vertex
{
	int value; //name of vertex
	int key;
	int predecessor; //value of predecessor
	struct node *owner;
	char *color;
	int distance; //distance from source
} Vertex;

extern Vertex *newVertex(int);
extern void addVerticesToRootlist(Binheap *, void *, int);
extern void updateVertexKey(Vertex *, int, Binheap *);
extern int lessthan(void *, void *);
extern int lessthanArray(void *, void *);
extern int findLargest(char *);
extern int main();
extern Vertex *prim(Binheap *);
extern void BFT(Vertex *);
