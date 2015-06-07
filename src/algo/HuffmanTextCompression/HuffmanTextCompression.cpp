// HuffmanTextCompression

#define HUFFMAN_BT
#define INCLUDE_ALL
#include "/home/mnciitbhu/Codes/stdafx.h"
#include "/home/mnciitbhu/Codes/first.hpp"
#include "../../ds/binaryTreeSorted/binaryTreeSorted.cpp"

using namespace std;
using namespace mydetails;

class Huffman
{
protected:
  typedef shared_ptr<Node<pair<char, size_t>>> NodePtr;
  typedef Node<pair<char, size_t>> NPCS;
  NodePtr root;
  string istr;
  string ostr;  
  Huffman(string _str)
    : istr(_str)
  {}  
};

class HuffmanComparer
{
public:
  typedef shared_ptr<Node<pair<char, size_t>>> NodePtr;
  typedef Node<pair<char, size_t>> NPCS;
  
  bool operator()( NodePtr& x1, NodePtr& x2)
  {
    return (x1->elem).second > (x2->elem).second;
  };
};

class HuffmanCompress : protected Huffman
{
private:
  unordered_map<char, size_t> freq;
  void getFreq()
  {
    for(const char& ch : istr)
      freq[ch]++;
  }
public:
  HuffmanCompress(string _str)
    : Huffman(_str)
  {}
  
  void Compress()
  {
    getFreq();
    priority_queue<NodePtr, vector<NodePtr>, HuffmanComparer> pq;
    for(const auto& pr : freq)
    {
      NodePtr newNode(new NPCS({pr.first, pr.second}));
      pq.push(newNode);
    }
    while(pq.size() > 1)
    {
      size_t f1 = (pq.top()->elem).second;
      NodePtr t1 = pq.top();
      pq.pop();
      size_t f2 = (pq.top()->elem).second;
      NodePtr t2 = pq.top();
      pq.pop();
      NodePtr newNode(new NPCS({' ', f1 + f2}));
      newNode->Left(false) = t1;
      newNode->Right(false) = t2;
      pq.push(newNode);
    }
    root = pq.top();
    pq.pop();
  }
  void inorderReverse(NodePtr node, int x = 0)
  {
    if(node == nullptr)
      return;
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
  void print()
  {
    inorderReverse(root);
  }
};

int main()
{
  HuffmanCompress hfc("Indian Institute of Technology, Banaras Hindi University, Varanasi, UP - 221005, India, Asia, Earth :)");
  hfc.Compress();
  hfc.print();
  return 0;
}
