#include <iostream>
#include <stdio.h>
using namespace std;


class Base //sizeof = 8字节；
{
public:
	int m_i1;
	char m_c1;
	char m_c2;
	char m_c3;
};

//多层继承--把一个类Base拆成多个类
class Base1
{
public:
	int m_i1;
	char m_c1;
};
class Base2 :public Base1
{
public:
	char m_c2;
};
class Base3 :public Base2
{
public:
	char m_c3;
};


int main()
{
	//第五节  4_5单一继承下的数据成员布局_多层继承
	
	//引入继承关系后，可能会带来内存空间的额外增加。Base3类增加了8个字节

	 cout << sizeof(Base1) << endl; //8
	 cout << sizeof(Base2) << endl; //12
	 cout << sizeof(Base3) << endl; //16
	 printf("Base3::m_mi1 = %d\n", &Base3::m_i1);//0
	 printf("Base3::m_mc1 = %d\n", &Base3::m_c1);//4
	 printf("Base3::m_mc2 = %d\n", &Base3::m_c2);//8
	 printf("Base3::m_mc3 = %d\n", &Base3::m_c3);//12

	 //linux上windows上数据布局不一样(8,12,12)，说明：
	 //a)编译器在不断的进步和优化；
	 //b)不同厂商编译器，实现细节也不一样；
	 //c)内存拷贝就要谨慎；

	Base2 mybase2obj;
	Base3 mybase3obj;
	//你就不能用memcpy内存拷贝把Base2内容直接Base3里拷贝；


	system("pause");
	return 1;
}

