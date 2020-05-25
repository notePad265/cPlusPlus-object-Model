#include <iostream>
#include <stdio.h>
using namespace std;

class Base
{
public:
	int m_bi;
	virtual void mybvirfunc() {}

	Base()
	{
		printf("Base1::Base1()的this指针是：%p!\n", this);
	}
};

class MYACLS :public Base
{
public:
	int m_i;
	int m_j;

	virtual void myvirfunc() {} //虚函数
	MYACLS()
	{
		int abc = 1; //方便加断点
		printf("MYACLS::MYACLS()的this指针是：%p!\n", this);
	}
	~MYACLS()
	{
		int def = 0;//方便加断点
	}
};

int main()
{
	/*
	 * 	//一：4_7单一继承数据成员布局this指针偏移知识补充01
	 * 当父类带有虚函数，this指针不需要调整。
	 */

	cout << sizeof(MYACLS) << endl;
	printf("MYACLS::m_bi = %d\n", &MYACLS::m_bi);
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);

	MYACLS myobj;
	myobj.m_i = 3;
	myobj.m_j = 6;
	myobj.m_bi = 9;


	MYACLS *pmyobj = new MYACLS();
	pmyobj->m_i = 3;
	pmyobj->m_j = 6;
	pmyobj->m_bi = 9;

	
	 	/*
	 父类Base类不带虚函数：
	16
	MYACLS::m_bi = 0--相对于父类偏移为0
	MYACLS::m_i = 8
	MYACLS::m_j = 12
	Base1::Base1()的this指针是：00AFFE4C!
	MYACLS::MYACLS()的this指针是：00AFFE48!
	Base1::Base1()的this指针是：00BF522C!
	MYACLS::MYACLS()的this指针是：00BF5228!  子类指针比父类指针小4个字节  子类this+4=父类this

	 父类Base类带虚函数：
	16
	MYACLS::m_bi = 4--父类带虚函数表指针
	MYACLS::m_i = 8
	MYACLS::m_j = 12
	Base1::Base1()的this指针是：00AFF880!
	MYACLS::MYACLS()的this指针是：00AFF880!
	Base1::Base1()的this指针是：00D8CE98!
	MYACLS::MYACLS()的this指针是：00D8CE98! ---子类指针和父类指针同样大--this指针访问父类成员变量不需要访问
		
	 */
	
	system("pause");
	return 1;
}
