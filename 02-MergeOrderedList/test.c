#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
  ElementType Data;
  PtrToNode   Next;
};
typedef PtrToNode List;

List Read()
{
  List l = malloc(sizeof(struct Node));
  PtrToNode curNode = l;

  int n = 0;
  scanf("%d\n", &n);
  for(int i = 0; i < n; ++i)
  {
    PtrToNode newNode = malloc(sizeof(struct Node));
    scanf("%d", &(newNode->Data));
    curNode->Next = newNode;
    newNode->Next = NULL;
    curNode = newNode;
  }

  return l;
}

void Print( List L )
{
  if(L->Next == NULL)
  {
    printf("NULL\n");
  }
  else
  {
    PtrToNode ptrToNode = L->Next;
    while(ptrToNode != NULL)
    {
      printf("%d ", ptrToNode->Data);
      ptrToNode = ptrToNode->Next;
    }
    printf("\n");
  }
}

List Merge( List L1, List L2 );

int main()
{
  List L1, L2, L;
  L1 = Read();
  L2 = Read();
  L = Merge(L1, L2);
  Print(L);
  Print(L1);
  Print(L2);
  return 0;
}

List Merge( List L1, List L2 )
{
  List mergedList = malloc(sizeof(struct Node));
  PtrToNode ptrToMergedList = mergedList;
  PtrToNode ptrToL1 = L1->Next;
  PtrToNode ptrToL2 = L2->Next;
  while(ptrToL1 != NULL && ptrToL2 != NULL)
  {
    if(ptrToL1->Data < ptrToL2->Data)
    {
      ptrToMergedList->Next = ptrToL1;
      ptrToL1 = ptrToL1->Next;
    }
    else
    {
      ptrToMergedList->Next = ptrToL2;
      ptrToL2 = ptrToL2->Next;
    }

    ptrToMergedList = ptrToMergedList->Next;
  }

  while(ptrToL1 != NULL)
  {
    ptrToMergedList->Next = ptrToL1;
    ptrToL1 = ptrToL1->Next;
    ptrToMergedList = ptrToMergedList->Next;
  }

  while(ptrToL2 != NULL)
  {
    ptrToMergedList->Next = ptrToL2;
    ptrToL2 = ptrToL2->Next;
    ptrToMergedList = ptrToMergedList->Next;
  }

  ptrToMergedList->Next = NULL;
  L1->Next = NULL;
  L2->Next = NULL;

  return mergedList;
}
