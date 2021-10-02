#include<iostream>
#include<cstring>
#define wrong 99
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
	int DeleteNode(Node* cur)
	{
		Node* p = cur;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		return p->data;
		delete p;
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
		if (head->data == 1) cout << "-";
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
				int sum = p->data + q->data + c; //每一位上面的和等于对应位相加再加上进位
				
				Result.DeverseInsert(sum % 10, t);//从低位向高位插入，起点在尾部，倒叙插入链表
				c = sum > 9 ? 1 : 0;

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
			int sum;
			if (flag == 1)
			{//被加数位数多，录入p
				if (p != this->head)
				{
					sum = p->data + c;
					Result.DeverseInsert(sum % 10, t);	//倒叙插入，高位在前		
					cout << "c=" << c << endl;
					c = sum > 9 ? 1 : 0;                  //进位处理
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
					sum = q->data + c;
					Result.DeverseInsert(sum % 10, t);	//倒叙插入，高位在前		
					c = sum > 9 ? 1 : 0;   //进位处理
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
	BigDataList operator-(const BigDataList& rhs)
	{
		int min_size = rhs.ListSize > this->ListSize ? this->ListSize : rhs.ListSize;//最小位数
		int max_size = rhs.ListSize < this->ListSize ? this->ListSize : rhs.ListSize;//最大位数
		int distance = max_size - min_size;                                            //位数之差

		cout << "maxsize=" << max_size << endl;
		BigDataList Result;    //结果存储对象
		int c = 0;              //表示借位，借位存储器，defalut:0
		NodePointer p, q, t;
		t = Result.tail;       //乘积录入起始位,从低位开始录入
		p = NULL;
		q = NULL;
		/////////////////////////////////////////////////

        /*通过判断后，确定大数减小数，确保借位不会超前*/
		int comp = compare(*this, rhs);
		cout << "comp=" << comp << endl;
		switch(comp)
		{
			case -1:// 减数<被减数
				q = this->tail->prev;   //被减数起始位,最低位
				p = rhs.tail->prev;     //减数起始位，最低位
				Result.head->data = 1;  //符号位为-：1
				break;
			case 0:// 减数=被减数
				Result.Insert(0, Result.head);
				return Result;
				break;
			case 1:// 减数>被减数
				p = this->tail->prev;  //被减数起始位,最低位
				q = rhs.tail->prev;    //减数起始位，最低位
				Result.head->data = 0; //符号位为+：0
				break;
		}

		/////////////////////////////////////////////////
		for (int i = 0; i < min_size; i++)
		{
			if (p != this->tail && q != rhs.tail)//去除链表端点
			{
				int difference;//差存储器
				difference = p->data - q->data - c;   //差值计算
				c = difference < 0 ? 1 : 0;    //借位判断
				cout << difference << endl;
				if (i + 1 != min_size && difference < 0) difference = difference + 10;//借位给差值（positive number)	

				if (distance == 0 && i + 1 == min_size && difference == 0) break;  //差值最高位为0时不输入
				Result.DeverseInsert(difference, t);//从低位向高位插入，起点在尾部，倒叙插入链表
				/*  移位  */
				t = t->prev;
				p = p->prev;
				q = q->prev;
			}
		}
		for (int i = 0; i < distance; i++)
		{//加数与被加数位数不等
				if (p != this->head)
				{
					int difference;//差存储器
					difference = p->data - c;
					c = difference < 0 ? 1 : 0;
					if (i + 1 != distance && difference < 0) difference = difference + 10;//计算差值（positive number)			
					if (i + 1 == min_size&& difference == 0) break;  //差值最高位为0时不输入
					Result.DeverseInsert(difference, t);//从低位向高位插入，起点在尾部，倒叙插入链表
					/*  移位  */
					t = t->prev;	
					p = p->prev;
				}
		}
		return Result;
	}
	BigDataList operator*(const BigDataList& rhs)
	{
		int min_size = rhs.ListSize > this->ListSize ? this->ListSize : rhs.ListSize;//最小位数
		int max_size = rhs.ListSize < this->ListSize ? this->ListSize : rhs.ListSize;//最大位数
		int distance = max_size - min_size;                                            //位数之差
		int M = rhs.ListSize + 1;
		cout << "maxsize=" << max_size << endl;
		BigDataList* Result = new BigDataList [M];
		Result[rhs.ListSize].Insert(0, Result[rhs.ListSize].head); //初始化
		int c = 0;              //表示借位，借位存储器，defalut:0
		NodePointer multiplicand, multiplier;
		/////////////////////////////////////////////////

		int comp = compare(*this, rhs);
		cout << "comp=" << comp << endl;
		multiplicand = this->tail->prev;  //被减数起始位,最低位
		multiplier = rhs.tail->prev;    //减数起始位，最低位
		for (int i = 0; i < rhs.ListSize&&multiplier!= rhs.head; ++i)
		{
			BigDataList Temp;//辅助对象
			Result[i].DeverseInsert(0, Result[i].tail);//defalut:Result存储0
			Temp = *this;
			cout << "mutliplier=" << multiplier->data << endl;
			for (int j = 0; j < multiplier->data; j++)
			{
				Result[i] = Result[i] + Temp;  //利用重载+
			}		
			for (int k = 0; k < i; k++) Result[i].DeverseInsert(0, Result[i].tail);//进位
			cout << "[" << i << "]:"; Result[i].TraverseBDL();
			multiplier = multiplier->prev;                                         //乘数进位
			Result[rhs.ListSize] = Result[rhs.ListSize] + Result[i];
		}
		return Result[rhs.ListSize];
	}
	BigDataList operator^(const int& exponent)
	{//exponent>0
		cout << "exponent=" << exponent;
		BigDataList res, temp;
		res.Insert(1, res.head);
		temp = *this;     
		if (exponent == 0) return res;
		else
		{
			for (int i = 0; i < exponent; ++i)
			{
				res = res * temp;  //利用重载*
			}
			return res;
		}

	}
	int compare(const BigDataList& BDL1,const BigDataList& BDL2)
	{//BDL1大：返回1  BDL2大：返回-1； 相等：返回0
		if (BDL1.ListSize > BDL2.ListSize) return 1;
		else if (BDL1.ListSize < BDL2.ListSize) return -1;
		else if (BDL1.ListSize == BDL2.ListSize)
		{
			int i;
			NodePointer p = BDL1.head->next;
			NodePointer q = BDL2.head->next;
			for (i = 0; i < BDL1.ListSize; ++i)
			{
				if (p->data == q->data)
				{
					p = p->next;
					q = q->next;
					continue;
				}
				else if (p->data > q->data) return 1;
				else if (p->data < q->data) return -1;
			}
			if (i = BDL1.ListSize) return 0;
		}
		else return wrong;
	}
};
int main()
{
	/*测试代码1
	LinkList<int>* L1=new LinkList<int>;
	L1->init();
	L1->node=L1->Insert(10, L1->head);
	cout << L1->node->data ;
	*/
	cout << endl;
	BigDataList<int> BDL1(0);
	BDL1.CreateBDL();
	BDL1.TraverseBDL();
	BigDataList<int> BDL2(0);
	BDL2.CreateBDL();
	BDL2.TraverseBDL();
	BigDataList<int> Reslut(0);
	Reslut = BDL1^2;
	cout << "BDL1 * BDL2=";
	Reslut.TraverseBDL();
}                                                                                                                                                                                                                                                                                                                                                                        
