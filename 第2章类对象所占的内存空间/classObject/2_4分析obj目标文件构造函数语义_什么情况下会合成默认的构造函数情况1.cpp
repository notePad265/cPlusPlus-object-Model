#include<iostream>
#include<cstdlib>
#include<functional>
#include <vector>
#include <algorithm>
using namespace std;
class  M0TX
{
public:
	M0TX()//默认构造函数
	{
		cout << "jijijijijiji" << endl;
	}
};


class MATX
{
public:
	MATX()
	{
		cout << "goodHAHAHAHHA" << endl;
	}
};

class MBTX
{
public:
	int m_i;
	int m_j;
	MATX ma;//类对象成员变量
	M0TX m0;//类对象成员变量
	void myFunction()
	{
		cout << "IAmVeryGood" << endl;
	}
};

int main(void)
{
	//根据MBTX类生成一个对象
	MBTX myb;
	system("pause");
	return 0;
}
/*
* (1)构造函数
* 默认构造函数(缺省):没有参数的构造函数，没有定义任何构造函数，编译器就会给我们定义一个默认构造函数
* 我们一般称这种构造函数为"合成的默认构造函数"。
*	探究一下：入门我们没有定义构造函数，编译器真的给我们合成了默认的构造函数了吗？？
*
*	结论：“合成的默认构造函数”只有在必要的时候，编译器才会给我们合成出来，而不是必然为我们合成出来。
*	问题：什么是“必要的时候”？？？
*
*预备知识：
*	每个.cpp文件都会编译生成一个.obj(linux .o)文件(目标文件)，最终把很多obj文件链接在一起生成一个可执行文件。
*	.obj属于二进制文件，需要借助于工具来查看
*
*	1.写好程序后，点击“生成”--“生成解决方案”--========== 生成: 成功 1 个，失败 0 个，最新 0 个，跳过 0 个 ==========
*	2.打开.cpp文件所在的文件夹，Debug文件夹下面有一个和.cpp文件相同的.obj文件
*	3.从开始菜单打开“vs2015开发人员命令提示”，进入.obj所在的目录
*		e:		进入e盘  cd进入目录，或者复制进入目录
*		E:\>cd E:\ProjectCode\第2章类对象所占的内存空间\classObject\Debug
*		使用dumpbin分析工具，将分析结果写入一个txt文件中
*			dumpbin /all 2_4分析obj目标文件构造函数语义.obj > 分析文件.txt
*
*	4.用dumpbin把.obj文件内容导出为可查看文件“2_4分析文件.txt”，一般被认为是COFF：通用文件对象格式(common object format)
*		不研究这种文件格式，只找我们关心的内容即可	
*
*	5.control +f 查找  MBTX::MBTX
*	结果：编译器没有为我们合成默认的构造函数。
*
*
*
* (2)问题：编译器会在哪些必要的时候帮助我们合成默认的构造函数？？？
*	1.当类没有任何构造函数，但包含一个类类型的成员，如MBTX包含MATX类型成员，而该对象所属的类MATX有一个缺省的构造函数。
*		编译器为MBTX合成一个默认的构造函数，合成的目的是为了调用MATX里的默认构造函数。
*		换句话说：编译器合成了默认的MBTX构造函数，并且在其中增加代码，调用MATX的缺省构造函数。
*		使用dumpbin生成COFF文件查找
*			COMDAT; sym= "public: __thiscall MBTX::MBTX(void)" (??0MBTX@@QAE@XZ)
*	当包含两个类对象成员的时候，按照包含的顺序调用构造函数
*	 --------  ----------------  -----------------  --------  ------
 0000002A  REL32                      00000000        91  ??0MATX@@QAE@XZ (public: __thiscall MATX::MATX(void))
 00000035  REL32                      00000000        8E  ??0M0TX@@QAE@XZ (public: __thiscall M0TX::M0TX(void))
----------------------------------------------------------------------------------------------------------------
		goodHAHAHAHHA
		jijijijijiji
	更换包含对象顺序后执行顺序相反


* (3)
* 10点21分2019年12月13日
*/
