#include <iostream>

struct Node
{
  Node(): next(NULL) {}
  Node(int coef, int expon):coef(coef),expon(expon),next(NULL) {}

  void swap(Node& rhs)
  {
    std::swap(coef, rhs.coef);
    std::swap(expon, rhs.expon);
    std::swap(next, rhs.next);
  }

  int coef;
  int expon;
  Node *next;
};

struct Polynominal
{
  ~Polynominal()
  {
    Node* pCur = root_.next;
    while(pCur != NULL)
    {
      Node* pNext = pCur->next;
      delete pCur;
      pCur = pNext;
    }
  }
  void swap(Polynominal& rhs)
  {
    root_.swap(rhs.root_);
  }

  Node root_;
};

void add(const Polynominal &lhs, const Polynominal &rhs, Polynominal &sum)
{
  Node* pSum = &sum.root_;
  Node* pLhs = lhs.root_.next;
  Node* pRhs = rhs.root_.next;
  while(pLhs != NULL && pRhs != NULL)
  {
    int lhsExpon = pLhs->expon;
    int rhsExpon = pRhs->expon;
    if(lhsExpon > rhsExpon)
    {
      Node* newNode = new Node(pLhs->coef, lhsExpon);
      pSum->next = newNode;
      pSum = newNode;

      pLhs = pLhs->next;
    }
    else if(lhsExpon < rhsExpon)
    {
      Node* newNode = new Node(pRhs->coef, rhsExpon);
      pSum->next = newNode;
      pSum = newNode;

      pRhs = pRhs->next;
    }
    else
    {
      int sumOfCoef = pLhs->coef + pRhs->coef;
      if(sumOfCoef != 0)
      {
        Node* newNode = new Node(sumOfCoef, lhsExpon);
        pSum->next = newNode;
        pSum = pSum->next;
      }

      pLhs = pLhs->next;
      pRhs = pRhs->next;
    }
  }

  while(pLhs != NULL)
  {
    Node* newNode = new Node(pLhs->coef, pLhs->expon);
    pSum->next = newNode;
    pSum = newNode;
    pLhs = pLhs->next;
  }
  while(pRhs != NULL)
  {
    Node* newNode = new Node(pRhs->coef, pRhs->expon);
    pSum->next = newNode;
    pSum = newNode;
    pRhs = pRhs->next;
  }
}

void multiply(const Polynominal& lhs, const Polynominal& rhs, Polynominal& product)
{
  Node* pLhs = lhs.root_.next;
  while(pLhs != NULL)
  {
    int lhsCoef = pLhs->coef;
    int lhsExpon = pLhs->expon;
    Node* pRhs = rhs.root_.next;
    Polynominal tmp;
    Node* pTmp = &tmp.root_;
    while(pRhs != NULL)
    {
      Node* newNode = new Node(lhsCoef * pRhs->coef, lhsExpon + pRhs->expon);
      pTmp->next = newNode;
      pTmp = newNode;
      pRhs = pRhs->next;
    }

    Polynominal sum;
    add(product, tmp, sum);
    product.swap(sum);
    pLhs = pLhs->next;
  }
}

void init(Polynominal& p)
{
  Node* pCur = &p.root_;
  int num;
  std::cin >> num;
  for(int i = 0; i < num; ++i)
  {
    int coef, expon;
    std::cin >> coef >> expon;

    Node* newNode = new Node(coef, expon);
    pCur->next = newNode;
    pCur = newNode;
  }
}

void print(const Polynominal& p)
{
  bool isNotFist = false;
  Node* pCur = p.root_.next;
  while(pCur != NULL)
  {
    if(isNotFist)
      std::cout << " ";
    std::cout << pCur->coef << " " << pCur->expon;
    isNotFist = true;
    pCur = pCur->next;
  }
  if(!isNotFist)
    std::cout << "0 0";
  std::cout << std::endl;
}

///////////////////////////////////////////////////////////////
int main()
{
  Polynominal p1, p2, sum, product;
  init(p1);
  init(p2);
  multiply(p1, p2, product);
  print(product);
  add(p1, p2, sum);
  print(sum);

  return 0;
}
