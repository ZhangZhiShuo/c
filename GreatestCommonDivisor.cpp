// GreatestCommonDivisor.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//最大公约数 最小公倍数
/*
 设 m=n*k+r;（m>n)
 所以 r=m-n*k;
 如果r等于0 则m ,m,n的最大公约数为n
 如果r不等于0 则 m ，n ，r 具有相同的最大公约数
 因为r为余数 所以 r<n
 可以有 n=r*(k2)+(r2) (n r 的最大公约数 就是 m n的最大公约数）
 一直进行下去 直到 （rN）为零
 */
int main()
{
	 //system("chcp 65001");
	 printf("你好\n");
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
	 printf("The two numbers： %d		%d\n",a,b);
	 printf("最大公约数：%d	\n最小公倍数:%d",n,n*(a/n)*(b/n));
	 system("pause");
    return 0;
}

