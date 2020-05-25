#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class MYACLS
{
public:
	virtual void myvirfunc1()
	{

	}
	virtual void myvirfunc2()
	{

	}
};

int main()
{
	printf("MYACLS::myvirfunc1()地址=%p\n", &MYACLS::myvirfunc1); //打印的是vcall函数（代码）地址，而不是真正的虚函数；
	printf("MYACLS::myvirfunc2()地址=%p\n", &MYACLS::myvirfunc2);
	cout << sizeof(MYACLS) << endl;//4
	MYACLS *pmyobj = new MYACLS();
	/*
	 *虚函数表中的真正地址：
	 0x00a41096 {FunctionSemantics.exe!MYACLS::myvirfunc1(void)}
	 0x00a4112c {FunctionSemantics.exe!MYACLS::myvirfunc2(void)}
	 打印的地址：
	 MYACLS::myvirfunc1()地址=00B8114A
	 MYACLS::myvirfunc2()地址=00B81064
	 4
	 vcall thunk-是编译器在编译阶段生成的东西，理解为一段代码，用于跳到真正的函数去执行。每一个vcall都对应着一个虚函数。
	 (1)调整this，在继承过程中，父类指针指向子类对象，当调用子类的虚函数，要调整到子类的位置。
	 (2)跳转到真正的虚函数中去

	 */
	

	system("pause");
	return 1;
}
/*5_3虚函数地址问题的vcall引入
 *结论：虚函数的调用是通过编译器生成的vcall代码间接调用，
 *vcall有两个功能，见上面。
 *
 *

请按任意键继续. . .
 * 
 */
