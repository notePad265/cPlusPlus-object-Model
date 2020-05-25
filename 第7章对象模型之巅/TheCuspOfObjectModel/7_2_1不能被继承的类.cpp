#include<iostream>

using namespace std;

//不能被继承的类
class A
{
private:
	A(){}
	friend class B;//我们希望类B能成为一个不能被继承的类
};

class B:virtual public A//“C::C(void)” : 尝试引用已删除的函数
//class B : public A//“C::C(void)” : 尝试引用已删除的函数	

{
public:
	int m_b;
};

//class C:public B
class C :public B
{
public:
	int m_c;
};
void myFunction01()
{
	//A obj_a;//A的构造函数是私有的，error
	B obj_b;//B类的构造函数去调用A类的构造函数，B是A类的友元类
	obj_b.m_b = 12;
	//C obj_c;
	//obj_c.m_c = 20;

	/*
	 * 如果B不是虚继承A，C调用B的构造函数，B调用A的构造函数，
	 * 如果B虚继承类A，那么A类的构造函数时C类孙子类来调用，而C不能调用A的private构造函数，会报错
	 */
	
}

int main(void)
{

	system("pause");
	return 0;
}
/*
 * 1.7_2_1不能被继承的类
 *		c++11中的final关键字，如果不用关键字怎么让类不能被继承？？
 *		友元函数+虚继承实现不能被继承的类
 *		副作用：友元函数破坏类的封装性，虚继承消耗比较大
 */