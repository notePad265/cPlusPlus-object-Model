#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class CTB
{
public:
	CTB()
	{
		
	}
	CTB(const CTB&B)//拷贝构造函数
	{
		cout << "父类有自己的拷贝构造函数" << endl;
	}
};

class CTBSon:public CTB
{
public:
	
};


int main(void)
{
	CTBSon myctbSon;
	CTBSon myctbson02 = myctbSon;
	
	system("pause");
	return 0;
}


/*
* (1)拷贝构造函数语义_问题的引入_对象赋值一定调用了拷贝构造函数吗？？
*	当一个类包含另一个类对象作为成员变量的时候，会“递归拷贝”。
*
*问题：什么是“必要的时候”？
*情况2.如果子类CTBSon没有自己的拷贝构造函数，但是他的父类CTB，父类有自己的拷贝构造函数
*当代码中有涉及到类CTBSon的拷贝构造函数时，编译器会为CTBSon合成一个拷贝构造函数。
*
* (3)
* (4)
* (5)
* (6)(7)
*/