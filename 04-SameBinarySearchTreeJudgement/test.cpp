#include <iostream>
#include <vector>

class BinarySearchTree
{
 public:
  BinarySearchTree():
      root_(NULL)
  {}
  ~BinarySearchTree()
  {
    freeTree(root_);
  }

  void insert(int data);
  bool isIsomorphic(const BinarySearchTree& rhs)const;

 protected:
  struct Node
  {
    Node(int data):
        data_(data),
        ptrToLeft_(NULL),
        ptrToRight_(NULL)
    {}

    int data_;
    Node* ptrToLeft_;
    Node* ptrToRight_;
  };

  static void insertImpl(Node*& root, int data);
  static bool isIsomorphicImpl(const Node* lhs, const Node* rhs);
  static void freeTree(Node* root);

  Node* root_;
};

///////////////////////////////////////////////////////
void BinarySearchTree::insertImpl(Node*& root, int data)
{
  if(root != NULL)
  {
    if(data < root->data_)
      insertImpl(root->ptrToLeft_, data);
    else if(data > root->data_)
      insertImpl(root->ptrToRight_, data);
    //else data exist, do nothing
  }
  else
    root = new Node(data);
}

void BinarySearchTree::insert(int data)
{
  insertImpl(root_, data);
}

bool BinarySearchTree::isIsomorphicImpl(const Node* lhs, const Node* rhs)
{
  if(lhs == NULL)
    return rhs == NULL;

  if(lhs->data_ == rhs->data_)
  {
    return (isIsomorphicImpl(lhs->ptrToLeft_, rhs->ptrToLeft_)
            && isIsomorphicImpl(lhs->ptrToRight_, rhs->ptrToRight_));
  }

  return false;
}

bool BinarySearchTree::isIsomorphic(const BinarySearchTree& rhs)const
{
  return isIsomorphicImpl(root_, rhs.root_);
}

void BinarySearchTree::freeTree(Node* root)
{
  if(root != NULL)
  {
    freeTree(root->ptrToLeft_);
    freeTree(root->ptrToRight_);
    delete root;
  }
}
///////////////////////////////////////////////////////

void initTree(int n, BinarySearchTree& t)
{
  int data;
  for(int i = 0; i < n; ++i)
  {
    std::cin >> data;
    t.insert(data);
  }
}

int main()
{
  while(true)
  {
    int n, l;

    std::cin >> n;
    if(n == 0)
      break;
    std::cin >> l;

    BinarySearchTree benchmarkTree;
    for(int i = 0; i <= l; ++i)
    {
      if(i == 0)
      {
        initTree(n, benchmarkTree);
      }
      else
      {
        BinarySearchTree t;
        initTree(n, t);
        if(benchmarkTree.isIsomorphic(t))
          std::cout << "Yes" << std::endl;
        else
          std::cout << "No" << std::endl;
      }
    }
  }

  return 0;
}
