#include<iostream>

using namespace std;

class A
{
private:
	virtual void myVirtualFunction()
	{
		myFunction();
		
	}
	void myFunction()
	{
		cout << "myFunction()被调用" << endl;
	}
};


int main(void)
{

	A obj_a;
	(reinterpret_cast<void(*)()>(**(int**)(&obj_a)))();//通过虚函数表调用虚函数myVirtualFunciton()
	/*
	 * 类只占有4个字节，是虚函数表指针，指向虚函数表,只有一个虚函数，就是虚函数表第一项
	 */
	long*pvptr = (long*)(&obj_a);//把对象obj_a的地址拿到
	long*vptr = (long*)(*pvptr);//拿到虚函数表指针
	typedef void(*Func)(void);//定义一个函数指针类型
	Func f1 = (Func)vptr[0];//虚函数表的第一项为myVirtualFunction()函数，
	f1();
	
	
	system("pause");
	return 0;
}
/*
 * 7_2_2类外调用私有函数
 *
 *myFunction()被调用
myFunction()被调用
请按任意键继续. . .

 *
 */