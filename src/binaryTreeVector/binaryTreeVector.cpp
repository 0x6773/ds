// binaryTreeVector.cpp
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template<typename T,
	 typename Cont = vector<T>>
class BTreeVector
{
private:
  typedef typename Cont::iterator Position;
  Cont ar;
  int idx(const Position& p)
  {
    return distance(ar.begin(), p);
  }
public:
  BTreeVector()
  {
    ar.push_back(0);
  }
  int Size() const
  {
    return ar.size() - 1;
  }
  bool Empty() const
  {
    return Size() == 0;
  }
  Position Root() const
  {
    assert(!this->Empty() && "No elements found");
    return ar.begin() + 1;
  }
  Position Last() const
  {
    assert(!this->Empty() && "No elements found");
    return ar.end() - 1;
  }
  bool isRoot(const Position& p) const
  {
    return idx(p) == 1;
  }
  bool hasLeft(const Position& p) const
  {
    return 2 * idx(p) <= Size();
  }
  Position Left(const Position& p) const
  {
    assert(hasLeft(p) && "Left child not found");
    return 2 * idx(p);
  }
  bool hasRight(const Position& p) const
  {
    return 2 * idx(p) + 1 <= Size();
  }
  Position Right(const Position& p) const
  {
    assert(hasRight(p) && "Right child not found");
    return 2 * idx(p) + 1; 
  }
  Position Parent(const  Position& p) const
  {
    int curr = idx(p);
    int res = curr / 2;
    assert(res > 0 && "No parent found");
    return res;
  }
  void addLast(const T& elem)
  {
    ar.push_back(elem);
  }
  void removeLast()
  {
    ar.pop_back();
  }
  void swap(const Position& p, const Position& q)
  {
    swap(*p, *q);
  }
};

int main2()
{
  
  return 0;
}
