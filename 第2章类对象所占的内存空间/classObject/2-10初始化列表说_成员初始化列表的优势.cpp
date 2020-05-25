#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class X
{
public:
	int m_x;
	X(int value=0):m_x(value)
	{
		printf("this =%p", this);
		cout << "类型转换构造函数执行" << endl;
	}
	X(const X& t)//拷贝构造函数
	{		
		printf("this=%p", this);
		cout << "拷贝构造函数执行" << endl;
	}
	X&operator=(const X&t)
	{
		printf("this=%p", this);
		cout << "拷贝赋值运算符被调用" << endl;
		return *this;
	}
	~X()
	{
		printf("this=%p", this);
		cout << "析构函数执行" << endl;
	}
};

//class A
//{
//public:
//	X obj_x;
//	int m_a;
//	A(int temvalue)//这里构造了obj_x对象，还没有指向函数体之前就构造出来了
//	/*
//	 * 站在编译器的角度：
//	 * X obj_x;
//	 * obj_x.X::();
//	 */
//	{
//		obj_x = 1000;//这一行导致3个动作
//		/*
//		 * 生成一个临时对象，调用类型转换构造函数，调用拷贝赋值运算符进行赋值给obj_x;
//		 * 然后调用析构函数释放自己。
//		 */
//		m_a = 500;
//	}
//};


class A
{
public:
	X obj_x;
	int m_a;
	A(int temvalue):obj_x(1000)
	 /*
	站在编译器的角度
	X obj_x;
	obj_x.X::X(1000);
	 */
	{
		m_a = 500;
	}
};

void playObj()
{
	A obj_a(1000);
	/*
	 *没有使用初始化成员列表
	    this =00DAF934类型转换构造函数执行
		this =00DAF778类型转换构造函数执行
		this=00DAF934拷贝赋值运算符被调用（已经定义过的），定于初始化和赋值的区别
		this=00DAF778析构函数执行
		this=00DAF934析构函数执行

	使用成员初始化列表:
		this =00AFFBFC类型转换构造函数执行
		this=00AFFBFC析构函数执行
	 */
}

int main(void)
{
	
	playObj();
	
	system("pause");
	return 0;
}
/*
* (1)成员初始化列表的优势
*	除了必须用初始化列表的场合，我们用初始化列表的最终目的是提高程序运行效率。
*
*	大家把初始化列表中的代码看作函数体的一部分即可，编译器会自动给插入到函数体内部。
*	结论：类类型的对象初始化最好是使用成员初始化列表的方式，能提高效率。
*			简单类型，如int，char放在初始化列表还是函数体里面差别不大。
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
