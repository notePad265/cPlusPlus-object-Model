#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Grand //爷爷类
{
public:
	int m_grand;
};

class Grand2 //爷爷类2
{
public:
	int m_grand2;
	//int m_grand2_1;
};

class A1 : virtual public Grand, virtual public Grand2
{
public:
	int m_a1;
};

class A2 : virtual public Grand//, virtual public Grand2
{
public:
	int m_a2;
};

class C1 :public A1, public A2
{
public:
	int m_c1;
};

int main()
{
	/*
	 * 一：虚基类表内容之5-8字节内容分析--是个偏移量8
	 * 虚基类表 一般是8字节，四个字节为一个单位。每多一个虚基类，虚基类表会多加4个字节.虚基类表中存储的是虚基类的成员变量的偏移量。
	 * 编译器因为有虚基类，会给A1,A2类增加默认的构造函数，并且这个默认构造函数里，会被编译器增加进去代码，
	 * 给vbptr虚基类表指针赋值的代码。
	 */

	cout << sizeof(Grand) << endl;
	cout << sizeof(A1) << endl;
	cout << sizeof(A2) << endl;
	cout << sizeof(C1) << endl;

	A1 a1obj;
	/*
	A1::A1:
	...
	00DC17B9  mov         eax,dword ptr [this]  
	00DC17BC  mov         dword ptr [eax],offset A1::`vbtable' (0DC6B30h)  
	00DC17C2  mov         eax,dword ptr [this]  
	 */
	a1obj.m_grand = 2;
	a1obj.m_grand2 = 6;
	//a1obj.m_grand2_1 = 7;
	a1obj.m_a1 = 5;

	//“虚基类表指针”成员变量的首地址 + 这个偏移量 就等于 虚基类对象首地址(m_grand)。跳过这个偏移值，我们就能够访问到虚基类对象的成员变量；

	//二：继续观察各种形色的继承_虚继承_实继承
	//a)虚基类表 现在是3项， +4，+8,都是通过取得虚基类表中的偏移值来赋值的
	//b)虚基类表中的偏移量是按照继承顺序来存放的；
	//c)虚基类子对象一直放在最下边；

	//三：虚基类表内容之1-4字节内容分析  当有一个是实继承，前面会有一个实继承的成员变量 ，然后是虚基类表指针，子类成员，虚继承的成员变量，所以这里=-4
	//虚基类表指针成员变量的首地址 ，和本对象A1首地址之间的偏移量 也就是：虚基类表指针 的首地址 - A1对象的首地址

	//结论：只有对虚基类成员进行处理比如赋值的时候，才会用到虚基类表，取其中的偏移，参与地址的计算；

	return 1;
}
/*
 * 虚基类表中存储的是虚基类的成员变量的偏移量。
 * 总结：
 *	1.爷爷类叫虚基类，父类的继承方式叫虚继承。
 *	2.每个虚继承的子类都有一个虚基类指针(占4个字节)和虚基类表。当虚继承的子类被当作父类继承的时候，虚基类指针也会被继承。
 *		所以本例中，C1类包含2个虚基类指针。
 *	3.vbptr虚基类表指针（virtual base table pointer），该指针指向了一个虚基类表（virtual table），
 *		虚表中记录了虚基类(爷爷类)与本类的偏移地址；
 *		通过偏移地址，这样就找到了虚基类成员，
 *	4.虚基类表中按照对象继承的顺序排列对象的直接虚继承类到虚基类的偏移。
 *
 *总结：1.虚继承的时候子类会有虚基类表，类对象有虚基类表指针。
 *	   2.虚基类表中记录的就是子类对象和虚基类(爷爷类)成员变量的偏移值(不要多记忆，就当一个偏移量)，“虚基类表指针”成员变量的首地址 + 这个偏移量 就等于 虚基类对象首地址(m_grand)。跳过这个偏移值，
 *			我们就能够访问到虚基类对象的成员变量；
 */
