#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;
class GrandFather
{
public:
	int a=0;
};

class A1:virtual public GrandFather
{
public:
	
};


class A2 :virtual public GrandFather
{
public:

};

class C:public A1,public A2
{
public:
	
};


int main(void)
{
	C obj_c;
	C obj_c2 = obj_c;//调用拷贝构造函数
	/*
	          Code
         COMDAT; sym= "public: __thiscall C::C(class C const &)" (??0C@@QAE@ABV0@@Z)
         16 byte align
         Execute Read
	......
		 Symbol    Symbol
		 Offset    Type              Applied To         Index     Name
		 --------  ----------------  -----------------  --------  ------
		 0000002E  DIR32                      00000000        66  ??_8C@@7BA1@@@ (const C::`vbtable'{for `A1'})
		 00000038  DIR32                      00000000        6A  ??_8C@@7BA2@@@ (const C::`vbtable'{for `A2'})
		 00000077  REL32                      00000000        4C  ??0A1@@QAE@ABV0@@Z (public: __thiscall A1::A1(class A1 const &))
		 000000A9  REL32                      00000000        4E  ??0A2@@QAE@ABV0@@Z (public: __thiscall A2::A2(class A2 const &))
		 000000BC  REL32                      00000000        54  __RTC_CheckEsp
	
	 */
	
	system("pause"); 
	return 0;
}
/*
* (1)情况4：类本身没有拷贝构造函数，但是该类继承自虚基类
* 
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
