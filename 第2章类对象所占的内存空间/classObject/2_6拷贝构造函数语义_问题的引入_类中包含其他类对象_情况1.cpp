#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class AMember
{
public:
	int m_testSon;
};

class A
{
public:
	int m_i;
	AMember asubObj;
};


class CTB
{
public:
	CTB(const CTB&b)
	{
		cout << "ctb拷贝构造函数执行了" << endl;
	}
	CTB()
	{
		
	}
};

class B
{
public:
	CTB m_ctb;
};



int main(void)
{
	A obj_a;
	obj_a.m_i = 15;
	obj_a.asubObj.m_testSon = 120;
	A obj_02 = obj_a;//我们理解这里是 调用拷贝构造函数
	/*obj_02.asubObj.m_testSon 也被赋值为120
	 *当一个类包含另一个类对象作为成员变量的时候，仍然没有合成拷贝构造函数。
	 *总结：
	 *	1.A obj_02 = obj_a;是拷贝构造一个对象
	 *	2.我们自己没有写类A的拷贝构造函数，编译器也没有帮助我们生成拷贝构造函数
	 *	3.通过dumpbin发现确实成员变量的值被拷贝到另一个对象的对应变量中，这是编译器内部的一些直接数据拷贝实现方法。
	 *		比如类中有类对象成员变量asubObj，也会递归式去拷贝，这是编译器内部的“按位拷贝”。
	 *		就是将一个对象在内存空间的值拷贝到零一对象的对应内存空间中去，有种内存拷贝的感觉。
	 */


	//情况1
	CTB ctb01;
	B obj_b;
	obj_b.m_ctb = ctb01;
	B obj_b02 = obj_b;//调用拷贝构造函数
	/*
		                                                 Symbol    Symbol
	 Offset    Type              Applied To         Index     Name
	 --------  ----------------  -----------------  --------  ------
	 0000000C  DIR32NB                    00000000        99  ??0B@@QAE@ABV0@@Z (public: __thiscall B::B(class B const &))
	 00000058  SECREL                     00000000        99  ??0B@@QAE@ABV0@@Z (public: __thiscall B::B(class B const &))
	 0000005C  SECTION                        0000        99  ??0B@@QAE@ABV0@@Z (public: __thiscall B::B(class B const &))
	 */
	

	system("pause");
	return 0;
}
/*
* (1)拷贝构造函数语义_问题的引入_对象赋值一定调用了拷贝构造函数吗？？
*	当一个类包含另一个类对象作为成员变量的时候，会“递归拷贝”。
* 
*问题：什么是“必要的时候”？
*	某些情况下，我们不写自己的拷贝构造函数，编译器就会帮助我们合成出拷贝构造函数。
*	这个合成出来的拷贝构造函数又要做什么事情呢？？
*	
*	情况1。 如果一个类B没有自己的拷贝构造函数，但是含有一个类CTB类型的对象作为成员变量，并且类CTB含有自己的拷贝构造函数。
*			当代码中有涉及到类A的拷贝构造时候，编译器就会给类B合成一个拷贝构造函数.
*			编译器合成的拷贝构造函数去调用包含类对象的拷贝构造函数。类B的拷贝构造函数去调用CTB类对象的拷贝构造函数。
*			
*
*
* (3)
* (4)
* (5)
* (6)(7)
*/
