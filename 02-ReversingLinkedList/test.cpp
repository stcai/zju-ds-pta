#include <iostream>
#include <cstdio>

#define MAX_NUMBER_OF_NODE 100000

struct Node
{
  int data;
  int next;
};
typedef Node LinkList;

void initLinkList(LinkList* mem, int& k)
{
  int addrOfFirstNode, totalNumOfNode;
  std::cin >> addrOfFirstNode >> totalNumOfNode >> k;
  mem[MAX_NUMBER_OF_NODE].next = addrOfFirstNode;

  int address, data, next;
  for(int i = 0; i < totalNumOfNode; ++i)
  {
    std::cin >> address >> data >> next;
    Node& node = mem[address];
    node.data = data;
    node.next = next;
  }

  int currentAddr = mem[MAX_NUMBER_OF_NODE].next;
  int elementCount = 0;
  while(currentAddr != -1)
  {
    ++elementCount;
    currentAddr = mem[currentAddr].next;
  }
  mem[MAX_NUMBER_OF_NODE].data = elementCount;
}

void reverseLinkList(LinkList* mem, int k)
{
  int lastReversedSubListEndAddr = MAX_NUMBER_OF_NODE;
  int currentAddr = mem[MAX_NUMBER_OF_NODE].next;
  int elementCount = mem[MAX_NUMBER_OF_NODE].data;

  while(elementCount >= k)
  {
    int subListBeginAddr = currentAddr;
    int lastAddr = -1;
    for(int i = 0; i < k; ++i)
    {
      Node& node = mem[currentAddr];
      int nextAddr = node.next;
      node.next = lastAddr;
      lastAddr = currentAddr;
      currentAddr = nextAddr;
    }
    elementCount -= k;

    mem[lastReversedSubListEndAddr].next = lastAddr;
    lastReversedSubListEndAddr = subListBeginAddr;
    mem[subListBeginAddr].next = currentAddr;
  }
}

void printLinkList(LinkList* mem)
{
  int currentAddr = mem[MAX_NUMBER_OF_NODE].next;
  while(currentAddr != -1)
  {
    const Node& node = mem[currentAddr];
    if(node.next == -1)
      printf("%05d %d -1\n", currentAddr, node.data);
    else
      printf("%05d %d %05d\n", currentAddr, node.data, node.next);

    currentAddr = node.next;
  }
}

int main()
{
  LinkList mem[100001];
  int k;
  initLinkList(mem, k);
  reverseLinkList(mem, k);
  printLinkList(mem);

  return 0;
}
