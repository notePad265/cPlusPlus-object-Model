#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Base
{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	//virtual void pvfunc() = 0;
};

class Derive :public Base {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Derive::g()" << endl; }//重写
	//void myselffunc() {} //只属于Derive的函数
};
int main()
{
	//一：单继承下的虚函数
	Derive myderive;
	Derive *pmyderive = &myderive;
	pmyderive->f();
	pmyderive->g();
	pmyderive->h();
	pmyderive->i();
	//查看反汇编代码，可以看到：子类对象的虚函数内存分布是和父类一样，然后把i()虚函数放在子类对象内存最后面。
	
	Base *pb = new Derive();  //基类指针 指向一个子类对象
	pb->g();
	//编译器视角
	//(*pb->vptr[1])(pb);//虚函数里面隐含一个this指针，这里传递过去pb

	Derive myderive02;
	Base &yb = myderive02; //基类引用 引用 一个子类对象
	yb.g();

	//我们唯一需要在执行期间知道的东西就是 通过 哪个虚函数表(父类虚函数表和子类虚函数表)来调用虚函数，（父类的还是子类的);
	//结论：都是走的子类的虚函数表

	/*
	 *二：回顾和一些小试验
	 *虚函数地址：编译期间知道,写在了可执行文件中,编译期间已经构建出来。
	 *vptr编译期间产生。编译器在构造函数中插入了给vptr赋值的代码；当创建对象时，因为要执行对象的构造函数，此时vptr就被赋值；
	 */

	Derive a1;
	Derive a2;//类Derive里都是虚函数的时候，a1，a2存储的内容应该是相同的，存储的都是虚函数表的地址
	//0x003c9b80 {FunctionSemantics.exe!const Derive::`vftable'} {0x003c14ab {FunctionSemantics.exe!Base::f(void)}, ...}
	Derive *pa3 = new Derive();


	Base b1;//当子类没有任何成员变量和函数，子类仍然有自己的虚函数表。

	
	//结论：纯虚函数也在虚函数表中。
	cout << sizeof(Base) << endl;//注释掉父类Base的所有虚函数，只保留纯虚函数是4

	system("pause");
	return 1;
}
