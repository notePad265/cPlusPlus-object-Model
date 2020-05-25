#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
	int a = 100;
};

//static成员变量
class B
{
public:
	static  int a;
	static  int b;
};

//static函数
class C
{
public:
	static  int a;
	static  int b;
public:
	void myFunction() {};//普通成员函数
	static  int myFunctionStatic() { return 0; }//静态成员函数
};

//4.虚函数
class D
{
public:
	virtual  void myFunction01() {}
	virtual  void myFunction02() {}
	virtual  void myFunction03() {}
	virtual  void myFunction04() {}
	virtual  void myFunction05() {}

};

//5内存对齐
class E
{
public:
	char a;//1个字节
	int b;//4个字节
};

class myObject//类对象占有8个字节
{
public:
	myObject(){}//构造函数
	virtual ~myObject() {}//构造函数
	float getValue()const//普通成员函数
	{
		return m_value;
	}

	static int s_getCount()//静态成员函数
	{
		return static_count;
	}

	virtual void virtualFunction(){}//虚函数
	
protected:
	float m_value;//普通成员变量--占有4个字节
	static int static_count;//静态成员变量
};

int main(void)
{
	//1.非静态的成员变量跟着类对象走(存储在对象内部),
	A obj_a;
	cout << sizeof(obj_a) << endl;//4
	/*
	 * 查看内存：
	 * +		&obj_a	0x001ff824 {a=100 }	A *
	 * 0x001FF824  64 00 00 00 cc cc cc cc d2 aa ca  d...???????
	 */
	
	//2.静态成员变量和对象没有关系，
	B obj_b;
	cout << sizeof(B) << endl;//1
	cout << sizeof(obj_b) << endl;//
	//结论：静态成员变量是跟着类走的，和类对象无关

	//3静态成员函数和普通成员函数都不占有类对象内存
	C obj_c;
	cout << sizeof(obj_c) << endl;//1
	cout << sizeof(C) << endl;//1

	//4.虚函数--不管几个虚函数，都是占有4个字节
	D obj_d;
	cout << sizeof(D) << endl;//4
	cout << sizeof(obj_d) << endl;//4

	//内存字节对齐
	E obj_e;
	cout << sizeof(obj_e) << endl;//8


	//这个对象内存分析图
	myObject myobj_o;
	cout << sizeof(myobj_o) << endl;//8--m_value占有4个字节，虚函数表占有4个字节
	
	system("pause");
	return 0;
}
/*
* (1)对象内存结构的发展和演化
*	c++对象模型是一个逐步发展演化建立起来的。
*		1.非静态的成员变量跟着类对象走(存储在对象内部),也就是每个类对象都有自己的成员变量。
*		2.静态成员变量和对象没有关系，肯定不会保存在对象内部，换句话说，静态成员变量是保存在对象外面的
*			(占用的内存空间和类对象无关)
*		3.成员函数：不管静态还是非静态全部都保存在类对象之外，所以不管几个成员函数，不管是不是静态成员函数，对象的sizeof(object)都是不增加的。
*		4.虚函数-不管几个虚函数，虚函数都是占有4个字节。
*			(1).为什么会多4个字节？？
*			这个类中只要有一个虚函数，那么这个类会产生一个指向虚函数的指针。
*			类中有两个虚函数，这个类就会产生两个指向虚函数的指针。
*			也就是说，一个类中有多少个虚函数，类就产生多少个指向虚函数的指针一一对应。
*			指向虚函数的指针我们要有地方存放，存放在一个表格里面，这个表格我们就称为“虚函数表virtual table[vtbl]”。(指针里面存放的是函数的入口地址)
*			这个虚函数表一般是保存在可执行文件中的，在程序执行的时候装载到内存中。
*
*			注意：虚函数表是类产生的，不是对象产生的。虚函数表是跟着类走的。
*
*			(2)说说类对象，为什么类对象增加4个字节？？
*			其实因为有了虚函数的存在，导致系统向类对象中添加了一个指针，这个指针正好指向虚函数表，这个指针叫vptr指针。虚函数表指针
*			也就是说：vptr指针指向类中的虚函数表。系统在产生对象的时候会在适当的时候（比如构造函数中通过增加额外的代码来给值）让虚函数表指针【vptr】指向虚函数表。
*总结：
*	1.对于类中的静态数据成员，不计算在sizeof()内
*	2.普通成员函数和静态成员函数不计算在类对象的sizeof()内
*	3.虚函数不计算在类对象的sizeof()内，但是虚函数会让类对象的sizeof()增加4个字节以容纳虚函数表指针vptr。
*	4.虚函数vtbl是基于类的，和对象无关，不是基于对象的。
*	5.如果有多个数据成员，为了提高访问速度，某些编译器可能会将数据成员所占有的内存比例进行调整。内存对齐
*	6.不管什么类型的指针，char* ,int*,指针所占有的内存大小是固定的，32环境是4个字节，64linux环境，虚函数表指针，指针占有8字节
* (2)总结类型对象大小的组成：
*	1.非静态成员变量所占的内存总量以及这些成员变量之间内内存对齐所占用的额外内存，以及若有虚函数，会产生虚函数表指针vptr。
*	当然，如何类之间是多重继承关系，并且每个父类都有虚函数，后续会探讨。
* (3)
* (4)
* (5)
* (6)(7)
*/
