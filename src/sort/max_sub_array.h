/***********************************************************************
* @ 最大子数组
* @ 分治
	1、先拆分成两个子数组，减少规模
	2、拆分后，最大子数组，只有三种情形：
		·只在左子数组
		·只在右子数组
		·两边都有，跨了分割点
	3、前两种情形，跟原始问题一样，递归处理
	4、跨分割点的情形，分别计算分割点到头尾的累计和，很容易找到最大子数组

* @ 增量
	1、遍历，记录每次找到的最大子数组
	2、当增加一个新元素时，最大子数组只有三种情形：
		·不变
		·右下标指向新元素
		·抛弃旧数组，新数组只含新元素

* @ author zhoumf
* @ date 2019-3-30
************************************************************************/
#pragma once
#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> SubArray; //左下标、右下标、累加和
#define SubArraySum(a) std::get<2>(a)

// ------------------------------------------------------------
// 分治
SubArray FindMaxCrossSubArray(const std::vector<int>& arr, int begin, int mid, int end) { //最大子数组包含中间元素的情形
	int leftSum(INT_MIN), rightSum(INT_MAX), leftIdx, rightIdx;
	for (int i(begin), sum(0); i < mid; ++i) {
		if ((sum += arr[i]) > leftSum) {
			leftSum = sum;
			leftIdx = i;
		}
	}
	for (int i(mid), sum(0); i < end; ++i) {
		if ((sum += arr[i]) > rightSum) {
			rightSum = sum;
			rightIdx = i;
		}
	}
	return { leftIdx, rightIdx, leftSum + rightSum };
}
SubArray FindMaxSubArray(const std::vector<int>& arr, int begin, int end) {
	if (end - begin <= 1) {
		return { begin, end, arr[begin] };
	} else {
		int mid = (begin + end + 1) / 2;//中间下标，+1向上取整，分成两个子数组
		auto left = FindMaxSubArray(arr, begin, mid);			//情形一：只在左子数组
		auto right = FindMaxSubArray(arr, mid, end);				//情形二：只在右子数组
		auto cross = FindMaxCrossSubArray(arr, begin, mid, end);	//情形三：两边都有，跨了分割点

		if (SubArraySum(left) >= SubArraySum(right) && SubArraySum(left) >= SubArraySum(cross))
			return left;
		else if (SubArraySum(right) >= SubArraySum(left) && SubArraySum(right) >= SubArraySum(cross))
			return right;
		else return cross;
	}
}
SubArray FindMaxSubArray(const std::vector<int>& arr) { return FindMaxSubArray(arr, 0, arr.size()); }

// ------------------------------------------------------------
// 增量
SubArray FindMaxSubArrayEx(const std::vector<int>& arr) {
	int left(0), right(1), sum(arr[0]), sum2(0);//right到新下标，期间元素的累加和
	for (size_t i = 1; i < arr.size(); ++i) {
		sum2 += arr[i];
		if (sum > 0 && sum2 > 0) { //右下标挪至新元素处
			right = i + 1; sum += sum2; sum2 = 0;
		}  else if (arr[i] > sum) { //抛弃旧结果
			left = i; right = i + 1; sum = arr[i]; sum2 = 0;
		}
	}
	return { left, right, sum };
}

// ------------------------------------------------------------
#undef SubArraySum