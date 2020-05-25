#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class TEST
{
public:
	int m_i;
	int *p;
	//构造函数
	TEST()
	{
		p = new int(23);
		m_i = 0;
		cout << "构造函数执行" << endl;
	}
	TEST(int value):m_i(value)
	{
		p = new int(value);
		cout << "带一个参数的构造函数执行" << endl;
		
	}
	~TEST()
	{
		delete p;
		cout << "析构函数执行" << endl;
	}
	//拷贝构造函数--没有拷贝构造函数会报异常
	TEST(const TEST&t)
	{
		this->p = new int(t.m_i);//字节分配内存
		this->m_i = t.m_i;
	}
};


void playObj()
{

	TEST test01(12);
	TEST test02(test01);
}

int main(void)
{
	playObj();
	//两个对象，会释放两次p指向的内存空间，会报异常。
	
	system("pause");
	return 0;
}
/*
* (1)
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
