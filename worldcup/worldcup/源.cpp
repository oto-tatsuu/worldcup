#include<iostream>
#include<list>
#include"List.h"

int main() 
{
	List<int>l;
	List<int>a;
	for (int i = 0; i < 10; i++)
		l.push_back(i);
	a = l;
	List<int>b = a;
	return 0;
}