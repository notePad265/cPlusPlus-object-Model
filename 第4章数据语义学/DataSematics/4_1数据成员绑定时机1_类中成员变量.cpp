#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string myvar="jisuanjizuchengyuanli";//全局量 字符串类型
class A
{
public:
	A(int value):myvar(value)
	{
		;
	}
	int myFunction();
private:
	int myvar;//同名局部变量，名字相同，但是类型不同
};

int A::myFunction()
{
	return myvar;//返回类内的int类型myvar
}
//编译器对成员函数的解析和绑定是整个类A定义完成后才开始的

string myFunciton01()
{
	return myvar;//返回的是全局的string类型变量
}

int main(void)
{
	//类对象内部的myvar
	A obj_a(12);
	cout << obj_a.myFunction();
	cout << endl;
	//全局的myvar
	cout << ::myvar << endl;//::就是表示全局变量
	
	system("pause");
	return 0;
}
/*
* (1)总结
* 编译器对myFunction函数的解析是在整个类A定义完毕后才开始的。
* 因为只有整个类A定义完毕后，编译器才能看到类A的myvar，才能根据时机的需要把出现myvar的场合做上述适当的解释。
* 成员函数中解释成类中myvar，全局变量中解释成string myvar。
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
