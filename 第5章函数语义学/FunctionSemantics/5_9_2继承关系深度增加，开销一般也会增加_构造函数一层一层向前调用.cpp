#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


	//二：继承关系深度增加，开销一般也会增加_构造函数一层一层向前调用C-->B--A(A1)
	//很多情况下，锁着继承深度的增加，开销或者说执行时间也会增加；
	//（2.1）多重继承一般也会导致开销增加

	class A
	{
	public:
		A()
		{
			cout << "A::A()" << endl;
		}
	};
	class A1
	{
	public:
		A1()
		{
			cout << "A1::A1()" << endl;
		}
	};

	class B :public A, public A1
	{
	public:
	};

	class C :public B
	{
	public:
		C()
		{
			cout << "C::C()" << endl;
		}
	};

/*
 00291FB0  push        ebp  
00291FB1  mov         ebp,esp  
00291FB3  sub         esp,0CCh  
00291FB9  push        ebx  
00291FBA  push        esi  
00291FBB  push        edi  
00291FBC  push        ecx  
00291FBD  lea         edi,[ebp-0CCh]  
00291FC3  mov         ecx,33h  
00291FC8  mov         eax,0CCCCCCCCh  
00291FCD  rep stos    dword ptr es:[edi]  
00291FCF  pop         ecx  
00291FD0  mov         dword ptr [this],ecx  
		{
00291FD3  mov         ecx,dword ptr [this]  
00291FD6  call        B::B (029139Dh)  
			cout << "C::C()" << endl;//编译器在构造函数中插入代码--构造函数一层一层向父类调用
 */
	void func()
	{
		C cobj;

	}


int main()
{
	func();
		
	system("pause");
	return 1;
}



