#pragma once
#include <functional>

// ------------------------------------------------------------
// 二分
int Search(int n, const std::function<bool(int)>& f) {
	// Define f(-1) == false and f(n) == true.
	int i = 0, j = n;
	while (i < j) {
		int mid = (i + j) >> 1; //中间下标，向下取整
		f(mid) ? j = mid : // f(j) == true
			i = mid + 1;   // f(i-1) == false
	}
	// i == j, f(i-1) == false, f(j) == true  =>  answer is i.
	return i;
}