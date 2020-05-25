#include <iostream>
#include <stdio.h>
using namespace std;

class Base
{
public:
	int m_bi;
	virtual void mybvirfunc() {}
};

class MYACLS :public Base
{
public:
	int m_i;
	int m_j;

	virtual void myvirfunc() {} //虚函数
	MYACLS()
	{
		int abc = 1; //这行代码没有实际意义 只是方便加断点
		/*
		 *1.创建虚函数表 2.虚函数表指针指向虚函数表
		 00CE1853  mov         eax,dword ptr [this]  
			00CE1856  mov         dword ptr [eax],offset MYACLS::`vftable' (0CE7B34h)  
					int abc = 1; //这行代码没有实际意义 只是方便加断点
			00CE185C  mov         dword ptr [abc],1  
				}
			00CE1863  mov         eax,dword ptr [this]  
		 */
	}
	~MYACLS()
	{
		int def = 0;//方便加断点
	}
};

int main()
{




	cout << sizeof(MYACLS) << endl;//16
	printf("MYACLS::m_bi = %d\n", &MYACLS::m_bi);//4
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i);//8
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);//12
	//Base类有虚函数时候是 4 8  12  没有虚函数的时候是0 8 12

	MYACLS myobj;//这里插入断点，跳到构造函数，查看反汇编代码，可以看到虚函数表指针指向虚函数的代码
	myobj.m_i = 3;
	myobj.m_j = 6;//查看内存，找出对应的值
	myobj.m_bi = 9;
	/*						虚函数表指针
	 0x00CFFDB0  cc cc cc cc 40 7b 98 00 09 00 00 00  ????@{?.....
	 0x00CFFDBC  03 00 00 00 06 00 00 00 cc cc cc cc  ........????
	 */


	system("pause");
	return 1;
}

/*4_6单类单继承带虚函数的数据成员布局
 * 	一：单个类带虚函数的数据成员布局
 * 	类中引入虚函数时，会有额外的成本付出
 * 	(1)编译的时候，编译器会产生虚函数表，参考三章五节
 * 	(2)对象中会产生 虚函数表指针vptr，用以指向虚函数表的，
 * 	(3)对象创造中编译器在构造函数中使虚函数表指针指向虚函数表，增加或者扩展构造函数，增加给虚函数表指针vptr赋值的代码，让vptr指向虚函数表；
 * 	(4)如果多重继承，比如你继承了2个父类，每个父类都有虚函数的话，每个父类都会有vptr，那继承时，
 * 		子类就会把这两根vptr都继承过来，
 *		如果子类还有自己额外的虚函数的话，子类与第一个基类共用一个vptr（三章四节）；
 * 	(5)析构函数中也被扩展增加了虚函数表指针vptr相关的赋值代码，感觉这个赋值代码似乎和构造函数中代码相同；

	二：单一继承父类带虚函数的数据成员布局--看图

	三：单一继承父类不带虚函数的数据成员布局
	与单一继承父类带虚函数的数据成员布局图相同
	但是m_bi的偏移值是0怎么理解？？
	因为m_bi的偏移值是相对于Base类的偏移值是0。
 */
