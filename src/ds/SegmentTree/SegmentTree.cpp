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
	struct node;

	template<typename T>
	class SegmentTree;
	
	//	Node of Segment Tree
	template<typename T>
	struct node
	{
		//	Elements required in Node<T>		
		T x;

		// Declaring Segment<T> as friend class of node<T>
		friend class SegmentTree<T>;

		/*
			node<T>::node()
				A default Constructor for node<T>.
				Edit it so that it will behave as identity for node<T>::merge()
		*/
		node()
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
		void merge(const node<T>& n1, const node<T>& n2)
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
		vector<node<T>> ar;
		//	Number of elements of vector - 1 
		size_t elem;

		/*
			Segment<T>::build()
				Function/Method to Build Segment Tree from input vector<T>.
				Initially: 
					nodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					mnciitbhuar = Input Vector

			Complexity : O(nlog2n)
		*/
		void build(int nodeNumber, int i, int j, const vector<T>& mnciitbhuar)
		{
			if (i == j)
			{
				ar[nodeNumber].setValue(mnciitbhuar[i]);
				return;
			}
			int left = nodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			build(left, i, mid, mnciitbhuar);
			build(right, mid + 1, j, mnciitbhuar);
			ar[nodeNumber].merge(ar[left], ar[right]);
		}

		/*
			SegmentTree<T>::update / Edit funtion 
				Function/Method to edit a value at position k to value newValue
				Initially:
					nodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					k = Position whose value to be changed
					newValue = New Value at k Position

			Complexity : O(log2n)
		*/
		void update(int nodeNumber, int i, int j, int k, T newValue)
		{
			if (i == j)
			{
				if (i == k)
					ar[nodeNumber].setValue(newValue);			
				return;
			}
			int left = nodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			if (k <= mid)
				update(left, i, mid, k, newValue);
			else
				update(right, mid + 1, j, k, newValue);
			ar[nodeNumber].merge(ar[left], ar[right]);
		}

		/*
			SegmentTree<T>::query 
				Function/Method to query between ri and rj.
				According to they are merge.
				Initially:
					nodeNumber = 1
					i = 1
					j = elem = vectorSize - 1
					ri = Left Value of Interval 
					rj = Right Value of Interval

			Complexity = O(log2n)
		*/
		const node<T> query(size_t nodeNumber, int i, int j, const int& ri, const int& rj)
		{
			if (j<ri || i>rj)
				return node<T>();
			if (ri <= i && rj >= j)
				return ar[nodeNumber];
			int left = nodeNumber << 1, right = left | 1, mid = (i + j) >> 1;
			auto q1 = query(left, i, mid, ri, rj);
			auto q2 = query(right, mid + 1, j, ri, rj);
			node<T> temp;
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
		{
			auto _Size = mnciitbhuar.size() - 1;
			ar = vector<node<T>>(4 * _Size);
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
		const node<T> querySegTree(const int& ri, const int& rj)
		{
			return query(1, 1, elem, ri, rj);
		}
	};
}