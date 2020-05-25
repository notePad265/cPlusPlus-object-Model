#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct AdvTeacher
{
	char name[64];
	int age;
	int p;
	char*pName;
}AdvTeacher;

int main(void)
{
	int i = 0;
	AdvTeacher t1;
	AdvTeacher*p = NULL;
	p = &t1;

	{
		int offsize1 = (int)&(p->age) - (int)p;//& (t1.age)，求出age的真实位置的地址
		int offsize2 = (int)&(((AdvTeacher*)0)->age);//当p-p=0  相对于0的位置求age的偏移量,这里的0是p-p,移动到0位置来解释
		 //按照(AdvTeacher *)类型解释0(p-p)开始的内存空间的位置
		printf("offsize1:%d \n", offsize1);//把结构体元素的内存分配方式映射到内存位0的位置，
		printf("offsize2:%d \n", offsize2);
	}

	printf("helloworld\n");
	system("pause");
	return 0;
}
/*
offsize1:64
offsize2:64
helloworld
请按任意键继续. . .


总结：如果自己发布了一个头文件，则里面的结构体变量位置不能随便修改
会改变偏移量的大小，
*/