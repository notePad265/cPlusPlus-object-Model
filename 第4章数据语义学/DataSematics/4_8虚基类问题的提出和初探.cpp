
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Grand //爷爷类
{
public:
	//int m_grand;
};

class A1 : virtual public Grand//直接父类A1
{
public:
};

class A2 : virtual public Grand//直接父类A2
{
public:
};

class C1 :public A1, public A2
{
public:
};


int main()
{
	/*
	 * 4_8虚基类问题的提出和初探
	 * 一：虚基类（虚继承/虚派生）问题的提出
	 * 一个类(孙子类)的两个父类继承自同一个爷爷类，会导致爷爷类的数据成员在孙子类中有两份。
	 * 传统多重继承造成的 ：空间问题，效率问题，二义性问题；
	 * 爷爷类叫虚基类，父类的继承方式叫虚继承。
	 */
	
	cout << sizeof(Grand) << endl;//1
	cout << sizeof(A1) << endl;//4
	cout << sizeof(A2) << endl;//4
	cout << sizeof(C1) << endl;//8

	C1 c1;
	//c1.m_grand = 12; //直接父类不虚继承爷爷类--访问不明确，名字冲突，二义性；
	//引入虚基类之后，就不会出现访问不明确的问题了
	//c1.A1::m_grand = 13;
	//c1.A2::m_grand = 15;

	//虚基类，让Grand类只被继承一次；
	
	/*二：虚基类初探
	 *两个概念：(1)虚基类表 vbtable(virtual base table).(2)虚基类表指针 vbptr(virtual base table pointer)
	 *当Grand A1 A2 C1类全部是空类的时候，使用sizeof运算符值分别为1，4，4，8
	 *空类sizeof(Grand) ==1好理解；
	 *virtual虚继承之后，A1,A2里就会被编译器插入一个虚基类表指针，这个指针，有点成员变量的感觉
	 *A1,A2里因为有了虚基类表指针，因此占用了4个字节
	 *C1继承两个虚基类表指针，所以占有8个字节
	*/
	A1 a1;//查看a1，a2中的内容，内容就是虚基类表的地址--从右向左侧读：：--30 6b 8d 00 
	A2 a2;//---3c 6b 8d 00
	//虚基类表指针，用来指向虚基类表（后续谈）。


	system("pause");
	return 1;
}
/*
 * 查看分配
 *	1. cl /d1 reportSingleClassLayoutGrand文件名.cpp  (注意没有看空格)
 *	cl /d1 reportSingleClassLayoutA1文件名.cpp
 *	cl /d1 reportSingleClassLayoutC1文件名.cpp
 *	
 */