/***********************************************************************
* @ ˼·�������������Ĳ���
	��������η������⣬���һ���������

* @ һ��������Ҫʵ�ֵļ����㣬�ٱ���
	�����������ʱ�Ĺ�����©����
		��memcpy������ԭʼָ��
		������reverse������ͷ�ڵ�

* @ ����ѭ������ʽ�����졢֤��
	�����ѭ������ʽ
	��֤������ʽ��ʼ��ʱΪ��
	��ÿ�ε�����ά�ֲ��� ---- ���Դ�n�ƹ㵽n+1��������ѧ���ɷ�ѽ
		����ֱ�۵Ĺ��ɣ����ù��ɷ��ܽ�
		���ݹ�ʽ -> β�ݹ� -> ѭ��
		��ÿ�ֵ�˼·������ϸ�����˵�д����

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