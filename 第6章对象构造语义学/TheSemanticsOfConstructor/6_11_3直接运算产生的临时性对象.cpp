#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>
using namespace std;


//三：6_11_3直接运算产生的临时性对象
//（3.1）临时对象被摧毁
//（3.2）临时对象因绑定到引用而被保留_临时对象的声明周期变为引用的声明周期
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
		m_i = tmpobj.m_i;
	}

	A & operator=(const A& tmpaobj)
	{
		cout << "A::operator()拷贝赋值运算符被执行" << endl;
		return *this;
	}

	~A()
	{
		cout << "A::~A()析构函数被执行" << endl;
	}
	int m_i;
};

A operator+(const A& obj1, const A& obj2)
{
	A tmpobj;
	tmpobj.m_i = obj1.m_i + obj2.m_i;

	return tmpobj; //编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数 把tmpobj的内容拷贝构造给这个临时对象；
				   //然后返回的是这个临时对象；

}

void func()
{
	A myobj1;
	myobj1.m_i = 1;

	A myobj2;
	myobj2.m_i = 2;

	A resultobj = myobj1 +myobj2;
	myobj1 + myobj2; //产生了临时对象，然后该临时对象立即被析构；
	printf("(myobj1 + myobj2).m_i = %d\n", (myobj1 + myobj2).m_i); //临时对象的析构是整行语句的最后一步，这样就能保证printf打印出来一个有效值；

	//A tmpobja1 = (myobj1 + myobj1); 复杂临时对象释放问题--编译器要往必要的地方，帮助我们插入代码，来产生临时对象供编译器完成我们程序开发者代码要实现的意图；
	/*if ((myobj1 + myobj1).m_i > 1 || (myobj1 + myobj2).m_i > 5)
	{
	int abc;
	abc = 4;
	}*/


	//c_str()取得它所指向的字符串
	cout << "***************************************" << endl;
	const char *p = (string("123") + string("456")).c_str(); //这一行有问题，因为临时对象过了这行就被摧毁；

	string aaa = (string("123") + string("456"));
	const char *q = aaa.c_str();   //这个应该OK

	printf("p = %s\n", p); 
	printf("q = %s\n", q);
	/*
	    p =
		q = 123456
	 */

	const string &aaa1212 = string("123") + string("456");
	printf("aaa1212 = %s\n", aaa1212.c_str());
	//aaa1212 = 123456



return;
}


int main()
{
	
	func();
	system("pause");
	return 1;
}



