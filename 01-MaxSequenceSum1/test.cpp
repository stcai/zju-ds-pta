#include <iostream>

class MaxSequenceSumCal
{
 public:
  MaxSequenceSumCal():
      maxSum_(0),
      curSum_(0)
  {}

  void push(int n)
  {
    curSum_ += n;
    if(curSum_ > maxSum_)
      maxSum_ = curSum_;
    else if(curSum_ < 0)
      curSum_ = 0;
  }
  int getMaxSum(){ return maxSum_; }

 private:
  int maxSum_;
  int curSum_;
};

int main()
{
  MaxSequenceSumCal cal;

  size_t num = 0;
  std::cin >> num;
  for(size_t i = 0; i < num; ++i)
  {
    int n;
    std::cin >> n;
    cal.push(n);
  }

  std::cout << cal.getMaxSum() << std::endl;
}
