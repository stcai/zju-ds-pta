#include <iostream>
#include <vector>

const static size_t INVALID_INDEX = static_cast<size_t>(-1);

class Tree
{
 public:
  Tree():nodes_(NULL),rootIndex_(0){}
  ~Tree()
  {
    if(nodes_ != NULL)
      delete[] nodes_;
  }

  struct Context
  {
    size_t curIndex_;
    std::vector<bool> indexs_;
  };

  void beginFeedData(size_t size, Context& context);
  void feedOneNode(char data, size_t lIndex, size_t rIndex, Context& context);
  void finish(Context& context);

  bool isIsomorphic(const Tree& rhs)const;

 protected:
  struct Node
  {
    char data_;
    size_t left_;
    size_t right_;
  };

  bool isIsomorphicImpl(size_t lIndex, size_t rIndex, const Tree& node2)const;

  Node* nodes_;
  size_t rootIndex_;
};

void Tree::beginFeedData(size_t size, Context& context)
{
  if(nodes_ != NULL)
    delete[] nodes_;

  if(size != 0)
  {
    nodes_ = new Node[size];

    context.curIndex_ = 0;
    context.indexs_.resize(size, false);
  }
}

void Tree::feedOneNode(char data, size_t lIndex, size_t rIndex, Context& context)
{
  Node& node =  nodes_[context.curIndex_++];
  node.data_ = data;
  node.left_ = lIndex;
  node.right_ = rIndex;

  if(lIndex < context.indexs_.size())
    context.indexs_[lIndex] = true;
  if(rIndex < context.indexs_.size())
    context.indexs_[rIndex] = true;
}

void Tree::finish(Context& context)
{
  for(size_t i = 0; i < context.indexs_.size(); ++i)
  {
    if(!context.indexs_[i])
    {
      rootIndex_ = i;
      break;
    }
  }
}

bool Tree::isIsomorphicImpl(size_t lIndex, size_t rIndex, const Tree& rhs)const
{
  if(lIndex == INVALID_INDEX)
    return rIndex == INVALID_INDEX;

  const Node& lNode = nodes_[lIndex];
  const Node& rNode = rhs.nodes_[rIndex];
  if(lNode.data_ == rNode.data_)
  {
    if(isIsomorphicImpl(lNode.left_, rNode.left_, rhs))
    {
      return isIsomorphicImpl(lNode.right_, rNode.right_, rhs);
    }
    else if(isIsomorphicImpl(lNode.left_, rNode.right_, rhs))
    {
      return isIsomorphicImpl(lNode.right_, rNode.left_, rhs);
    }
  }

  return false;
}

bool Tree::isIsomorphic(const Tree& rhs)const
{
  if(nodes_ == NULL)
    return rhs.nodes_ == NULL;

  return isIsomorphicImpl(rootIndex_, rhs.rootIndex_, rhs);
}

///////////////////////
size_t convertIndex(char c)
{
  if(c == '-')
    return INVALID_INDEX;

  return (c - '0');
}

void InitTree(Tree& t)
{
  Tree::Context cxt;

  size_t n;
  std::cin >> n;
  t.beginFeedData(n, cxt);

  char data, left, right;
  for(size_t i = 0; i < n; ++i)
  {
    std::cin >> data >> left >> right;
    t.feedOneNode(data, convertIndex(left), convertIndex(right), cxt);
  }
  t.finish(cxt);
}

int main()
{
  Tree t1, t2;
  InitTree(t1);
  InitTree(t2);
  if(t1.isIsomorphic(t2))
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;

  return 0;
}
