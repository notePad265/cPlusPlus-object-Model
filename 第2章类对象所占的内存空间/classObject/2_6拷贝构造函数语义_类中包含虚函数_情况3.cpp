
#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class CTBSon
{
public:
	virtual void myFunctionStatic()
	{
		;
	}
};

int main(void)
{
	CTBSon ctbs_son;
	CTBSon ctbs_son02 = ctbs_son;//拷贝构造函数
	/*
	 *          Code
       COMDAT; sym= "public: __thiscall CTBSon::CTBSon(class CTBSon const &)" (??0CTBSon@@QAE@ABV0@@Z)
	 */
	
	system("pause");
	return 0;
}
/*
* (1)拷贝构造函数语义学情况3
*	如果一个类CTBSon没有拷贝构造函数，但是该类声明了或者继承了虚函数。
*	当代码中遇见CTBSon的拷贝构造函数时候，就会合成默认的拷贝构造函数,向这个拷贝构造函数中插入语句。
*
*	插入语句的作用是设定类对象ctbs_son的虚函数表指针指向虚函数表。
*	
*	
* (2)
*/
