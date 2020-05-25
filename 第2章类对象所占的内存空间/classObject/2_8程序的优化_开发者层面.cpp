#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class CTemValue
{
public:
	int value1;
	int value2;
public:
	CTemValue(int v1=0,int v2=0):value1(v1),value2(v2)//构造函数
	{
		cout << "调用了构造函数" << endl;
		cout << "value1=" << value1 << endl;
		cout << "value2=" << value2 << endl;
	}
	CTemValue(const CTemValue &ct):value1(ct.value1),value2(ct.value2)
	{
		cout << "调用了拷贝构造函数" << endl;
		
	}
	virtual  ~CTemValue()
	{
		cout << "调用了析构函数" << endl;
	}
};

//开发者视角
CTemValue DoubleMyself(CTemValue&t)
{
	//(1)开发者层面
	//CTemValue tem;
	//tem.value1 = t.value1 * 2;
	//tem.value2 = t.value2 * 2;
	//return  tem;//生成一个临时对象，然后调用拷贝构造函数把tem对象拷贝到主调函数的内存空间。

	//优化后
	return CTemValue(t.value1 * 2, t.value2 * 2);//生成一个临时对象直接返回
}
//编译器视角
void DoubleMyself(CTemValue&obj,CTemValue&t)
{
	obj.CTemValue::CTemValue(t.value1 * 2, t.value2 * 2);
	return;
}


int main(void)
{
	CTemValue ts1(10, 20);
	//CTemValue ts2=DoubleMyself(ts1);//使用一个对象来接收，就会少一个析构函数
	DoubleMyself(ts1);
	/*
	 * 编译器视角
	 * CTemValue ts1;
	 * ts1.CTemValue::CTemValue(10,20);
	 * CTemValue temObj;
	 * DoubleMyself(temObj,ts1);
	 */
	/*
	 调用了构造函数
	value1=10
	value2=20
	调用了构造函数
	value1=20
	value2=40
	调用了析构函数
	 */
	
	system("pause");
	return 0;
}
/*
* (1)开发者层面
* 
* (2)编译器层面
* (3)
* (4)
* (5)
* (6)(7)
*/
