
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;



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

	virtual void myvirfuncPrev(int tempvalue)
	{
		cout << "A::myvirfuncPrev()虚成员函数--tempvalue = " << tempvalue << endl;
	}

	virtual void myvirfunc(int tempvalue)
	{
		cout << "A::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
	}

};

void func()
{
	void (A::*pmyvirfunc)(int) = &A::myvirfunc; //成员函数指针  -- vcall(vcall trunk)地址（虚函数）

	A *pvaobj = new A;
	pvaobj->myvirfunc(190);//对象指针调用虚函数--有vcall
	(pvaobj->*pmyvirfunc)(190);//通过成员函数指针调用，依然走虚函数表调用虚函数
	printf("%p\n", &A::myvirfunc);//打印的是vcall的地址，是个中间地址，并不是虚函数的真正地址

	//调用普通成员函数，是真正的地址
	pmyvirfunc = &A::myfunc2;  //真正的成员函数地址
	(pvaobj->*pmyvirfunc)(33);

	delete pvaobj;

}



int main()
{
	func();


	return 1;
}
/*
 *二：5_10_2指向虚成员函数的指针及vcall进一步谈
 *vcall (vcall trunk) = virtual call：虚调用
 *	它代表一段要执行的代码的地址，这段代码引导咱们去执行正确的虚函数，
 *	或者我们直接把vcall看成虚函数表，如果这么看待的话，那么vcall{0}代表的就是虚函数表里的第一个函数，
 *	vcall{4}就代表虚函数表里的第二个虚函数
 *
 *	完善理解：&A::myvirfunc：打印出来的是一个地址，这个地址中有一段代码，这个代码中记录的是该虚函数在虚函数表中的一个偏移值
 *	有了这个偏移值，再有了具体的对象指针，我们就能够知道调用的是哪个虚函数表里边的哪个虚函数了；
 *
 *	成员函数指针里，保存的可能是一个vcall(vcall trunk)地址（调用虚函数）,要么也可能是一个真正的成员函数地址(调用成员函数)
 *	如果是一个vcall地址，那vcall能够引导编译器找出正确的虚函数表中的虚函数地址进行调用；

 */



