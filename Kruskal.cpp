// Kruskal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#define VEX 7
#define EDGE 11
typedef struct
{
	int arc[VEX][VEX];
	//二维数组里面存储的是边的权重，下标为节点的序号
	//例如  arc[0][3]=7 节点0--> 节点3  边的权重为7
	int numVertexes, numEdges;//顶点数，边数
}MGraph ,*MGraphP;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge,*EdgeP;//对边集数组Edge结构的定义


//qsort 比较条件
int cmp(void const *a, void const * b)
{
	return (*(EdgeP)a).weight - (*(EdgeP)b).weight;
}

//创建图的邻接矩阵
void CreateMGraph(MGraphP G)
{
	
		int i, j;

		G->numEdges = EDGE;//单边数量
		G->numVertexes = VEX;//节点数量 下标0~6


		//初始化图的边的权重数组
		for (i = 0; i < G->numVertexes; i++) {
			for (j = 0; j < G->numVertexes; j++) {
				if (i == j)
					G->arc[i][j] = 0;
				else
					G->arc[i][j] = G->arc[j][i] = INT_MAX;
			}
		}
		//向边的权重数组中附上真正的值
		G->arc[0][1] = 7;
		G->arc[0][3] = 5;
		G->arc[1][2] = 8;
		G->arc[1][3] = 9;
		G->arc[1][4] = 7;
		G->arc[2][4] = 5;
		G->arc[3][4] = 15;
		G->arc[3][5] = 6;
		G->arc[4][5] = 8;
		G->arc[4][6] = 9;
		G->arc[5][6] = 11;


		//<3,2> 和<2，3>公用一条边，双向图
		// 对角线两边 对等化
		for (i = 0; i < G->numVertexes; i++)
			//第一趟0字辈全部遍历完…… ，所以就j就可以从i开始 ，而不用从0开始
		{
			for (j = i; j < G->numVertexes; j++) {
				G->arc[j][i] = G->arc[i][j];
			}
		}

}

int Find(int * parent, int i)
//传入的是一个记录父亲节点坐标的数组，i是需要索引 最根上 父节点的下标，
//返回最根上父节点的坐标
{
	while (parent[i] >= 0)
	{
		i = parent[i];
	}
	return i;

}
void MiniSpanTree_Kruskal(MGraph G)
{
	int parent[VEX];
	Edge edges[EDGE];
	//初始化边数组
	int k = 0;
	int begin, end;
	int begin_par, end_par;
	for (int i = 0; i < G.numVertexes-1; i++)
	{
		for (int j = i + 1; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] < INT_MAX)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	//初始化parent数组
	for (int i = 0; i < G.numVertexes; i++)
	{
		parent[i] = -1;
	}

	qsort(edges, G.numEdges, sizeof(Edge),cmp);//对edges数组进行从小到大排序
	//记录父节点信息，生成最小生成树
	for (int i = 0; i < k ; i++)
	{
		begin = edges[i].begin;
		end = edges[i].end;
		begin_par = Find(parent, begin);
		end_par = Find(parent, end);
		if (begin_par != end_par)//如果不成环，将最小的权重添加进生成树中
		{

			parent[end_par] = begin_par;
			//如果最根父节点不一样，将最根父节点连在一起 成树 
			//将独立的节点结构 纳入树的结构中
		/*
		o   o               o——o
		|   |   ------>      |  |
		o   o               o  o
		*/

			printf("(%d, %d) %d\n", begin, end, edges[i].weight);
		}
		
	}
}

void Prim(MGraph G)
{
	int lowcost[VEX];//下标为节点 标志 值为 目前所探测到的最短路径
	//INT_MAX 表示还没探测到 0 表示已经纳入生成树的节点了
	for (int i = 0; i < VEX; i++)
	{
		lowcost[i] = INT_MAX;
	}

	int parent[VEX];
	//-1表示已经纳入生成树的节点了 INT_MAX 表示还没探测到
	//下标为节点标志 值为最短路径的源节点,
	for (int i = 0; i < VEX; i++)
	{
		parent[i] =INT_MAX ;
	}
	int current_id = 0;
	int min;
	for (int i = 0; i < VEX - 1; i++)
	{
		
		for (int j = 0; j < VEX; j++)
		{
			if (j != current_id)//找到更小的路径，就替换
			{
				if (G.arc[current_id][j] < lowcost[j]&&lowcost[j]>0)
				{
					lowcost[j] = G.arc[current_id][j];
					parent[j] = current_id;//到j节点最小的路径是从current_id 节点发出的
				}
				}
			else
			{
				lowcost[j] = 0;
				
			}
		}
		min = INT_MAX;
		for (int j = 0; j < VEX; j++)
		{
			if (lowcost[j] > 0 && lowcost[j] < INT_MAX)
			{
				if (lowcost[j] < min)
				{
					min = lowcost[j];
					current_id = j;
				}
			}
		}
		printf("<%d,%d> weight:%d\n", parent[current_id], current_id, G.arc[parent[current_id]][current_id]);
		
	}
}

int main()
{
	MGraphP gp = (MGraphP)malloc(sizeof(MGraph));
	CreateMGraph(gp);
	MiniSpanTree_Kruskal(*gp);
	Prim(*gp);
	system("pause");
    return 0;
}

