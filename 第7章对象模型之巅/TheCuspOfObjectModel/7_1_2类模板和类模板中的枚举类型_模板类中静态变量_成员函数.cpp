#include<iostream>

using namespace std;

//7_1_2类模板和类模板中的枚举类型_模板类中静态变量_成员函数
/*
 * 结论：1.如果程序中没有使用到类模板，那么编译器就会对MyClass的类模板视而不见，就好像从来没保存过一样。
 * 2.1模板中的枚举类型
 * 2.2类模板中的静态成员变量
 *		结论：类本身并没有被实例化，只是成员变量被实例化
 *2.3类模板的实例化
 *
 *2.4成员函数的实例化
 * 问题：类被实例化出来，类中的成员函数被实例化出来了吗？？
 *		在没有调用成员函数的情况下，是不会实例化
 *
 * 
 * 
 */
template <typename T>
class MyClass
{
public:
	T m_i;
	T m_j;
	MyClass(T temi=0,T temj=0):m_i(temi),m_j(temj)
	{
		;
	}

	//普通成员函数
	void myFunction01() const{ cout << "myFunction01被调用" << endl; }
	void myFunction02() const{ cout << "myFunction02被调用" << endl; }
	
	//类模板中的枚举类型
	enum ECURRSTATUS
	{
		ECUS_Busy, ECUS_Free
	};

	//静态成员变量--声明
	static int m_static_i;
	static T m_static_j;



};

//静态成员变量定义
template<typename T>
int MyClass<T>::m_static_i = 10;

template<typename T>
T MyClass<T>::m_static_j = 15;//这里赋值取决于T的类型，下面指定类型要和15兼容


void func()
{
	MyClass<int>::ECURRSTATUS myEnum;
	myEnum = MyClass<int>::ECUS_Busy;

	//两亿中枚举类型
	MyClass<double>::ECURRSTATUS myEnum02;
	myEnum02 = MyClass<double>::ECUS_Free;
	//结论：类中的枚举类型依赖于具体的类模板类型，但是和类模板关系不大


	//2.2静态成员变量--类本身并没有被实例化，只是成员变量被实例化
	MyClass<int>::m_static_i = 14;
	MyClass<float>::m_static_i = 15;
	cout << MyClass<int>::m_static_i << endl;//14
	cout << MyClass<float>::m_static_i << endl;//15
	//是两个不相关的类型变量

	MyClass<int>::m_static_j = 34;
	cout << MyClass<int>::m_static_j << endl;//34
	

	//2.3类模板的实例化
	MyClass<int>*pobj01 = NULL;//这种写法没有实例化出具体的类
	
	const MyClass<int>&obj01 = 0;//调用了构造函数，实例化了类模板
	/*
	 * 站在编译器角度：
	 * MyClass<int> temObj(0);
	 * const MyClass<int>&obj01=temObj;
	 */

	//2.4成员函数实例化
	obj01.myFunction01();//const对象必须调用const函数
	
}

int main(void)
{
	func();
	system("pause");
	return 0;
}