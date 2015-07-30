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
  int idx(const Position& p) const
  {
    return p - ar.begin();
  }
public:
  BTreeVector()
  {
    ar.push_back(T());
  }
  int Size() const
  {
    return ar.size() - 1;
  }
  bool Empty() const
  {
    return Size() == 0;
  }
  Position Root()	      
  {
    assert(!this->Empty() && "No elements found");
    return ar.begin() + 1;
  }
  Position Last()
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
  Position Left(const Position& p)
  {
    assert(hasLeft(p) && "Left child not found");
    return ar.begin() + 2 * idx(p);
  }
  bool hasRight(const Position& p) const
  {
    return 2 * idx(p) + 1 <= Size();
  }
  Position Right(const Position& p)
  {
    assert(hasRight(p) && "Right child not found");
    return ar.begin() + 2 * idx(p) + 1;
  }
  Position Parent(const  Position& p)
  {
    int curr = idx(p);
    int res = curr / 2;
    assert(res > 0 && "No parent found");
    return ar.begin() + res;
  }
  void addLast(const T& elem)
  {
    ar.push_back(elem);
  }
  void removeLast()
  {
    ar.pop_back();
  }
  void Swap(const Position& p, const Position& q)
  {
    swap(*p, *q);
  }
};

int main2()
{
  return 0;
}
