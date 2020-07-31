//prim.c
#define _CRT_NONSTDC_NO_WARNINGS //because visual studio
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 

#include "prim.h"
#include "binheap.h"
#include "queue.h"
#include "CDLL.h"
#include "node.h"
#include "scanner.h"
#include <string.h>
#include <stdlib.h>
#include "array.h"

Vertex **vertexList;
int **adjacencyMatrix;
int matrixSize; //# of vertices + 1
int infinity = 0; //max weight + 1
Binheap *b;

int lessthan(void *a, void *b)
{
	Vertex *x = (Vertex *)a;
	Vertex *y = (Vertex *)b;
	int result = x->key - y->key;
	if (result == 0)
	{
		result = x->predecessor - y->predecessor;
		if (result == 0)
			result = x->value - y->value;
	}
	return result;
	//returns a neg when a is less than b
	//0 if equal
}

Vertex *newVertex(int x)
{
	Vertex *v = malloc(sizeof(Vertex));
	v->value = x;
	v->key = -1;
	v->predecessor = -1;
	v->owner = NULL;
	v->color = "white";
	v->distance = 0;
	return v;
}

void addVerticesToRootlist(Binheap *b, void *a, int key)
{
		Vertex *v = (Vertex*)a;
		v->key = key;
		v->owner = insertHeap(b, v);
}


void updateVertexKey(Vertex *v, int weight, Binheap *b) 
{
	vertexList[v->value]->key = weight;
	v->key = weight;
	decreaseKey(b, v->owner, v);
}

int lessthanArray(void * a, void *b) //used to sort the vertices in BFT
{
	Vertex *x = (Vertex *)a;
	Vertex *y = (Vertex *)b;

	return x->value - y->value;
	//returns a neg when a is less than b
	//0 if equal
}

int findLargest(char *file)
{
	if (file == NULL) // if no file
	{
		printf("No file");
		exit(0);
	}
	int maxVertex = 0;
	FILE *fp = fopen(file, "r");
	char *ev = readToken(fp); //1st vertex
	if (ev == NULL) //if empty file
	{
		printf("Empty File");
		exit(0);
	}
	if (atoi(ev) > maxVertex)
		maxVertex = atoi(ev);
	ev = readToken(fp); //2nd vertex
	if (atoi(ev) > maxVertex)
		maxVertex = atoi(ev);
	ev = readToken(fp); //weight
	
	while (ev != 0 && ev != NULL)
	{
		if (strcmp(ev, ";") == 0)
			infinity += 0;
		else
		{
			if (atoi(ev) > infinity)
				infinity = atoi(ev) + 1;
			ev = readToken(fp); //ignore the ;
		}

		ev = readToken(fp); //1st vertex
		if (ev == NULL)
			break;
		if (atoi(ev) > maxVertex)
			maxVertex = atoi(ev);
		ev = readToken(fp); //2nd vertex
		if (atoi(ev) > maxVertex)
			maxVertex = atoi(ev);

		ev = readToken(fp); //weight
		if (ev == NULL)
			break;
	}
	return maxVertex;
}


int main(int argc, char **argv)
{
	matrixSize = findLargest(argv[1]) + 1;

	vertexList = malloc(sizeof(Vertex *) * matrixSize);
	for (int i = 0; i < matrixSize; i++)
		vertexList[i] = NULL;

	adjacencyMatrix = malloc(matrixSize * sizeof(int*));
	int *temp = malloc(matrixSize * matrixSize * sizeof(int));
	for (int i = 0; i < matrixSize; i++) 
		adjacencyMatrix[i] = &temp[i * matrixSize];

	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
			adjacencyMatrix[i][j] = infinity;


	FILE *fp = fopen(argv[1], "r");
	int weight = 0;
	b = newBinheap(lessthan);

	char *ev = readToken(fp); //1st vertex
	int v1 = atoi(ev);
	Vertex *v = newVertex(v1);
	for (int i = 0; i < matrixSize; i++) //check to see if its already there
	{
		if (vertexList[v1] == NULL)
		{
			vertexList[v1] = v;
			addVerticesToRootlist(b, v, infinity);
		}
	}

	ev = readToken(fp); //2nd vertex
	int v2 = atoi(ev);
	v = newVertex(v2);
	for (int i = 0; i < matrixSize; i++) //check to see if its already there
	{
		if (vertexList[v2] == NULL)
		{
			vertexList[v2] = v;
			addVerticesToRootlist(b, v, infinity);
		}
	}

	ev = readToken(fp);
	while (ev != 0 && ev != NULL)
	{
		if (strcmp(ev, ";") == 0)
			weight = 1;
		else
		{
			weight = atoi(ev);
			ev = readToken(fp);
		}
		if (adjacencyMatrix[v1][v2] == infinity && adjacencyMatrix[v2][v1]) //handle duplicates
		{
			adjacencyMatrix[v1][v2] = weight;
			adjacencyMatrix[v2][v1] = weight;
		}

		ev = readToken(fp);
		if (ev == NULL)
			break;
		v1 = atoi(ev);
		v = newVertex(v1);
		for (int i = 0; i < matrixSize; i++) //check to see if its already there
		{
			if (vertexList[v1] == NULL)
			{
				vertexList[v1] = v;
				addVerticesToRootlist(b, v, infinity);
			}
		}

		ev = readToken(fp);
		v2 = atoi(ev);
		v = newVertex(v2);
		for (int i = 0; i < matrixSize; i++) //check to see if its already there
		{
			if (vertexList[v2] == NULL)
			{
				vertexList[v2] = v;
				addVerticesToRootlist(b, v, infinity);
			}
		}
		
		ev = readToken(fp); //weight
		if (ev == NULL)
			break;
	}

	fclose(fp);

	for (int i = 0; i < matrixSize; i++) //set key to infinity
	{
		if (vertexList[i] != NULL)
			vertexList[i]->key = infinity;
		
	}
/*
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			if (adjacencyMatrix[i][j] != infinity)
			{
				printf("Vertex %d Vertex %d ", i, j, adjacencyMatrix[i][j]);
				printf(" Weight %d ", adjacencyMatrix[i][j]);
				printf("\n");
			}
		}
	}
*/			

	Vertex *r = newVertex(0);
	while (b->count > 0)
	{
		r = prim(b);
		BFT(r);
		printf("\n");
	}

	return 0;
}

