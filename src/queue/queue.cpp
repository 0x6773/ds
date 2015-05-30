// queue.cpp
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
  {
    elem = _elem;
    next = nullptr;
  }
};

template<typename T>
class Queue
{
private:
  shared_ptr<Node<T>> front;
  shared_ptr<Node<T>> back;
  int _size = 0;
public:
  Queue() : front(nullptr), back(nullptr)
  {}
  int Size() const
  {
    return _size;
  }
  bool Empty() const
  {
    return _size == 0;
  }
  const T& Front() const
  {
    assert(!this->Empty() && "Queue is Empty");
    return front->elem;
  }
  const T& Back() const
  {
    assert(!this->Empty() && "Queue is Empty");
    return back->elem;
  }
  void Push(T elem)
  {
    shared_ptr<Node<T>> newNode(new Node<T>(elem));
    if(front == nullptr)
    {
      front = newNode;
      back = newNode;
    }
    else
    {
      front->next = newNode;
      front = newNode;
    }
    ++_size;
  }
  void Pop()
  {
    assert(!this->Empty() && "Queue is Empty");
    back = back->next;
    --_size;
  }
};
int main()
{
  Queue<int> st;
  
  st.Push(10);
  cout<<"Pushed"<<endl;
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.Push(20);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.Push(30);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
 
  st.Pop();
  cout<<st.Front()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<st.Front()<<" : "<<st.Size()<<'\n';
  st.Pop();
  cout<<"Stack Empty : "<<st.Size()<<'\n';
  
  return 0;
}
