#include <iostream>
#include <vector>
#include <stack>

class FixedSizeStack
{
 public:
  FixedSizeStack(size_t sizeLimit):
      sizeLimit_(sizeLimit)
  {}

  bool push(size_t i)
  {
    if(stack_.size() >= sizeLimit_)
      return false;

    stack_.push(i);
    return true;
  }
  void pop()
  {
    stack_.pop();
  }
  size_t top()
  {
    return stack_.top();
  }
  bool empty()
  {
    return stack_.empty();
  }

 protected:
  std::stack<size_t> stack_;
  size_t sizeLimit_;
};

class ElementGenerator
{
 public:
  ElementGenerator(size_t elementLimit)
      :element_(1),
       elementLimit_(elementLimit) {}

  bool gen(size_t& element)
  {
    if(element_ > elementLimit_)
      return false;

    element = element_++;
    return true;
  }

 protected:
  size_t element_;
  size_t elementLimit_;
};

bool checkPopSequece(const std::vector<size_t>& sequence, FixedSizeStack& stack)
{
  ElementGenerator elementGenerator(sequence.size());
  std::vector<size_t>::const_iterator it = sequence.begin();
  size_t element;
  while(true)
  {
    if(!elementGenerator.gen(element))
      break;

    if(!stack.push(element))
      break;

    while(!stack.empty() && it != sequence.end() && stack.top() == *it)
    {
      stack.pop();
      ++it;
    }
  }

  return it == sequence.end();
}

void readAndCheckPopSequence()
{
  size_t stackSize, sequenceSize, n;
  std::cin >> stackSize >> sequenceSize >> n;

  std::vector<size_t> sequence;
  sequence.reserve(sequenceSize);
  for(size_t i = 0; i < n; ++i)
  {
    FixedSizeStack stack(stackSize);
    for(size_t j = 0; j < sequenceSize; ++j)
    {
      int num;
      std::cin >> num;
      sequence.push_back(num);
    }

    if(checkPopSequece(sequence, stack))
      std::cout << "YES" << std::endl;
    else
      std::cout << "NO" << std::endl;

    sequence.clear();
  }
}

int main()
{
  readAndCheckPopSequence();
  return 0;
}
