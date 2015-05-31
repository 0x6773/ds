// binary_tree.cpp
#include <iostream>
#include <cassert>
#include <memory>
#include <string>

using namespace std;

template<typename T>
struct Node;

template<typename T>
bool operator ==(const Node<T>& n1, const Node<T>& n2)
{
  return &n1 == &n2;
}

template<typename T>
struct Node
{
  typedef shared_ptr<Node<T>> NodePtr;
  T elem;
  NodePtr parent;
  NodePtr left;
  NodePtr right;
  Node(T _elem)
    : elem(_elem),
      parent(nullptr),
      left(nullptr),
      right(nullptr)
  {}
  T& operator*()
  {
    return this->elem;
  }
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
    cout<<(*NodePtr).elem;
  return cout;
}

template<typename T>
class BTree
{
private:
  typedef shared_ptr<Node<T>> NodePtr;
  NodePtr root;
  int _size = 0;
public:
  BTree()
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
  NodePtr addRoot(T elem)
  {
    root.reset(new Node<T>(elem));
    ++_size;
    return root;
  }
  NodePtr addLeft(NodePtr node, T elem)
  {
    assert(root != nullptr && "No root found");
    assert(node->left == nullptr && "Left Node is not Null");
    node->left.reset(new Node<T>(elem));
    node->left->parent = node;
    ++_size;
    return node->left;
  }
  NodePtr addRight(NodePtr node, T elem)
  {
    assert(root != nullptr && "No root found");
    assert(node->right == nullptr && "Right Node is not Null");
    node->right.reset(new Node<T>(elem));
    node->right->parent = node;
    ++_size;
    return node->right;
  }
  NodePtr removeExternal(NodePtr node)
  {
    assert(node->isExternal() && "Cannot Remove External. Not External");
    assert(node != nullptr && "Nullptr found in removeExternal");
    auto parent = node->parent;
    auto sib = node->Sibling();
    if(parent->left == node)
      parent->left = sib;
    else
      parent->right = sib;
    return parent;
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
  BTree<string> bts;
  auto curr = bts.addRoot("Root");
  auto currLeft = bts.addLeft(curr, "Left1");
  auto currRight = bts.addRight(curr, "Right1");
  currRight = bts.addRight(currLeft, "Right1");
  bts.addLeft(currRight, "Left2");
  bts.inorder(bts.Root());
  return 0;
}
