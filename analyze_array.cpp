// analyze_array.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf(" array[0] %d", array[0]);//�������������Ƭ�����ڴ�ͱ�printf������д�ˣ���Ƭ�ڴ�ͳ��ײ�����������

	printf("array[1] %d ", array[1]);//��������ľ���һ���������˵���
	system("pause");
    return 0;
}

