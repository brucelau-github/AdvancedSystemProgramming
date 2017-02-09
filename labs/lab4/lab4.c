#include <stdio.h>
#include <stdlib.h>

struct number {
  int value;
  struct number *ptrNext;
};
struct number *ptFirst = NULL;
struct number *ptLast = NULL;
int amount = 0;

struct number *createNumber();
void deleteNumber();

struct number *createNumber() {
  return (struct number *)malloc( sizeof(struct number));
}

int main(int argc, char const *argv[]) {

  struct number *ptrCurrentNumber = NULL;
  struct number *ptrFirst = NULL;
  int n = 0;
  int i;

  printf("input a series of integer to memory (maximum 8 digits) and maximum 1000 integers. print -1 to finish.\n");
  for (i = 0; i < 1000 ; i++) {
    printf("enter the %d integer:",i);
    scanf("%8d", &n);
    if( n == -1 ) break;
    //first value;
    if( ptrCurrentNumber == NULL ) {
      ptrCurrentNumber = createNumber();
      ptrFirst = ptrCurrentNumber;
    } else { //second and other node
      ptrCurrentNumber->ptrNext = createNumber();
      ptrCurrentNumber = ptrCurrentNumber->ptrNext;

    }
    ptrCurrentNumber->value = n;
    ptrCurrentNumber->ptrNext = NULL;

  }

  //show the list;
  ptrCurrentNumber = ptrFirst;
  printf("\nAll the value are \n[ ");
  i = 0;
  while( ptrCurrentNumber != NULL) {
    printf("%d ", ptrCurrentNumber->value );
    ptrCurrentNumber = ptrCurrentNumber->ptrNext;
  }
  printf("]\n");

  //show the list;
  ptrCurrentNumber = ptrFirst;
  printf("\nstart clear memory!\n");
  while( ptrCurrentNumber != NULL) {
    free(ptrCurrentNumber);
    ptrCurrentNumber = ptrCurrentNumber->ptrNext;
  }
  printf("memory is clear now!\n");
  return 0;
}
