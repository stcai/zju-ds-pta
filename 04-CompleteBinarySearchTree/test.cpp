                                                \
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class CompleteBianrySearchTree
{
 public:
  typedef std::vector<int> typeArray;

  CompleteBianrySearchTree(const typeArray& array)
  {
    a_.resize(array.size());
    arrange(array, 0, array.size() - 1, 0);
  }

  void levelOrderTraversal(std::ostream& out)
  {
    for(typeArray::const_iterator it = a_.begin(); it != a_.end(); ++it)
    {
      if(it != a_.begin())
        out << " ";

      out << *it;
    }
    out << std::endl;
  }

 private:
  typedef typeArray::size_type size_type;

  void arrange(const typeArray& array, size_type arrayLeftIndex, size_type arrayRightIndex, size_type treeRootIndex)
  {
    size_type nodeCount = arrayRightIndex - arrayLeftIndex + 1;
    if(nodeCount == 0)
      return;

    size_type leftTreeNodeCount = getLeftTreeNodeCount(nodeCount);
    size_type arrayRootIndex = arrayLeftIndex + leftTreeNodeCount;
    a_[treeRootIndex] = array[arrayRootIndex];
    size_type leftTreeRoot = treeRootIndex * 2 + 1;
    size_type rightTreeRoot = treeRootIndex * 2 + 2;
    arrange(array, arrayLeftIndex, arrayRootIndex - 1, leftTreeRoot);
    arrange(array, arrayRootIndex + 1, arrayRightIndex, rightTreeRoot);
  }

  size_type getLeftTreeNodeCount(size_type nodeCount)
  {
    // size_type hight = static_cast<size_type>(log2(nodeCount + 1));
    size_type hight = 0;
    size_type nodeCountPlusOne = nodeCount + 1;
    while(nodeCountPlusOne >>= 1) ++hight;

    size_type x1 = nodeCount - (1 << hight) + 1;
    size_type x2 = (1 << (hight - 1));
    return std::min(x1, x2) + (1 << (hight - 1)) - 1;
  }

  typeArray a_;
};

//----------------------------------------------------
int main()
{
  std::vector<int> array;
  std::vector<int>::size_type n;
  std::cin >> n;
  array.reserve(n);
  for (std::vector<int>::size_type i = 0; i < n; ++i)
  {
    int data;
    std::cin >> data;
    array.push_back(data);
  }
  std::sort(array.begin(), array.end());

  CompleteBianrySearchTree tree(array);
  tree.levelOrderTraversal(std::cout);

  return 0;
}
