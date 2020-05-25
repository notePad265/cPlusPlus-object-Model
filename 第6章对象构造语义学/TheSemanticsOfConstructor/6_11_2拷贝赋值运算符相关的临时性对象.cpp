#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>
#include<string>

using namespace std;



//二：5_11_2拷贝赋值运算符相关的临时性对象
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
	//重载拷贝赋值运算符
	A & operator=(const A& tmpaobj)
	{
		cout << "A::operator()拷贝赋值运算符被执行" << endl;

		printf("拷贝赋值运算符中tmpaobj的地址为%p\n", &tmpaobj);
		return *this;
	}

	~A()
	{
		cout << "A::~A()析构函数被执行" << endl;
	}
};

A operator+(const A& obj1, const A& obj2)
{
	A tmpobj;

	printf("tmpobj的地址为%p\n", &tmpobj);
	//printf("---------------------\n");
	//.....
	return tmpobj; //编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数 把tmpobj的内容拷贝构造给这个临时对象；
				   //然后返回的是这个临时对象；

}

void func()
{
	A myobj1;
	printf("myobj1的地址为%p\n", &myobj1);

	A myobj2;
	printf("myobj2的地址为%p\n", &myobj2);

	A resultobj;
	resultobj = myobj1 + myobj2;	//先调用operator+,然后调用拷贝赋值运算符

	//A resultobj = myobj1 + myobj2; //拷贝构造函数(定义的时候给初值就会调用拷贝构造函数)

	printf("resultobj的地址为%p\n", &resultobj);

	return;
}
/*
A::A()构造函数被执行
myobj1的地址为0137FB9B
A::A()构造函数被执行
myobj2的地址为0137FB8F
A::A()构造函数被执行
A::A()构造函数被执行
tmpobj的地址为0137FA6F
A::A()拷贝构造函数被执行
A::~A()析构函数被执行
A::operator()拷贝赋值运算符被执行
拷贝赋值运算符中tmpaobj的地址为0137FAB7
A::~A()析构函数被执行
resultobj的地址为0137FB83
A::~A()析构函数被执行
A::~A()析构函数被执行
A::~A()析构函数被执行
请按任意键继续. . .

 */

int main()
{
	func();
	system("pause");

	return 1;
}



