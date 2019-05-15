#pragma once
//对于模板类，函数的定义要放在头文件中；
#define NULL 0
#include <iostream>
using namespace std;

template <class object>
struct Node
{
	Node* next;
	Node* prior;
	object* data;
};

template <class object>
class MyList
{	/*双向链表节点*/
	
public:
	MyList();
	~MyList();
	bool ClearList();
	bool ListEmpty();
	Node<object>* GetElem(int i);
	int GetLength();
	int LocateELem(object e, bool (*compare)(object a, object b));
	void ListInsert(int i, object& e);
	object *PriorElem(object cur_e);
	void show();
protected:
	Node<object>* head, * tail;
	int length;

};
// 默认构造函数
template <class object>
MyList<object>::MyList()
{	/*head和tail节点初始化为同一个节点*/
	length = 0;
	head = new Node<object>;
	head->next = NULL;
	head->prior = NULL;
	static int c = 0;
	head->data = &c;
	tail = head;
}

template <class object>
MyList<object>::~MyList()
{
	Node<object>* temp;
	while (this->head!=NULL)
	{
		temp = head;
		head = head->next;
		delete(temp);
	}
	temp = NULL;
}

template<class object>
bool MyList<object>::ClearList()
{	
	Node<object>* temp1,*temp2;
	temp1 = head->next;
	while (temp1 != NULL)
	{
		temp2 = temp1;
		delete(temp1);
		temp1 = temp2->next;
	}
	this->length = 0;
	return true;
}

template<class object>
bool MyList<object>::ListEmpty()
{
	if (length == 0)
		return true;
	else
		return false;
}

template<class object>
Node<object>* MyList<object>::GetElem(int i)
{
	if (i < this->length)
	{
		return NULL;
	}
	else
	{
		Node<object>* temp = this->head;
		for (int j = 0; j < i; j++)
		{
			temp = temp->next;
		}
		return temp;
	}
}





template<class object>
int MyList<object>::GetLength()
{	
	return length;
}

template<class object>
int MyList<object>::LocateELem(object e, bool(*compare)(object a, object b))
{
	Node<object>* temp = this->head->next;
	int num = 1;
	while (!compare(e, *(temp->data)))
	{
		temp = temp->next;
		num++;
	}
	return num;
}

template<class object>
void MyList<object>::ListInsert(int i, object& e)
{
	if (i>=0&&i<=this->length)
	{	
		Node<object> *temp=this->GetElem(i);
		Node<object>* newNode = new Node<object>;
		newNode->data = &e;
		newNode->prior = temp;
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

template<class object>
/*返回值为指针*/
inline object* MyList<object>::PriorElem(object cur_e)
{	
	Node<object>* temp;
	temp = head;
	while (temp->next!= NULL)
	{
		if (*(temp->next->data) == cur_e)
		{
			return temp->data;
		}
		temp = temp->next;
	}
	return NULL;
}

template<class object>
void MyList<object>::show()
{
	Node<object>* temp=NULL;
	temp = head->next;
	while (temp!=NULL)
	{	
		/*此处的data是个指针*/
		cout << temp->data<< endl;
		temp = temp->next;
	}
}
