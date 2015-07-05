#pragma once

#include "stdafx.h"
#include "First.hpp"

using namespace std;
using namespace mydetails;

/*
	How to Use :

	Edit Node<T>, Node<T>.setValue() and Node<T>.merge() as required.

	Create and object of SegmentTree<T> with a Constructor of 1 - based vector<T>
	query and update as required.

	EVERYTHING IS 1 - BASED. NEVER TRY TO USE 0 - BASED. EVEN WHILE QUERYING OR UPDATING.
*/

namespace SegTree
{
	template<typename T>
	struct Node;

	template<typename T>
	class SegmentTree;

	//	Node of Segment Tree
	template<typename T>
	struct Node
	{
		//	Elements required in Node<T>
		T x;

		// Declaring Segment<T> as friend class of Node<T>
		friend class SegmentTree<T>;

		/*
			Node<T>::Node()
				A default Constructor for Node<T>.
				Edit it so that it will behave as identity for Node<T>::merge()
		*/
		Node()
			: x(0)
		{}

	private:
		/*
			Node<T>::setValue()
				Edit Parameters and function as required.
				To set Values elements of Node<T>.
		*/
		void setValue(T _X)
		{
			x = _X;
		}

		/*
			Node<T>::merge()
				Edit funtion Only not parameters.
				Merge child Node<T>s to Parent Node<T>.
		*/
		void merge(const Node<T>& n1, const Node<T>& n2)
		{
			x = n1.x + n2.x;
		}
	};

	//Class SegTree
	template<typename T>
	class SegmentTree
	{
	private:

		//	A vector to store Segment Tree
		vector<Node<T>> ar;
		//	Number of elements of vector - 1
		size_t elem;

		/*
			Segment<T>::build()
				Function/Method to Build Segment Tree from input vector<T>.
				Initially:
					NodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					mnciitbhuar = Input Vector

			Complexity : O(nlog2n)
		*/
		void build(int NodeNumber, int i, int j, const vector<T>& mnciitbhuar)
		{
			if (i == j)
			{
				ar[NodeNumber].setValue(mnciitbhuar[i]);
				return;
			}
			int left = NodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			build(left, i, mid, mnciitbhuar);
			build(right, mid + 1, j, mnciitbhuar);
			ar[NodeNumber].merge(ar[left], ar[right]);
		}

		/*
			SegmentTree<T>::update / Edit funtion
				Function/Method to edit a value at position k to value newValue
				Initially:
					NodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					k = Position whose value to be changed
					newValue = New Value at k Position

			Complexity : O(log2n)
		*/
		void update(int NodeNumber, int i, int j, int k, T newValue)
		{
			if (i == j)
			{
				if (i == k)
					ar[NodeNumber].setValue(newValue);
				return;
			}
			int left = NodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			if (k <= mid)
				update(left, i, mid, k, newValue);
			else
				update(right, mid + 1, j, k, newValue);
			ar[NodeNumber].merge(ar[left], ar[right]);
		}

		/*
			SegmentTree<T>::query
				Function/Method to query between ri and rj.
				According to they are merge.
				Initially:
					NodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					ri = Left Value of Interval
					rj = Right Value of Interval

			Complexity = O(log2n)
		*/
		const Node<T> query(size_t NodeNumber, int i, int j, const int& ri, const int& rj)
		{
			if (j<ri || i>rj)
				return Node<T>();
			if (ri <= i && rj >= j)
				return ar[NodeNumber];
			int left = NodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			auto q1 = query(left, i, mid, ri, rj);
			auto q2 = query(right, mid + 1, j, ri, rj);
			Node<T> temp;
			temp.merge(q1, q2);
			return temp;
		}

	public:
		/*
			SegmentTree<T>::SegmentTree() Constructor
			Takes one argument as 1 - based vector to buildSegTree
			mnciitbhuar = 1 - based vector<T>
			mnciitbhuar[0] will be neglected!
		*/
		SegmentTree(const vector<T>& mnciitbhuar)
			: ar(0), elem(0)
		{
			auto _Size = mnciitbhuar.size() - 1;
			ar = vector<Node<T>>(4 * _Size);
			buildSegTree(mnciitbhuar);
		}

		/*
			SegmentTree<T>::buildSegTree()
				Function/Method to buildSegmentTree
		*/
		void buildSegTree(const vector<T>& mnciitbhuar)
		{
			elem = mnciitbhuar.size() - 1;
			build(1, 1, elem, mnciitbhuar);
		}

		/*
			SegmentTree<T>::updateSegTree()
				Funtion/Method to updateSegmentTree at position _Position with Value newValue
		*/
		void updateSegTree(int _Position, T newValue)
		{
			update(1, 1, elem, _Position, newValue);
		}

		/*
			SegmentTree<T>::querySegTree()
				Function/Method to querySegmentTree between ri and rj
		*/
		const Node<T> querySegTree(const int& ri, const int& rj)
		{
			return query(1, 1, elem, ri, rj);
		}
	};
}
