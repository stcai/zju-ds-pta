#include <iostream>

class Set
{
 public:
  typedef int ElementType;

  Set(int capacity);

  void combine(ElementType e1, ElementType e2);
  ElementType find(ElementType e);
  int getComponetCount();

 private:
  ElementType *s_;
  int capacity_;
};

Set::Set(int capacity)
    :capacity_(capacity)
{
  s_ = new ElementType[capacity];
  for(int i = 0; i < capacity; ++i)
    s_[i] = -1;
}

void Set::combine( ElementType e1, ElementType e2 )
{
  ElementType r1 = find(e1);
  ElementType r2 = find(e2);

  if(r1 != r2)
  {
    if(s_[r1] < s_[r2])
    {
      s_[r1] += s_[r2];
      s_[r2] = r1;
    }
    else
    {
      s_[r2] += s_[r1];
      s_[r1] = r2;
    }
  }
}

Set::ElementType Set::find(ElementType e)
{
  if(s_[e] < 0)
    return e;
  else
    return s_[e] = find(s_[e]);
}

int Set::getComponetCount()
{
  int result = 0;
  for(int i = 0; i < capacity_; ++i)
  {
    if(s_[i] < 0)
      ++result;
  }
  return result;
}

//----------------------------------------------------
int main()
{
  int numberOfComputers;
  std::cin >> numberOfComputers;
  Set set(numberOfComputers);

  while(true)
  {
    char operation;
    std::cin >> operation;

    if(operation == 'C')
    {
      Set::ElementType c1, c2;
      std::cin >> c1 >> c2;
      if(set.find(c1) == set.find(c2))
        std::cout << "yes" << std::endl;
      else
        std::cout << "no" << std::endl;
    }
    else if(operation == 'I')
    {
      Set::ElementType c1, c2;
      std::cin >> c1 >> c2;
      set.combine(c1, c2);
    }
    else
      break;
  }

  int count = set.getComponetCount();
  if(count == 1)
    std::cout << "The network is connected." << std::endl;
  else
    std::cout << "There are " << count << " components." << std::endl;
}
