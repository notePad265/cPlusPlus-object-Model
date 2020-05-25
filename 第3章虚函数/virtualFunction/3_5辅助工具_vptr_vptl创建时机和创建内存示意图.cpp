#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	system("pause");
	return 0;
}
/*
* (1)辅助工具
* vs2015开发人员命令提示符
* cl.exe 编译链接工具
*	1.切换到cpp所在的路径
*	2.E:\ProjectCode\第3章虚函数\virtualFunction>cl /d1 reportSingleClassLayoutDerived 3_4多重继承虚函数表分析.cpp
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.00.24215.1 版
版权所有(C) Microsoft Corporation。保留所有权利。


3_4多重继承虚函数表分析.cpp
D:\Microsoft Visual Studio 14.0\VC\INCLUDE\xlocale(341): warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指
定 /EHsc

class Derived   size(8):
+---
0      | +--- (base class Base01)
0      | | {vfptr}
| +---
4      | +--- (base class Base02)
4      | | {vfptr}
| +---
+---

Derived::$vftable@Base01@:
| &Derived_meta
|  0
0      | &Base01::myVirtulFunction01
1      | &Derived::myVirtulFunction02
2      | &Derived::deriveVirtulFunction05
3      | &Derived::deriveVirtulFunction06

Derived::$vftable@Base02@:
| -4
0      | &Base02::myVirtulFunction03
1      | &Derived::myVirtulFunction04

Derived::myVirtulFunction02 this adjustor: 0
Derived::myVirtulFunction04 this adjustor: 4
Derived::deriveVirtulFunction05 this adjustor: 0
Derived::deriveVirtulFunction06 this adjustor: 0
D:\Microsoft Visual Studio 14.0\VC\INCLUDE\exception(359): warning C4577: 在未指定异常处理模式的情况下使用了 "noexcept"
；不一定会在异常时终止。指定 /EHsc
Microsoft (R) Incremental Linker Version 14.00.24215.1
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:3_4多重继承虚函数表分析.exe
3_4多重继承虚函数表分析.obj

linux  g++ -fdump-class-hierarchy -fsyntax-only 文件名字.cpp生成.class文件


* (2)vptr vtbl创建时机
* vptr指针是什么时候创建出来的？？
*	vptr跟着对象走，所以对象什么时候创建出来，vptr就什么时候创建出来。
*	实际上，对于这种有虚函数的类，在编译的时候，编译器会往相关的构造函数中国和增加为vptr赋值的代码。
*	这是编译器为在编译期间增加的代码。
*	当程序运行的时候，遇见创建的代码，肯定要执行构造函数，构造函数中给vptr指针赋值。
*
*	vtbl的创建和赋值时机？？
*	实际上，虚函数表是编译器在编译期间就为每个类确定好了对应的虚函数表vtbl的内容。
*	然后在编译期间给相应的类的构造函数中添加给vptr赋值的代码。
*	这样程序运行到创建对象时候调用构造函数，进行把 虚函数表地址赋值给虚函数表指针。
* (3)程序运行创建虚函数表和虚函数内存示意图
* (4)
* (5)
* (6)(7)
*/
