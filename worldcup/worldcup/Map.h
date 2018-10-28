#pragma once
#include<vector>
#include<iostream>
#include"List.h"
using std::vector;
template <typename E>
class MapNode;//边结点
template <typename N,typename E>
class MapHNode;//图结点
template<typename N,typename E>
class Map;//图邻接表
template <typename E>
class MapNode//边结点
{
public:
	MapNode();
	MapNode(E data, int index);
	E GetData();
	int GetIndex();
	E data;
	int index;//后继
};
template<typename E>
class Edge 
{
public:
	Edge();
	Edge(int from,int to,List_iter<MapNode<E>>edge);
	~Edge();
	Edge<E>&operator++();
	Edge<E>&operator++(int);
	bool empty();
	E operator*();
public:
	int from;//前驱
	int to;//后继
private:
	List_iter<MapNode<E>>edge;
	
};
template <typename N, typename E>
class MapHNode//图结点
{
	friend class Map<N, E>;
private:
	List<MapNode<E>> edgeList;
	N data;
public:
	MapHNode();
	MapHNode(N data);
	N GetData();
	void AddNode(E data, int index);
};

template<typename N, typename E>
class Map
{
public:
	
	Map(int n);
	//返回边内容
	E GetEData(MapNode<E> e);
	//返回后继
	int GetIndex(MapNode<E> e);
	//添加点
	void AddVertice(N data);
	void SetVertice(int index, N data);
	int VerticesNum();
	N GetVData(int n);
	void AddEdge(int from, int to, E data);
	int EdgesNum(int v);
	int EdgesAllNum();
	Edge<E> FirstEdge(int index);
private:
	vector<MapHNode<N, E>*>map;

};

template<typename N, typename E>
inline Map<N, E>::Map(int n)
{
	map.reserve(n);
}

template<typename N, typename E>
inline E Map<N, E>::GetEData(MapNode<E> e)
{
	return e.GetData();
}

template<typename N, typename E>
inline int Map<N, E>::GetIndex(MapNode<E> e)
{
	return e.GetIndex();
}

template<typename N, typename E>
inline void Map<N, E>::AddVertice(N data)
{
	MapHNode<N,E>*p=new MapHNode<N,E>(data);
	map.push_back(p);
}

template<typename N, typename E>
inline void Map<N, E>::SetVertice(int index, N data)
{
	MapHNode<N, E>*p = new MapHNode<N, E>(data);
	delete map[index];
	map[index] = p;
}

template<typename N, typename E>
inline int Map<N, E>::VerticesNum()
{
	return map.size();
}

template<typename N, typename E>
inline N Map<N, E>::GetVData(int n)
{
	return map[n]->GetData();
}

template<typename N, typename E>
inline void Map<N, E>::AddEdge(int from, int to, E data)
{
	map[from]->AddNode(data, to);
}

template<typename N, typename E>
inline int Map<N, E>::EdgesNum(int v)
{
	return map[v]->edgeList.Size();
}

template<typename N, typename E>
inline int Map<N, E>::EdgesAllNum()
{
	int r = 0;
	for (int i = 0; i < map.size(); i++) 
	{
		r += EdgesNum(i);
	}
	return r;
}

template<typename N, typename E>
inline Edge<E> Map<N, E>::FirstEdge(int index)
{
	List_iter<MapNode<E>>p = map[index]->edgeList.begin();
	int to = (*p).index;
	return Edge<E>(index,to,p);
}

template<typename E>
inline MapNode<E>::MapNode()
{
}

template<typename E>
inline MapNode<E>::MapNode(E data, int index):data(data),index(index)
{
}

template<typename E>
inline E MapNode<E>::GetData()
{
	return data;
}

template<typename E>
inline int MapNode<E>::GetIndex()
{
	return index;
}

template<typename N, typename E>
inline MapHNode<N, E>::MapHNode()
{
}

template<typename N, typename E>
inline MapHNode<N, E>::MapHNode(N data):data(data)
{
}


template<typename N, typename E>
inline N MapHNode<N, E>::GetData()
{
	return data;
}

template<typename N, typename E>
inline void MapHNode<N, E>::AddNode(E data, int index)
{
	MapNode<E>*p = new MapNode<E>(data,index);
	edgeList.push_back(*p);
}

template<typename E>
inline Edge<E>::Edge()
{
}

template<typename E>
inline Edge<E>::Edge(int from, int to, List_iter<MapNode<E>> edge):from(from),to(to),edge(edge)
{
}

template<typename E>
inline Edge<E>::~Edge()
{
}

template<typename E>
inline Edge<E>& Edge<E>::operator++()
{
	if (edge.operator->() != nullptr) 
	{
		++edge;
		if (edge.operator->())
			to = (*edge).index;
		else
			to = -1;
		return *this;
	}
	throw std::runtime_error("该边为空边");
}

template<typename E>
inline Edge<E>& Edge<E>::operator++(int)
{
	if (edge.operator->() != nullptr) 
	{
		List_iter<MapNode<E>>temp = edge;
		++edge;
		to = (*edge).index;
		return temp;
	}
	throw std::runtime_error("该边为空边");
	
	
}

template<typename E>
inline bool Edge<E>::empty()
{
	return edge.operator->()==nullptr;
}

template<typename E>
inline E Edge<E>::operator*()
{
	return (*edge).data;
}
