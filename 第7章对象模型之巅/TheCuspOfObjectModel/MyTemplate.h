#pragma once

template <typename T>
class MyClass
{
public:
	T m_i;
	T m_j;
	MyClass(T temi = 0, T temj = 0) :m_i(temi), m_j(temj)
	{
		;
	}

	//普通成员函数
	void myFunction01() const { cout << "myFunction01被调用" << endl; }
	void myFunction02() const { cout << "myFunction02被调用" << endl; }

	//虚函数
	void myVirtualFunction01() const { cout << "myVirtualFunction01被调用" << endl; }


	//类模板中的枚举类型
	enum ECURRSTATUS
	{
		ECUS_Busy, ECUS_Free
	};

	//静态成员变量--声明
	static int m_static_i;
	static T m_static_j;



};