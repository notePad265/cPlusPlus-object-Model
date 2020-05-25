#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
	int m_x;
	int m_y;
	A():m_x(0),m_y(0)//初始化列表，可以使用，可以不用
	{
		
	}	
};

//1.成员变量是个引用
class B
{
public:
	int m_x;
	int m_y;
	int &m_value;
	const int myConst;
	B(int number01,int number02,int &temValue,int myc) :m_x(number01), m_y(number02),m_value(temValue),myConst(myc)//初始化列表	{
	{
		
	}
};


class BASE
{
public:
	int ba;
	int bb;
	BASE(int a,int b):ba(a),bb(b)
	{
		;
	}
};

class SON :public BASE
{
public:
	int s;
	SON(int a,int b,int ss):BASE(a,b),s(ss)
	{
		;
	}
};


//4.如果某个成员变量是类类型，并且这个成员变量的构造函数带参数

class IncludeTest
{
public:
	BASE base01;
	int i;
	IncludeTest(int in, int a, int b) :i(in), base01(a, b)
	{
		;
	}
};
int main(void)
{
	//1.成员变量是个引用
	int number01 = 12;
	int number02 = 23;
	B b(122,23,number01,23);//传递一个引用

	//3.如果类是继承一个基类，并且基类中的构造函数有参数。
	SON son01(1, 2, 3);


	//4.如果某个成员变量是类类型，并且这个成员变量的构造函数带参数
	IncludeTest it(23, 34, 45);
	system("pause");
	return 0;
}
/*
* (1)何时必须用成员初始化列表
* 有没有什么场合必须使用成员初始化列表
*	1.成员变量是个引用
*	2.是个const类型成员
*	3.如果类是继承一个基类，并且基类中的构造函数有参数。
*	4.如果某个成员变量是类类型，并且这个成员变量的构造函数带参数
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
