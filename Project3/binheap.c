//binheap.c
#include "binheap.h"
#include "prim.h"
#include "CDLL.h"
#include "node.h"
#include <math.h>

Binheap *newBinheap(int(*c)(void *,void *))
{
	Binheap *b = malloc(sizeof(Binheap));
	b->comparator = c;
	b->root = newCDLL();
	b->extreme = NULL;
	b->count = 0;
	return b;
}

Node *insertHeap(Binheap *b, void *v)
{
	//printf("UUUU");
	Node *n = newNode(v);
	n->parent = n;
	n->children = newCDLL();
	insertCDLL(b->root, n);
	b->count++;
	consolidate(b);
	return n;
}

void decreaseKey(Binheap *b, Node *n, void *v)
{
	n->value = v;
	n = bubbleUp(b, n);
	if (b->comparator(n->value, b->extreme->value) < 0) //update extreme pointer 
		b->extreme = n; 
}

Node *bubbleUp(Binheap *b, Node *n)
{
	//printf("CHILD IS %d and PARENT IS %d ", ((Vertex *)n->value)->value, ((Vertex *)n->parent->value)->value);
	if (n == n->parent)
		return n;
	
	if (!(b->comparator(n->value, n->parent->value) < 0))
		return n;
	else
	{
		Vertex *a = n->value;
		a->owner = n->parent;
		a = n->parent->value;
		a->owner = n;

		void *temp = n->value;
		n->value = n->parent->value;
		n->parent->value = temp;
		return bubbleUp(b, n->parent);
	}
}
//Note: the comparator function has to be implemented so that it treats a null value as more extreme than any other value.

void *extractMin(Binheap *b)
{
	Node *y = b->extreme;
	Node *temp = y->children->head;
	//printf("$$$$Extreme Node is: %d", ((Vertex *)y->value)->value);
	deleteCDLL(b->root, y);
	// the children of y are a linked list
	while (temp) //set each of the children's parent to point to themselves
	{
		temp->parent = temp;
		temp = temp->next;
	}

	if (y->children->count > 0)
	{
		CDLL *m = merge(b->root, y->children);
		b->root = m;
	}

	consolidate(b);
	b->count--;
	return y->value;
}

void consolidate(Binheap *b)
{
	double newSize = log2(b->count) + 1; //hmmm double or nawh?
	Node **D;
	D = malloc(sizeof(Node *) * newSize); //set a variable D to the allocation of an array of D's size
	for (int i = 0; i < newSize; ++i)
		D[i] = NULL; //initialize the D array to nulls

	//place all the subheaps in the D array, combining as necessary */
	while (b->root->count != 0)
	{
		Node *spot = b->root->head;
		deleteCDLL(b->root, spot);
		updateConsolidationArray(b, D, spot);
	}

	//transfer the D array back to the heap, keeping track of the extreme value
	b->extreme = NULL;
	for (int i = 0; i < newSize; ++i)
	{
		if (D[i] != NULL)
		{
			insertCDLL(b->root, D[i]);
			if (b->extreme == NULL || b->comparator(D[i]->value, b->extreme->value) < 0)
				b->extreme = D[i];
			//printf("!!!!Extreme Node is: %d", ((Vertex *)D[i]->value)->value);
		}
	}
}
	  
void updateConsolidationArray(Binheap *b, Node **D, Node *spot)
{
	int degree = spot->children->count;
	while (D[degree] != NULL)
	{
		spot = combine(b, spot, D[degree]); //combine spot and D[degree], setting spot to the combined subheap
		D[degree] = NULL;
		degree++;
	}
	D[degree] = spot;
}

Node *combine(Binheap *b, Node *x, Node *y)
{
	if (b->comparator(x->value,y->value) < 0)
	{
		insertCDLL(x->children, y);
		y->parent = x;
		return x;
	}
	else
	{
		insertCDLL(y->children, x);
		x->parent = y;
		return y;
	}
}

void displayHeap(Binheap *b) 
{
	printf("FFFF");
	CDLL *c = b->root;
	if (c == NULL) 
	{
		printf("\nHEAP EMPTY");
	}
	while (c->head != NULL) 
	{
		printf("Root Node: %d", ((Vertex *)c->head->value)->value);
		printf(" Children:");
		displayCDLL(c->head->children);
		c->head = c->head->next;
		if (c->head == c->tail->next)
			break;
	}
	//printf("\n");
}