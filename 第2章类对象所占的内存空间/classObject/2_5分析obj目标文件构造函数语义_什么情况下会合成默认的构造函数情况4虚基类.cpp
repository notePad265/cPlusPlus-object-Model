#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;



class  GrandFather//爷爷类
{
public:
	
};

class A1:virtual public GrandFather
{
public:
	
	
};

class A2:virtual public GrandFather
{
public:
	
};

class C :public A1, public A2
{
	
};


int main(void)
{
	C obj_c;
	/*
	 *调用A1，A的构造函数
	 60501020 flags
         Code
         COMDAT; sym= "public: __thiscall C::C(void)" (??0C@@QAE@XZ)
         16 byte align
         Execute Read

RAW DATA #8
  00000000: 55 8B EC 81 EC CC 00 00 00 53 56 57 51 8D BD 34  U.ì.ìì...SVWQ.?4
  00000010: FF FF FF B9 33 00 00 00 B8 CC CC CC CC F3 AB 59  ???13...?ììììó?Y
  00000020: 89 4D F8 83 7D 08 00 74 13 8B 45 F8 C7 00 00 00  .M?.}..t..E??...
  00000030: 00 00 8B 45 F8 C7 40 04 00 00 00 00 6A 00 8B 4D  ...E??@.....j..M
  00000040: F8 E8 00 00 00 00 6A 00 8B 4D F8 83 C1 04 E8 00  ?è....j..M?.á.è.
  00000050: 00 00 00 8B 45 F8 5F 5E 5B 81 C4 CC 00 00 00 3B  ....E?_^[.?ì...;
  00000060: EC E8 00 00 00 00 8B E5 5D C2 04 00              ìè.....?]?..

RELOCATIONS #8
                                                Symbol    Symbol
 Offset    Type              Applied To         Index     Name
 --------  ----------------  -----------------  --------  ------
 0000002E  DIR32                      00000000        49  ??_8C@@7BA1@@@ (const C::`vbtable'{for `A1'})
 00000038  DIR32                      00000000        4D  ??_8C@@7BA2@@@ (const C::`vbtable'{for `A2'})
 00000042  REL32                      00000000        32  ??0A1@@QAE@XZ (public: __thiscall A1::A1(void))
 0000004F  REL32                      00000000        33  ??0A2@@QAE@XZ (public: __thiscall A2::A2(void))
 00000062  REL32                      00000000        38  __RTC_CheckEsp
	 */


	system("pause");
	return 0;
}
/*
* (1)问题：编译器会在哪些必要的时候帮助我们合成默认的构造函数？？？
* 情况3：如果一个类含有虚基类，编译器也会为它合成一个默认构造函数
* 虚基类--通过两个直接基类继承同一个间接基类。---虚继承
* A<---B C<----D
*
* 虚基类结构，编译器为子类和父类都产生了“合成的构造函数”。
*
*
* vbtable virtual base table虚基类表

* (2)
*/
