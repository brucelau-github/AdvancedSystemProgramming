#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// structure definition
struct ant
{
	char name[21];	// name of the ant!
	int id;		// unique positive number.
	
	struct ant * ptrNext;	// self-ref. pointer to the next ant
	struct ant * ptrPrev;	// self-ref. pointer to the previous ant
};


// global:
struct ant *ptrFirst = NULL;		// pointer to the first ant; empty list of ants!
struct ant *ptrLast = NULL;		// pointer to the last ant
int AntCount =0;				// global counter (used for autoincrementing the id)

struct ant *CreateAnt();
struct ant *InitializeAnt(struct ant *ptrNew);
struct ant *PrintAnt(struct ant *ptrAnt);
struct ant *PrintAnts(struct ant *ptrAnt);
struct ant *PrintAntsReverse(struct ant *ptrAnt);
void KillAnt(struct ant *ptrAnt);
void Exterminate(struct ant *ptrFirstAnt);

struct ant* AddLast(struct ant* ptrNew);
struct ant* AddFirst(struct ant* ptrNew);
struct ant* Insert(struct ant* ptrNew);



// will create a new record, and return a pointer to it if successful, NULL otherwise
struct ant *CreateAnt()
{
	return (struct ant *)(malloc (sizeof (struct ant)));
}

// assumes a record exists. Will override the record with values from the user.
struct ant *InitializeAnt(struct ant *ptrNew)
{
	if (ptrNew == NULL) 
	{
		return NULL;
	}
	else
	{
		printf("Ant name: ");
		scanf("%s", ptrNew->name);
		ptrNew->id = AntCount++;
		ptrNew->ptrNext = NULL;
		ptrNew->ptrPrev = NULL;

		return ptrNew;
	}
}

// assume a record exists and is initialized properly. Will display the contents of one record
struct ant *PrintAnt(struct ant *ptrAnt)
{
	if (ptrAnt == NULL) 
	{
		return NULL;
	}
	else
	{	
		printf("Ant id:%d Name:%s reporting for duty!\n", ptrAnt->id, ptrAnt->name);
 
		return ptrAnt;
	}	
}

struct ant *PrintAnts(struct ant *ptrAnt)
{
	if (ptrAnt == NULL)
	{
		return ptrAnt;
	}
	else
	{
		PrintAnt(ptrAnt);
		PrintAnts(ptrAnt->ptrNext);
		return ptrAnt;
	}
}

struct ant *PrintAntsReverse(struct ant *ptrAnt)
{
	if (ptrAnt == NULL)
	{
		return ptrAnt;
	}
	else
	{
		PrintAntsReverse(ptrAnt->ptrNext);
		PrintAnt(ptrAnt);
		return ptrAnt;
	}
}

// free the memory space occupied by a dynamically allocated record
void KillAnt(struct ant *ptrAnt)
{
	printf("%s has left the farm!\n", ptrAnt->name);
	free(ptrAnt);
}

// will erase ants starting from ptrFirstAnt; it is up to the caller to ensure the previous ant's next is taken care of.
void Exterminate(struct ant *ptrFirstAnt)
{
	struct ant *ptrDelete;

	ptrLast = ptrFirstAnt->ptrPrev;	// update the last node to be the previous node

	// auto fix previous node
	if (ptrFirstAnt != NULL && ptrFirstAnt->ptrPrev != NULL)
	{
		ptrFirstAnt->ptrPrev->ptrNext = NULL;
	}

	while (ptrFirstAnt != NULL)
	{
		ptrDelete = ptrFirstAnt;
		ptrFirstAnt = ptrFirstAnt->ptrNext;
		KillAnt(ptrDelete);
	}

	// if this is now an empty list...
	if (ptrLast == NULL) ptrFirst = NULL;

}

// add an ant to the end of the list
struct ant* AddLast(struct ant* ptrNew)
{
	if (ptrNew == NULL) return NULL;	// error proofing our code

	if (ptrFirst == NULL)	// case adding a new ant to an empty list
	{
		ptrFirst = ptrNew;
		ptrLast = ptrNew;
	}
	else
	{
		ptrLast->ptrNext = ptrNew;
		ptrNew->ptrPrev = ptrLast;
		ptrLast = ptrNew;
	}

	return ptrNew;
}

struct ant* AddFirst(struct ant* ptrNew)
{
	if (ptrNew == NULL) return NULL;	// error proofing our code

	if (ptrFirst == NULL)	// case adding a new ant to an empty list
	{
		ptrFirst = ptrNew;
		ptrLast = ptrNew;
	}
	else
	{
		ptrFirst->ptrPrev = ptrNew;
		ptrNew->ptrNext = ptrFirst;
		ptrFirst = ptrNew;
	}

	return ptrNew;
}


struct ant* Insert(struct ant* ptrNew)
{
	struct ant *ptrPos = ptrFirst;

        if (ptrNew == NULL) return NULL;        // error proofing our code
                
        if (ptrFirst == NULL)   // case adding a new ant to an empty list
        {   
                ptrFirst = ptrNew;
                ptrLast = ptrNew;
        }
        else if (ptrNew->id <= ptrFirst->id)
        {
                AddFirst(ptrNew);
        }
        else if (ptrNew->id >= ptrLast->id) 
        {       
                AddLast(ptrNew); 
        }
        else
        {
		while (ptrNew->id >= ptrPos->ptrNext->id)
		{
			ptrPos = ptrPos->ptrNext;
		}
		
		ptrPos->ptrNext->ptrPrev = ptrNew;
		ptrNew->ptrNext = ptrPos->ptrNext;
		ptrPos->ptrNext = ptrNew;
		ptrNew->ptrPrev = ptrPos;        
        }
        
        return ptrNew;
}


int main()
{

//	KillAnt(PrintAnt(InitializeAnt(CreateAnt())));
	
/*
	AddLast(InitializeAnt(CreateAnt()));
	AddLast(InitializeAnt(CreateAnt()));
	AddFirst(InitializeAnt(CreateAnt()));
	AddLast(InitializeAnt(CreateAnt()));
	AddLast(InitializeAnt(CreateAnt()));
	AddFirst(InitializeAnt(CreateAnt()));
	AddLast(InitializeAnt(CreateAnt()));

*/
	struct ant *ptrTemp = NULL;

	ptrTemp = InitializeAnt(CreateAnt());
	ptrTemp->id = 4;
	Insert(ptrTemp);

	ptrTemp = InitializeAnt(CreateAnt());
	ptrTemp->id = 3;
	Insert(ptrTemp);

	ptrTemp = InitializeAnt(CreateAnt());
	ptrTemp->id = 7;
	Insert(ptrTemp);

	ptrTemp = InitializeAnt(CreateAnt());
	ptrTemp->id = 5;
	Insert(ptrTemp);

	ptrTemp = InitializeAnt(CreateAnt());
	ptrTemp->id = 6;
	Insert(ptrTemp);


	PrintAnts(ptrFirst);

//	PrintAntsReverse(ptrFirst);

	Exterminate(ptrFirst);

	return 0;
}
