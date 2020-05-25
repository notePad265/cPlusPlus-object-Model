#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;

class MBTXPARENT
{
public:
	MBTXPARENT()
	{
		cout << "ppppppppppppppppppppppp" << endl;
	}
};

class MBTX:public MBTXPARENT
{
public:
	int m_i;
	int m_j;
};

int main(void)
{
	MBTX mb;//父类的构造函数被子类合成的构造函数调用
	
	system("pause");
	return 0;
}
/*
* (1)问题：编译器会在哪些必要的时候帮助我们合成默认的构造函数？？？
* 情况2：父类带缺省构造函数，子类没有任何构造函数,当创建子类对象的时候。
*	因为父类缺省的构造函数被调用，编译器会给子类合成出一个默认的构造函数。
*	合成的目的是为了在子类中调用父类的构造函数，完成父类成员的初始化工作。
*	换句话说，编译器为子类合成默认的构造函数，并在其中安插代码，调用其父类的缺省构造函数。
*
*	使用dumpbin工具查看如下：
		60501020 flags
		         Code
		         COMDAT; sym= "public: __thiscall MBTX::MBTX(void)" (??0MBTX@@QAE@XZ)
		         16 byte align
		         Execute Read

		RAW DATA #9
		  00000000: 55 8B EC 81 EC CC 00 00 00 53 56 57 51 8D BD 34  U.ì.ìì...SVWQ.?4
		  00000010: FF FF FF B9 33 00 00 00 B8 CC CC CC CC F3 AB 59  ???13...?ììììó?Y
		  00000020: 89 4D F8 8B 4D F8 E8 00 00 00 00 8B 45 F8 5F 5E  .M?.M?è.....E?_^
		  00000030: 5B 81 C4 CC 00 00 00 3B EC E8 00 00 00 00 8B E5  [.?ì...;ìè.....?
		  00000040: 5D C3                                            ]?

		RELOCATIONS #9
		                                                Symbol    Symbol
		 Offset    Type              Applied To         Index     Name
		 --------  ----------------  -----------------  --------  ------
		 00000027  REL32                      00000000        88  ??0MBTXPARENT@@QAE@XZ (public: __thiscall MBTXPARENT::MBTXPARENT(void))


* (2)
* (3)
* (4)
* (5)
* (6)(7)
*/
