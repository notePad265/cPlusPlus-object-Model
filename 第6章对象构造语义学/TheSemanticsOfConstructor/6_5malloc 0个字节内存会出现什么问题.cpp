#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>

using namespace std;


/*
 *一：特别说明：《C++从入门到精通 C++98/11/14/17》第七章内容融入到本门课程中来
 *二：malloc来分配0个字节
 *	老手程序员和新手程序员最大区别：老手程序员对于不会或者没闹明白的东西可以不去用，但是一般不会用错；
 *	新手程序员正好相反，他发现系统没有报什么异常他就觉得这种用法是正确的；
 *	即便malloc(0)返回的是一个有效的内存地址，你也不要去动这个内存，不要修改内容，也不要去读；
 */


	void func()
	{
		//void *p = malloc(0); //new调用的也是malloc，所以

		void *p = malloc(100); //new调用的也是malloc，所以
							   //char *p = new char[0];
		char *q = (char *)p;
		strcpy_s(q, 100, "这里是一个测试"); //这行导致程序出现暗疾和隐患；
		free(p);


		int abc;
		abc = 1;
	}


int main()
{
	func();
	system("pause");
	return 1;
}



