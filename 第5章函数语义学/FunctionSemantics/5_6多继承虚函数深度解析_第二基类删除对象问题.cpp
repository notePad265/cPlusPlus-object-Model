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

	virtual ~Base()
	{
		int abc;
		abc = 1;
	}

};

class Base2
{
public:
	virtual void hBase2() {

		cout << "Base2::hBase2()" << endl;
	}

	virtual ~Base2() {
		int abc;
		abc = 1;
	}
};

class Derive :public Base, public Base2
{
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Derive::g()" << endl; }
	void myselffunc() {} //只属于Derive的函数

	virtual ~Derive()
	{
		int abc;
		abc = 1;//仅仅是为了调试方便，无意义代码
	}
};
int main()
{
	//一：多继承下的虚函数
	//多重继承复杂性体现在后边这个基类上,存在this指针调整的问题--这里Base1的this指针不需要调整，Base2的this指针需要调整
	Base2 *pb2 = new Derive();//pb2指向的地址是经过this指针调整后的地址，pb2是指向Base2 这个类中的子对象，不是指向子对象开始位置。
	//编译器视角
	//Derive *temp = new Derive();
	//Base2 *pb2 = temp + sizeof(Base); // tem类型决定后面加多少，实际上是sizeof(Base) * sizeoeof(Base2);//跳过Base，搭配Base2对象等价于下面
	//Base2 *pb2 = (Base2 *)((char *)temp + sizeof(Base));
	//double类型变量+1，实际上是8个字节

	delete pb2;//使用调整后的this指针删除内存空间报异常，如何解决？？让Derive类的析构函数是一个虚析构函数。


	/*
	 *二：如何成功删除用第二基类指针new出来的继承类对象--让Derive类的析构函数是一个虚析构函数。(或者让Base2，Base1类有虚析构函数)
	 *a)我们要删除的实际是整个Derive()对象
	 *b)要能够保证Derive()对象的析构函数被正常调用
	 *c)编译器会调用Base2的析构函数，还是调用Derive的析构函数呢？
	 *d)执行delte pb2时，系统的动作会是？--一定要调用Derive类的析构函数才对。
	 *	d.1)如果Base2里没有析构函数,编译器会直接删除以pb2开头的这段内存，一定报异常，因为这段内存压根就不是new起始的内存，从中间删除了。
	 *	d.2)如果Base2里有一个析构函数，但整个析构函数是个普通析构函数（非虚析构函数），那么当delte pb2，
	 *		这个析构函数就会被系统调用,但是delete的仍旧是pb2开头这段内存，所以一定报异常。因为这段内存压根就不是new起始的内存；
	 *		析构函数如果不是虚函数，编译器会实施静态绑定，静态绑定意味着你delete Base2指针时，删除的内存开始地址就是pb2的当前位置；
	 *		所以肯定是错误的
	 *	d.3)如果Base2里是一个虚析构函数，
	 *	编译器内部
			 *	1.~Dervice()调用子类Derive的析构函数
			 *	2.~Base2()调用父类2的虚析构函数
			 *	3.~Base()调用父类1的虚析构函数
	d.4)Derive里就就算没有虚析构函数，因为Base2里 有虚析构函数，编译器也会为此给Derive生成虚析构函数，为了调用~Base2()和~Base()虚析构函数；
		e)老师要求大家，凡是涉及到继承的，所有类都要求大家些虚析构函数;

	 */

	//测试代码，用于绘制虚函数表--在视频5-6 46：27秒
	Base *pbm = new Base();
	/* [0] = 0x009414ab {FunctionSemantics.exe!Base::f(void)}
	 * [1] = 0x009414b5 {FunctionSemantics.exe!Base::g(void)}
	 * [2] = 0x009414b0 {FunctionSemantics.exe!Base::h(void)}
	 * [3] = 0x009414fb {FunctionSemantics.exe!Base::`vector deleting destructor'(unsigned int)}析构函数
	 */
	Base2 *pb222 = new Base2();
	/*[0] = 0x009414ec {FunctionSemantics.exe!Base2::hBase2(void)}
	 *[1] = 0x009414e2 {FunctionSemantics.exe!Base2::`vector deleting destructor'(unsigned int)}析构函数
	 * 
	 */
	Derive *p11212 = new Derive();
	/*继承Base和Base2两个虚函数表
	 *__vfptr = 0x00949ba4 {FunctionSemantics.exe!const Derive::`vftable'{for `Base'}} {0x009414ab {FunctionSemantics.exe!Base::f(void)}, ...}
	 *	[0] = 0x004814ab {FunctionSemantics.exe!Base::f(void)}
	 *	[1] = 0x004814a6 {FunctionSemantics.exe!Derive::g(void)}
	 *	[2] = 0x004814b0 {FunctionSemantics.exe!Base::h(void)}
	 *	[3] = 0x004814f6 {FunctionSemantics.exe!Derive::`vector deleting destructor'(unsigned int)}
	  __vfptr = 0x00949bc4 {FunctionSemantics.exe!const Derive::`vftable'{for `Base2'}} {0x009414ec {FunctionSemantics.exe!Base2::hBase2(void)}, ...}
		[0] = 0x004814ec {FunctionSemantics.exe!Base2::hBase2(void)}
		[1] = 0x004814dd {FunctionSemantics.exe![thunk]:Derive::`vector deleting destructor'`adjustor{4}' (unsigned int)}

	Derive 类的第二个虚函数表中发现了thunk字样：
	一般这玩意用在多重继承中（从第二个虚函数表开始可能就 会有）；用于this指针调整。这玩意其实是一段汇编代码，这段代码干两个事情：
	(1)调整this指针，调整到Derive类对象的开始位置，而不是Base2类对象位置。
	(2)调用Derive析构函数
	 */
	p11212->g();
	p11212->i(); //走虚函数表

	Derive dddd;
	dddd.i(); //直接调用虚函数




	system("pause");
	return 1;
}
