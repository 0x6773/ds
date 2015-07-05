
#include "../stdafx.h"
#include "../first.hpp"

using namespace std;
using namespace std::literals;
using namespace mydetails;

namespace Trie
{
	//	Number of different elements data can have
#define SIZE 26
	template<typename T>
	struct node
	{
		//	Array of shared_ptr`s pointing to their childrens
		array<shared_ptr<node<T>>, SIZE> children;
		//	Check if Given node is also an End Point of Some element
		bool endPoint;

		//	Constructor for node<T>
		node()
			:endPoint(false)
		{
			for (auto& x : children)
				x = nullptr;
		}

		//	return a value between [0,SIZE) for a given Value of T
		size_t getPosition(T ch)
		{
			return (int(ch) - int('a'));	//	Implemented for T = char
			//return (int(ch) - int('0'));
		}

		//	return a value of T for a given value between [0,SIZE)
		T operator[](int i)
		{
			return char(int('a') + i);		//	Implemented for T = char
			//return char(int('0') + i);
		}
	};

	//	class Tries
	template < typename S, typename T = typename S::value_type >
	class Tries
	{
	private:
		//	node<T> for vertex
		node<T> vertex;

		//	Function/method to Add Node
		void addNodes(const S& s, shared_ptr<node<T>> curr, size_t i = 1)
		{
			if (s.size() == i)
			{
				curr->endPoint = true;
				return;
			}
			size_t pos = curr->getPosition(s[i]);
			if (curr->children[pos] == nullptr)
				curr->children[pos].reset(new node<T>());
			addNodes(s, curr->children[pos], i + 1);
		}

		// Function/Method to showall Elements
		void showall(S s, shared_ptr<node<T>> curr)
		{
			if (curr->endPoint)
				cout << s << endl;
			for (size_t i = 0; i < curr->children.size(); ++i)
			{
				if (curr->children[i] == nullptr)
					continue;
				else
				{
					s.push_back((*curr)[i]);
					showall(s, curr->children[i]);
				}
			}
		}

	public:

		//	Function initiator to add element
		void add(const S& s)
		{
			size_t pos = vertex.getPosition(s[0]);
			if (vertex.children[pos] == nullptr)
				vertex.children[pos].reset(new node<T>());
			addNodes(s, vertex.children[pos]);
		}

		//	Function initiator to showall elements
		void show()
		{
			for (size_t i = 0; i < vertex.children.size(); ++i)
			{
				if (vertex.children[i] != nullptr)
				{
					S ss = { vertex[i] };
					showall(ss, vertex.children[i]);
				}
			}
		}
	};
}

using namespace Trie;

int main()
{
	Tries<string> t;
	t.add("govind");
	t.add("sahai");
	t.show();
	return 0;
}
