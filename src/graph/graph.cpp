#pragma once
#include "stdafx.h"
#include "first.hpp"

using namespace std;

#define T int
#define S int

namespace MyGraph
{
	struct VertexNode;
	struct EdgeNode;
	struct EdgeSet;
	class Graph;

	typedef shared_ptr<VertexNode> VertexTypePtr;
	typedef shared_ptr<EdgeNode> EdgeNodeTypePtr;
	typedef shared_ptr<EdgeSet> EdgeSetTypePtr;

	struct VertexNode
	{
		T VertexElem;
		EdgeSetTypePtr es;

		VertexNode(T _elem)
			: VertexElem(_elem), es(nullptr)
		{}

		T& operator*()
		{
			return this->VertexElem;
		}

		const EdgeSet& IncidentEdges() const
		{
			return *es;
		}
	};

	struct EdgeNode
	{
		pair<VertexTypePtr, VertexTypePtr> PairVertexElem;
		pair<EdgeSetTypePtr, EdgeSetTypePtr> PairEdgeNode;
		S EdgeElem;

		EdgeNode(S _elem)
			: PairVertexElem({ nullptr, nullptr }), PairEdgeNode({ nullptr, nullptr }), EdgeElem(_elem)
		{}
	};
	
	namespace MyHashers
	{
		struct MyHashVertex
		{
			inline size_t operator()(const VertexTypePtr& v) const
			{
				return hash<T>()(v->VertexElem);
			}
		};

		struct MyHashEdge
		{
			inline size_t operator()(const EdgeNodeTypePtr& e) const
			{
				size_t seed = 0;
				::hash_combine(seed, e->PairVertexElem.first->VertexElem);
				::hash_combine(seed, e->PairVertexElem.second->VertexElem);
				return seed;
			}
		};

		struct MyCompVertex
		{
			bool operator()(const VertexTypePtr& _Left, const VertexTypePtr& _Right) const
			{
				return (_Left->VertexElem == _Right->VertexElem);
			}
		};

		struct MyCompEdge
		{
			bool operator()(const EdgeNodeTypePtr& _Left, const EdgeNodeTypePtr& _Right) const
			{
				return _Left->PairVertexElem.first->VertexElem == _Right->PairVertexElem.first->VertexElem &&
					_Left->PairVertexElem.second->VertexElem == _Right->PairVertexElem.second->VertexElem;
			}
		};
	}

	typedef unordered_set<VertexTypePtr, MyHashers::MyHashVertex, MyHashers::MyCompVertex> vertex_unordered_set;
	typedef unordered_set<EdgeNodeTypePtr, MyHashers::MyHashEdge, MyHashers::MyCompEdge> edge_unordered_set;

	template<typename X>
	using vertex_unordered_map = unordered_map<VertexTypePtr, X, MyHashers::MyHashVertex, MyHashers::MyCompVertex>;
	template<typename X>
	using edge_unordered_map = unordered_map<EdgeNodeTypePtr, X, MyHashers::MyHashEdge, MyHashers::MyCompEdge>;

	struct EdgeSet
	{
		edge_unordered_set UNEdgeSet;

		EdgeSet()
			: UNEdgeSet(0)
		{
			UNEdgeSet.max_load_factor(0.78f);
			UNEdgeSet.reserve(10);
		}
	};

	class Graph
	{
	public:
		//	typedef  VertexNode::VertexTypePtr VertexTypePtr;
		//	typedef  EdgeSet::EdgeNodeTypePtr EdgeNodeTypePtr;
	private:
		vertex_unordered_set var;
		edge_unordered_set ear;

		bool CheckIncident(const VertexTypePtr& vtPtr1, const VertexTypePtr& vtPtr2) const
		{
			for (const auto& xr : vtPtr1->es->UNEdgeSet)
			{
				if (xr->PairVertexElem.first->VertexElem == vtPtr2->VertexElem ||
					xr->PairVertexElem.second->VertexElem == vtPtr2->VertexElem)
					return true;
			}
			return false;
		}		

		void DFSHelper(VertexTypePtr _vnode, T _elem, vertex_unordered_set& color, bool& found)
		{
			color.insert(_vnode);
			if (_vnode->VertexElem == _elem)
			{
				found = true;
				return;
			}
			for (const auto& xr : _vnode->es->UNEdgeSet)
			{
				VertexTypePtr _next2 = xr->PairVertexElem.first;
				VertexTypePtr _next1 = xr->PairVertexElem.second;
				if(color.find(_next1) == color.end())
					Graph::DFSHelper(_next1, _elem, color, found);
				if (color.find(_next2) == color.end())
					Graph::DFSHelper(_next2, _elem, color, found);
			}
		}

		void BFSHelper(VertexTypePtr _vnode, vector<vertex_unordered_set>& vvus, vertex_unordered_map<size_t>& vumst, size_t _sz)
		{
			if (vumst.find(_vnode) == vumst.end())
			{
				if (vvus.size() < _sz + 1)
					vvus.resize(_sz + 1);
				vvus[_sz].insert(_vnode);
				vumst.insert({ _vnode, _sz });
			}
			else if (vumst[_vnode] > _sz)
			{
				vvus[_sz].insert(_vnode);
				vvus[vumst[_vnode]].erase(_vnode);
				vumst[_vnode] = _sz;
			}
			else
				return;
			for (const auto& xr : _vnode->es->UNEdgeSet)
			{
				BFSHelper(xr->PairVertexElem.first, vvus, vumst, _sz + xr->EdgeElem);
				BFSHelper(xr->PairVertexElem.second, vvus, vumst, _sz + xr->EdgeElem);
			}
		}

