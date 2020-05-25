#include<iostream>
#include "MyTemplate.h"
using namespace std;
template class MyClass<int>;//显示实例化类模板
template void MyClass<int>::myFunction02()const;//实例化具体的成员函数



int main(void)
{
	MyClass<int>myOjb01;
	myOjb01.m_i = 10;
	myOjb01.m_j = 20;
	myOjb01.myFunction01();
	myOjb01.myFunction02();
	myOjb01.myVirtualFunction01();
	system("pause");
	return 0;
}
/*
 * (1)7_1_3多个源文件中使用类模板
 * 一般多个文件都会用到类模板，所以放在.h文件中
 * 在多个cpp生成的obj文件中，可能产生多个重复的实例化类，但是链接的时候指挥保留一个MyClass<int>类的实体。
 *
 * 1.1虚函数的实例化
 *	为什么虚函数没有被调用，也会被实例化出来？？
 *	因为有虚函数，编译器就会产生虚函数表，虚函数表项是虚函数的地址，也就意味着要知道虚函数的地址，。
 */