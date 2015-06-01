// binaryTreeSorted.cpp
#include <iostream>
#include <cassert>
#include <memory>

using namespace std;

template<typename T>
struct Node
{
  T elem;
  typedef shared_ptr<Node<T>> NodePtr;
  NodePtr parent;
  NodePtr left;
  NodePtr right;
  Node(T _elem)
    : elem(_elem),
      parent(nullptr),
      left(nullptr),
      right(nullptr)
  {}   
  bool isRoot() const
  {
    return parent == nullptr;
  }
  bool isExternal() const
  {
    return left == nullptr &&
      right == nullptr;
  }
  bool hasSibling() const
  {
    return this->parent->left != nullptr &&
      this->parent->right != nullptr;
  }
  NodePtr Left(const bool chk = true) const
  {
    if(chk)
      assert(this->left != nullptr && "Left Child not found");
    return this->left;
  }
  NodePtr Right(const bool chk = true) const
  {
    if(chk)
      assert(this->right != nullptr && "Right Child not found");
    return this->right;
  }
  NodePtr Sibling() const
  {
    assert(!isRoot() && "Root has no Sibling");
    assert(hasSibling() && "Given Node has no Sibling");
    if(*this == *this->parent->left)
      return this->parent->right;
    else
      return this->parent->left;
  }
  NodePtr Parent() const
  {
    assert(this->parent != nullptr && "Parent of Root not found");
    return this->parent;
  }
};

template<typename T>
ostream& operator<<(ostream& cout, const shared_ptr<Node<T>>& NodePtr)
{
  if(NodePtr == nullptr)
    cout<<"<null>";
  else
    cout<<NodePtr->elem;
  return cout;
}

template<typename T,
	 typename C = less<T>>
class BTreeSorted
{
private:
  typedef shared_ptr<Node<T>> NodePtr;
  NodePtr root;
  int _size = 0;
  C comp = C();
  
  tuple<NodePtr, NodePtr, bool> TreeSearch(T elem, NodePtr node, NodePtr nodePar) const
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
    : root(nullptr)
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
  NodePtr add(T elem)
  {
    auto pos = TreeSearch(elem, root, root);
    while(get<2>(pos))
      pos = TreeSearch(elem, get<0>(pos)->Right(false), get<0>(pos));
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
	  nodePar->left.reset(new Node<T>(elem));
	  node = nodePar->left;
	}
	else
	{
	  nodePar->right.reset(new Node<T>(elem));
	  node = nodePar->right;
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
  BTreeSorted<int> sbt;
  sbt.add(50);
  sbt.add(10);
  sbt.add(30);
  sbt.add(60);
  sbt.add(10);
  sbt.add(40);
  sbt.add(10);
  sbt.add(60);
  sbt.add(55);
  sbt.add(50);
  sbt.add(50);

  sbt.inorderReverse(sbt.Root());
  cout<<boolalpha<<sbt.Contains(10)<<endl;
  cout<<boolalpha<<sbt.Contains(0);
  return 0;
}
