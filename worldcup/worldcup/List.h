#pragma once
#include<iostream>
template<typename T>
class List_iter;
template<typename T>
class List;
template<typename  T>
class ListNode
{
	friend class List<T>;
	friend class List_iter<T>;
private:
	T data;
	ListNode<T>* next;
public:
	ListNode();
	ListNode(T data, ListNode<T>*next = nullptr);
	~ListNode();
};

template<typename T>
class List_iter 
{
	friend class List<T>;
private:
	ListNode<T>*ptr;
public:
	List_iter(ListNode<T>*ptr) :ptr(ptr) {};
	List_iter(List_iter<T>&src) :ptr(src) {};
	~List_iter() { ptr = nullptr; };
	List_iter<T>&operator =(List_iter<T>&src);
	bool operator ==(List_iter<T>&src);
	bool operator !=(List_iter<T>&src);
	List_iter<T>& operator ++();
	List_iter<T>& operator ++(int);
	T operator *();
	ListNode<T>* operator->();
};

template<class T>
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
	List_iter<T> begin();
	List_iter<T> end();
	void assign(List_iter<T> begin, List_iter<T> end);
	bool empty();
	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	void remove(T data);
	void insert(int index,T data);
	int Size();
	void clear();
	void Show();

	
};
////
//template<typename T>
//inline ListNode<T>::ListNode()
//{
//}
////
//template<typename T>
//inline ListNode<T>::ListNode(T data, ListNode<T>* next) :data(data), next(next)
//{
//}
////
//template<typename T>
//inline ListNode<T>::~ListNode()
//{
//	if (next)
//	{
//		delete next;
//		next = nullptr;
//	}
//	std::cout << "xigou";
//}
//
//template<typename T>
//inline List<T>::List()
//{
//	first = iterator(new ListNode<T>());
//	last = first;
//	size = 0;
//}
//
//template<typename T>
//inline List<T>::List(List<T>& src)
//{
//	first = iterator(new ListNode<T>());
//	assign(src.begin(), src.end());
//}
//
//template<typename T>
//inline List<T>::~List()
//{
//	clear();
//	delete first;
//	first = nullptr;
//	last = nullptr;
//}
//
//template<class T>
//inline List<T>::iterator List<T>::begin()
//{
//	return iterator();
//}
//
//
//
//template<class T>
//inline List<T>::iterator List<T>::end()
//{
//	return last++;
//}
//
//
//
//template<typename T>
//inline List<T>& List<T>::operator=(List & rhs)
//{
//	// TODO: 在此处插入 return 语句
//	assign(rhs.begin(),rhs.end());
//	return this;
//}
//
//template<typename T>
//inline void List<T>::assign(List<T>::iterator first, List<T>::iterator last)
//{
//	clear();
//	List<T>::iterator iter;
//	while (iter != end()) 
//	{
//		push_back(*iter);
//		iter++;
//	}
//}
//
//
//template<typename T>
//inline bool List<T>::empty()
//{
//	return size==0;
//}
//
//template<typename T>
//inline void List<T>::push_back(T data)
//{
//	ListNode<T>*p = new ListNode<T>(data);
//	last->next = p;
//	last = p;
//	size++;
//}
//
//template<typename T>
//inline void List<T>::push_front(T data)
//{
//	ListNode<T>*p = new ListNode<T>(data);
//	p->next = first->next;
//	first->next = p;
//	size++;
//}
//
//template<typename T>
//inline void List<T>::pop_back()
//{
//	ListNode<T>*p = first->next;
//	while (p->next!=last) 
//	{
//		p=p->next
//	}
//	delete p->next;
//	last = p;
//	size--;
//}
//
//template<typename T>
//inline void List<T>::pop_front()
//{
//	ListNode<T>*p = first->next;
//	first - next = p->next;
//	p->next = nullptr;
//	delete p;
//	size--;
//}
//
//
//template<typename T>
//inline void List<T>::remove(T data)
//{
//	ListNode<T>*p = first, *q;
//	while (p->next&&p->next->data != data)
//		p = p->next;
//	q = p->next;
//	if (!q)
//		return;
//	if (q == last)
//		last = p;
//	p->next = q->next;
//	q->next = nullptr;
//	delete q;
//	size--;
//}
//
//template<typename T>
//inline void List<T>::insert(int index,T data)
//{
//	if (index > size)
//		return;
//	ListNode<T>*p = first;
//	for (int count = 0; count < index; count++)
//		p = p->next;
//	p->next = new ListNode<T>(data, p->next);
//	size++;
//	if (last == p)
//		last = p->next;
//}
//
//template<typename T>
//inline int List<T>::Size()
//{
//	return size;
//}
//
//template<typename T>
//inline void List<T>::clear()
//{
//	delete first->next;
//	first->next = nullptr;
//	size = 0;
//	last = first;
//}
//
//template<typename T>
//inline void List<T>::Show()
//{
//	ListNode<T>*p = first->next;
//	while (p)
//	{
//		std::cout << p->data;
//		p = p->next;
//	}
//}
//
////
//template<typename T>
//inline List<T>::iterator::iterator(ListNode<T>* ptr):ptr(ptr)
//{
//}
//template<class T>
//inline List<T>::iterator::iterator(List<T>::iterator& src) : ptr(src.ptr)
//{
//}
////
//
////
//template<typename T>
//inline List<T>::iterator::~iterator()
//{
//	delete ptr;
//}
////
//template<class T>
//inline bool List<T>::iterator::operator==(List<T>::iterator& src)
//{
//	return false;
//}
////
//template<typename T>
//inline bool List<T>::iterator::operator!=(List<T>::iterator& src)
//{
//	return ptr != src.ptr;
//}
////
//template<class T>
//inline List<T>::iterator List<T>::iterator::operator++()
//{
//	if (ptr)
//		ptr = ptr.next;
//	else
//		throw runtime_error("链表迭代器越界");
//	return this;
//}
////
//template<typename T>
//inline T List<T>::iterator::operator*()
//{
//	return ptr->data;
//}
////
//template<typename T>
//inline ListNode<T>* List<T>::iterator::operator->()
//{
//	return ptr;
//}

