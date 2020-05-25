#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
public:
	int number01;//4个字节
	virtual void virtualFunction()//虚函数
	{}
};

int main(void)
{
	A obj_a;
	int length = sizeof(obj_a);
	cout << "length=" << length << endl;//8

	char*p1 = reinterpret_cast<char*>(&obj_a);//强制类型转换，&obj_a的首地址
	char*p2 = reinterpret_cast<char*>(&obj_a.number01);
	if (p1==p2)//对象和对象中的成员变量位置相同，说明number01在对象内存布局上面，虚函数表指针在下面。
	{
		cout << "number01对象内存在上面4个字节，虚函数表指针在对象内存的末尾" << endl;
	}
	else
	{
		cout << "虚函数表指针位置对象内存布局开始位置，number01在末尾位置" << endl;
	}
	//结论：虚函数表指针位于整个对象内存布局的开头位置。
	
	
	system("pause");
	return 0;
}
/*
 *3_1虚函数表指针位置分析_位于对象内存布局的开头位置
* (1)虚函数表指针位置分析
* 类：有虚函数，该类会产生一个虚函数表。
* 使用类生成对象的时候，对象中会有一个虚函数表指针，用于指向类的虚函数表开始地址。
* 虚函数表在生成可执行程序的时候会保存在可执行程序文件中。
*
* //结论：虚函数表指针位于整个对象内存布局的开头位置。
*
*	虚函数表指针
*	number01

length=8
虚函数表指针位置对象内存布局开始位置，number01在末尾位置
请按任意键继续. . .
*	
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
