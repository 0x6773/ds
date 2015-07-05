// deque.cpp
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

template<typename T>
struct Node
{
  T elem;
  shared_ptr<Node<T>> next;
  shared_ptr<Node<T>> prev;
  Node(T _elem)
  {
    elem = _elem;
    next = nullptr;
    prev = nullptr;
  }
};

template<typename T>
class Deque
{
private:
  shared_ptr<Node<T>> front;
  shared_ptr<Node<T>> back;
  int _size = 0;
public:
  Deque()
    : front(nullptr), back(nullptr)
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
    assert(!this->Empty() && "Deque is Empty");
    return front->elem;
  }
  const T& Back() const
  {
    assert(!this->Empty() && "Deque is Empty");
    return back->elem;
  }
  void PushFront(T elem)
  {
    shared_ptr<Node<T>> newNode(new Node<T>(elem));
    if(front == nullptr)
    {
      front = newNode;
      back = front;
    }
    else
    {
      front->next = newNode;
      newNode->prev = front;
      front = newNode;
    }
    ++_size;
  }
  void PushBack(T elem)
  {
    shared_ptr<Node<T>> newNode(new Node<T>(elem));
    if(back == nullptr)
    {
      back = newNode;
      front = back;
    }
    else
    {
      back->prev = newNode;
      newNode->next = back;
      back = newNode;
    }
    ++_size;
  }
  void PopFront()
  {
    assert(!this->Empty() && "Deque is Empty");
    front = front->prev;
    --_size;
  }
  void PopBack()
  {
    assert(!this->Empty() && "Deque is Empty");
    back = back->next;
    --_size;
  }
};

int main()
{
  Deque<int> st;
  
  st.PushFront(10);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PushFront(20);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PushFront(30);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PushBack(40);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PushBack(50);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PushBack(60);
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
 
  st.PopFront();
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PopFront();
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PopFront();
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PopBack();
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PopFront();
  cout<<st.Front()<<" : "<<st.Back()<<" : "<<st.Size()<<'\n';
  st.PopBack();
  cout<<"Deque Empty : "<<st.Size()<<'\n';
  
  return 0;
}

  
