// GreatestCommonDivisor.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//���Լ�� ��С������
/*
 �� m=n*k+r;��m>n)
 ���� r=m-n*k;
 ���r����0 ��m ,m,n�����Լ��Ϊn
 ���r������0 �� m ��n ��r ������ͬ�����Լ��
 ��ΪrΪ���� ���� r<n
 ������ n=r*(k2)+(r2) (n r �����Լ�� ���� m n�����Լ����
 һֱ������ȥ ֱ�� ��rN��Ϊ��
 */
int main()
{
	 //system("chcp 65001");
	 printf("���\n");
	 int a, b, r;
	 int m, n;
	 scanf_s("%d %d", &a, &b);
	 if (a > b)
	 {
		 a = a^b;
		 b = a^b;
		 a = a^b;
	 }
	 m = a;
	 n = b;
	 r = m%n;
	 while (r)
	 {
		 m = n;
		 n = r;
		 r = m%n;

	 }
	 printf("The two numbers�� %d		%d\n",a,b);
	 printf("���Լ����%d	\n��С������:%d",n,n*(a/n)*(b/n));
	 system("pause");
    return 0;
}

