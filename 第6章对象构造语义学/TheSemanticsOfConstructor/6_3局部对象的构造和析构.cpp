#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>

using namespace std;

//一：6_3局部对象的构造和析构
//主要出了对象的作用域，编译器总会在适当的地方插入调用对象析构函数的代码；
//结论：使用的时候定义，不要在开头定义，遇见下一个作用域，可能多调用构造函数
class A
{
public:
	A()
	{
		cout << "A::A()" << endl;
	}
	~A()
	{
		cout << "A::~A()" << endl;
	}
	int m_i;
};


void func()
{
	int i;
	int j;

	//......
	/*if (1)
	{
	return;
	}*/
	//.......
	//....
	A obja;//建议：现用现定义 ，定义处是插入调用构造函数的语句，对于局部对象，里边的m_i是随机值；，
	//如果放在开头，遇到下一个作用域，就要调用析构函数，等到使用的时候还要再次调用构造函数，多调用依次构造和析构
	obja.m_i = 10;

	int mytest = 1;
	if (mytest == 0) //swtich case return;
	{
		return;
	}
	
	return;
}

//main函数开始之前要干很多事
int main()
{

	func();		
	system("pause");
	return 1;
}
//main函数结束之后要干很多事


