#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class Base
{
public:
	virtual void myVirtualFunction01() { cout << "myFunction01" << endl; }
	virtual void myVirtualFunction02() { cout << "myFunction02" << endl; }
	virtual void myVirtualFunction03() { cout << "myFunction03" << endl; }

};

class Derive:public Base
{
	//重写父类myVirtualFunction02()函数
	void myVirtualFunction02() override
	{
		cout << "这是子类重写的myVirtualFunction02函数" << endl;
	}
};

int main(void)
{
	cout << sizeof(Base) << endl;//4
	cout << sizeof(Derive) << endl;//4

	Derive *pderive01 = new Derive();//子类指针
	long*pvptr = (long*)pderive01;//将指向子类对象的指针转换为long*类型
	long*vptr = (long*)(*pvptr);//(*pvptr指向的对象本身，也就是Deriv对象本身)--
	//Derive对象本身是占有4个字节的，里面存储的是虚函数表地址   vptr指向基于类的虚函数表
	/*
	 pderive01	0x01534be0 {...}	Derive *
	 pvptr	0x01534be0 {7445368}	long *
	 vptr	0x00719b78(值为7445368) {virtualFunction.exe!const Derive::`vftable'} {7410594}	long *
	 */

	//我们预计虚函数表里面存储了3项，3个虚函数
	for (int i=0;i<5;i++)
	{
		printf("vptr[%d]=0x:%p\n", i, vptr[i]);
	}
	/*
	 *  vptr[0]=0x:00C513A2
		vptr[1]=0x:00C51258
		vptr[2]=0x:00C5108C
		vptr[3]=0x:00000000
		vptr[4]=0x:C7CAE2D5
	 */
	//尝试调用虚函数
	typedef void(*Func)(void);//定义一个函数指针类型
	Func f1 = (Func)vptr[0];//vptr[0]是指向第一个虚函数
	Func f2 = (Func)vptr[1];//vptr[0]是指向第二个虚函数
	Func f3 = (Func)vptr[2];//vptr[0]是指向第三个虚函数
	Func f4 = (Func)vptr[3];//vptr[0]是指向第一个虚函数
	Func f5 = (Func)vptr[4];//vptr[0]是指向第一个虚函数

	f1();
	f2();
	f3();
	//f4();//报异常
	/*
	 myFunction01
	这是子类重写的myVirtualFunction02函数
	myFunction03
	 */

	Base *base01 = new Base();
	long*pbase = (long*)base01;
	long*vptrBase = (long*)(*pbase);//base01指针指向的内存空间中存储的就是虚函数表
	for (int i=0;i<3;i++)
	{
		printf("vptrBase[%d]=0x:%p\n", i, vptrBase[i]);
	}
	/*
	 *  vptrBase[0]=0x:009913A2
		vptrBase[1]=0x:0099119F
		vptrBase[2]=0x:0099108C
	 */
	Func fb1 = (Func)vptrBase[0];
	Func fb2 = (Func)vptrBase[1];
	Func fb3 = (Func)vptrBase[2];

	fb1();
	fb2();
	fb3();
	/*
	myFunction01
	myFunction02
	myFunction03
	*/
	
	
	system("pause");
	return 0;
}
/*
* (1)继承关系下虚函数的手工调用
*	当一个类中都是虚函数类型的成员函数，那么类对象指针指向的内存空间都是用来保存虚函数表的。
*	虚函数表可以看成一个数组，可以使用[]下表访问符来访问。就可以使用函数类型来调用虚函数表里面的虚函数
* (2)
*	1.一个类只有包含虚函数才会存在虚函数表，同属一个类的对象共享虚函数表，各自有自己的虚函数表指针
*	2.父类中有虚函数，子类中肯定有虚函数，换句话说，父类中有虚函数表，子类中有虚函数表。因为子类继承父类。
*		2.1也可以认为：父类中是虚函数，不管子类overwrite的函数中写不写virtual依然是虚函数。
*		2.2但是不管父类还是子类，都分别有一个虚函数表，不能认为子类中一个虚函数表+父类中继承的虚函数表=子类中2个虚函数表。
*		子类父类分别一个虚函数表。
*		2.3子类中是否可能存在多个虚函数表？？ 后面讲解。
*	3.如果子类完全没有新的虚函数，则我们可以认为子类的虚函数表和父类的虚函数表内容相同。
*		仅仅是内容相同，但是在内存中处于不同位置。换句话说：这是内容相同的两张表。
*		表的内存位置和表中存储的内容是不同的概念。
*		3.2虚函数表中每一项保存着一个虚函数的首地址，但是如果子类的虚函数表某项和父类虚函数表某项表示同一个函数，
*			（子类没有覆盖父类的函数），则该表项所表示的虚函数地址应该相同。
*
*	4.超出虚函数表部分内容不可知。类的虚函数有几个就可以使用数组方式访问几个。
*		
* (4)
* (5)
* (6)(7)
*/
