#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class Base
{
public:
	virtual void myVirtualFunction01() { cout << "myFunction01" << endl; }
	virtual void myVirtualFunction02() { cout << "myFunction02" << endl; }
	virtual void myVirtualFunction03() { cout << "myFunction03" << endl; }

};

class Derive :public Base
{
	//重写父类myVirtualFunction02()函数
	void myVirtualFunction02() override
	{
		cout << "这是子类重写的myVirtualFunction02函数" << endl;
	}
};

int main(void)
{
	typedef void(*Func)(void);//定义一个函数指针类型
	Derive derive01;
	long*pDe = (long*)(&derive01);
	long* VptrDerive = (long*)(*pDe);//对象pDe中存储的就是虚函数表指针。0x005c8b78 {virtualFunction.exe!const Derive::`vftable'} {6034243}
	//long* VptrDerive = (long*)(derive01);//使用上面三行的原因是不能之间把一个Derive对象转换为指针
	Func f1 = (Func)VptrDerive[0];//0x005c1343 {virtualFunction.exe!Base::myVirtualFunction01(void)}
	Func f2 = (Func)VptrDerive[1];//0x005c1217 {virtualFunction.exe!Derive::myVirtualFunction02(void)}
	Func f3 = (Func)VptrDerive[2];//0x005c1082 {virtualFunction.exe!Base::myVirtualFunction03(void)}
	Func f4 = (Func)VptrDerive[3];//0x00000000
	Func f5 = (Func)VptrDerive[4];

	Derive derive02 = derive01;//调用拷贝构造函数
	long*pDe02 = (long*)(&derive02);
	long* VptrDerive02 = (long*)(*pDe02);
	//两个对象指向类的虚函数表

	Base base = derive01;//使用子类给父类赋值
	long* pBase = (long*)(&base);
	long*vptrBase = (long*)(*pBase);//父类的虚函数表指针  0x00f7f9ac {6064948}
	Func fb1 = (Func)vptrBase[0];//0x005c1343 {virtualFunction.exe!Base::myVirtualFunction01(void)}
	Func fb2 = (Func)vptrBase[1];//0x005c116d {virtualFunction.exe!Base::myVirtualFunction02(void)}
	Func fb3 = (Func)vptrBase[2];//0x005c1082 {virtualFunction.exe!Base::myVirtualFunction03(void)}
	Func fb4 = (Func)vptrBase[3];//0x00000000
	Func fb5 = (Func)vptrBase[4];

	
	
	system("pause");
	return 0;
}
/*
* (1)
* 使用子类对象初始化父类对象，父类对象的虚函数表赋值给子类了吗？
* 切割
* 子类中属于父类的那部分会被编译器切割（区分）出来，拷贝给父类对象。
* 所以Base base = derive01;做了2个事情
*	1.生成一个base对象，
*	2.使用derive01来初始化base'对象，编译器给我们做了一个选择，derive01的虚函数指针值
*	并没有覆盖base对象的 虚函数表指针值，编译器帮助我们做了这一点。
* (4)oo 面向对象和ob基于对象概念
*	1.c++通过类的指针和引用来表示父类或者子类对象来支持多态，这是一个程序设计风格。
*		这就是我们说的面向对象object-oriented model
*	2.object-based也叫AD，抽象数据模型 abstract datatype model
*		不支持多态，没有虚函数表。因为函数调用的解析不需要运行时决定，运行速度更快。
*		程序在编译期间就解析完成了函数的调用，对象内存空间更加紧凑，因为没有虚函数表和虚函数表指针。
*		但是OB的设计灵活性就差。
*	c++既支持面向兑现程序设计（继承，多态），也支持基于对象程序设计。
* (5) 
* (6)(7)
*/
