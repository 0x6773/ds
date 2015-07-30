#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct Node
{
	shared_ptr<Node<T>> prev;
	T elem;
	shared_ptr<Node<T>> next;
	Node(T _elem)
		: prev(nullptr), next(nullptr), elem(_elem)
	{ }
};

template<typename T>
class LinkedList
{
private:
	shared_ptr<Node<T>> head;
	shared_ptr<Node<T>> last;
public:
	LinkedList()
		: head(nullptr), last(nullptr)
	{ }
	shared_ptr<Node<T>>& Head() { return head; }
	shared_ptr<Node<T>>& Last() { return last; }
	void add(const T& _elem)
	{
		if (last == nullptr)
		{
			head.reset(new Node<T>(_elem));
			last = head;
		}
		else
		{
			last->next.reset(new Node<T>(_elem));
			last->next->prev = last;
			last = last->next;
		}
	}
	void remove(shared_ptr<Node<T>> sptr)
	{
		sptr->prev->next = sptr->next;
		sptr->next->prev = sptr->prev;
	}
	void checkAll()
	{
		if (last == nullptr)
		{
			assert(head == nullptr);
			return;
		}
		shared_ptr<Node<T>> curr = head->next;
		assert(head->prev == nullptr);
		while (curr != last)
		{
			assert(curr->prev != nullptr);
			assert(curr->next != nullptr);
			curr = curr->next;
		}
		assert(last->next == nullptr);
	}
	void showAll()
	{
		shared_ptr<Node<T>> curr = head;
		while (curr != nullptr)
		{
			cout << curr->elem << " ";
			curr = curr->next;
		}
		cout << endl;
	}
	void reset()
	{
		head.reset();
		last.reset();
	}
};

template<typename T>
void mergeLinkedList(LinkedList<T>& lkd1, LinkedList<T>& lkd2)
{
	lkd1.Last()->next = lkd2.Head();
	lkd2.Head()->prev = lkd1.Last();
	lkd1.Last() = lkd2.Last();
	lkd2.reset();
}

int main()
{
	cout << boolalpha;
	_CRT_MEMORY_CHECK_AT_EXIT;

	LinkedList<int> ar;
	LinkedList<int> br;

	for (int i = 0; i < 10; ++i)
	{
		ar.add(i);
		br.add(i * 10);
	}

	ar.checkAll();
	ar.showAll();
	br.checkAll();
	br.showAll();

	mergeLinkedList(ar, br);

	ar.checkAll();
	ar.showAll();
	br.checkAll();
	br.showAll();

	return 0;
}

