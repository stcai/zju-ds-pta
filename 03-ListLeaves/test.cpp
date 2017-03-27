#include <iostream>
#include <vector>
#include <queue>


class Tree
{
 public:
  Tree():nodes_(NULL),rootIndex_(0){}
  ~Tree()
  {
    if(nodes_ != NULL)
      delete[] nodes_;
  }

  class InitContext
  {
    size_t curIndex_;
    std::vector<bool> indexs_;

    friend class Tree;
  };

  class VisitContext
  {
   public:
    VisitContext(const Tree& tree)
    {
      indexesToVisit_.push(tree.rootIndex_);
    }

    size_t getCurrentNodeIndex() const { return curIndex_; }

   private:
    size_t curIndex_;
    std::queue<size_t> indexesToVisit_;

    friend class Tree;
  };
  friend class VisitContext;

  void beginFeedData(size_t size, InitContext& context);
  void feedOneNode(size_t lIndex, size_t rIndex, InitContext& context);
  void finish(InitContext& context);

  bool visitNodeLDR(VisitContext& context)const;
  bool isLeafNode(const VisitContext& context)const;

  const static size_t INVALID_INDEX = static_cast<size_t>(-1);

 protected:
  struct Node
  {
    size_t left_;
    size_t right_;
  };

  static void checkValidAndPush(size_t index, VisitContext& context);

  Node* nodes_;
  size_t rootIndex_;
};

////////////////////////////////////////////////////////////////////////
void Tree::beginFeedData(size_t size, InitContext& context)
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

void Tree::feedOneNode(size_t lIndex, size_t rIndex, InitContext& context)
{
  Node& node =  nodes_[context.curIndex_++];
  node.left_ = lIndex;
  node.right_ = rIndex;

  if(lIndex < context.indexs_.size())
    context.indexs_[lIndex] = true;
  if(rIndex < context.indexs_.size())
    context.indexs_[rIndex] = true;
}

void Tree::finish(InitContext& context)
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

void Tree::checkValidAndPush(size_t index, Tree::VisitContext& context)
{
  if(index != INVALID_INDEX)
  {
    context.indexesToVisit_.push(index);
  }
}

bool Tree::visitNodeLDR(VisitContext &context)const
{
  if(context.indexesToVisit_.empty())
    return false;

  context.curIndex_ = context.indexesToVisit_.front();
  context.indexesToVisit_.pop();
  const Node& node = nodes_[context.getCurrentNodeIndex()];
  checkValidAndPush(node.left_, context);
  checkValidAndPush(node.right_, context);

  return true;
}

bool Tree::isLeafNode(const VisitContext &context)const
{
  const Node& node = nodes_[context.getCurrentNodeIndex()];
  if(node.left_ == INVALID_INDEX
     && node.right_ == INVALID_INDEX)
    return true;

  return false;
}

////////////////////////////////////////////////////////////////////////
size_t convertIndex(char c)
{
  if(c == '-')
    return Tree::INVALID_INDEX;

  return (c - '0');
}

void InitTree(Tree& t)
{
  Tree::InitContext cxt;

  size_t n;
  std::cin >> n;
  t.beginFeedData(n, cxt);

  char left, right;
  for(size_t i = 0; i < n; ++i)
  {
    std::cin >> left >> right;
    t.feedOneNode(convertIndex(left), convertIndex(right), cxt);
  }
  t.finish(cxt);
}

int main()
{
  Tree t;
  InitTree(t);

  Tree::VisitContext cxt(t);
  bool isFirstPrint = true;
  while(t.visitNodeLDR(cxt))
  {
    if(t.isLeafNode(cxt))
    {
      if(isFirstPrint)
        isFirstPrint = false;
      else
        std::cout << " ";

      std::cout << cxt.getCurrentNodeIndex();
    }
  }
  std::cout << std::endl;

  return 0;
}
