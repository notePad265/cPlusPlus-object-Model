#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class MYACLS
{
public:
	int m_i;
	int m_j;
	int m_k;
};

void myfunc(int MYACLS::*mempoint, MYACLS &obj)
{
	obj.*mempoint = 260; //注意写法
}

int main()
{
	//一：对象成员变量内存地址及其指针_是个真正的指针
	MYACLS myobj;
	myobj.m_i = myobj.m_j = myobj.m_k = 0;
	printf("myobj.m_i = %p\n", &myobj.m_i); //对象的成员变量是有真正的内存地址的。

	//堆上分配内存
	MYACLS *pmyobj = new MYACLS();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);

	int *p1 = &myobj.m_i;
	int *p2 = &pmyobj->m_j;

	*p1 = 15;
	*p2 = 30;

	printf("p1地址=%p,p1值=%d\n", p1, *p1);
	printf("p2地址=%p,p2值=%d\n", p2, *p2);
	/*
	 myobj.m_i = 004FF8C0
	 pmyobj->m_i = 0070E438
	 pmyobj->m_j = 0070E43C
	 p1地址=004FF8C0,p1值=15
	 p2地址=0070E43C,p2值=30
	 */

	//二：成员变量的偏移值及其指针（和具体对象是没有关系的--不是对象绑定
	cout << "打印成员变量偏移值----------------" << endl;
	printf("MYACLS::m_i偏移值 = %d\n", &MYACLS::m_i); //打印偏移值，这里用的%d
	printf("MYACLS::m_j偏移值 = %d\n", &MYACLS::m_j);
	//用成员变量指针来打印偏移值也可以，看写法
	//大家要知道，成员变量指针里边保存的 实际上是个偏移值（不是个实际内存地址）。
	int MYACLS::*mypoint = &MYACLS::m_j;
	printf("MYACLS::m_j偏移地址 = %d\n", mypoint);

	mypoint = &MYACLS::m_i; //这里注意，单独使用时直接用名字，定义时才需要加MYACLS::
	printf("MYACLS::m_i偏移地址 = %d\n", mypoint);
	/*
	 MYACLS::m_i偏移值 = 0
	MYACLS::m_j偏移值 = 4
	MYACLS::m_j偏移地址 = 4
	MYACLS::m_i偏移地址 = 0
	 */

	//三：没有指向任何数据成员变量的指针
	//通过 一个对象名或者对象指针后边跟  成员变量指针 来访问某个对象的成员变量：
	cout << "****************************" << endl;
	myobj.m_i = 13;
	myobj.*mypoint = 22;
	pmyobj->*mypoint = 19;

	myfunc(mypoint, myobj);
	myfunc(mypoint, *pmyobj);
	cout << "sizeof(mypoint) =" << sizeof(mypoint) << endl; //成员变量指针也是个4字节；

	//结论：成员变量指针指向成员变量首地址才是000000000，你赋值为0则编译器给你减1，变为0xffff ffff
	int *ptest = 0;
	int MYACLS::*mypoint2;
	mypoint2 = 0; //成员变量指针赋值为0，编译器给你减1
	mypoint2 = NULL; //0xffffffff
	printf("mypoint2 = %d\n", mypoint2);//-1

	//if(mypoint2 == mypoint) //不成立，一个是0，一个是-1
	int MYACLS::*mypoint10 = &MYACLS::m_i;
	if (mypoint == mypoint10) //成立的
	{
		cout << "成立" << endl;
	}

	//mypoint2 += 1;//编译器不让加
	//mypoint2++;
	//mypoint2 = ((&MYACLS::m_i) + 1);

	/*
	 * sizeof(mypoint) =4
		mypoint2 = -1
		成立
	 */

	system("pause");

	return 1;
}

