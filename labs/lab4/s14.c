#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Self-Ref. Struct Definition
struct node
{
	int value;
	struct node *ptrNext;
	struct node *ptrPrevious;
};


struct node *CreateNode();

struct node* InputNodeFromUser(struct node *ptrNew);

void AddFirst(struct node *ptrNew);
void AddLast(struct node *ptrNew);

void ClearList(struct node * ptrF);
void PrintList(struct node * ptrF);
void PrintListReverse(struct node * ptrF);

int CountList(struct node * ptrF);

void DeleteFirst();
void DeleteLast();
void DeleteAt(struct node *ptrDelete);

void Insert(struct node *ptrNew);

int isEmpty();

void SaveList(struct node *ptrF, char *filename);


// Global Variables for the List
struct node *ptrFirst = NULL;
struct node *ptrLast = NULL;

int main()
{

	// Predefined/simulated user input:
	//AddFirst(InputNodeFromUser(CreateNode()));
	//AddFirst(InputNodeFromUser(CreateNode()));
	

	Insert(InputNodeFromUser(CreateNode()));
	Insert(InputNodeFromUser(CreateNode()));
	Insert(InputNodeFromUser(CreateNode()));
	Insert(InputNodeFromUser(CreateNode()));
	Insert(InputNodeFromUser(CreateNode()));
	

	PrintList(ptrFirst);

//	DeleteAt(ptrFirst->ptrNext);

//	PrintList(ptrFirst);

//	PrintListReverse(ptrFirst);

	ClearList(ptrFirst);

	return 0;
}

// user needs to check if it is NULL
struct node *CreateNode()
{
	return (struct node*) (malloc (sizeof(struct node)));
}

struct node* InputNodeFromUser(struct node *ptrNew)
{
	printf("Please enter a number: ");
	scanf("%d", &ptrNew->value); 
	ptrNew->ptrNext = NULL;
	ptrNew->ptrPrevious = NULL;
	return ptrNew;
}

// assume ptrFirst and ptrLast are global
void AddFirst(struct node *ptrNew)
{
	if (isEmpty())
	{
		ptrFirst = ptrNew;
		ptrLast = ptrNew;
	}
	else
	{
		ptrNew->ptrNext = ptrFirst;
		ptrFirst->ptrPrevious = ptrNew;
		ptrFirst = ptrNew;
	}
}

void AddLast(struct node *ptrNew)
{
	if (isEmpty())
	{
		ptrFirst = ptrNew;
		ptrLast = ptrNew;
	}
	else
	{
		ptrLast->ptrNext = ptrNew;
		ptrNew->ptrPrevious = ptrLast;
		ptrLast = ptrNew;
	}
}

int isEmpty()
{
	if(ptrFirst == NULL)
		return 1;
	else 
		return 0;
}

// user must clear ptrFirst and ptrLast
void ClearList(struct node * ptrF)
{
	// base case: empty list
	if (ptrF == NULL)
		return;
	else
	{
		ClearList(ptrF->ptrNext);
		free(ptrF);
	}
}

void PrintList(struct node * ptrF)
{
	// base case: empty list
	if (ptrF == NULL)
		return;
	else
	{
		printf("%d ", ptrF->value);
		PrintList(ptrF->ptrNext);
	}
}

void PrintListReverse(struct node * ptrF)
{
	// base case: empty list
	if (ptrF == NULL)
		return;
	else
	{
		PrintListReverse(ptrF->ptrNext);
		printf("%d ", ptrF->value);
	}
}

void PrintListReverseUsingPrev(struct node * ptrL)
{
	while (ptrL != NULL)
	{
		printf("%d ", ptrL->value);
		ptrL = ptrL->ptrPrevious;
	}
}

int CountList(struct node * ptrF)
{
	// base case: empty list
	if (ptrF == NULL)
		return 0;
	else
	{
		return CountList(ptrF->ptrNext) + 1;
	}
}

void DeleteFirst()
{
	struct node * ptrDelete = NULL;

	if (isEmpty())
	{
		return;
	}
	
	if (ptrFirst == ptrLast)  // if there is only one node!
	{
		free(ptrFirst);
		ptrFirst = NULL;
		ptrLast = NULL;
	}
	else
	{
		// delete from a big list
		ptrDelete = ptrFirst;
		ptrFirst = ptrFirst->ptrNext;
		free(ptrDelete);
		ptrFirst->ptrPrevious = NULL;
	}
}

void DeleteLast()
{
	struct node * ptrDelete = NULL;

	if (isEmpty())
	{
		return;
	}
	
	if (ptrFirst == ptrLast)
	{
		free(ptrFirst);
		ptrFirst = NULL;
		ptrLast = NULL;
	}
	else
	{
		// delete from a big list
		ptrDelete = ptrLast;
		ptrLast = ptrLast->ptrPrevious;
		ptrLast->ptrNext = NULL;

		free(ptrDelete);
	}
}

void DeleteAt(struct node *ptrDelete)
{
	if (ptrDelete == NULL)
		return;

	if (isEmpty())
		return;

	if (ptrDelete == ptrFirst)
	{
		DeleteFirst(ptrDelete);
		return;
	}

	if (ptrDelete == ptrLast)
	{
		DeleteLast(ptrDelete);
		return;
	}

	ptrDelete->ptrPrevious->ptrNext = ptrDelete->ptrNext;
	ptrDelete->ptrNext->ptrPrevious = ptrDelete->ptrPrevious;

	free(ptrDelete);

}

void Insert(struct node *ptrNew)
{

	struct node *ptrP = ptrFirst;

	if (ptrNew == NULL)
		return;

	if (ptrFirst == NULL)
	{
		ptrFirst = ptrNew;
		ptrLast = ptrNew;
		return;
	}

	if (ptrNew->value <= ptrFirst->value)
	{
		ptrNew->ptrNext = ptrFirst;
		ptrFirst->ptrPrevious = ptrNew;
		ptrFirst = ptrNew;
		return;
	}

	if (ptrNew->value >= ptrLast->value)
	{
		ptrNew->ptrPrevious = ptrLast;
		ptrLast->ptrNext = ptrNew;
		ptrLast = ptrNew;
		return;
	}

	while (ptrNew->value >= ptrP->ptrNext->value)
	{
		ptrP = ptrP->ptrNext;
	} 

	ptrNew->ptrPrevious = ptrP;
	ptrNew->ptrNext = ptrP->ptrNext;
	ptrP->ptrNext = ptrNew;
	ptrNew->ptrNext->ptrPrevious = ptrNew;
}



void SaveList(struct node *ptrF, char *filename)
{
	FILE *outFile;

	outFile = fopen(filename, "w");

	if (outFile == NULL)
		return;

	while(ptrF != NULL)
	{
		fprintf(outFile, "%d ", ptrF->value);
		ptrF = ptrF->ptrNext;
	}

	fclose(outFile);
}


