#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class CTemValue
{
public:
	int value1;
	int value2;
public:
	CTemValue(int v1 = 0, int v2 = 0) :value1(v1), value2(v2)//构造函数
	{
		cout << "调用了构造函数" << endl;
		cout << "value1=" << value1 << endl;
		cout << "value2=" << value2 << endl;
	}
	CTemValue(const CTemValue &ct) :value1(ct.value1), value2(ct.value2)
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
	//测试执行1000000次的使用时间，未实现
	clock_t start, end;
	start = clock();//返回执行到这里的时间，毫秒
	//测试代码
	end = clock();
	CTemValue tem;
	tem.value1 = t.value1 * 2;
	tem.value2 = t.value2 * 2;
	return  tem;//生成一个临时对象，然后调用拷贝构造函数把tem对象拷贝到主调函数的内存空间。

	//优化后
	//return CTemValue(t.value1 * 2, t.value2 * 2);//生成一个临时对象直接返回
}
//编译器视角
void DoubleMyself(CTemValue&obj, CTemValue&t)
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
	

	system("pause");
	return 0;
}
/*
 *在linux平台执行这个代码
* (1)编译器层面
* linux下面的g++编译器会对针对返回临时值进行优化，NRV优化(named Return Value)
*	ROV优化（return Value Optimization）
*	关闭优化：
*	g++ -fno-elide-constructors 文件名.cpp -o 生成文件名字
* (2)在Windows平台，项目属性右击--“属性”--“c/c++”--"优化"
*	“代码生成”--“基本运行时检查”--“默认值”
* (4)优化说明：
*	1.编译器是否真正优化了需要做测试
*	2.当代码很复杂，编译器会放弃优化
*	3.不要过度优化，过度优化可能导致程序错误，如你向在构造函数里面实现某些功能，但是被优化掉没有执行。
*	
* (5)
* (6)(7)
*/
