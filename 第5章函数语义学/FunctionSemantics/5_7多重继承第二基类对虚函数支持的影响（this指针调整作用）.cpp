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

	virtual ~Base() {
		
	}

	virtual Base *clone() const
	{
		return new Base();
	}

};

class Base2
{
public:
	virtual void hBase2() {

		cout << "Base2::hBase2()" << endl;
	}

	virtual ~Base2()	{
	
	}

	virtual Base2 *clone() const
	{
		return new Base2();
	}
};

class Derive :public Base,public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Derive::g()" << endl; }
	void myselffunc() {} //只属于Derive的函数

	virtual ~Derive() {
		
	}	
	virtual Derive *clone() const
	{
		return new Derive();
	}
};



int main()
{
	//一：多重继承第二基类对虚函数支持的影响（this指针调整作用）
	//子类继承了几个父类，子类就有几个虚函数表

	/*
	 *多重继承下，有几种情况，第二个或者后续的基类会对虚函数的支持产生影响
	 *this指针调整,调整的目的是干什么？
	 *this指针调整的目的就是让对象指针正确的指向对象首地址，从而能正确的调用对象的成员函数或者说正确确定数据成员的存储位置。
	 */

	//a)通过指向第二个基类的指针调用继承类的虚函数；
	Base2 *pb2 = new Derive();
	delete pb2; //调用继承类的虚析构函数

	//b)一个指向派生类的指针，调用第二个基类中的虚函数
	Derive *pd3 = new Derive();
	pd3->hBase2();

	//c)允许虚函数的返回值类型有所变化--子类和父类的同名函数返回值可以不同
	Base2 *pb1 = new Derive(); //pb1指向的是Base2子对象的首地址
	Base2 *pb4 = pb1->clone(); //调用Derive::clone();
	 //执行clone()时，pb1首先会调整回指向Derivce对象的首地址，这样调用的是Derive版本的clone()

	system("pause");
	return 1;
}
