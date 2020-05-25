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
		m_i += abc;
	}


};

//编译器视角linux
//void _ZN6MYACLS6myfuncEi(MYACLS *const this, int abc) //编译器会额外安插一个this指针，一般会扔到参数的开头
//{
//	this->m_i + abc;
//}

void gmyfunc(MYACLS *ptmp, int abc)
{
	ptmp->m_i += abc;
}

int main()
{
	//5_1普通成员函数调用方式_转换为全局函数调用

	MYACLS myacls;
	myacls.myfunc(18); //调用成员函数
	//_ZN6MYACLS6myfuncEi(&myacls,18)


	gmyfunc(&myacls, 18); //调用全局函数

   /*
    * c++语言设计的时候有一个要求：要求对这种普通成员函数的调用不应该比全局函数效率差；
    * 基于这种设计要求，编译器内部实际上是将对成员函数myfunc()的调用转换成了对 全局函数的调用；
    * 成员函数有独立的内存地址，是跟着类走的，并且成员函数的地址 是在编译的时候就确定好的；
    *
    * a）编译器额外增加了一个叫this的形参，是个指针，指向的其实就是生成的对象；
    * b)常规成员变量的存取，都通过this形参来进行，比如上述this->m_i + abc;
    */
	printf("MYACLS::myfunc的地址=%p\n", &MYACLS::myfunc);//002A102D

	system("pause");
	return 1;
}
