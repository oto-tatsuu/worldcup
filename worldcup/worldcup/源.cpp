#include<iostream>
#include<list>
#include"List.h"

int main() 
{
	std::list<int>l;
	for (int i = 0; i < 10; i++)
		l.push_back(i);
	int*p=l.begin().operator->();
	std::cout << p<<"iiter"<<&*l.begin();
	return 0;
}