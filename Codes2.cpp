#include<iostream>
#include<cstring>
using namespace std;
template <typename T>
class LinkList 
{
public:
	int ListSize;//链表长度
	class Node;  //嵌套类声明
	Node* head;
	Node* tail;//链表的头指针，与尾指针
	class Node  //嵌套类
	{
	public:
		T data;
		Node* prev;
		Node* next;

		Node() { prev = NULL; next = NULL; data = -1; }
		Node(const T& D, Node* p, Node* n) : data(D), prev(p), next(n) {};
	};

	Node* node;                  //链表的结点指针
	LinkList() 
	{init();}       //初始化 
	LinkList(const int& length, Node* h, Node* t ) :ListSize(length), head(h), tail(t) {};

	void init()
	{//初始化
		ListSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}  
	Node* Insert(const T& Data, Node* cur)
	{//在cur结点的右边插
		//构造结点
		Node* p = new Node;
		p->data = Data;
		
		//插入结点
		cur->next->prev = p;   
	    p->prev = cur;
		p->next = cur->next;  
		cur->next = p;

		ListSize++;     //链表长度加一		
		return p;
	}
	Node* DeverseInsert(const T& Data, Node* cur)
	{//在cur结点的左边插
		//构造结点
		Node* p = new Node;
		p->data = Data;

		//插入结点
		cur->prev->next = p;
		p->prev = cur->prev;
		p->next = cur;
		cur->prev = p;

		ListSize++;     //链表长度加一		
		return p;
	}
	bool IsEmpty(LinkList* list) 
	{//判空
		return (list->head->next=NULL) ? 1 : 0;
	}
	void Traverse()
	{
		for(node = head->next;node!=tail;node++)
		cout << node->data;
	}
};
template <typename T>
class BigDataList :public LinkList<T>
{
private:
	T num;
	LinkList<T>::Node;
	typedef LinkList<T>::Node* NodePointer;
	LinkList<T>::head;
	LinkList<T>::tail;
public:
	BigDataList() :LinkList<T>(), num(-1) {};
	BigDataList(T NUM) :LinkList<T>(), num(NUM) {};

	void CreateSDL()
	{//按位录入数据进入链表
		NodePointer p = new Node;
		NodePointer str = head;  //倒叙插入起点
		int tmp = num; //tmp 被除数，商存储器
		int qmp; //余数存储器
		while (tmp)
		{//当tmp位个位数时，被10除，商取0，终止输入
			qmp = tmp % 10;
			p->data = qmp;
			cout << p->data << endl;
			LinkList<T>::Insert(p->data, str);//依次向链表输入数据
			tmp = tmp / 10;
			
		}
	}
	void CreateBDL()
	{//高位在尾部，低位在头部
		NodePointer str;
		str = head;
		int bit = 0;
		cout << "请从高位到低位输入数据，截止请输入<0的数" << endl;
		cout << "请依次输入：" << endl;
		while (bit>=0)
		{//Ctrl+Z 停止循环
			cin >> bit;
			if(bit>=0)
			LinkList<int>::Insert(bit, str);
			str = str->next;
		}
	}
	void TraverseBDL()
	{
		LinkList<T>::node = head->next;
		for (int i = 0; i < LinkList<T>::ListSize; ++i)
		{
			cout << LinkList<T>::node->data;
			LinkList<T>::node = LinkList<T>::node->next;
		}
		cout << endl;
	}

	BigDataList operator+(const BigDataList& rhs)
	{
		int min_size = rhs.ListSize > this->ListSize ? this->ListSize : rhs.ListSize;//最小位数
		int max_size = rhs.ListSize < this->ListSize ? this->ListSize : rhs.ListSize;//最大位数
		int distance = max_size-min_size;                                            //位数之差

		int flag;                                    //位数判断标志
		if (max_size == this->ListSize) flag = 1;    //1：被加数位数大
		else if (max_size == rhs.ListSize) flag = 0; //0：加数位数大

		cout << "maxsize=" << max_size << endl;
		BigDataList Result;    //结果存储对象
		int c = 0;              //表示进位，进位存储器，defalut:0
		NodePointer p, q, t;
		p = this->tail->prev;  //被加数起始位
		q = rhs.tail->prev;    //加数起始位
		t = Result.tail;       //乘积录入起始位
		for (int i = 0; i < min_size; i++)
		{
			if (p != this->head && q != rhs.head)//去除链表端点
			{
				int s = p->data + q->data + c; //每一位上面的和等于对应位相加再加上进位
				
				Result.DeverseInsert(s % 10, t);//从低位向高位插入，起点在尾部，倒叙插入链表
				c = s > 9 ? 1 : 0;

				/*  移位  */
				t = t->prev;
				p = p->prev;
				q = q->prev;
				if (i + 1 == min_size && c == 1&&distance==0)//最高位产生溢出时,且为运算的末位时
					Result.DeverseInsert(c, t);  //进位插入
			}
		}
		for (int i = 0; i < distance; i++)
		{//加数与被加数位数不等
			int s;
			if (flag == 1)
			{//被加数位数多，录入p
				if (p != this->head)
				{
					s = p->data + c;
					Result.DeverseInsert(s % 10, t);	//倒叙插入，高位在前		
					cout << "c=" << c << endl;
					c = s > 9 ? 1 : 0;                  //进位处理
					cout << "c=" << c << endl;
					/*  移位  */
					t = t->prev;
					p = p->prev;
					if (i + 1 == distance && c == 1)Result.DeverseInsert(c, t);     //进位插入
					
				}
			}

			else if (flag == 0)
			{//加数位数多，录入q
				if (q != rhs.head)
				{
					s = q->data + c;
					Result.DeverseInsert(s % 10, t);	//倒叙插入，高位在前		
					c = s > 9 ? 1 : 0;   //进位处理
					/*  移位  */
					t = t->prev;
					q = q->prev;
					if (i + 1 == distance && c == 1)//最高位产生溢出时
						Result.DeverseInsert(c, t);  //进位插入
				}
			}

		}
		
		return Result;
	}
};
int main()
{
	LinkList<int>* L1=new LinkList<int>;
	L1->init();
	L1->node=L1->Insert(10, L1->head);
	cout << L1->node->data ;

	cout << endl;
	BigDataList<int> BDL1(0);
	BDL1.CreateBDL();
	BDL1.TraverseBDL();
	BigDataList<int> BDL2(0);
	BDL2.CreateBDL();
	BDL2.TraverseBDL();
	BigDataList<int> Reslut(0);
	Reslut=BDL1 + BDL2;
	Reslut.TraverseBDL();


}

