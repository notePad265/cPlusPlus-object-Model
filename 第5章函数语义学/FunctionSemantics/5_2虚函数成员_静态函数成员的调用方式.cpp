#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

class MYACLS
{
public:
	int m_i;
	void myfunc(int abc)
	{
		//m_i += abc; //这里需要用到this指针，而this指针为空，则会报告异常
		mystfunc();
	}
	
	virtual void myvirfunc()
	{
		printf("myvirfunc()被调用,this = %p\n", this);
		//myvirfunc2(); 居然走虚函数表指针调用(查看反汇编)
		MYACLS::myvirfunc2(); //直接调用虚函数，效率更高。这种写法压制了虚拟机制，不再通过查询虚函数表来调用
							  //这种用类名::虚函数名()明确调用虚函数的方式等价于直接调用一个普通函数；
	}
	
	virtual void myvirfunc2()
	{
		printf("myvirfunc2()被调用,this = %p\n", this);
	}

	//静态成员函数
	//static int m_si;
	static void mystfunc() //不需要this参数
	{
		printf("mystfunc()被调用\n");
		//m_si = 1;
	}
};

int main()
{
	//一：虚成员函数（虚函数）调用方式
	MYACLS myacls;
	myacls.myvirfunc(); //用对象调用虚函数，就像调用普通成员函数一样(三章六节),不需要通过虚函数表

	MYACLS *pmyacls = new MYACLS();
	pmyacls->myvirfunc(); //要通过虚函数表指针查找虚函数表，通过虚函数表在好到虚函数的入口地址，完成对虚函数的调用

	/*编译器视角
	 (*pmyacls->vptr[0])(pmyacls);
	 *a)vptr，编译器给生成的虚函数表指针，指向虚函数表
	 *b)[0] 虚函数表中第一项。代表myvirfunc()地址
	 *c)传递一个参数进去，就是this，也是编译器给加的
	 *d)*就得到了虚函数的地址；
	 总结：虚成员函数也有一个固定的内存地址，在编译的时候就已经确定。通过对象直接调用虚函数，是不通过虚函数表。
		通过指针或者引用调用虚函数是走虚函数表。
	 */

	printf("MYACLS::myvirfunc2虚函数的地址为%p\n", &MYACLS::myvirfunc2);
	/*
		myvirfunc()被调用,this = 00EFFC90
		myvirfunc2()被调用,this = 00EFFC90
		myvirfunc()被调用,this = 010E4AB8
		myvirfunc2()被调用,this = 010E4AB8
		MYACLS::myvirfunc2虚函数的地址为00301415
	 */


	//二：静态成员函数调用方式
	cout << "--------------------" << endl;
	//通过对象，对象指针，类名调用静态成员函数。
	myacls.mystfunc();
	pmyacls->mystfunc();
	MYACLS::mystfunc();

	//编译器眼中：
	//_ZN6MYACLS8mystfuncEv();
	//_ZN6MYACLS8mystfuncEv();
	//_ZN6MYACLS8mystfuncEv();

	/*重要：
	 *(1)把结构体元素MYACLS的内存分配方式映射到内存位0的位置
	 *(2)((MYACLS *)0)按照MYACLS的类型解释0开始的内存空间的内容。0来自 pmyacls-pmyacls，移动到0地址空间
	 */
	((MYACLS *)0)->mystfunc();  //能够正常调用静态成员函数，因为不需要传递this指针，不操作任何非静态成员变量，本身不需要this指针。
	cout << "*******************" << endl;
	//((MYACLS *)0)->myfunc(12);  //如果myfunc()函数里面不对成员变量进行操作，也就是不用this指针，可以调用。
	//为什么设计出这么奇怪的方法？？--有些成员函数希望支持独立于类对象之外的存取操作；

	myacls.myfunc(12);
	pmyacls->myfunc(12);

	/*结论：
	 *静态成员函数特性
	 *a)静态成员函数没有this指针，这点最重要
	 *b)无法直接存取类中普通的非静态成员变量，静态成员变量通过this指针存取的
	 *c)静态成员函数不能在屁股后使用const，也不能设置为virtual
	 *d)可以用类对象调用，但不非一定要用类对象调用。可以使用类对象，类对象指针，类名字，来调用。
	 *e)静态成员函数等同于非成员函数，有的需要提供回调函数的这种场合，可以将静态成员函数作为回调函数；
	 */

	printf("MYACLS::mystfunc()地址 = %p\n", MYACLS::mystfunc);
	/*
	 mystfunc()被调用
	 mystfunc()被调用
	 MYACLS::mystfunc()地址 = 00FA122B
	 */



	delete pmyacls;
	system("pause");
	return 1;
}