	public:
		Graph(size_t _var_size = 1000, size_t _ear_size = 10000)
			: var(0), ear(0)
		{
			var.reserve(_var_size);
			ear.reserve(_ear_size);
		}

		void Add(T e1, T e2, S e3)
		{
			VertexTypePtr vtPtr1 = make_shared<VertexNode>(e1);
			VertexTypePtr vtPtr2 = make_shared<VertexNode>(e2);			

			EdgeNodeTypePtr entPtr = make_shared<EdgeNode>(e3);
			EdgeSetTypePtr estPtr1;
			EdgeSetTypePtr estPtr2;

			vertex_unordered_set::iterator HasE1 = var.find(vtPtr1);
			vertex_unordered_set::iterator HasE2 = var.find(vtPtr2);

			if (HasE1 == var.end())
			{
				estPtr1 = make_shared<EdgeSet>();
				vtPtr1->es = estPtr1;
				var.insert(vtPtr1);
			}
			else
			{
				estPtr1 = (*HasE1)->es;
				vtPtr1 = (*HasE1);
			}
			if (HasE2 == var.end())
			{
				estPtr2 = make_shared<EdgeSet>();
				vtPtr2->es = estPtr2;
				var.insert(vtPtr2);
			}
			else
			{
				estPtr2 = (*HasE2)->es;
				vtPtr2 = (*HasE2);
				
			}
			entPtr->PairVertexElem.first = vtPtr1;
			entPtr->PairVertexElem.second = vtPtr2;
			entPtr->PairEdgeNode.first = estPtr1;
			entPtr->PairEdgeNode.second = estPtr2;

			estPtr1->UNEdgeSet.insert(entPtr);
			estPtr2->UNEdgeSet.insert(entPtr);

			ear.insert(entPtr);
		}

		bool AreIncident(const T e1, const T e2) const
		{
			VertexTypePtr vtPtr1 = make_shared<VertexNode>(e1);
			VertexTypePtr vtPtr2 = make_shared<VertexNode>(e2);			
			vertex_unordered_set::iterator HasE1 = var.find(vtPtr1);
			vertex_unordered_set::iterator HasE2 = var.find(vtPtr2);

			if (HasE1 == var.end() || HasE2 == var.end())
				return false;

			if ((*HasE1)->es->UNEdgeSet.size() > (*HasE1)->es->UNEdgeSet.size())
			{
				return CheckIncident(*HasE2, *HasE1);
			}
			else
			{
				return CheckIncident(*HasE1, *HasE2);
			}
		}

		vector<VertexTypePtr> GetVertices() const
		{
			vector<VertexTypePtr> _temp(var.begin(), var.end());
			return move(_temp);
		}

		vector<EdgeNodeTypePtr> GetEdges() const
		{
			vector<EdgeNodeTypePtr> _temp(ear.begin(), ear.end());
			return move(_temp);
		}

		bool TryEraseVertex(T _val)
		{
			VertexTypePtr vtPtr1 = make_shared<VertexNode>(_val);
			vertex_unordered_set::iterator HasE1 = var.find(vtPtr1);
			if (HasE1 == var.end())
				return false;
			
			for (auto& xr : (*HasE1)->es->UNEdgeSet)
			{
				if (xr->PairVertexElem.first->VertexElem != _val)
				{
					xr->PairEdgeNode.first->UNEdgeSet.erase(xr);
					if (xr->PairEdgeNode.first->UNEdgeSet.empty())
						var.erase(xr->PairVertexElem.first);
				}
				else
				{
					xr->PairEdgeNode.second->UNEdgeSet.erase(xr);
					if (xr->PairEdgeNode.second->UNEdgeSet.empty())
						var.erase(xr->PairVertexElem.second);
				}
				ear.erase(xr);
			}
			var.erase(HasE1);
			return true;
		}

		VertexTypePtr GetVertex(T _val)
		{
			VertexTypePtr vtPtr1 = make_shared<VertexNode>(_val);
			vertex_unordered_set::iterator HasE1 = var.find(vtPtr1);
			if (HasE1 == var.end())
				return nullptr;
			return *HasE1;
		}

		bool DepthFirstSearch(VertexTypePtr _start, T _elem)
		{
			vertex_unordered_set color;
			bool found = false;
			DFSHelper(_start, _elem, color, found);
			return found;			
		}

		vector<vertex_unordered_set> BreadthFirstTraversal(VertexTypePtr _start)
		{
			vector<vertex_unordered_set> vvus(var.size());
			vertex_unordered_map<size_t> vumst;
			BFSHelper(_start, vvus, vumst, 0);
			vvus.erase(find_if(vvus.rbegin(), vvus.rend(),
				[](const vertex_unordered_set& _xr)
			{
				return !_xr.empty();
			}).base(), vvus.end());
			return vvus;
		}

		~Graph()
		{
			cout << "BP";
		}
	};
}