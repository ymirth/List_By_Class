#include<iostream>
using namespace std;
template <typename T>
class Node  //嵌套类
{
public:
		T data;
		Node<T>* prev;
		Node<T>* next;
		
		Node<T>(const T& D, Node<T>* p, Node<T>* n) :data(D), prev(p), next(n) {};
};
template <typename T>
class LinkList 
{
private:
	int ListSize;//链表长度
	Node<T>* head;
	Node<T>* tail;//链表的头指针，与尾指针
public:
	LinkList() { init(); }       //初始化 
	LinkList(const int& length, Node<T>* h, Node<T>* t ) :ListSize(length), head(h), tail(t) {};
	
	void init()
	{//初始化
		ListSize = 0;
		head = new Node<T>;
		tail = new Node<T>;
		head->next = tail;
		tail->prev = head;
	}
	bool insert(const T& Data, Node<T>* cur)
	{//在cur结点的右边插
		Node<T>* p = new Node<T>;
		p->data = Data;
		cur->next->prev = p;   
	    p->prev = cur;
		p->next = cur->next;  
		cur->next = p;
		ListSize++;     //链表长度加一
		delete p;       //释放辅助指针p
		return 1;
	}
	void CreateList()
	{
		Node<T>* p=new Node<T>;//辅助创建结点
		Node<T>* str;
		int bits;   //数据位数
		cout << "请输入数据位数";
		cin >> bits;
		int i = 0;//循环标志
		cout << "请输入数据";
		for (str=head;i<bits;i++)
		{
			cin >> p->data;
			insert(p->data, str);  //依次向链表输入数据
			str = str->next;
		}
	}
	bool IsEmpty(LinkList* list) 
	{//判空
		return (list->head->next=NULL) ? 1 : 0;
	}

	Node<T>* Head()
	{
		return head;
	}
	Node<T>* Tail() {
		return tail;
	}
};
int main()
{
	LinkList<int>* L1=new LinkList<int>;
	L1->init();
	Node<int>* p = L1->Head();
	L1->insert(10, p);
	p = p->next;
	cout <<p->data ;
}

