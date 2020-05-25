#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>

using namespace std;


/*
 * 一：对象的构造顺序_在子类中调用父类的构造函数，先构造父类子对象，然后再构造子类特有的对象，完成子类对象的构造。
 * 二：虚函数的继续观察--本例中虚函数指针被赋值三次，在构造对象转换的时候需要把虚函数指针指向每个类的虚函数表
 *    大家千万不要在构造函数中你自己的代码中使用诸如memcpy或者直接操作等手段，来修改虚函数表指针的值，否则，调用虚函数时就可能造成系统崩溃；
 * 三：构造函数中对虚函数的调用
 *	 构造函数中调用虚函数，不是走虚函数表调用，因此也不是多态。因为构造函数中虚函数表指针还没有指向虚函数表。
 *	 但是在虚函数中调用其他虚函数，可能走虚函数表，实现多态，不同编译器实现不一样
 *   某个类的构造函数 中 调用一个虚函数，那么走的不是虚函数表，而是直接调用。
 * 四：举一反三
 *	虚基类，虚继承中的分析
 * 

 */

class A
{
public:
	A()
	{
		printf("A this = %p\n", this);
		cout << "A::A()" << endl;
	}
	virtual ~A() {}
	virtual void myvirfunc() {}
	virtual void myvirfunc2() {}
};

class B :public A
{
public:
	B()
	{
		printf("B this = %p\n", this);
		cout << "B::B()" << endl;
	}
	virtual ~B() {}
	virtual void myvirfunc() {}
	virtual void myvirfunc2() {}
};

class C :public B
{
public:
	C() :m_c(11)//注意成员变量m_c的赋值时机
	{
		//memcpy(this,)
		myvirfunc(); //构造函数中，这里没有走虚函数表，而是直接通过虚函数地址，直接调用这个虚函数（静态方式调用）
		printf("C this = %p\n", this);
		cout << "C::C()" << endl;
	}
	virtual ~C() {}
	virtual void myvirfunc() { myvirfunc2(); }//调用myvirfunc2()是通过虚函数表调用的
	virtual void myvirfunc2() {}
	int m_c;

};

void func()
{
	//C cobj;
	/*
    C cobj;
    C::C()   //末端类--在C类的构造函数中调用B类的构造函数，在B类的构造函数中调用A类的构造函数，
        B::B()
            A::A()  //根源类
                vptr = A::vftable; //编译器插入的代码   34 9b 2f 01  爷爷类A把虚函数表地址赋值给vptr
                cout << "A::A()" << endl; //我们自己的代码
            vptr = B::vftable;   //编译器插入的代码  54 9b 2f 01  父类B把虚函数表地址赋值给vptr
            cout << "B::B()" << endl;  //我们自己的代码
        vptr = C::vftable;   //编译器插入的代码  3c 9b 2f 01	孙子类C把虚函数表地址赋值给vptr--虚函数表指针的值被赋值3次
        //....不要在这里动虚函数表指针
        //memset(this,0,sizeof(C));

        m_c = 11; //初始化列表中基本类型变量m_c的赋值时机
        cout << "C::C()" << endl; //我们自己的代码


	A B C是同一个this指针
	A this = 010FF614
	A::A()
	B this = 010FF614
	B::B()
	C this = 010FF614
	C::C()

	 */
	
	C *mycobj = new C();
	mycobj->myvirfunc(); //代码实现上的多态，五章四节


}

int main()
{

	func();
	system("pause");
	return 1;
}



