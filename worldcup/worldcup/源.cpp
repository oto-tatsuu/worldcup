#include<iostream>
#include<list>
#include"List.h"

int main() 
{
	List<int>l;
	List<int>a;
	for (int i = 0; i < 10; i++)
		l.push_front(i);
	l.pop_front();
	l.pop_front();
	l.insert(5, 9);
	l.insert(9, 8);
	for (List_iter<int> p = l.begin(); p != l.end(); p++)
		std::cout << *p<<std::endl;
	return 0;
}