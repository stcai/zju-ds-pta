#include <iostream>
#include <limits>

typedef int DataType;

class MinHeap
{
 public:
  typedef size_t size_type;

  MinHeap(size_type capacity)
      : size_(0)
      , capacity_(capacity)
  {
    data_ = new DataType[capacity + 1];
    data_[0] = std::numeric_limits<DataType>::min();
  }
  ~MinHeap()
  {
    if(data_)
      delete[] data_;
  }

  void insert(DataType data);
  void dumpPathFromIndex(size_type index, std::ostream& out);

 private:
  DataType *data_;
  size_type size_;
  size_type capacity_;
};

void MinHeap::insert(DataType data)
{
  ++size_;

  size_t childIndex = size_;
  size_t parentIndex = childIndex / 2;
  while(data_[parentIndex] > data)
  {
    data_[childIndex] = data_[parentIndex];

    childIndex = parentIndex;
    parentIndex = childIndex / 2;
  }
  data_[childIndex] = data;
}

void MinHeap::dumpPathFromIndex( size_type index, std::ostream &out )
{
  for(size_type i = index; i > 0; i /= 2)
  {
    if(i != index)
      out << " ";

    out << data_[i];
  }
  out << std::endl;
}

//----------------------------------------------------
int main()
{
  int elementCount, pathToPrintCount;
  std::cin >> elementCount >> pathToPrintCount;

  MinHeap heap(elementCount);
  for(int i = 0; i < elementCount; ++i)
  {
    DataType data;
    std::cin >> data;
    heap.insert(data);
  }

  for(int i = 0; i < pathToPrintCount; ++i)
  {
    MinHeap::size_type index;
    std::cin >> index;
    heap.dumpPathFromIndex(index, std::cout);
  }
}
