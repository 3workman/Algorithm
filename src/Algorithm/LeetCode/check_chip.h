/***********************************************************************
* @ 芯片检测
	、n片可能完全一样的芯片，可用来互相检测。测试夹只能容纳两块芯片
	、夹具装载芯片时，每块都检测另一块，并报告它的好坏
	、好的芯片总能准确报告另一块的好坏，坏芯片不一定

* @ 证明：若超过n/2芯片坏的，任何基于逐对的检测，都无法确定芯片好坏

* @ 超过n/2好的，寻找一块好芯片问题，n/2将问题规模减半

* @ 超过n/2好的，设计θ(n)算法，找出它们

* @ author zhoumf
* @ date 2019-3-31
************************************************************************/
#pragma once
#include <functional>

//TODO:zhoumf: