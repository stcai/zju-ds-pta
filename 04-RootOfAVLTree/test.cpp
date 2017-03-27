#include <iostream>

template<typename DataType>
class AVLTree
{
 public:
  AVLTree(): root_(NULL) {}
  ~AVLTree()
  {
    if(root_)
      delete root_;
  }

  void insert(const DataType& data);
  const DataType& getRootData();

 private:
  class Node
  {
   public:
    Node(const DataType& data):
        data_(data)
        , hight_(0)
        , left_(NULL)
        , right_(NULL)
    {}
    ~Node() {clear();}

    void clear();
    const DataType& getData() {return data_;}

    static int getHight(Node *node);
    static Node* insert(Node* node, const DataType& data);

   private:
    static Node* singleLeftRotate(Node *node);
    static Node* singleRightRotate(Node *node);
    static Node* leftRightRotate(Node *node);
    static Node* rightLeftRotate(Node *node);

    DataType data_;
    int hight_;
    Node *left_;
    Node *right_;
  };

  Node *root_;
};

template<typename DataType>
void AVLTree<DataType>::insert(const DataType& data)
{
  root_ = Node::insert(root_, data);
}

template<typename DataType>
const DataType& AVLTree<DataType>::getRootData()
{
  if(root_ == NULL)
    throw "Empty Tree";

  return root_->getData();
}

template<typename DataType>
void AVLTree<DataType>::Node::clear()
{
  if(left_)
  {
    left_->clear();
    delete left_;
    left_ = NULL;
  }
  if(right_)
  {
    right_->clear();
    delete right_;
    right_ = NULL;
  }
}

template<typename DataType>
int AVLTree<DataType>::Node::getHight(typename AVLTree<DataType>::Node *node)
{
  if(node == NULL)
    return -1;
  return node->hight_;
}

template<typename DataType>
typename AVLTree<DataType>::Node* AVLTree<DataType>::Node::insert(Node *node, const DataType& data)
{
  if(node == NULL)
    return new Node(data);

  if(data < node->getData())
  {
    node->left_ = insert(node->left_, data);

    int leftTreeHight = getHight(node->left_);
    int rightTreeHight = getHight(node->right_);
    node->hight_ = std::max(leftTreeHight, rightTreeHight) + 1;

    if(leftTreeHight - rightTreeHight == 2)
    {
      if(data < node->left_->getData())
        return singleLeftRotate(node);
      else
        return leftRightRotate(node);
    }
  }
  else if(data > node->getData())
  {
    node->right_ = insert(node->right_, data);

    int leftTreeHight = getHight(node->left_);
    int rightTreeHight = getHight(node->right_);
    node->hight_ = std::max(leftTreeHight, rightTreeHight) + 1;

    if(leftTreeHight - rightTreeHight == -2)
    {
      if(data > node->right_->getData())
        return singleRightRotate(node);
      else
        return rightLeftRotate(node);
    }
  }

  return node;
}

template<typename DataType>
typename AVLTree<DataType>::Node* AVLTree<DataType>::Node::singleLeftRotate(Node *node)
{
  Node *lastLeft = node->left_;
  Node *lastLeftRight = lastLeft->right_;
  lastLeft->right_ = node;
  node->left_ = lastLeftRight;

  node->hight_ = std::max(getHight(node->left_), getHight(node->right_)) + 1;
  lastLeft->hight_ = std::max(getHight(lastLeft->left_), getHight(lastLeft->right_)) + 1;

  return lastLeft;
}

template<typename DataType>
typename AVLTree<DataType>::Node* AVLTree<DataType>::Node::singleRightRotate(Node *node)
{
  Node *lastRight = node->right_;
  Node *lastRightLeft = lastRight->left_;
  lastRight->left_ = node;
  node->right_ = lastRightLeft;

  node->hight_ = std::max(getHight(node->left_), getHight(node->right_)) + 1;
  lastRight->hight_ = std::max(getHight(lastRight->left_), getHight(lastRight->right_)) + 1;

  return lastRight;
}

template<typename DataType>
typename AVLTree<DataType>::Node* AVLTree<DataType>::Node::leftRightRotate(Node *node)
{
  node->left_ = singleRightRotate(node->left_);
  return singleLeftRotate(node);
}

template<typename DataType>
typename AVLTree<DataType>::Node* AVLTree<DataType>::Node::rightLeftRotate(Node *node)
{
  node->right_ = singleLeftRotate( node->right_);
  return singleRightRotate(node);
}

//---------------------------------------------------------------
int main()
{
  int n, data;
  AVLTree<int> tree;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> data;
    tree.insert(data);
  }

  std::cout << tree.getRootData() << std::endl;
  return 0;
}

