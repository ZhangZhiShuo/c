// HeapSort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include <stdlib.h>

void HeapAjust(int array[], int i,int len)//����
{
	//֪ʶ����  ����Ϊlength�Ķ����� ���һ����Ҷ�ڵ���±꣨���㿪ʼ) Ϊ length/2-1
	//�±�Ϊi�Ľڵ�� ���ӵ��±�Ϊ2*i+1 �Һ��ӵ��±�Ϊ2*i+2
	int max_child_i=0;//�ϴ��ӵ��±�
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
//��һ�ε����Ӻ���ǰ�����������һ����Ҷ�ڵ�len/2 -1 ��0�� �����ѵĹ��� ÿһ�ν�һ����Ҷ�ڵ��������ȷ��λ��
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		HeapAjust(array, i, len);//
	}

	//��ʼ������̣����������ֻ���������λ�õĽڵ㣬�����ڵ���Ϊ�Ѿ���һ�����ˣ����������ڵ�϶�����ѵ�����
	//��0��ʼ�������ܹ���Ϊ��len�����ݣ�����Ҫ���� len-1��
	for (int i = 1; i <= len - 1; i++)//ע�⣺���һ����ʣ�����ڵ�ʱ�������ɴ󶥶ѣ�����Ҫ����Ԫ�ص��� ʵ�ִ�С��������
	{
		array[0] = array[0] ^ array[len-i];
		array[len-i] = array[0] ^ array[len-i];
		array[0] = array[0] ^ array[len-i];
		HeapAjust(array, 0, len - i);//���»������Ľڵ����
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

