#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class X
{
public:
	int m_x;
	X(const X&temx)
	{
		m_x = temx.m_x;
		cout << "拷贝构造函数被调用" << endl;
	}

	X()
	{
		m_x = 0;
		cout << "构造函数被调用" << endl;
	}
	~X()//析构函数
	{
		cout << "析构函数被调用" << endl;
	}
	//普通函数
	void funcTest()
	{
		cout << "普通函数被调用" << endl;
	}
};

class X1
{
public:
	int m_x;
	X1(const X1&temx)
	{
		m_x = temx.m_x;
		cout << "X1类拷贝构造函数被调用" << endl;
	}

	X1()
	{
		m_x = 0;
		cout << "X1类构造函数被调用" << endl;
	}
	//析构函数
	~X1()
	{
		cout << "X1类析构函数被调用" << endl;
	}
};

void myFunction01( X1 x)
{
	return ;
}


//(4)返回值初始化
X myFunction02()
{
	X x0;//调用构造函数
	return x0;//调用拷贝构造函数构造出一个临时对象返回,在函数调用处的分配的内存空间构造my_x01，然后调用析构函数析构掉x0
}
//(4)编译器角度的函数调用  --返回值变为void，里面调用拷贝构造函数，传递引用
void myFunction03(X &extra)
{
	X x0;//编译器角度不调用X的构造函数
	//。。。。
	extra.X::X(x0);//调用拷贝构造函数
	return;
	
}

int main(void)
{
	//(2)定义初始化对象
	X x0;//调用构造函数
	x0.m_x = 14;
	X x1 = x0;
	X x2(x0);
	X x3 = (x0);

	cout << "111111111111111111111111111111111111" << endl;
	X x100;
	x100.X::X(x0);//拷贝构造函数可以直接调用
	/*
	 * 编译器角度：定义时候初始化是怎么做的？
	 * 实际上会拆分成2个步骤：
	 *	1. X x100;//步骤以：定义一个对象，给对象分配内存，从编译器的角度，这句是不调用X类的构造函数
	 *	2. x100.X::X(x0)//步骤二：直接调用对象的拷贝构造函数。
	 */

	//(3)参数的初始化
	cout << "222222222222222222" << endl;
	X1 x1_x1;
	myFunction01(x1_x1);
	/*
	 *  X1类构造函数被调用
		X1类拷贝构造函数被调用
		X1类析构函数被调用

	现代编译器视角：从实参传递个形参，会调用类的拷贝构造函数，创建一个对象

	 */
	//老的编译器视角--用临时对象调用myFunction01函数
	cout << "33333333333333333333333333333333333" << endl;
	X1 x1_x2;
	X1 temobjX1;//编译器产生一个临时对象
	temobjX1.X1::X1(x1_x2);//调用拷贝构造函数
	myFunction01(temobjX1);//并把形式参数变为引用，也就是说老编译器在外部构建对象，作为一个引用传递给形参。
	temobjX1.X1::~X1();//函数调用完毕后调用析构函数。


	//(4)返回值初始化
	cout << "4444444444444444444444444444444444444" << endl;
	X my_x01 = myFunction02();
	myFunction02().funcTest();//返回的X对象可以调用X的成员函数
	/*
	 *程序员角度见函数
	构造函数被调用
	拷贝构造函数被调用
	析构函数被调用	
	 */
	/*
	编译器角度对上述代码的理解：	
	 */
	X my_x02;//编译器角度不会调用构造函数，这里分配内存空间，供myFunction03函数把对象构造在这个内存空间中
	myFunction03(my_x02);
	(myFunction03(my_x02), my_x02);//逗号表达式，返回的一个对象调用普通函数

	cout << "4444444444444444444444444444442" << endl;
	X(*pfunc)();//定义以恶搞函数指针
	pfunc = myFunction02;
	pfunc().funcTest();
	/**
	 * 编译器视角：
	 * X my;//分配内存，不调用构造函数
	 * void (*pfunc)(X&);
	 * pfunc=myFunction02;
	 * pfunc(my);
	 * my.funcTest();
	 * 
	 * 
	 */
	
	system("pause");
	return 0;
}
/*
* (1)程序转化语义_编译器是如何解析这些代码
*	我们写的代码，编译器会对代码进行拆分，拆分成编译器更容易理解和实现的代码。
*	站在程序员的视觉看代码
*	编译器看代码视角
*
* (2)定义初始化对象
*	 拆分成两个步骤--编译器视角
* (3)函数调用（形参）参数的初始化
* 编译器视角
*	新编译器、
*	老编译器
* 
* (4)返回值初始化
* 在函数内部调用构造函数构造出一个对象（在主调函数分配的内存空间中），然后调用析构函数析构掉临时对象。
* 
* (5)
* (6)(7)
*/
