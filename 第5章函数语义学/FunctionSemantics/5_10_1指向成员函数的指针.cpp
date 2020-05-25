
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


	/*
	 *一：指向成员函数的指针
	 *成员函数地址，编译时就确定好的。但是，调用成员函数，是需要通过对象来调用的；
	 *所有常规（非静态）成员函数，要想调用，都需要 一个对象来调用它；
	 *
	 *类成员函数是被放在代码区，而类的静态成员变量在类定义时就已经在全局数据区分配了内存，
	 因而它是属于类的。对于非静态成员变量，我们是在类的实例化过程中(构造对象)才在栈区或者堆区为其分配内存，
	是为每个对象生成一个拷贝，所以它是属于对象的。
	 */

class A
{
public:
	void myfunc1(int tempvalue1)
	{
		cout << "tempvalue1 = " << tempvalue1 << endl;
	}
	void myfunc2(int tempvalue2)
	{
		cout << "tempvalue2 = " << tempvalue2 << endl;
	}

	static void mysfunc(int tempvalue)
	{
		cout << "A::mysfunc()静态成员函数--tempvalue = " << tempvalue << endl;
	}
};

void func()
{
	A mya;
	void (A::*pmypoint)(int) = &A::myfunc1; //定义一个成员函数指针并给初值
	pmypoint = &A::myfunc2; //给成员函数指针赋值

	(mya.*pmypoint)(15); //通过成员函数指针来调用成员函数，必须要通过对象的介入才能调用

	A *pmya = new A();
	(pmya->*pmypoint)(20); //用对象指针介入来使用成员函数指针 来调用成员函数

   //编译器视角
   //pmypoint(&mya, 15);
   //pmypoint(pmya, 20);

	//静态函数指针就是普通的函数指针
	void(*pmyspoint)(int) = &A::mysfunc; //一个普通的函数指针，而不是成员函数指针
	pmyspoint(80);

	//通过成员函数指针对常规的成员函数调用的成本，和通过普通的函数指针来调用静态成员函数，成本上差不多；


}


int main()
{
	func();
	
	system("pause");
	return 1;
}

/*
    tempvalue2 = 15
	tempvalue2 = 20
	A::mysfunc()静态成员函数--tempvalue = 80
	请按任意键继续. . .

 */


