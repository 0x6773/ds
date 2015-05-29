// stack.cpp
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

template<typename T>
struct Node
{
  T elem;
  unique_ptr<Node<T>> next = nullptr;
  Node (T _elem, unique_ptr<Node<T>> _pos)
  {
    elem = _elem;
    next = move(_pos);
  }
};

template<typename T>
class Stack
{
private:
  unique_ptr<Node<T>> ar;
  int _size = 0;
public:
  const int& Size() const
  {
    return _size;
  }
  bool Empty() const
  {
    return _size == 0;
  }
  const T& Top() const
  {
    assert(!this->Empty() && "Stack is Empty");
    return ar->elem;
  }
  void Push(T elem)
  {
    unique_ptr<Node<T>> newNode(new Node<T>(elem, move(ar)));
    ar = move(newNode);
    _size++;
  }
  void Pop()
  {
    assert(ar!=nullptr && "Stack is Empty");
    ar = move(ar->next);
    _size--;
  }
};

int main()
{
  Stack<int> st;

  st.Push(10);
  cout<<st.Top()<<" : "<<st.Size()<<'\n';
  st.Push(20);
  cout<<st.Top()<<" : "<<st.Size()<<'\n';
  st.Push(30);
  cout<<st.Top()<<" : "<<st.Size()<<'\n';

  st.Pop();
  cout<<st.Top()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<st.Top()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<"Stack Empty : "<<st.Size()<<'\n';

  return 0;
}
