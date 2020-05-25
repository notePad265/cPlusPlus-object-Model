
#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>

using namespace std;


/*
 * 四：析构函数语义
 * （4.1）析构函数被合成
 *	问题：什么情况下编译器会给我们生成一个析构函数？
 *	a)如果继承一个基类，基类中带析构函数，那么编译器就会给咱们A合成出一个析构函数--来调用基类JI中的析构函数
 *	b)如果类成员是一个类类型成员，并且这个成员带析构函数，编译器也会合成出一个析构函数，这个析构函数存在的意义是要调用m_j这个类类型成员所在类的析构函数；
 *
 *	（4.2）析构函数被扩展
 *	如果我们有自己的析构函数，那么编译器就会在适当的情况下扩展我们的析构函数代码；
 *	a)如果类成员m_j是一个类类型JI成员，并且这个成员m_j带析构函数~JI()，编译器扩展类A的析构函数~A()代码
 *	先执行了类A的析构函数代码，再执行JI的析构函数代码
 *	b)如果继承一个基类，基类中带析构函数，那么编译器就会扩展咱们类A的析构函数来调用基类JI中的析构函数
 *	虚基类：留给大家探索；虚基类会带来更多的复杂性，也会程序执行效率有一定的影响；
 */


class JI
{
public:
	JI()
	{
		cout << "JI::JI()" << endl;
	}
	virtual ~JI()
	{
		cout << "JI::~JI()" << endl;
	}
};
class A :public JI
{
public:
	//JI m_j; //类类型成员变量
	A()
	{
		cout << "A::A()" << endl;
	}
	virtual ~A()
	{
		cout << "A::~A()" << endl;
	}
};

void func()
{
	A aobj;

}


int main()
{
	func();

	system("pause");
	return 1;
}



