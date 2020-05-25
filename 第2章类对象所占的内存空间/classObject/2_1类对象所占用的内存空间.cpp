#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

//空类
class A
{
public:
	
};

class B
{
public:
	void myFunction01() {};//成员函数
	void myFunction02() {};
	void myFunction03() {};

};


class C
{
public:
	void myFunction01() {};//成员函数
	void myFunction02() {};
	void myFunction03() {};
	char ab;//成员变量
};


class D
{
public:
	void myFunction01() {};//成员函数
	void myFunction02() {};
	void myFunction03() {};

	int dd;//成员变量
};

int main(void)
{
	A obj_a;
	cout << sizeof(obj_a) << endl;//1  sizeof(a)和sizeof(A)是等价的
	cout << sizeof(A) << endl;//1
	/*
	 * 为什么sizeof(空类)=1，而不是等于0；
	 * shift+f9快速监视，查看地址，在内存中查看地址的内容是：cc
	 * 	&obj_a	0x008ffc13 {...}	A *
	 * 	因为对象在内存中是有起始地址的，既然这个起始地址是属于对象obj_a,
	 * 	所以sizeof(a)一个对象的内存空间至少要有一个字节，因为在内存中占有位置。
	 * 	就好像一个房子的面积要存在，而不是0平方米。
	 * 	一个对象存在就有内存地址，最少要在内存空间中占有一个字节。
	 */

	B obj_b;
	cout << sizeof(B) << endl;//1
	cout << sizeof(obj_b) << endl;//1
	/*
	 * 类的成员函数不占用类对象(b)的内存空间
	 * 
	 */

	C obj_c;
	cout << sizeof(C) << endl;//1
	cout << sizeof(obj_c) << endl;//1
	/*
	 * 现在加上一个char类型占一个字节内存，现在为什么还是一个字节？？
	 * 现在这一个字节里面存储的是char成员变量，怎么验证？
	 */
	obj_c.ab = 'c';
	/*
	 *加断点调试，shift+F查看obj_c的地址，然后在“内存1”面板中查看
	 *+		&obj_c	0x00f9fc87 {ab=-52 '?' }	C *
	 *
	 *值为0x00F9FC87  63 cc cc cc cc cc cc cc cc cc cc  c??????????
	 *
	 *结论：3.成员变量是占用类对象的内存空间的
	 * 
	 */
	D obj_d;
	cout << sizeof(D) << endl;//4
	cout << sizeof(obj_d) << endl;//4
	obj_d.dd = 4;
	/*+		&obj_d	0x00affb9c {dd=-858993460 }	D *
	 *0x00AFFB9C  04 00 00 00 cc cc cc cc cc cc cc  ....???????
	 *
	 * 结论：成员变量是包含在每个对象中的，是占用对象字节内存的，而成员函数虽然也写在类的定义中，但是成员函数是不占对象字节数的（不占内存空间）
	 *一个类生成多个对象，每个对象都给自己的成员变量分配内存空间，每个类的成员属性可以存储不同的值。
	 * 成员函数每个类只诞生一个，跟着类走，而不管用这个类产生了多少个该类的对象。
	 */
	
	system("pause");
	return 0;
}

/*
* (1)类对象所占用的空间
*	1.一个类对象至少占用1个字节的内存空间
*	2.类的成员函数不占用类对象的内存空间
*	3.成员变量是占用类对象的内存空间的
*/
