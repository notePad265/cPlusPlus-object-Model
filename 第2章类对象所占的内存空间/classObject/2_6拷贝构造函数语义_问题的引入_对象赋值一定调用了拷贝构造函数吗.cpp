#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
	int m_i;
};

int main(void)
{
	A obj_a;
	obj_a.m_i = 15;
	A obj_02 = obj_a;//我们理解这里是 调用拷贝构造函数
	/*
	 *，通过dumpbin查看并没有生成拷贝构造函数
	 *将obj_02的m_i成员属性的值赋值为15，，这是编译器内部的一个手法：
	 *成员变量初始化手法，比如这种int简单类型，直接按值拷贝过去，编译器不需要合成拷贝构造函数的情况下，
	 *编译器简单的按值拷贝，拷贝到另一个对象的同名成员变量中去。
	 * 
	 */
	
	system("pause");
	return 0;
}
/*
* (1)拷贝构造函数语义_问题的引入_对象赋值一定调用了拷贝构造函数吗？？
*	当用一个对象初始化另一个对象时候，就会调用拷贝构造函数
*	传统上，如果我们没有定义自己的拷贝构造函数，编译器会帮助我嫩合成一个拷贝构造函数。
*	实际上，只有在必要的时候拷贝构造函数才会被合成出来。
*问题：什么是“必要的时候”？
*	
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
