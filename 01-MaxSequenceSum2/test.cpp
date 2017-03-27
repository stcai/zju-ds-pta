#include <iostream>

class MaxSequenceSumCal
{
 public:
  MaxSequenceSumCal():
      maxSum_(0),
      curSum_(0),
      subSequenceFirst_(0),
      subSequenceLast_(0),
      sequenceFirst_(0),
      curFirst_(0),
      curLast_(0),
      isBegin_(true),
      NeedSetCurFirst_(true),
      isAllNegative_(true)
  {}

  void push(int n)
  {
    curSum_ += n;
    curLast_ = n;

    if(n >= 0)
      isAllNegative_ = false;

    if(isBegin_)
    {
      sequenceFirst_ = n;
      isBegin_ = false;
    }

    if(NeedSetCurFirst_)
    {
      curFirst_ = n;
      NeedSetCurFirst_ = false;
    }

    if(curSum_ < 0)
    {
      curSum_ = 0;
      NeedSetCurFirst_ = true;
    }
    else if(curSum_ > maxSum_)
    {
      maxSum_ = curSum_;
      subSequenceFirst_ = curFirst_;
      subSequenceLast_ = curLast_;
    }
  }

  void finish()
  {
    if(isAllNegative_)
    {
      subSequenceFirst_ = sequenceFirst_;
      subSequenceLast_ = curLast_;
    }
  }

  int getMaxSum()const { return maxSum_; }
  int getSubSequenceFrist()const { return subSequenceFirst_; }
  int getSubSequenceLast()const { return subSequenceLast_; }

 private:
  int maxSum_;
  int curSum_;
  int subSequenceFirst_;
  int subSequenceLast_;

  int sequenceFirst_;
  int curFirst_;
  int curLast_;
  bool isBegin_;
  bool NeedSetCurFirst_;
  bool isAllNegative_;
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
  cal.finish();

  std::cout << cal.getMaxSum() << " " << cal.getSubSequenceFrist() << " " << cal.getSubSequenceLast() << std::endl;
}
