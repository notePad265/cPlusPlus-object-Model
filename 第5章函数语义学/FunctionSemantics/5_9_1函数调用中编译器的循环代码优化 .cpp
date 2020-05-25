#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


	//一：函数调用中编译器的循环代码优化	
	//debug,release
	//（1）优化循环，把循环优化成1条语句；
	//（2）在编译期间，编译器也具有运算能力，有些运算编译器在编译期间就能搞定；

	__int64 mytest(int mv)
	{
		__int64 icout = 0;
		for (int i = 1; i < 1000000; i++)
		{
			icout += 1;
			/*if (i == 10000 && mv == 999)//多一个逻辑判断--这几行代码时为了防止编译器优化成直接加总和(编译器提前把和值计算出来。)
			{
				printf("------\n");
			}*/
		}
		//icout += 循环多少次之后的和值
		return icout;
	}

	void func()
	{
		clock_t start, end;
		__int64 mycout = 1;
		start = clock();
		for (int i = 0; i <= 1000; i++)
		{
			//mycout += mytest(i); //给固定参数时，编译器将这种参数固定的函数调用视为一种不变的表达式
			mycout += mytest(6);
		}
		//优化成一个语句：mycout += 循环1000次的和值
		end = clock();
		cout << " 用时(毫秒）：" << end - start << endl;
		cout << " mycout:" << mycout << endl;
	}


int main()
{
	func();
	/*
	 *debug版本：
	    用时(毫秒）：2653
		mycout:1000999000
	Released版本：
		 用时(毫秒）：0
		mycout:1000999000
	 */
	
	system("pause");
	return 1;
}



