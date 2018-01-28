// HuffTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct HuffTreeNode {
	unsigned int weight;//权重
	 int lchild, rchild, parent;
}HuffTreeNode, *HuffTreeNodeP;
 
void select( HuffTreeNodeP huffTree, int n, int * im_1, int *im_2)
//huffTree是huffNode的数组，包含所有的huffNode节点 n是数组的长度  im_1是最小权重下标，im_2 是第二小权重下标
{
	int min_1 = INT_MAX;
	int min_2 = INT_MAX;
	*im_2 = *im_1 = 0;//初始化下标
	for (int i = 0; i < n; i++)
	{
		if (huffTree[i].parent == -1)//数组下标取值的过程就是取地址中值的过程
			//在没有父节点的节点中选取，所有初始权重值组成的节点一开始都视为没有父节点的独立节点
		{
			if (huffTree[i].weight < min_1)
			{
				//比最少值小
				min_2 = min_1;//将最小值付给第二小的值
				*im_2 = *im_1;//下标也要变化

				min_1 = huffTree[i].weight;
				*im_1 = i;//记住最小值下标

		    }
			else if ((huffTree[i].weight >= min_1) && (huffTree[i].weight <= min_2))
				//在第一小和第二小的之间
			{
				min_2 = huffTree[i].weight;
				*im_2 = i;
			}
			else
			{
				//什么都不做
			}
		}
	}
}
//指针的指针 ->指针变量->普通变量
// 指针变量的地址->指针变量的值（普通变量的地址）->普通变量的值
//若要想在子函数中修改 实际内存单元中 存储的 指针变量的值，需要通过指针变量的地址来寻找到其指向的内存单元中存储的指针变量的值
void HuffmanCode(HuffTreeNodeP * huffTree, int w[], int n,char * * *HuffCode)
//w[] 为权重数组 n为权重数组的长度 也是HuffTree的叶节点个数
//则HuffTree非叶节点的个数为n-1 总节点的个数为2n-1
{
	int length = 2 * n - 1;
	int im_1 = 0;
	int im_2 = 0;
	(*huffTree) = (HuffTreeNodeP)malloc(sizeof(HuffTreeNode)*length);
	for (int i = 0; i < n; i++)//初始化 权重叶节点
	{
		(*huffTree)[i].lchild = -1;
		(*huffTree)[i].rchild = -1;
		(*huffTree)[i].parent = -1;
		(*huffTree)[i].weight = w[i];
	}
	for (int i = n; i < length; i++)//初始化parent节点
	{
		(*huffTree)[i].lchild = -1;
		(*huffTree)[i].rchild = -1;
		(*huffTree)[i].parent = -1;
		(*huffTree)[i].weight = 0;
	}

	//构建HuffmanTree
	for (int i = n; i < length; i++)
	{
		select(*huffTree, i, &im_1, &im_2);
		//原始数组中有n个节点，从第n+1个节点开始填充，也就是下标0开始填充
		//当前节点数组的个数为i个，且当前需要填充的数组下标为i
		//每次数组中增加一个节点
		(*huffTree)[i].lchild = im_1;//记录孩子节点下标
		(*huffTree)[i].rchild = im_2;
		(*huffTree)[im_1].parent = i;
		(*huffTree)[im_2].parent = i;
		(*huffTree)[i].weight = (*huffTree)[im_1].weight + (*huffTree)[im_2].weight;

	}

	char * code = (char *)malloc(sizeof(char)*(n+1));
	for (int i = 0; i < n+1; i++)
	{
		code[i] = '\0';
	}
	(*HuffCode) = (char* *)malloc(sizeof(char*)*n);
	//对指针的指针开辟内存，实际上是开辟了一个指针的数组，里面存储着的是指针变量的值（原始变量的首地址）
	//记住一个原则，所有传入的变量 都存在这个子函数栈上的内存 和实际内存没有关系
	//所以在子函数中修改任何传入的参数都只是修改子函数栈上的数据，
	//所以若想修改实际内存中的值，需要传入实际内存的地址来 进行地址寻值操作才可以修改真正内存的值
	//可以说子函数类似一个沙盒
	int j ;
	int cur_i=0;
	int par_i=0;
	for (int i = 0; i < n+1; i++)
	{
		cur_i = i;
		j = 0 ;
		par_i = (*huffTree)[cur_i].parent;
		while (par_i != -1)
		{
			if ((*huffTree)[par_i].lchild == cur_i)
			{
				code[j] = '0';
				j++;
			}
			else if ((*huffTree)[par_i].rchild == cur_i)
			{
				code[j] = '1';
				j++;
			}
			else
			{
				//什么都不做
			}
			//向根节点追溯
			cur_i = par_i;
			par_i = (*huffTree)[cur_i].parent;

		}
		(*HuffCode)[i] = (char*)malloc(sizeof(char)*(n+1));
		strcpy_s((*HuffCode)[i],n+1,code);
}

}
int main()
{
	int i;
	char key[5] = { 'A','B','C','D','E' };
	int w[5] = { 1,2,4,5,6 }; 
	HuffTreeNodeP huffTree=NULL;
	char ** huffCode=NULL;
	HuffmanCode(&huffTree,w,5, &huffCode);
	for (i = 0; i < 5; i++)
		printf("%c:%s\n", key[i], huffCode[i]);

	printf("\n");
	system("pause");
	return 0;
}