Vertex *prim(Binheap *b)
{
	Vertex *root = newVertex(0);
	void *u;
	for (int i = 0; i < matrixSize; i++) //find the root
	{
		if (vertexList[i] != NULL && vertexList[i]->key == infinity)
		{
			root = vertexList[i];
			break;
		}
	}

	u = extractMin(b); //extract root
	addVerticesToRootlist(b, u, 0); //throw it back in with a key of 0
	while (b->count > 0)
	{
		u = extractMin(b);
		
		if (((Vertex *)u)->key == infinity)
		{
			addVerticesToRootlist(b, u, infinity); //if not visited its disconnected to thow it back in and end prim's
			break;
		}
		for (int i = 0; i < matrixSize; i++)
		{
			if (adjacencyMatrix[((Vertex*)u)->value][i] != infinity)
			{
				if (strcmp(vertexList[i]->color, "black") != 0 && (adjacencyMatrix[((Vertex*)u)->value][i]) < vertexList[i]->key)
				{
					vertexList[((Vertex*)u)->value]->color = "black";
					vertexList[i]->predecessor = ((Vertex*)u)->value;
					updateVertexKey(vertexList[i], adjacencyMatrix[((Vertex*)u)->value][i], b);
				}
				printf("%d PRED %d", vertexList[45]->value, vertexList[45]->predecessor);
			}

		}

	}
		return root;
}

void BFT(Vertex *root)
{
	Queue *q = createQueue();
	Node *traverse = newNode(root);
	array *finalArray = newArray(lessthanArray);

	int level = 0;
	int totalWeight = 0;

	vertexList[root->value]->color = "gray";
	vertexList[root->value]->distance = 0;
	vertexList[root->value]->predecessor = root->value;

	enqueue(q, vertexList[root->value]);

	printf("%d :", level);
	Vertex *v = vertexList[root->value];
	printf(" %d;", v->value);
	printf("\n");

	while (q->front != NULL)
	{
		int levelNodes = q->count;
		while (levelNodes > 0)
		{
			traverse = dequeue(q); //returns a node

			for (int i = 0; i < matrixSize; i++)
			{
				if (vertexList[i] != NULL && adjacencyMatrix[((Vertex *)traverse->value)->value][i] != infinity)
					if (((Vertex *)traverse->value)->value == vertexList[i]->predecessor)
					{
						{
							vertexList[i]->color = "gray";
							vertexList[i]->distance = adjacencyMatrix[((Vertex*)traverse->value)->value][i];
							totalWeight += adjacencyMatrix[((Vertex*)traverse->value)->value][i];
							enqueue(q, vertexList[i]);
							addArray(finalArray, vertexList[i]);
						}
					}
			}
			vertexList[((Vertex*)traverse->value)->value]->color = "black";
			levelNodes--;
		}

		if (q->front == NULL)
			break;

		level++;
		printf("%d :", level);

		sortArray(finalArray);

		for (int i = 0; i < finalArray->size; ++i)
		{
			Vertex *v = finalArray->store[i];
			printf(" %d(%d)%d", v->value, v->predecessor, v->distance);
			if (i == finalArray->size-1)
				printf(";");
			else
				printf(",");
		}
		finalArray = newArray(lessthanArray);
		printf("\n");
	}
	//printf(";");
	printf("weight: %d", totalWeight);
}

/*
void BFT(Vertex *root)
{
	Queue *q = createQueue();
	Node *traverse = newNode(root);

	int level = 0;
	int totalWeight = 0;
	int flag = 0; //if at end of level

	vertexList[root->value]->color = "gray";
	vertexList[root->value]->distance = 0;
	vertexList[root->value]->predecessor = -1;

	enqueue(q, vertexList[root->value]);

	printf("\n%d:", level);

	while (q->front != NULL)
	{
		int levelNodes = q->count;
		while (levelNodes > 0)
		{
			traverse = dequeue(q); //returns a node
			printf(" %d", ((Vertex*)traverse->value)->value);
			if (level != 0)
			{
				printf("(%d)", ((Vertex*)traverse->value)->predecessor);
				printf("%d", ((Vertex*)traverse->value)->distance);
				printf(",");
			}

			for (int i = 0; i < matrixSize; i++)
			{
				if (vertexList[i] != NULL && adjacencyMatrix[((Vertex *)traverse->value)->value][i] != infinity)
					if (((Vertex *)traverse->value)->value == vertexList[i]->predecessor)
					{
						{
							vertexList[i]->color = "gray";
							vertexList[i]->distance = adjacencyMatrix[((Vertex*)traverse->value)->value][i];
							totalWeight += adjacencyMatrix[((Vertex*)traverse->value)->value][i];
							enqueue(q, vertexList[i]);
						}
					}
			}
			vertexList[((Vertex*)traverse->value)->value]->color = "black";
			levelNodes--;
		}

		if (q->front == NULL)
			break;

		printf(";");
		printf("\n");
		level++;
		printf("%d:", level);
	}
	printf(";");
	printf("\nweight: %d", totalWeight);
}
*/