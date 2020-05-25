#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class A
{
	public:
	int test00;
	int test01;
	int test02;
	//3.初始化成员列表的初始化顺序是变量定义顺序。
	A(int a,int b):test01(a),test02(b),test00(test01)//这是错误的，按照定义的顺序给值，现有test00的值，才有test01,test02的值
	{
		cout << "构造函数执行" << endl;
		cout << "test00="<<test00 << endl;
		cout << "test01=" << test01 << endl;
		cout << "test02=" << test02 << endl;
		
	}
};

int main(void)
{
	A(1, 2);
	/*
	    构造函数执行
		test00=-858993460
		test01=1
		test02=2
	 */
	system("pause");
	return 0;
}
/*
* (1)初始化列表细节探秘
*	1.成员初始化列表中的代码可以看作是被编译器安插到构造函数中的代码，只是这些代码有些特殊。
*	2.成员初始化列表中这些代码的执行时机：是在任何用户自己的代码执行之前被执行的，所以用户要区别编译器插入的代码和用户自己写的代码。
*		编译器插入的代码最先执行
*	3.初始化成员列表的初始化顺序是变量定义顺序。建议：不要出现成员列表变量之间相互赋值。
* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
