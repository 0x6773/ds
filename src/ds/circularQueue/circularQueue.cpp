// Circular_Queue.cpp
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

template<typename T>
struct Node
{
  T elem;
  shared_ptr<Node<T>> next;
  Node(T _elem)
    : elem(_elem), next(nullptr)
  {}  
};

template<typename T>
class CircularQueue
{
private:
  shared_ptr<Node<T>> curr;
  int _size = 0;
public:
  CircularQueue()
    : curr(nullptr)
  {}
  int Size() const
  {
    return _size;
  }
  bool Empty() const
  {
    return _size == 0;
  }
  const T& Current() const
  {
    assert(!this->Empty() && "Circular-Queue is Empty");
    return curr->elem;
  }
  void Rotate(int rt)
  {
    assert(!this->Empty() && "Circular-Queue is Empty");
    assert(rt>0 && "Cannot Rotate in Opposite direction");
    while(rt--)
    {
      curr = curr->next;
    }    
  }
  void Push(T elem)
  {
    shared_ptr<Node<T>> newNode(new Node<T>(elem));
    if(curr == nullptr)
    {
      curr = move(newNode);
      curr->next = curr;
    }
    else
    {
      newNode->next = curr->next;
      curr->next = newNode;
      curr = move(newNode);
    }
    ++_size;
  }
  void Pop()
  {
    assert(!this->Empty() && "Circular-Queue is Empty");
    curr->next = curr->next->next;
    --_size;
  }
};

int main()
{
  CircularQueue<int> st;
  
  st.Push(10);
  cout<<st.Current()<<" : "<<st.Size()<<'\n';
  st.Push(20);
  cout<<st.Current()<<" : "<<st.Size()<<'\n';
  st.Push(30);
  cout<<st.Current()<<" : "<<st.Size()<<'\n';

  st.Rotate(2);
  st.Pop();
  cout<<st.Current()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<st.Current()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<"Circular-Queue Empty : "<<st.Size()<<'\n';

  return 0;
}
