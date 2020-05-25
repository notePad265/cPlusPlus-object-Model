#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
	int a;
	A()
	{
		printf("A::A()的this指针是%p\n", this);
	}

	void myFunctionA()
	{
		printf("A::myFunctionA的this指针是%p\n", this);

	}
};

class B
{
public:
	int b;
	B()
	{
		printf("B::B()的this指针是%p\n", this);
	}

	void myFunctionB()
	{
		printf("B::myFunctionB的this指针是%p\n", this);

	}
};

class C:public A,public B
{
public:
	int c;
	C()
	{
		printf("C::C()的this指针是%p\n", this);
	}

	void myFunctionC()
	{
		printf("C::myFunctionC的this指针是%p\n", this);

	}
	//重写的函数

	void myFunctionB()
	{
		printf("C::myFunctionB的this指针是%p\n", this);

	}
};
int main(void)
{
	cout << sizeof(A) << endl;//4
	cout << sizeof(B) << endl;//4
	cout << sizeof(C) << endl;//12

	C obj_c;
	obj_c.myFunctionA();
	obj_c.myFunctionB();//调用子类重写的函数
	obj_c.B::myFunctionB();//调用父类的函数
	obj_c.myFunctionC();
	/*
	A::A()的this指针是006FF904
	B::B()的this指针是006FF908
	C::C()的this指针是006FF904
	A::myFunctionA的this指针是006FF904
	C::myFunctionB的this指针是006FF904
	B::myFunctionB的this指针是006FF908
	C::myFunctionC的this指针是006FF904
	A B C的构造函数按照先父类后子类，并按照继承顺序执行。
	类A和类C得到指针指向同一个地址。类B增加4个字节。

	派生类对象是包含父类的子对象。
	如果派生类只从一个基类继承，那么这个派生类对象的地址和基类子对象的地址相同。
	如果派生类对象同时继承多个基类，第一个基类子对象的开始地址和派生类对象的开始地址相同。
	后续的基类子对象的开始地址和派生类子对象差多少？？
	差前边的基类对象占有的内存空间，这里A类占有4个字节内存空间，所以基类A和基类B差 4个字节内存空间

	调用这个obj_c.myFunctionA()  obj_c.myFunctionC()使用001EFCE4这个指针，
	调用obj_c.myFunctionB()属于类B的函数;系统会调用this指针，使this指针增加4个字节。
	如果在C类中重写了B类的myFunctionB()函数，this指针调用本身函数不用调整。
	总结：你调用哪个子类的成员函数，this指针就会被编译器自动调整到对象内存布局中对应对象的起始地址。
	 */
	

	system("pause");
	return 0;
}
/*
* (1)this指针调整
* 一般存在于多重继承中
* (2)
*/
