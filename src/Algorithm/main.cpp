/***********************************************************************
* @ 思路分析，解决问题的步骤
	·重现如何分析问题，如何一步步解决的

* @ 一、先罗列要实现的几个点，再编码
	·方便最后检查时的功能遗漏，如
		·memcpy忘返回原始指针
		·链表reverse返回新头节点

* @ 二、循环不变式，构造、证明
	·设计循环不变式
	·证明不变式初始化时为真
	·每次迭代都维持不变 ---- 可以从n推广到n+1，就是数学归纳法呀
		·不直观的规律，利用归纳法总结
		·递归式 -> 尾递归 -> 循环
		·每种的思路分析，细致明了的写出来

* @ author zhoumf
* @ date 2019-4-6
************************************************************************/
#include "stdafx.h"
#include "divide-and-conquer/max_sub_array.h"
#include "divide-and-conquer/sort.h"
#include "divide-and-conquer/search.h"

int main(int argc, char* argv[])
{
	//LogFile log("log/algorithm", LogFile::DEBUG);
	//_LOG_MAIN_(log);

	std::vector<int> arr{-9,-1,-2, 5, 1, 6, 0, -11};
	//std::vector<int> arr{ 1,2,3};
	SortBucket(arr, -11, 6);
	int ret = SelectMinEx(arr, 1);

    system("pause");
    return 0;
}