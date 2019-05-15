#include <iostream>
#include "MyList.h"
using namespace std;
bool compare(int a, int b)
{
	if (a== b)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	bool (*fun)(int a, int b);
	fun = compare;
	struct MyStruct
	{
		int data;
	};
	MyList <int> List;
	int c = List.GetLength();
	cout << c << endl;
	int a = 3, b = 4;
	cout << &a << " " << &b << endl;
	List.ListInsert(0, a);
	List.ListInsert(0, b);
	List.show();
	int *i=List.PriorElem(4);
	cout << *i;
	return 0;
}