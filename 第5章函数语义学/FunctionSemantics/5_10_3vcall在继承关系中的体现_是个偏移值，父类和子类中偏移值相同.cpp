#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


//三：5_10_3vcall在继承关系中的体现_是个偏移值，父类和子类中偏移值相同
class A
{
public:
	virtual void myvirfunc(int tempvalue)
	{
		cout << "A::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
	}
	//虚析构函数
	virtual ~A()
	{

	}
};

class B :public A
{
public:
	virtual void myvirfunc(int tempvalue)
	{
		cout << "B::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
	}
	
	virtual ~B() {}
};

void func()
{
	B *pmyb = new B();   //pmyb：对象指针
	void (B::*pmyvirfunc)(int) = &A::myvirfunc; //成员函数指针
	//void (B::*pmyvirfunc)(int) = &B::myvirfunc; //成员函数指针
	/*
	 *   A::myvirfunc;--记录的是一个vcall地址,实际上记录的是一个偏移，和B::myvirfunc保存的偏移值一样

	 */

	(pmyb->*pmyvirfunc)(190);

	printf("%p\n", &A::myvirfunc); //A的vcall地址 和下个vcall地址不一样，但是里面保存的偏移量是同样的
	printf("%p\n", &B::myvirfunc); //B的vcall地址
}


int main()
{
	func();
	system("pause");
	return 1;
}



