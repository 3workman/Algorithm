/***********************************************************************
* @ 合并k个排序链表（升序）

* @ 最小堆思路 O(nklogk)
	、取每个List头节点，放入最小堆，堆顶即为最小元素，取出放入输出List
	、然后将该节点的下一个节点放入最小堆

* @ 归并思路 O(nklogk)
	、分为两个子部分，归并，递归

* @ author zhoumf
* @ date 2019-4-11
************************************************************************/
#pragma once
#include <vector>
#include "divide-and-conquer/sort.h"

template <typename T> std::vector<T> MergeList(std::vector<T>* arr, int k) {
	typedef std::pair<std::vector<T>::iterator, std::vector<T>::iterator> pair;
	std::vector<pair> heap; heap.reserve(k);
	auto cmp = [](const pair& a, const pair& b) { return *(a.first) > *(b.first); };

	for (int i = 0; i < k; ++i) {
		std::vector<T>& list = arr[i];
		if (list.empty()) continue;
		heap.push_back(make_pair(list.begin(), list.end()));
	}
	make_heap(heap.begin(), heap.end(), cmp); //建堆

	std::vector<T> ret;
	while (!heap.empty()) {
		pop_heap(heap.begin(), heap.end(), cmp); //取出堆顶，放入输出列表
		auto itHeap = heap.rbegin();
		auto& it = itHeap->first;
		auto& end = itHeap->second;
		ret.push_back(*it);
		if (++it == end) heap.pop_back(); //该元素所在列表空了，堆长减少
		else push_heap(heap.begin(), heap.end(), cmp); //该元素的下个元素，重新加入堆
	}
	return ret;
}

template <typename T> std::vector<T> MergeList(std::vector<T>* arr, int begin, int end) {
	if (end - begin > 1) {
		int mid = (begin + end) >> 1;  //中间下标，向下取整，分成两个子数组
		auto ret1 = MergeList(arr, begin, mid);
		auto ret2 = MergeList(arr, mid, end);
		return _Merge2List(ret1, ret2);
	}
	return arr[begin];
}
template <typename T> std::vector<T> _Merge2List(std::vector<T>& L, std::vector<T>& R) {
	int size = L.size() + R.size();
	L.push_back(INT_MAX); R.push_back(INT_MAX); //放置哨兵，数组判空，合并到元素比较之中

	std::vector<T> ret; ret.resize(size);
	for (int i(0), l(0), r(0); i < size; ++i)
	{
		L[l] <= R[r] ? ret[i] = L[l++] : ret[i] = R[r++];
	}
	return ret;
}