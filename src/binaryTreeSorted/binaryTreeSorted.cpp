// binaryTreeSorted.cpp
#include <iostream>
#include <cassert>
#include <memory>

using namespace std;

template<typename T>
struct Node
{
public:
  T elem;
private:
  typedef shared_ptr<Node<T>> NodePtr;
  NodePtr parent;
  NodePtr left;
  NodePtr right;
  
public:
  Node(T _elem)
    : elem(_elem),
      parent(nullptr),
      left(nullptr),
      right(nullptr)
  {}   
  bool isRoot() const
  {
    return this->parent == nullptr;
  }
  bool isExternal() const
  {
    return this->left == nullptr &&
      this->right == nullptr;
  }
  bool hasSibling() const
  {
    if(this->parent != nullptr)
      return this->parent->left != nullptr &&
	this->parent->right != nullptr;
    return false;
  }
  NodePtr& Left(const bool chk = true)
  {
    if(chk)
      assert(this->left != nullptr && "Left Child not found");
    return this->left;
  }
  NodePtr& Right(const bool chk = true)
  {
    if(chk)
      assert(this->right != nullptr && "Right Child not found");
    return this->right;
  }
  NodePtr& Sibling()
  {
    assert(!isRoot() && "Root has no Sibling");
    assert(hasSibling() && "Given Node has no Sibling");
    if(*this == *this->parent->left)
      return this->parent->right;
    else
      return this->parent->left;
  }
  NodePtr& Parent()
  {
    assert(this->parent != nullptr && "Parent of Root not found");
    return this->parent;
  }
};

template<typename T> ostream&
operator<<(ostream& cout, const shared_ptr<Node<T>>& NodePtr)
{
  if(NodePtr == nullptr)
    cout<<"<null>";
  else
    cout<<NodePtr->elem;
  return cout;
}

template<typename T,
	 typename C = less<T>,
	 bool repeat = true>
class BTreeSorted
{
private:
  typedef shared_ptr<Node<T>> NodePtr;
  NodePtr root;
  int _size;
  C comp = C();
  
  tuple<NodePtr, NodePtr, bool>
  TreeSearch(T elem, NodePtr node, NodePtr nodePar) const
  {
    if(node == nullptr)
      return make_tuple(node, nodePar, false);
    else if(elem == node->elem)
      return make_tuple(node, nodePar, true);
    else if(comp(elem, node->elem))
      return TreeSearch(elem, node->Left(false), node);
    else
      return TreeSearch(elem, node->Right(false), node);
  }    
public:
  BTreeSorted()
    : root(nullptr),
      _size(0)
  {}
  int Size() const
  {
    return _size;
  }
  bool Empty() const
  {
    return _size == 0;
  }
  NodePtr Root() const
  {
    assert(root != nullptr && "No root found");
    return root;
  }
  NodePtr Add(T elem)
  {
    auto pos = TreeSearch(elem, root, root);
    if(repeat)
      while(get<2>(pos))
	pos = TreeSearch(elem, get<0>(pos)->Right(false), get<0>(pos));
    else if(get<2>(pos))
      return get<0>(pos);
    NodePtr node = get<0>(pos);
    NodePtr nodePar = get<1>(pos);
    if(root == nullptr)
    {
      root.reset(new Node<T>(elem));
      return node;
    }
    else
    {	
	if(comp(elem, nodePar->elem))
	{
	  nodePar->Left(false).reset(new Node<T>(elem));
	  node = nodePar->Left();
	}
	else
	{
	  nodePar->Right(false).reset(new Node<T>(elem));
	  node = nodePar->Right();
	}
    }      
    return node;
  }
  bool Contains(T elem) const
  {
    if(!Empty())
      return false;
    return get<2>(TreeSearch(elem, root, root));
  }  
  void preorder(NodePtr node, int x = 0)
  {
    for(int i = 0; i < x; ++i)
      cout<<"|  ";
    cout<<"|--"<<node<<endl;
    if(node != nullptr)
    {
      preorder(node->Left(false), x + 1);
      preorder(node->Right(false), x + 1);
    }
    return;
  }
  void inorder(NodePtr node, int x = 0)
  {
    if(node != nullptr)
    {
      inorder(node->Left(false), x + 1);
    }
    for(int i = 0; i < x; ++i)
      cout<<"|  ";
    cout<<"|--"<<node<<endl;
    if(node != nullptr)
    {
      inorder(node->Right(false), x + 1);
    }
    return;
  }
  void inorderReverse(NodePtr node, int x = 0)
  {
    if(node != nullptr)
    {
      inorderReverse(node->Right(false), x + 1);
    }
    for(int i = 0; i < x; ++i)
      cout<<"|  ";
    cout<<"|--"<<node<<endl;
    if(node != nullptr)
    {
      inorderReverse(node->Left(false), x + 1);
    }
    return;
  }
  void postorder(NodePtr node, int x = 0)
  {
    if(node != nullptr)
    {
      postorder(node->Left(false), x + 1);
      postorder(node->Right(false), x + 1);
    }
    for(int i = 0; i < x; ++i)
      cout<<"|  ";
    cout<<"|--"<<node<<endl;
    return;
  }
};

int main()
{
  BTreeSorted<int,less<int>,false> sbt;
  sbt.Add(50);
  sbt.Add(10);
  sbt.Add(30);
  sbt.Add(60);
  sbt.Add(10);
  sbt.Add(40);
  sbt.Add(10);
  sbt.Add(60);
  sbt.Add(55);
  sbt.Add(50);
  sbt.Add(50);

  sbt.inorderReverse(sbt.Root());
  cout<<boolalpha<<sbt.Contains(10)<<endl;
  cout<<boolalpha<<sbt.Contains(0);
  return 0;
}
