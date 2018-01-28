// HeapSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include <stdlib.h>

void HeapAjust(int array[], int i,int len)//调整
{
	//知识储备  长度为length的二叉树 最后一个非叶节点的下标（从零开始) 为 length/2-1
	//下标为i的节点的 左孩子的下标为2*i+1 右孩子的下标为2*i+2
	int max_child_i=0;//较大孩子的下标
	for (; 2 * i + 1 < len; i = max_child_i)
	{
		max_child_i = 2 * i + 1;
		if (2 * i + 2 < len)
		{
			if (array[2 * i + 1] > array[2 * i + 2])
			{
				max_child_i = 2 * i + 1;
			}
			else
			{
				max_child_i = 2 * i + 2;
			}
			if (array[i] < array[max_child_i])
			{
				array[i] = array[i] ^ array[max_child_i];
				array[max_child_i]= array[i] ^ array[max_child_i];
				array[i] = array[i] ^ array[max_child_i];
			}
			else
			{
				break;
			}
		}
		else if (2 * i + 2 == len)
		{
			if (array[i] < array[max_child_i])
			{
				array[i] = array[i] ^ array[max_child_i];
				array[max_child_i] = array[i] ^ array[max_child_i];
				array[i] = array[i] ^ array[max_child_i];
			}
			else
			{
				break;
			}
		}
	}
}

void HeapSort(int array[], int len)
{
//第一次调整从后往前调整（从最后一个非叶节点len/2 -1 到0） 构建堆的过程 每一次将一个非叶节点调整到正确的位置
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		HeapAjust(array, i, len);//
	}

	//开始排序过程，这个过程中只需调整换过位置的节点，其他节点因为已经是一个堆了，所以其他节点肯定满足堆的性质
	//从0开始调整，总共因为有len个数据，所以要调整 len-1次
	for (int i = 1; i <= len - 1; i++)//注意：最后一步就剩两个节点时，调整成大顶堆，还需要进行元素调换 实现从小到大排列
	{
		array[0] = array[0] ^ array[len-i];
		array[len-i] = array[0] ^ array[len-i];
		array[0] = array[0] ^ array[len-i];
		HeapAjust(array, 0, len - i);//将新换上来的节点调整
	}
}
int main()
{
	int array[10] = { 1,4,6,7,10,3,4,2,4,20 };
	HeapSort(array, 10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d	", array[i]);
	}
	system("pause");
    return 0;
}

