#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;



class MBTX 
{
public:
	int m_i;
	int m_j;
	virtual void myFunctionVirtual()
	{
		cout << "vvvvvvvvvvvvvvvvvvvvvv" << endl;
	}
};

int main(void)
{
	MBTX mb;//父类的构造函数被子类合成的构造函数调用

	system("pause");
	return 0;
}
/*
* (1)问题：编译器会在哪些必要的时候帮助我们合成默认的构造函数？？？
* 情况3：如果一个类含有虚函数，但该类没有任何构造函数时
*	因为虚函数的存在：
*		1.编译器会给我们生成一个基于该类的虚函数表(vtbl),vftable  =virtual function table
*		2.编译器合成默认构造函数，并把类的虚函数表地址赋值给类对象的虚函数表指针（赋值语句）
*			也就是在构造函数中添加一句赋值语句
*			我们可以把虚函数表指针看成一个我们表面上看不见的类对象成员。
*		问题：为什么把虚函数处理这么麻烦？？
*			因为虚函数的调用存在一个多态问题，所以许哟啊用到虚函数表指针，第三章详细讨论。
*
	40301040 flags
         Initialized Data
         COMDAT; sym= "const MBTX::`vftable'" (??_7MBTX@@6B@)
         4 byte align
         Read Only

RAW DATA #2B
  00000000: 00 00 00 00 00 00 00 00                          ........

RELOCATIONS #2B
                                                Symbol    Symbol
 Offset    Type              Applied To         Index     Name
 --------  ----------------  -----------------  --------  ------
 00000000  DIR32                      00000000        CE  ??_R4MBTX@@6B@ (const MBTX::`RTTI Complete Object Locator')
 00000004  DIR32                      00000000        88  ?myFunctionVirtual@MBTX@@UAEXXZ (public: virtual void __thiscall MBTX::myFunctionVirtual(void))


如果我们自己给MBTX中写入自己的构造函数，并继承自MBTXPARENT类，编译器增加了代码？？--这里代码没写出
	1.增加了生成类MBTX的虚函数表vftable
	2.调用了父类的构造函数。
	3.因为虚函数的存在，把类的虚函数表地址赋值给类对象的虚函数表指针。
		当我们有自己的默认构造函数时候，编译器会根据需要扩充我们自己写的构造函数代码，比如调用父类构造函数，给类对象的虚函数表指针赋值
	编译器干了很多事情，没有默认构造函数是必要情况下会帮助我们合成默认构造函数，如果我们有默认构造函数，编译器会根据需要帮助我们扩充构造函数代码。

* (2)
*/
