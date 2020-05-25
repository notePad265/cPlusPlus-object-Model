#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>
#include<string>

using namespace std;


//一：6_11_1拷贝构造函数相关的临时性对象
class A
{
public:
	A()
	{
		cout << "A::A()构造函数被执行" << endl;
	}
	A(const A& tmpobj)
	{
		cout << "A::A()拷贝构造函数被执行" << endl;
	}
	~A()
	{
		cout << "A::~A()析构函数被执行" << endl;
	}
};

A operator+(const A& obj1, const A& obj2)
{
	A tmpobj;//这里调用构造函数，超出作用域调用析构函数

	printf("tmpobj的地址为%p\n", &tmpobj);
	printf("---------------------\n");
	//.....
	return tmpobj; //编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数 把tmpobj的内容拷贝构造给这个临时对象；
					//然后返回的是这个临时对象；临时对象没有被析构

}

void func()
{
	A myobj1;
	printf("myobj1的地址为%p\n", &myobj1);

	A myobj2;
	printf("myobj2的地址为%p\n", &myobj2);

	A resultobj = myobj1 + myobj2; //这个从operator +里返回的临时对象直接构造到了resultobj里；
	printf("resultobj的地址为%p\n", &resultobj);
	return;
}
/*
	A::A()构造函数被执行
	myobj1的地址为00AFF923
	A::A()构造函数被执行
	myobj2的地址为00AFF917
	A::A()构造函数被执行
	tmpobj的地址为00AFF80B//直接把temobj构造在resultobj的对象空间，他们的地址相同
	---------------------
	A::A()拷贝构造函数被执行
	A::~A()析构函数被执行
	resultobj的地址为00AFF90B
	A::~A()析构函数被执行
	A::~A()析构函数被执行
	A::~A()析构函数被执行

可以在项目属性 c++ --“优化”--“优化”--设置优化级别
同时，“代码生成”--“基本运行时检查”--“两者”
*/

int main()
{
	func();
	system("pause");

	return 1;
}



