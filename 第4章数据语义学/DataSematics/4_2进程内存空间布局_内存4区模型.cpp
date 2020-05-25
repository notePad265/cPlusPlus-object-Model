#include <iostream>
#include <ctime>
#include <stdio.h>
#include<cstdlib>
using namespace std;

int *ptest = new int(120);
int g1;//未初始化的全局量或者初始化为0的全局量放在.BSS段(操作系统自动给没有初始化的变量自动赋值0)
int g2;

int g3 = 12;//初始化放在数据段
int g4 = 32;
int g5;
int g6 = 0;
static int g7;
static int g8 = 0;
static int g9 = 10;
void mygfunc()
{
	return;
}

//定义一个类
class MYACLS
{
public:
	int m_i;
	static int m_si; //声明不是定义，不会分配内存空间
	int m_j;
	static int m_sj;
	int m_k;
	static int m_sk;
	//static void myclsfunc() {}
};
int MYACLS::m_sj = 0; //这才是定义；类的静态成员变量也会存储在数据段

int main()
{
	


	int i = 7;//栈中分配的内存每次都分配内存，地址每次改变
	printf("i地址=%p\n", &i);


	printf("ptest地址=%p\n", &ptest);
	printf("g1地址=%p\n", &g1);
	printf("g2地址=%p\n", &g2);
	printf("g3地址=%p\n", &g3);
	printf("g4地址=%p\n", &g4);
	printf("g5地址=%p\n", &g5);
	printf("g6地址=%p\n", &g6);
	printf("g7地址=%p\n", &g7);
	printf("g8地址=%p\n", &g8);
	printf("g9地址=%p\n", &g9);
	printf("MYACLS::m_sj地址=%p\n", &(MYACLS::m_sj));

	printf("mygfunc()地址=%p\n", mygfunc);
	printf("main()地址=%p\n", main);


	cout << (void*)mygfunc << endl;
	
	system("pause");
	return 0;
}
/*
 * 4_2进程内存空间布局--内存四区i模型
 * 不同的数据在内存中会有不同的 保存时机，保存位置
 * 当运行一个可执行文件时，操作系统就会把这个可执行文件加载到内存；此时进程有一个虚拟的地址空间（内存空间）
 * 
 * linux有个nm命令:能够列出可执行文件中的全局变量存放的地址
 *	1.先编译出可执行文件
 *	2.nm 可执行文件名字
 *
 i地址=009DF718
 ptest地址=008CB300
 g1地址=008CB2E8
 g2地址=008CB2EC
 g3地址=008CB000
 g4地址=008CB004
 g5地址=008CB2F0
 g6地址=008CB2F4
 g7地址=008CB304
 g8地址=008CB2F8
 g9地址=008CB008
 MYACLS::m_sj地址=008CB2FC
 mygfunc()地址=008C11DB
 main()地址=008C132F
 008C11DB
 请按任意键继续. . .


 */

