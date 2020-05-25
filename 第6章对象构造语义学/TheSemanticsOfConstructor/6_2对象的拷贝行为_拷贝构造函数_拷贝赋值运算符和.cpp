
#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>

using namespace std;

/*
 *一：对象的默认复制行为
 *如果我们不写自己的拷贝构造函数和拷贝赋值运算符，编译器也会有默认的对象拷贝和对象赋值行为。直接的内存拷贝，
 *将对对象成员变量的值拷贝到另一个对象的对应位置上。
 *
 *二：拷贝赋值运算符，拷贝构造函数
 *当我们提供自己的拷贝赋值运算符和拷贝构造函数时，我们就接管了系统默认的拷贝行为，
 *此时，我们有责任在拷贝赋值运算符和拷贝构造函数中写适当的代码，来完成对象的拷贝或者赋值的任务；
 *
 *三：如何禁止对象的拷贝构造和赋值：把拷贝构造函数和拷贝赋值运算符私有起来，只声明，不需要些函数体；


 */
class A
{
public:
	int m_i, m_j;

	A() {} //缺省构造函数
//private:	
	A & operator=(const A &tmp)//; //拷贝赋值运算符
	 {
	 m_i = tmp.m_i;
	 m_j = tmp.m_j;
	 return *this;
	 }
	
	A(const A& tmp)//;  //拷贝构造函数
	{
		m_i = tmp.m_i;
		m_j = tmp.m_j;
	 }

};

void func()
{
	A aobj;
	aobj.m_i = 15;
	aobj.m_j = 20;

	A aobj2 = aobj; //执行拷贝构造函数(如果你写了拷贝构造函数)
	//A aobj2;

	A aobj3;
	aobj3.m_i = 13;
	aobj3.m_j = 16;
	aobj2 = aobj3; //执行拷贝赋值运算符（如果你写了拷贝赋值运算符）


}


int main()
{
	func();	
	
	system("pause");
	return 1;
}



