#include <iostream>
#include <stack>
#include <cstdlib>

class BinaryTree
{
 public:
  BinaryTree():
      root_(NULL)
  {}
  ~BinaryTree()
  {
    freeTree(root_);
  }

  void buildTree();
  void traversalByPostOrder();

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

  typedef bool OPType;
  static const bool OP_PUSH = true;
  static const bool OP_POP = false;


  static void freeTree(Node* root);
  static void traversalByPostOrderImpl(Node* root, bool& isFristElement);

  Node* root_;
};
///////////////////////////////////////////////////////

void BinaryTree::buildTree()
{
  std::string line;
  std::getline(std::cin, line);
  int n = atoi(line.c_str());
  n = n*2 - 1;

  std::stack<Node*> stack;
  std::getline(std::cin, line);
  int data = atoi(line.substr(5).c_str());
  root_ = new Node(data);
  stack.push(root_);

  Node* lastNode = root_;
  OPType lastNodeOpType = OP_PUSH;
  for(int i = 0; i < n; ++i)
  {
    std::getline(std::cin, line);
    if(line.compare(0, 4, "Push") == 0)
    {
      int data = atoi(line.substr(5).c_str());
      Node* node = new Node(data);

      if(lastNodeOpType == OP_PUSH)
        lastNode->ptrToLeft_ = node;
      else
        lastNode->ptrToRight_ = node;

      stack.push(node);
      lastNode = node;
      lastNodeOpType = OP_PUSH;
    }
    else if(line == "Pop")
    {
      lastNode = stack.top();
      lastNodeOpType = OP_POP;
      stack.pop();
    }
  }
}

void BinaryTree::traversalByPostOrder()
{
  bool isFristElement = true;
  traversalByPostOrderImpl(root_, isFristElement);
}

void BinaryTree::traversalByPostOrderImpl(Node* root, bool& isFristElement)
{
  if(root)
  {
    traversalByPostOrderImpl(root->ptrToLeft_, isFristElement);
    traversalByPostOrderImpl(root->ptrToRight_, isFristElement);

    if(isFristElement)
      isFristElement = false;
    else
      std::cout << " ";

      std::cout << root->data_;
  }
}

void BinaryTree::freeTree(Node* root)
{
  if(root != NULL)
  {
    freeTree(root->ptrToLeft_);
    freeTree(root->ptrToRight_);
    delete root;
  }
}
///////////////////////////////////////////////////////

int main()
{
  BinaryTree t;
  t.buildTree();
  t.traversalByPostOrder();
  return 0;
}
