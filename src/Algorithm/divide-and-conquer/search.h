#pragma once
#include <functional>
#include "sort.h"

// ------------------------------------------------------------
// 二分，闭包中与目标比较
int SearchInOrder(int n, const std::function<bool(int)>& f) {
	//f(-1) == false and f(n) == true.
	int i = 0, j = n;
	while (i < j) {
		int mid = (i + j) >> 1; //中间下标，向下取整
		f(mid) ? 
			j = mid :	//f(j) == true
			i = mid + 1;//f(i-1) == false
	}
	return i; //i == j, f(i-1) == false, f(j) == true
}

// ------------------------------------------------------------
// 第k小的元素
template <typename T> T SelectMin(std::vector<T> arr, int k) { return SelectMin(arr, k, 0, arr.size()); }
template <typename T> T SelectMin(std::vector<T>& arr, int k, int begin, int end) {
	if (end - begin <= 1) return arr[begin];
	int pivot = Divide(arr, begin, end);
	int leftCnt = pivot - begin; //前半部元素数量
	if (leftCnt == k) return arr[pivot];			//k正在主元处
	return leftCnt > k ? 
		SelectMin(arr, k, begin, pivot) :			//k在前半部
		SelectMin(arr, k-leftCnt-1, pivot+1, end);	//k在后半部，删去前部数目、删去主元
}

// ------------------------------------------------------------
// 线性，第k小的元素
template <typename T> T SelectMinEx(std::vector<T> arr, int k) { return SelectMinEx(arr, k, 0, arr.size()); }
template <typename T> T SelectMinEx(std::vector<T>& arr, int k, int begin, int end) {
	if (end-begin <= 1) return arr[begin];

	int n = (end-begin)/5;			//多少组5元素
	int leftCnt = (end-begin)%5;	//剩余的一组，有几个元素

	//对每组排序，找出其中位数
	std::vector<T> mids(n);
	for (int i = 1; i <= n; ++i) {
		SortQuick(arr, 5*(i-1), 5*i);
		mids[i-1] = arr[5*i-3];
	}
	if (leftCnt > 0) {
		SortQuick(arr, end-leftCnt, end);
		mids.push_back(arr[end-(leftCnt+1)/2]);
	}

	//找出中位数的中位数，用它作主元
	auto mid = SelectMin(mids, (mids.size()+1)/2);
	int pivot = DivideByKey(arr, mid, begin, end);

	leftCnt = pivot - begin; //前半部元素数量
	if (leftCnt == k) return arr[pivot];					//k正在主元处
	return leftCnt > k ?
		SelectMinEx(arr, k, begin, pivot) :					//k在前半部
		SelectMinEx(arr, k - leftCnt - 1, pivot + 1, end);	//k在后半部，删去前部数目、删去主元
}