#include<iostream>
#include <algorithm>
using namespace std;

/*
 *7_1_1函数模板
 *结论：
 *函数模板  针对类型T的类型推断是编译器在编译的时候，针对addFunction函数的调用来确定T的类型。
 *如果我们没有针对addFunction()函数的调用代码，编译器不会为我们产生任何和函数模板有关的代码。
 *就好像函数addFunctioin没有存在过一样
*
 */
template<typename T>
//T addFunction( T&a, T&b)
T addFunction(const T&a,const T&b)
{
	T addtem = a + b;
	return  addtem;
}

void myFunction()
{
	int a = 12;
	int b = 23;
	cout << addFunction<int>(12, 14) << endl;//函数必须加const才不会报错
	cout << addFunction(a, b) << endl;

}

int main(void)
{
	myFunction();
	system("pause");
	return 0;
}