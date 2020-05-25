#include <iostream>
#include <stdio.h>
using namespace std;

class FAC //父类
{
public:
	int m_fai;
	int m_faj;
};
class MYACLS :public FAC //子类
{
public:
	int m_i;
	int m_j;
};

class Base //sizeof = 8字节；
{
public:
	int m_i1;
	char m_c1;
	char m_c2;
	char m_c3;
};


int main()
{
	//第五节  4-5单一继承下的数据成员布局
	//查看偏移值
	printf("FAC::m_fai = %d\n", &FAC::m_fai);//0
	printf("FAC::m_faj = %d\n", &FAC::m_faj);//4

	printf("MYACLS::m_fai = %d\n", &MYACLS::m_fai);//0
	printf("MYACLS::m_faj = %d\n", &MYACLS::m_faj);//4
	
	printf("MYACLS::m_i = %d\n", &MYACLS::m_i);//8
	printf("MYACLS::m_j = %d\n", &MYACLS::m_j);//12
	/*
	    FAC::m_fai = 0
		FAC::m_faj = 4
		MYACLS::m_fai = 0
		MYACLS::m_faj = 4
		MYACLS::m_i = 8
		MYACLS::m_j = 12
	总结：
		(1)一个子类对象，所包含的内容，是他自己的成员，加上他父类的成员的总和；
		(2)从偏移值看，父类成员先出现，然后才是孩子类成员。父类成员在上，子类成员在下
	 */
	
	FAC facobj;//父类FAC对象布局
	MYACLS myaclobj; //子类对象中实际上是包含着父类子对象的--查看数据布局图

	//对象内存对齐时候的偏移量
	cout << "---------------------------------" << endl;
	cout << sizeof(Base) << endl;   //8字节，数据布局（内存排列上）紧凑；
	printf("Base::m_i1 = %d\n", &Base::m_i1);//0
	printf("Base::m_c1 = %d\n", &Base::m_c1);//4
	printf("Base::m_c2 = %d\n", &Base::m_c2);//5
	printf("Base::m_c3 = %d\n", &Base::m_c3);//6
	/*
	 8
	Base::m_i1 = 0
	Base::m_c1 = 4
	Base::m_c2 = 5
	Base::m_c3 = 6
	 */

	system("pause");
	return 0;
}

/*
 * 结论：1.子类对象包含父类对象的数据成员
 * 2.类中成员变量会自动进行内存对齐
 * 2019年12月15日17点18分
 */
