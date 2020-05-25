#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class X
{
public:
	int x;
	int y;
	int z;
	//X():x(0),y(0),z(0)
	X() 
	{
		/*编译器插入代码的伪代码：
		 *this->vptr=&vtebl
		*
		 */
		memset(this, 0, sizeof(X));
		cout << "构造函数被执行" << endl;
		
	}
	//拷贝构造函数
	//X(const X&tm):x(tm.x),y(tm.y),z(tm.z)
	X(const X&tm)
	{
		memcpy(this, &tm, sizeof(X));//单纯的类--更加有效率的拷贝方法--会把虚函数表指针清空
		cout << "拷贝构造函数被执行" << endl;
	}
	//普通成员函数
	void myFunction()
	{
		cout << "普通函数myFunction()函数被执行了" << endl;
	}
	
	virtual  ~X()
	{
		cout << "虚析构函数被执行" << endl;
	}
	virtual void myVirtualFunction()
	{
		cout << "普通虚析构函数myVirtualFunction被执行" << endl;
	}
};

int main(void)
{
	X x0;//调用构造函数
	x0.x = 100;
	x0.y = 200;
	x0.z = 300;
	X x1(x0);//调用拷贝构造函数   当注释掉拷贝构造函数里的memset，虚函数指针有值0x00a78b34 {virtualFunction.exe!const X::`vftable'} {0x00a711ae {virtualFunction.exe!X::`vector deleting destructor'(unsigned int)}, ...}
	cout << "x1.x" << x1.x << endl;
	cout << "y1.x" << x1.y << endl;
	cout << "z1.x" << x1.z << endl;

	//虚函数指针被清空，但是还是可以调用成功虚函数
	x0.myVirtualFunction();
	

	//在堆上分配内存创建对象，能否调用虚函数？？ --new出来的对象（堆上）无法调用虚函数
	X *p_x = new X();//构造函数可以成功调用
	p_x->myFunction();//ok
	//p_x->myVirtualFunction();//error 会引发异常,无法调用虚函数，--是通过虚函数表指针，从虚函数表中找到对应的函数执行。
	//delete p_x;//error也无法调用虚析构函数

	int i = 9;
	printf("&i=%p\n", &i);

	printf("myFunction的地址是%p\n", &X::myFunction);//0x00ca2830 {virtualFunction.exe!X::myFunction(void)}
	//这样打印的虚函数地址对不对？？？？还是要使用前面的转换为long*类型来打印??
	printf("myVirtualFunction的地址是%p\n", &X::myVirtualFunction);//0x00ca28b0 {virtualFunction.exe!X::myVirtualFunction(void)}
	/*
	 &i=0076F8F8
	myFunction的地址是001B14B5
	myVirtualFunction的地址是001B14BA
	每次运行i的地址都发生改变，但是每次运行myFunction 和M有VirtualFunction的地址都不发生改变。

	查看反汇编代码：
			printf("myFunction的地址是%p\n", &X::myFunction);//0x00ca2830 {virtualFunction.exe!X::myFunction(void)}
		00C02B14  push        offset X::myFunction (0C014B5h)  
		00C02B19  push        offset string "myFunction\xb5\xc4\xb5\xd8\xd6\xb7\xca\xc7%p\n" (0C09B68h)  
		00C02B1E  call        _printf (0C014B0h)  
		00C02B23  add         esp,8  
			//这样打印的虚函数地址对不对？？？？还是要使用前面的转换为long*类型来打印??
			printf("myVirtualFunction的地址是%p\n", &X::myVirtualFunction);//0x00ca28b0 {virtualFunction.exe!X::myVirtualFunction(void)}
		00C02B26  push        offset X::`vcall'{4}' (0C014BAh)  
		00C02B2B  push        offset string "myVirtualFunction\xb5\xc4\xb5\xd8\xd6\xb7\xca\xc7%p\n" (0C09B94h)  
		00C02B30  call        _printf (0C014B0h)  
		00C02B35  add         esp,8  

	我们推断：编译的时候就确定好了函数的地址，依据就是反汇编代码是直接call一个数字的。

	静态联编：编译的时候就确定调用哪一个函数。编译器把函数名字直接转换为一个地址，直接call
	动态联编：是在程序运行时，根据时机情况，动态把调用语句和被调用函数绑定到一起，动态联编一般只在多态和虚函数的情况下才会发生。
		所以60行x0.myVirtualFunction();的函数调用不叫多态，虚函数指针被清空，也可以直接调用虚函数。
		66行//p_x->myVirtualFunction();是通过虚函数表调用。

	总结：1。在栈上分配的对象，是不通过虚函数表调用虚函数，是静态联编，所以类对象的虚函数表指针被清空也可以调用虚函数
		2.在堆上通过new分配的对象，是通过虚函数表指针，找虚函数表对应函数来调用，虚函数表指针不能清空，也就是构造函数不能使用memset和memcoy
		3.更要明白，虚函数，多态，这种概念是专门给指针或者引用使用的。
	 */

	system("pause");
	return 0;
}
/*
* (1)单纯的类不纯时引发的虚函数调用问题
*	单纯的类：比较简单的类，尤其不包含虚函数和虚基类
*	
*使用memset和memcoy写构造函数，但是这个类并不单纯，如包含虚基类和虚函数，使用这种写法就会有错误。
结论：构造函数中，当有虚函数时候不能使用memset和memcpy()函数。
*不单纯：某些情况下，编译器会往类内部添加一些我们看不见，但是真是存在的成员变量(隐式成员变量,如虚函数表指针),有了这些成员变量的类，就不单纯了。
*同时这种隐藏的成员变量的增加或者赋值的时机往往是往往都是在执行构造函数或者拷贝构造函数的函数体开始之前。
*那么你如果使用memcpy，memset可能把编译器给隐藏变量(虚函数表指针)的值给清空了(或者覆盖了)。
*如：你向类中增加了虚函数，编译器默认往类对象中增加虚函数表指针，这个虚函数表指针就是隐藏的成员变量。
*	
* (2)类的构造函数中包含memset和memcoy，堆上的new出来的对象无法调用虚函数
*	对于多态，虚函数，父类，子类，虚函数，主要解决的问题就是父类指针指向子类对象这种情况。
*	只有虚函数，没有继承，那么虚函数和普通函数有什么区别呢？----可以认为没什么实际区别。
*	
* (3)多态问题理解
* 存在虚函数表指针，通过虚函数表指针查找虚函数表中的虚函数执行这种行为叫多态。
* (4)
* (5)
* (6)(7)
*/
