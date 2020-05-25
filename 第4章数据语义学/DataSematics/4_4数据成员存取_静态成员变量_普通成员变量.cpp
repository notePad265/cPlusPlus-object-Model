#include <iostream>
#include <ctime>
#include <stdio.h>
using namespace std;

class FAC
{
public:
	int m_fai;
	int m_faj;
};

class MYACLS : public FAC
{
public:
	int m_i;
	static int m_si; //声明而不是定义
	int m_j;

	void myfunc()
	{
		m_i = 5;
		m_j = 6;
	}
};

int MYACLS::m_si = 10; //这个是定义


int main()
{
	/*
	 * 1.静态成员变量的存取
	 * 类的静态成员变量，可以当做一个全局量，但是他只在类的空间内可见；引用时用 类名::静态成员变量名
	 * 类中的静态成员变量只有一个实体，保存在可执行文件的数据段的；
	 */

	MYACLS myobj;
	MYACLS *pmyobj = new MYACLS();

	//静态成员的访问
	cout << MYACLS::m_si << endl;//通过类名字
	cout << myobj.m_si << endl;//通过对象名字
	cout << pmyobj->m_si << endl;//通过对象指针

	//这3行汇编代码没有任何差别
	MYACLS::m_si = 1;
	myobj.m_si = 2;
	pmyobj->m_si = 3;

	//对象的普通成员变量--每个对象的普通成员变量地址不同
	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);

	//静态成员变量的地址相同，是一个对象，地址相同
	printf("MYACLS::m_si = %p\n", &MYACLS::m_si);
	printf("myobj.m_si = %p\n", &myobj.m_si);
	printf("pmyobj->m_si = %p\n", &pmyobj->m_si);

	//2.非静态成员变量的存取（普通的成员变量），存放在类的对象中。存取通过类对象（类对象指针）

	pmyobj->myfunc();
	//编译器角度--插入一个隐藏的参数this指针：MYACLS::myfunc(pmyobj)
	//MYACLS::myfunc(MYACLS *const this)
	//{
	//this->m_i = 5;
	//this->m_j = 5;
	//}
	
	//对于普通成员的访问方式，编译器是把类对象的首地址加上成员变量的偏移值；
	// &myobj + 4  = &myobj.m_j
	cout << "222222222222222222222222222222222222222222222222222222" << endl;
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i);//偏移8字节 ----继承的父类中有2个int，所以第一个变量偏移8
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);//偏移12字节

	pmyobj->myfunc();
	pmyobj->m_faj = 7;

	//通过对象和对象指针访问有什么区别吗？？？没有明显区别，当有虚基类，孙子类去访问爷爷类的有区别。无法直接访问偏移值
	myobj.m_i = 15;
	pmyobj->m_i=15;

	system("pause");
	return 1;
}
/*1.静态成员变量的存取
 *	静态成员变量保存在数据段.data段，不占用类的空间，访问可以使用类名，对象名字，对象指针。
 *
 *2.普通成员变量按照定义存储在创建的类对象中。
 *访问时使用类对象地址加成员变量偏移值进行访问。
 *注意：
 *	1.虚函数表指针占有头4个字节，如果有虚函数的话。
 *	2.继承的父类的成员函数在虚函数后面。然后才是类自己的成员变量。
 *
 *	虚函数表指针
 *	父类成员变量
 *	类成员变量
 *2019年12月15日16点49分
 * 
 */

