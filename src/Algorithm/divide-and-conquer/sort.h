/***********************************************************************
* @ 排序
* @ 算法的一般思路
	1、构造“循环不变式”，有些算法会有预处理，让输入满足“循环不变式”
	2、考察每次循环的处理方式
	3、优化评估：
		·在原思路之上查找优化点
			·那些步骤是重复的
			·如何利用已计算出的结果
			·合并判断条件，次级指针、哨兵
		·切换新思路

* @ Optimize：利用已有的结果
	、插入排序中，定位新元素位置时，用的遍历方式
		·此时列表是已排序的，有更快的定位方法
		·如二分
	、再比如计算X^n，可以连续乘n次，时间复杂度θ(n)
		·分治思路，拆成两相等部分后，仅需计算一个部分即可，θ(lgn)

* @ author zhoumf
* @ date 2019-3-30
************************************************************************/
#pragma once
#include <vector>

template <typename T> void SortInsert(std::vector<T>& arr) {
	for (int i = 1; i < arr.size(); ++i) {
		T key = arr[i];	//待比较的新元素
		int j = i - 1;	//新元素之前的，已经排序好了
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j]; //已排序元素后移一位
			--j;
		}
		arr[j + 1] = key; //将新元素插入空位中（排序元素挪出的）
	}
}

// ------------------------------------------------------------
// 归并
template <typename T> void SortMerge(std::vector<T>& arr) { SortMerge(arr, 0, arr.size()); }
template <typename T> void SortMerge(std::vector<T>& arr, int begin, int end) {
	if (end - begin > 1) {
		int mid = (begin + end) >> 1;  //中间下标，向下取整，分成两个子数组
		SortMerge(arr, begin, mid);    //分别递归
		SortMerge(arr, mid, end);
		SortMerge2(arr, begin, mid, end); //合并已排序的子数组
	}
}
template <typename T> void SortMerge2(std::vector<T>& arr, int begin, int mid, int end) {
	//两子数组……可优化为原址排序，挪动元素
	std::vector<T> L(arr.begin() + begin, arr.begin() + mid), R(arr.begin() + mid, arr.begin() + end);
	L.push_back(INT_MAX); R.push_back(INT_MAX); //放置哨兵，数组判空，合并到元素比较之中

	for (int i(begin), l(0), r(0); i < end; ++i)
	{
		L[l] <= R[r] ? arr[i] = L[l++] : arr[i] = R[r++];
	}
}

// ------------------------------------------------------------
// 快排
template <typename T> void SortQuick(std::vector<T>& arr) { SortQuick(arr, 0, arr.size()); }
template <typename T> void SortQuick(std::vector<T>& arr, int begin, int end) {
	if (end - begin > 1) {
		int pivot = SortQuick2(arr, begin, end); //按主元将arr分成两部分，Left全小于主元，Right全大于
		SortQuick(arr, begin, pivot);
		SortQuick(arr, pivot+1, end);
	}
}
template <typename T> int SortQuick2(std::vector<T>& arr, int begin, int end) { 
	int& pivot = arr[begin]; //定主元，用以分割……TODO:optimize:随机选取主元，交换至排头
	int i = begin; //i之前是小于等于主元的
	for (int i = begin + 1; i < end; ++i) {
		if (arr[i] <= pivot) std::swap(arr[++i], arr[i]);
		//循环不变式：idx之前<=pivot，idx到i>pivot，i之后待检测
	}
	std::swap(pivot, arr[i]); //主元交换到正确的位置
	return i;
}