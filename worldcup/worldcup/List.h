#pragma once
#include<iostream>
template<typename T>
class List;//链表
template<typename T>
class ListNode;//链表结点
template<typename T>
class List_iterator;//链表迭代器


template<typename  T>
class ListNode
{
	friend class List<T>;
private:
	T data;
	ListNode<T>* next;
public:
	ListNode();
	ListNode(T data, ListNode<T>*next = nullptr);
	~ListNode();
};
template<typename T>
class List
{
private:
	ListNode<T>*first;
	ListNode<T>*last;
	int size;
public:
	List();
	List(List<T>&src);
	~List();
	List<T>&operator=(List&rsh);
	void assign(List&src);
	void push_back(T data);
	void push_front(T data);
	void Delete(T data);
	void Insert(T data, int index);
	int Size();
	void Clear();
	void Show();
	ListNode<T>* begin();
	ListNode<T>* end();
	template<typename T>
	class List_iterator
	{
	public:
		List_iterator();
		List_iterator(ListNode<T>*ptr = nullptr);
		List_iterator(List_iterator<T>&src);
		~List_iterator();
		bool operator ==(List_iterator<T>&src);
		bool operator !=(List_iterator<T>&src);
		void operator ++();
		T operator *();
		ListNode<T>*operator->();
	private:
		ListNode<T>*ptr;
	};
};

template<typename T>
inline ListNode<T>::ListNode()
{
}

template<typename T>
inline ListNode<T>::ListNode(T data, ListNode<T>* next) :data(data), next(next)
{
}

template<typename T>
inline ListNode<T>::~ListNode()
{
	if (next)
	{
		delete next;
		next = nullptr;
	}
	std::cout << "xigou";
}

template<typename T>
inline List<T>::List()
{
	first = new ListNode<T>();
	last = first;
	size = 0;
}

template<typename T>
inline List<T>::List(List<T>& src)
{
	first = new ListNode<T>();
	ListNode<T>*p = src.first->next;
	while (p)
	{
		Append(p->data);
	}
}

template<typename T>
inline List<T>::~List()
{
	Clear();
	delete first;
	first = nullptr;
	last = nullptr;
}

template<typename T>
inline List<T>& List<T>::operator=(List & rhs)
{
	// TODO: 在此处插入 return 语句
	Clear();
	ListNode<T>*p = rhs.first->next;
	while (p)
	{
		Append(p->data);
	}
}

template<typename T>
inline void List<T>::assign(List & src)
{
}

template<typename T>
inline void List<T>::Append(T data)
{
	ListNode<T>*p = new ListNode<T>(data);
	last->next = p;
	last = p;
	size++;
}

template<typename T>
inline void List<T>::Delete(T data)
{
	ListNode<T>*p = first, *q;
	while (p->next&&p->next->data != data)
		p = p->next;
	q = p->next;
	if (!q)
		return;
	if (q == last)
		last = p;
	p->next = q->next;
	q->next = nullptr;
	delete q;
	size--;
}

template<typename T>
inline void List<T>::Insert(T data, int index)
{
	if (index > size)
		return;
	ListNode<T>*p = first;
	for (int count = 0; count < index; count++)
		p = p->next;
	p->next = new ListNode<T>(data, p->next);
	size++;
	if (last == p)
		last = p->next;
}

template<typename T>
inline int List<T>::Size()
{
	return size;
}

template<typename T>
inline void List<T>::Clear()
{
	delete first->next;
	first->next = nullptr;
	size = 0;
	last = first;
}

template<typename T>
inline void List<T>::Show()
{
	ListNode<T>*p = first->next;
	while (p)
	{
		std::cout << p->data;
		p = p->next;
	}
}

template<typename T>
inline ListNode<T>* List<T>::begin()
{
	return first->next;
}

template<typename T>
inline ListNode<T>* List<T>::end()
{
	return last;
}

//iterator
template<typename T>
template<typename T>
inline List<T>::List_iterator<T>::List_iterator()
{
	iter = nullptr;
}

template<typename T>
template<typename T>
inline List<T>::List_iterator<T>::List_iterator(ListNode<T>* ptr):ptr(ptr)
{
}

template<typename T>
template<typename T>
inline List<T>::List_iterator<T>::List_iterator(List_iterator<T>& src):ptr(src.ptr)
{
}

template<typename T>
template<typename T>
inline List<T>::List_iterator<T>::~List_iterator()
{
	ptr = nullptr;
}

template<typename T>
template<typename T>
inline bool List<T>::List_iterator<T>::operator==(List_iterator<T>& src)
{
	return ptr==src.ptr;
}

template<typename T>
template<typename T>
inline bool List<T>::List_iterator<T>::operator!=(List_iterator<T>& src)
{
	return ptr!=src.ptr;
}

template<typename T>
template<typename T>
inline void List<T>::List_iterator<T>::operator++()
{
	if (ptr)
		ptr = ptr.next;
	else
		throw runtime_error("链表迭代器越界");
}

template<typename T>
template<typename T>
inline T List<T>::List_iterator<T>::operator*()
{
	return ptr->data;
}

template<typename T>
template<typename T>
inline ListNode<T>* List<T>::List_iterator<T>::operator->()
{
	return ptr;
}
