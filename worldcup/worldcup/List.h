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
	List_iter(ListNode<T>*ptr=nullptr) :ptr(ptr) {};
	~List_iter() { ptr = nullptr; };
	bool operator ==(List_iter<T>&src);
	bool operator ==(List_iter<T>&&src);
	bool operator !=(List_iter<T>&src);
	bool operator !=(List_iter<T>&&src);
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
	void clear();
	bool empty();
	T back();
	T front();
	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	void remove(T data);
	void remove(List_iter<T> fore_iter);
	bool search(T data);
	void insert(int index,T data);
	T find(int index);
	int Size();
	//void show();
private:
	List_iter<T> search_foreiter(T data);
	List_iter<T> index_foreiter(int index);
};

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
	//std::cout << "xigou" <<sizeof(T) <<std::endl;
}


template<typename T>
inline bool List_iter<T>::operator==(List_iter<T>&src)
{
	return ptr==src.ptr;
}

template<typename T>
inline bool List_iter<T>::operator==(List_iter<T>&& src)
{
	return ptr==src.ptr;
}

template<typename T>
inline bool List_iter<T>::operator!=(List_iter<T>&src)
{
	return ptr!=src.ptr;
}

template<typename T>
inline bool List_iter<T>::operator!=(List_iter<T>&& src)
{
	return ptr!=src.ptr;
}

template<typename T>
inline List_iter<T>& List_iter<T>::operator++()
{
	// TODO: 在此处插入 return 语句
	if (ptr)
	{
		ptr = ptr->next;
		return *this;
	}
	throw std::runtime_error("操作无法执行，到达链表尾部");
	
}

template<typename T>
inline List_iter<T>& List_iter<T>::operator++(int)
{
	// TODO: 在此处插入 return 语句
	if (ptr)
	{
		List_iter<T> temp = *this;
		ptr = ptr->next;
		return temp;
	}
	throw std::runtime_error("操作无法执行，到达链表尾部");
}

template<typename T>
inline T List_iter<T>::operator*()
{
	if(ptr)
	return ptr->data;
	throw std::runtime_error("迭代器指针为空");
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
inline List<T>::List(List<T>& src)
{
	first = new ListNode<T>();
	last = first;
	assign(src.begin(),src.end() );
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
	return *this;
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
		size++;
	}
}

template<class T>
inline void List<T>::clear()
{
	ListNode<T>*p;
	while (first->next) 
	{
		p = first->next;
		first->next = p->next;
		delete p;
		p = nullptr;
	}
	last = first;
	size = 0;
}

template<class T>
inline bool List<T>::empty()
{
	return size==0;
}

template<class T>
inline T List<T>::back()
{
	return last->data;
}

template<class T>
inline T List<T>::front()
{
	return first->next->data;
}

template<class T>
inline void List<T>::push_back(T data)
{
	last->next = new ListNode<T>(data);
	last = last->next;
	size++;
}

template<class T>
inline void List<T>::push_front(T data)
{
	ListNode<T>*p=new ListNode<T>(data,first->next);
	if (!first->next)
		last = p;
	first->next = p;
	size++;
}

template<class T>
inline void List<T>::pop_back()
{
	ListNode<T>*p = first;
	for (; p->next != last; p = p->next);
	delete p->next;
	p->next = nullptr;
	size--;
	last = p;
}

template<class T>
inline void List<T>::pop_front()
{
	ListNode<T>*p = first->next;
	first->next = p->next;
	if (p == last)
		last = first;
	delete p;
	size--;
	p = nullptr;
}

template<class T>
inline void List<T>::remove(T data)
{
	List_iter<T> p = search_foreiter(data);
	if (p.ptr != nullptr)
		remove(p);
}

template<class T>
inline void List<T>::remove(List_iter<T> fore_iter)
{
	ListNode<T>*p = fore_iter->next;
	fore_iter->next = p->next;
	if (p == last)
		last = fore_iter.ptr;
	delete p;
	size--;
	p = nullptr;
	
}

template<class T>
inline bool List<T>::search(T data)
{
	ListNode<T>*p = first->next;
	while (p) 
	{
		if (p->data == data)
			return true;		
		p = p->next;
	}
	return false;
}

template<class T>
inline void List<T>::insert(int index, T data)
{
	List_iter<T>iter=index_foreiter(index);
	iter->next = new ListNode<T>(data, iter->next);
	size++;
	if (iter.ptr == last)
		last = iter->next;
}

template<class T>
inline T List<T>::find(int index)
{
	ListNode<T>*p = first->next;
	if (index >= size)
		throw std::runtime_error("下标越界");
	for (int i = 0; i < index; p = p->next, i++);
	return p->data;
}

template<class T>
inline int List<T>::Size()
{
	return size;
}

template<class T>
inline List_iter<T> List<T>::search_foreiter(T data)
{
	ListNode<T>*p = first;
	while (p)
	{
		if (p->next->data == data)
			return List_iter<T>(p);
		p = p->next;
	}
	
	return List_iter<T>(nullptr);
}

template<class T>
inline List_iter<T> List<T>::index_foreiter(int index)
{
	ListNode<T>*p = first;
	if (index > size)
		throw std::runtime_error("下标越界");
	for (int i = 0; i < index; p = p->next, i++);
	return List_iter<T>(p);
}

