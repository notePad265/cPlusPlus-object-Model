#include<iostream>

using namespace std;

class Base
{
public:
	virtual void f() {}
	virtual ~Base() {}
	int m_basei;
};

class Derive :public virtual Base
{
public:
	virtual ~Derive() {}
	int m_derivei;
};

int main()
{



   //二： 虚继承下的虚函数
   cout << sizeof(Derive) << endl;  //16   --2个int，一个虚基类表，一个虚函数表
   Derive dobj;
   dobj.m_basei = 2;//13-16字节
   dobj.m_derivei = 5;//5-8字节
	//9-12字节--虚函数表地址
	//1-4字节虚基类表指针---布局详细见图

   Derive *pdobj = new Derive();
   pdobj->f();
	/*
	 * 
	 */

   Base *pbase = new Derive();//创建子类对象，用父类来接收
   pbase->m_basei = 6;

	
   Derive *pderive = new Derive();//pderive = 0x013349b0 {m_derivei=0 }
   Base *pbase2 = (Base *)pderive;//pbase2 = 0x013349b8 {m_derivei=0 }//地址差8字节
	/*
	 *
	 *
	 * __vfptr = 0x00068b44 {FunctionSemantics.exe!const Derive::`vftable'} {0x00061078 {FunctionSemantics.exe!Base::f(void)}, ...}
	 *	[0] = 0x00061078 {FunctionSemantics.exe!Base::f(void)}
	 *	[1] = 0x000613f7 {FunctionSemantics.exe!Derive::`vector deleting destructor'(unsigned int)}
	 */
   pbase2->m_basei = 7;




system("pause");
return 1;
}
/*内存布局见图
 *结论： 带虚基类的内存布局非常复杂，不需要深入研究
 */