template<typename T>
inline ListNode<T>::ListNode()
{
}

template<typename T>
inline ListNode<T>::ListNode(T data, ListNode<T>* next):data(data),next(next)
{
}

template<typename T>
inline ListNode<T>::~ListNode()
{
}

template<typename T>
inline List_iter<T> & List_iter<T>::operator=(List_iter<T> & src)
{
	// TODO: 在此处插入 return 语句
	ptr = src.ptr;
	return this;
}

template<typename T>
inline bool List_iter<T>::operator==(List_iter<T>&src)
{
	return ptr==src.ptr;
}

template<typename T>
inline bool List_iter<T>::operator!=(List_iter<T>&src)
{
	return ptr!=src.ptr;
}

template<typename T>
inline List_iter<T>& List_iter<T>::operator++()
{
	// TODO: 在此处插入 return 语句
	ptr = ptr->next;
	return *this;
}

template<typename T>
inline List_iter<T>& List_iter<T>::operator++(int)
{
	// TODO: 在此处插入 return 语句
	List_iter<T> temp = *this;
	ptr = ptr->next;
	return temp;
}

template<typename T>
inline T List_iter<T>::operator*()
{
	return ptr->data;
}

template<typename T>
inline ListNode<T>* List_iter<T>::operator->()
{
	return ptr;
}

template<class T>
inline List<T>::List()
{
	first = new ListNode<T>();
	last = first;
	size = 0;
}

template<class T>
inline List<T>::List(List<T>& src):List()
{
	first = new ListNode<T>();
	last = first;
	assign(src.begin(), src.end());
}

template<class T>
inline List<T>::~List()
{
	clear();
	delete first;
	first = nullptr;
	last = nullptr;
}

template<class T>
inline List<T>& List<T>::operator=(List & rsh)
{
	// TODO: 在此处插入 return 语句
	assign(rsh.begin(), rsh.end());
}

template<class T>
inline List_iter<T> List<T>::begin()
{
	return List_iter<T>(first->next);
}

template<class T>
inline List_iter<T> List<T>::end()
{
	return List_iter<T>(last->next);
}

template<class T>
inline void List<T>::assign(List_iter<T> begin, List_iter<T> end)
{
	clear();
	for (List_iter<T> iter = begin; iter != end; iter++) 
	{
		push_back(*iter);
	}
}
