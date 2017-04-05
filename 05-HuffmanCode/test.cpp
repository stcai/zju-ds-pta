#include <iostream>
#include <map>
#include <queue>

class PrefixCodeChecker
{
 public:
  void reset()
  {
    root_.free();
    root_.hasData_ = false;
  }

  bool addAndCheckValid(const std::string& encodeString);

 private:
  struct Node
  {
    Node()
        : hasData_(false)
        , left_(NULL)
        , right_(NULL)
    {}
    ~Node()
    {free();}

    void free()
    {
      if(left_)
      {
        left_->free();
        delete left_;
        left_ = NULL;
      }
      if(right_)
      {
        right_->free();
        delete right_;
        right_ = NULL;
      }
    }

    bool hasData_;
    Node *left_;
    Node *right_;
  };

  Node root_;
};

class HuffmanEncoder
{
 public:
  HuffmanEncoder()
      :root_(NULL)
  {}
  ~HuffmanEncoder()
  {
    if(root_)
    {
      root_->free();
      delete root_;
      root_ = NULL;
    }
  }
  void encode(const std::map<char, int>& charactor2Frequency);
  int getEncodeLength();

 private:
  struct Node
  {
    Node(int weight)
        : weight_(weight)
        , left_(NULL)
        , right_(NULL)
    {}
    ~Node()
    {free();}

    void free()
    {
      if(left_)
      {
        left_->free();
        delete left_;
        left_ = NULL;
      }
      if(right_)
      {
        right_->free();
        delete right_;
        right_ = NULL;
      }
    }

    int weight_;
    Node *left_;
    Node *right_;
  };

  class NodeCompare
  {
   public:
    bool operator()(const Node* lhs, const Node* rhs)
    {
      if(lhs->weight_ < rhs->weight_)
        return false;
      return true;
    }
  };

  typedef std::priority_queue<Node*, std::vector<Node*>, NodeCompare> MinHeap;

  void buildTree(MinHeap& minHeap);
  static void getEncodeLengthImpl(const Node* node, int& curResult, int depth);

  Node *root_;
};

//--------------------------------------------------------
bool PrefixCodeChecker::addAndCheckValid(const std::string &encodeString)
{
  Node *pParent = &root_;
  for(std::string::size_type i = 0; i < encodeString.size(); ++i)
  {
    char c = encodeString[i];
    Node **ppChild;
    if(c == '0')
    {
      ppChild = &pParent->left_;
    }
    else
    {
      ppChild = &pParent->right_;
    }

    if(*ppChild == NULL)
    {
      *ppChild = new Node;
    }
    else if(pParent->hasData_)
      return false;
    pParent = *ppChild;
  }

  if(pParent->hasData_)
    return false;
  if(pParent->left_ || pParent->right_)
    return false;
  pParent->hasData_ = true;
  return true;
}

//--------------------------------------------------------
void HuffmanEncoder::encode(const std::map<char, int>& charactor2Frequency)
{
  MinHeap minHeap;
  for(std::map<char, int>::const_iterator it = charactor2Frequency.begin();
      it != charactor2Frequency.end();
      ++it)
  {
    minHeap.push(new Node(it->second));
  }
  buildTree(minHeap);
}

void HuffmanEncoder::buildTree(MinHeap& minHeap)
{
  while(minHeap.size() > 1)
  {
    Node *left = minHeap.top(); minHeap.pop();
    Node *right = minHeap.top(); minHeap.pop();
    int weight = left->weight_ + right->weight_;

    Node *newTree = new Node(weight);
    newTree->left_ = left;
    newTree->right_ = right;
    minHeap.push(newTree);
  }
  root_ = minHeap.top();
}

int HuffmanEncoder::getEncodeLength()
{
  int result = 0;
  if(root_)
  {
    getEncodeLengthImpl(root_, result, 0);
  }
  return result;
}

void HuffmanEncoder::getEncodeLengthImpl(const Node* node, int& curResult, int depth)
{
  if(node->left_ == NULL
     && node->right_ == NULL)
  {
    curResult += depth * node->weight_;
  }
  else
  {
    if(node->left_ != NULL)
      getEncodeLengthImpl(node->left_, curResult, depth+1);
    if(node->right_ != NULL)
      getEncodeLengthImpl(node->right_, curResult, depth+1);
  }
}

//--------------------------------------------------------
int main()
{
  std::map<char, int> charactor2Frequency;

  size_t charCount;
  std::cin >> charCount;
  for(size_t i = 0; i < charCount; ++i)
  {
    char c;
    int frequency;
    std::cin >> c >> frequency;
    charactor2Frequency[c] = frequency;
  }

  HuffmanEncoder huffmanEncoder;
  huffmanEncoder.encode(charactor2Frequency);
  int huffmanEncodeLength = huffmanEncoder.getEncodeLength();

  PrefixCodeChecker prefixCodeChecker;
  int caseCount;
  std::cin >> caseCount;
  for(int i = 0; i < caseCount; ++i)
  {
    bool isError = false;
    prefixCodeChecker.reset();

    int encodeLength = 0;
    size_t j;
    for(j = 0; j < charCount; ++j)
    {
      char charactor;
      std::string encodeString;
      std::cin >> charactor >> encodeString;

      if(isError)
        continue;

      if(encodeString.size() >= charCount)
        isError = true;
      else if(!prefixCodeChecker.addAndCheckValid(encodeString))
        isError = true;
      else
        encodeLength += charactor2Frequency[charactor] * encodeString.size();
    }
    if(!isError && encodeLength == huffmanEncodeLength)
      std::cout << "Yes" << std::endl;
    else
      std::cout << "No" << std::endl;
  }
}
