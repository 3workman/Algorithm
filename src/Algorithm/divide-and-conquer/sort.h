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

// ------------------------------------------------------------
// 插入 Θ(n^2)
template <typename T> void SortInsert(std::vector<T>& arr) {
	for (size_t i = 1; i < arr.size(); ++i) {
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
// 归并 Θ(nlgn)
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
// 快排 Θ(nlgn)：算法成熟常数因子很小，cpu cache友好
template <typename T> void SortQuick(std::vector<T>& arr) { SortQuick(arr, 0, arr.size()); }
template <typename T> void SortQuick(std::vector<T>& arr, int begin, int end) {
	if (end - begin > 1) {
		int pivot = SortQuick2(arr, begin, end); //按主元将arr分成两部分，Left全小于主元，Right全大于
		SortQuick(arr, begin, pivot);
		SortQuick(arr, pivot+1, end);
	}
	//while (end - begin > 1) { //尾递归，减少栈深度
	//	int pivot = SortQuick2(arr, begin, end);
	//	SortQuick(arr, begin, pivot);
	//	begin = pivot + 1;
	//}
}
template <typename T> int SortQuick2(std::vector<T>& arr, int begin, int end) {
	//std::swap(arr[begin], arr[Rand::rand(begin, end)]);
	int& pivot = arr[begin]; //定主元，用以分割……Optimize:随机选取主元，交换至排头；三数取中；
	int i = begin; //i之前是小于等于主元的，所以交换的是i+1元素
	for (int j = begin + 1; j < end; ++j) {
		if (arr[j] <= pivot) std::swap(arr[++i], arr[j]);
		//循环不变式：i之前<=pivot，i到j>pivot，j之后待检测
	}
	std::swap(pivot, arr[i]); //主元交换到正确的位置
	return i;
}

// ------------------------------------------------------------
// 堆排序，最大堆 Θ(nlgn)
#define Left(i)		((i<<1)+1)
#define Right(i)	((i<<1)+2)
#define Parent(i)	((i-1)>>1)
template <typename T> void SortHeap(std::vector<T>& arr) {
	//构建最大堆
	int heapSize = arr.size();
	for (int i = Parent(heapSize-1); i >= 0; --i) { //从最后一个元素的父结点开始调整
		HeapIfy(arr, i, heapSize);
	}
	for (--heapSize; heapSize > 0; --heapSize) {//减少堆size
		std::swap(arr[0], arr[heapSize]);		//根节点交换至尾部
		HeapIfy(arr, 0, heapSize);				//调整新堆
	}
}
template <typename T> void HeapIfy(std::vector<T>& arr, int i, const int kHeapSize) {
	int l = Left(i), r = Right(i), big = i;
	if (l < kHeapSize && arr[l] > arr[big]) big = l;
	if (r < kHeapSize && arr[r] > arr[big]) big = r;
	if (big != i) {
		std::swap(arr[big], arr[i]);
		HeapIfy(arr, big, kHeapSize);
	}
}
#undef Left
#undef Right
#undef Parent

// ------------------------------------------------------------
// 计数排序 Θ(n+k)：输入都属于一个小区间中的整数 [range1, range2]
template <typename T> void SortCount(std::vector<T>& arr, T range1, T range2) {
	std::vector<T> ret(arr.size());
	std::vector<T> range(range2-range1+1);
	for (auto & it : arr) ++range[ it-range1 ];
	for (size_t i = 1; i < range.size(); ++i) range[i] += range[i-1]; //range[i]记录有多少个元素<=i
	for (size_t i = arr.size()-1; i >= 0; --i) { //倒序遍历，保证排序是稳定的
		auto rangeIdx = arr[i]-range1;
		ret[ --range[rangeIdx] ] = arr[i]; //计数减一，即元素要放入的位置
	}
	arr = std::move(ret);
}

// ------------------------------------------------------------
// 基数排序 Θ(d(n+k))：n个d位元素3
// 先对个位稳定排序，再对十位，再对百位……可对多关键字的记录排序，如日期(年月日)
#define Radix(n, d) ((n%std::pow(10,d))/std::pow(10,d-1))
#undef Radix

// ------------------------------------------------------------
// 桶排序 Θ(n)：元素均匀分布于[range1, range2]
#define BucketIdx(n) (n-range1)*(arr.size()-1)/(range2-range1)
template <typename T> void SortBucket(std::vector<T>& arr, T range1, T range2) {
	std::vector<std::vector<T>> buckets(arr.size());
	for (auto& it : arr) {
		buckets[BucketIdx(it)].push_back(it); //按元素大小，分布到桶中
	}
	arr.resize(0);
	for (auto& it : buckets) {
		SortInsert(it);								//对每个桶排序
		for (auto& iter : it) arr.push_back(iter);	//依次将桶组装
	}
}