// priorityQueue.cpp
// Uses binaryTreeVector
#include "../binaryTreeVector/binaryTreeVector.cpp"
#include <string>

using namespace std;

template<typename T,
	 typename C = less<T>,
  	 typename Cont = vector<T>>
class heapPriorityQueue
{
private:
  BTreeVector<T, Cont> ar;
  C comp = C();
  typedef decltype(ar.Root()) Position;
public:
  heapPriorityQueue() { }
  int Size() const
  {
    return ar.Size();
  }
  bool Empty() const
  {
    return Size() == 0;
  }
  const T& Min()
  {
    return *(ar.Root());
  }
  void Insert(const T& elem)
  {
    ar.addLast(elem);
    Position it = ar.Last();
    while(!ar.isRoot(it))
    {
      Position it2 = ar.Parent(it);
      if(!comp(*it, *it2))
	break;
      ar.Swap(it, it2);
      it = it2;
    }
  }
  void removeMin()
  {
    if(Size() == 1)
      ar.removeLast();
    else
    {
      Position it = ar.Root();
      ar.Swap(it, ar.Last());
      ar.removeLast();
      while(ar.hasLeft(it))
      {
	Position it2 = ar.Left(it);
	if(ar.hasRight(it) && comp(*(ar.Right(it)), *it2))
	  it2 = ar.Right(it);
	if(comp(*it2, *it))
	{
	  ar.Swap(it, it2);
	  it = it2;
	}
	else
	  break;
      }
    }
  }
};

int main()
{
  heapPriorityQueue<string> hpq;
  hpq.Insert("Govind"s);
  hpq.Insert("Sahai"s);
  cout<<hpq.Min()<<endl;
  
  heapPriorityQueue<string, greater<string>> hpq2;
  hpq2.Insert("Govind"s);
  hpq2.Insert("Sahai"s);
  cout<<hpq2.Min()<<endl;
  
  return 0;
}
