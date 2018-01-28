// analyze_array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
int * array_fun()
{
	printf("I'm here");
	int arr[] = { 1,2,3,4,5 };
	arr[0] = 4;
	arr[2] = 8;
	return arr;
 }

int main()
{
	printf("This is main");
	int * array = array_fun();
	printf(" array[0] %d", array[0]);//调用完这个，这片数组内存就被printf函数重写了，这片内存就彻底不属于我们了

	printf("array[1] %d ", array[1]);//这里输出的就是一个被覆盖了的数
	system("pause");
    return 0;
}

