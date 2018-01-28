// CMD5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>



//知识储备
/*
如一个long型数据0x12345678
大端字节序：（用于网络数据传输）
内存低地址--> 0x12
             0x34
　　　　　　   0x56
内存高地址--> 0x78

小端字节序：（Win Linux 内存）
内存低地址--> 0x78
		 　　0x56
			0x34
内存高地址--> 0x12
*/
//生成MD5


/*
1.填充
在MD5算法中，首先需要对信息进行填充，使其位长对512求余的结果等于448，并且填充必须进行，即使其位长对512求余的结果等于448。
因此，信息的位长（Bits Length）将被扩展至N*512+448，N为一个非负整数，N可以是零。
注：如果 其位长对512求余的结果 多余448 那么就要填充到下一个448处
填充的方法如下：
1) 在信息的后面填充一个1和无数个0，直到满足上面的条件时才停止用0对信息的填充。
2) 在这个结果后面附加一个以64位二进制表示的填充前信息长度（单位为Bit），如果二
进制表示的填充前信息长度超过64位，则取低64位。
经过这两步的处理，信息的位长=N*512+448+64=(N+1）*512，即长度恰好是512的整数倍。这样做的原因是为满足后面处理中对信息长度的要求。
*/

//计算字符串有多少字节
unsigned int str_len(char * raw_str)
{
	unsigned int length=0;
	char * p = raw_str;
	while (*p++ != '\0')
	{
		length++;
	}
	//printf("The raw string length is: %d", length);
	return length;
	
}
unsigned int * addBits(char * raw_str,unsigned int * int_array_len)
{
	/*
	计算填充后的组数（64byte）为一组
	填充公式：
	当 长度/64byte（512bit） 如果 余数大于448bit那么需要填充到下一个余数448bit处，那么填充组就需要单独占一组 组数会相应的+1
	+8 当 length/64余数大于56时 ，+8有进位，会增加一组
	当 长度/64byte（512bit） 如果 余数小于448bit，那么填充数和 余数组 就会占同一组
	+8当 length/64余数小于56时 ，+8不影响，没有进位，还是会舍弃
	+1 为加的是余数组
	*/
	unsigned int raw_str_len = str_len(raw_str);
	//printf("%d", (raw_str_len >> 32) & 0xffffffff); 32bit 移位32 位又转回来了
	unsigned int group_count = (raw_str_len + 8) / 64 + 1;
	/*
	将每个64byte大组分成16个小组 每个小组4byte 是一个unsigned int类型的元素 也就是说每个大组中有16个unsigned int 类型变量
	*/
	unsigned int int_length = group_count * 64 / 4;
	*int_array_len = int_length;
	unsigned int  *byte2int = (unsigned int *)malloc((int_length)*sizeof(unsigned int ));
	//将这片内存赋初值
	for (int i = 0; i < int_length; i++)
	{
		byte2int[i] = 0;
	}
	/*for (int i = 0; i < int_length; i++)
	{
		printf("%d", byte2int[i]);

	}*/

	for (int i = 0; i < raw_str_len; i++)
	{

		/*
		i>>2 == i* 1/4(pow(2,-2))  类比于10进制的左移右移 添0 去0的过程
		这个步骤实际做的事情是  类型的“紧凑转换” 数据的移动 
		等号左边决定填充在哪个 四个字节的大区域，等号右边决定填充在这四个字节哪个位置上，分别是 第8（不移位）位 16，24，32
		*/
		byte2int[i >> 2] |= raw_str[i] << ((i % 4) * 8);
		
    }

	/*
	接下来要做的是进行填充了 先填一个1 之后填0
	左边确定大块 右边确定第一个字节具体的填充位置
	*/
	byte2int[raw_str_len>>2] |= 0x80 << ((raw_str_len % 4) * 8);//0x80 -->   1000 0000 保证第一个填充字节的第一位为1
	/*
	后边已经初始化为零不需要填充，仅仅将最后64位填充为raw_str的长度,占多少bit
	*/
	byte2int[int_length - 2] = (raw_str_len*8) & 0xffffffff;//0~31

	return byte2int;
}
/*
2.计算
每一分组的算法流程如下：
第一分组需要将上面四个链接变量复制到另外四个变量中：
a=A(temp[0])，b=B(temp[1])，c=C(temp[2])，d=D(temp[3])。
从第二分组开始的变量为上一分组的运算结果，
即A(temp[0]) = a， B (temp[1])= b， C(temp[2]) = c， D (temp[3])= d。
主循环有四轮（MD4只有三轮），每轮循环都很相似。
1）第一轮进行16次操作。每次操作对a、b、c和d中的其中三个作一次非线性函数运算，
2）然后将所得结果加上    第四个变量，文本的一个子分组   和  一个常数。
3）再将所得结果向左环移一个不定的数，
4）并加上a、b、c或d中之一。
5）最后用该结果取代a、b、c或d中之一。
以下是每次操作中用到的四个非线性函数（每轮一个）。
F( X ,Y ,Z ) = ( X & Y ) | ( (~X) & Z )
G( X ,Y ,Z ) = ( X & Z ) | ( Y & (~Z) )
H( X ,Y ,Z ) =X ^ Y ^ Z
I( X ,Y ,Z ) =Y ^ ( X | (~Z) )

*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))//右移的时候，高位一定要补零，而不是补充符号位 这个是循环左移公式 针对 32位的类型
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
/*
初始的128位值为初试链接变量，这些参数用于第一轮的运算，以大端字节序来表示，他们分别为： A=0x01234567，B=0x89ABCDEF，C=0xFEDCBA98，D=0x76543210。
（每一个变量给出的数值是高字节存于内存低地址，低字节存于内存高地址，即大端字节序。在程序中变量A、B、C、D的值分别为0x67452301，0xEFCDAB89，0x98BADCFE，0x10325476）
*/
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
unsigned int temp[4] = {A,B,C,D};
/*
现定义：
假设Mj表示消息的第j个子分组（从0到15）  64byte 是一个大组 4byte一个子分组 正好和就是一个unsigned int 类型，16个子分组（Mj）
常数ti是4294967296*abs( sin(i) ）的整数部分，
i 取值从1到64，单位是弧度。（4294967296=pow(2,32)）
FF(a ,b ,c ,d ,Mj ,s ,ti ) 操作为 a = b + ( (a + F(b,c,d) + Mj + ti) << s)
GG(a ,b ,c ,d ,Mj ,s ,ti ) 操作为 a = b + ( (a + G(b,c,d) + Mj + ti) << s)
HH(a ,b ,c ,d ,Mj ,s ,ti) 操作为 a = b + ( (a + H(b,c,d) + Mj + ti) << s)
II(a ,b ,c ,d ,Mj ,s ,ti) 操作为 a = b + ( (a + I(b,c,d) + Mj + ti) << s)
注意：“<<”表示循环左移位，不是左移位。
*/
#define FF(a,b,c,d,Mj,s,ti) {a += F(b, c, d) + Mj + ti; a = ROTATE_LEFT(a, s);a += b;}
#define GG(a,b,c,d,Mj,s,ti){ a += G(b, c, d) + Mj + ti;  a = ROTATE_LEFT(a, s);  a += b; } 
#define HH(a,b,c,d,Mj,s,ti) { a += H(b, c, d) + Mj + ti; a = ROTATE_LEFT(a, s); a += b;}
#define II(a,b,c,d,Mj,s,ti) { a += I(b, c, d) + Mj + ti; a = ROTATE_LEFT(a, s); a += b;}
/*

这四轮（共64步）是：
第一轮
FF(a ,b ,c ,d ,M0 ,7 ,0xd76aa478 )
FF(d ,a ,b ,c ,M1 ,12 ,0xe8c7b756 )
FF(c ,d ,a ,b ,M2 ,17 ,0x242070db )
FF(b ,c ,d ,a ,M3 ,22 ,0xc1bdceee )
FF(a ,b ,c ,d ,M4 ,7 ,0xf57c0faf )
FF(d ,a ,b ,c ,M5 ,12 ,0x4787c62a )
FF(c ,d ,a ,b ,M6 ,17 ,0xa8304613 )
FF(b ,c ,d ,a ,M7 ,22 ,0xfd469501)
FF(a ,b ,c ,d ,M8 ,7 ,0x698098d8 )
FF(d ,a ,b ,c ,M9 ,12 ,0x8b44f7af )
FF(c ,d ,a ,b ,M10 ,17 ,0xffff5bb1 )
FF(b ,c ,d ,a ,M11 ,22 ,0x895cd7be )
FF(a ,b ,c ,d ,M12 ,7 ,0x6b901122 )
FF(d ,a ,b ,c ,M13 ,12 ,0xfd987193 )
FF(c ,d ,a ,b ,M14 ,17 ,0xa679438e )
FF(b ,c ,d ,a ,M15 ,22 ,0x49b40821 )
第二轮
GG(a ,b ,c ,d ,M1 ,5 ,0xf61e2562 )
GG(d ,a ,b ,c ,M6 ,9 ,0xc040b340 )
GG(c ,d ,a ,b ,M11 ,14 ,0x265e5a51 )
GG(b ,c ,d ,a ,M0 ,20 ,0xe9b6c7aa )
GG(a ,b ,c ,d ,M5 ,5 ,0xd62f105d )
GG(d ,a ,b ,c ,M10 ,9 ,0x02441453 )
GG(c ,d ,a ,b ,M15 ,14 ,0xd8a1e681 )
GG(b ,c ,d ,a ,M4 ,20 ,0xe7d3fbc8 )
GG(a ,b ,c ,d ,M9 ,5 ,0x21e1cde6 )
GG(d ,a ,b ,c ,M14 ,9 ,0xc33707d6 )
GG(c ,d ,a ,b ,M3 ,14 ,0xf4d50d87 )
GG(b ,c ,d ,a ,M8 ,20 ,0x455a14ed )
GG(a ,b ,c ,d ,M13 ,5 ,0xa9e3e905 )
GG(d ,a ,b ,c ,M2 ,9 ,0xfcefa3f8 )
GG(c ,d ,a ,b ,M7 ,14 ,0x676f02d9 )
GG(b ,c ,d ,a ,M12 ,20 ,0x8d2a4c8a )
第三轮
HH(a ,b ,c ,d ,M5 ,4 ,0xfffa3942 )
HH(d ,a ,b ,c ,M8 ,11 ,0x8771f681 )
HH(c ,d ,a ,b ,M11 ,16 ,0x6d9d6122 )
HH(b ,c ,d ,a ,M14 ,23 ,0xfde5380c )
HH(a ,b ,c ,d ,M1 ,4 ,0xa4beea44 )
HH(d ,a ,b ,c ,M4 ,11 ,0x4bdecfa9 )
HH(c ,d ,a ,b ,M7 ,16 ,0xf6bb4b60 )
HH(b ,c ,d ,a ,M10 ,23 ,0xbebfbc70 )
HH(a ,b ,c ,d ,M13 ,4 ,0x289b7ec6 )
HH(d ,a ,b ,c ,M0 ,11 ,0xeaa127fa )
HH(c ,d ,a ,b ,M3 ,16 ,0xd4ef3085 )
HH(b ,c ,d ,a ,M6 ,23 ,0x04881d05 )
HH(a ,b ,c ,d ,M9 ,4 ,0xd9d4d039 )
HH(d ,a ,b ,c ,M12 ,11 ,0xe6db99e5 )
HH(c ,d ,a ,b ,M15 ,16 ,0x1fa27cf8 )
HH(b ,c ,d ,a ,M2 ,23 ,0xc4ac5665 )
第四轮
II(a ,b ,c ,d ,M0 ,6 ,0xf4292244 )
II(d ,a ,b ,c ,M7 ,10 ,0x432aff97 )
II(c ,d ,a ,b ,M14 ,15 ,0xab9423a7 )
II(b ,c ,d ,a ,M5 ,21 ,0xfc93a039 )
II(a ,b ,c ,d ,M12 ,6 ,0x655b59c3 )
II(d ,a ,b ,c ,M3 ,10 ,0x8f0ccc92 )
II(c ,d ,a ,b ,M10 ,15 ,0xffeff47d )
II(b ,c ,d ,a ,M1 ,21 ,0x85845dd1 )
II(a ,b ,c ,d ,M8 ,6 ,0x6fa87e4f )
II(d ,a ,b ,c ,M15 ,10 ,0xfe2ce6e0 )
II(c ,d ,a ,b ,M6 ,15 ,0xa3014314 )
II(b ,c ,d ,a ,M13 ,21 ,0x4e0811a1 )
II(a ,b ,c ,d ,M4 ,6 ,0xf7537e82 )
II(d ,a ,b ,c ,M11 ,10 ,0xbd3af235 )
II(c ,d ,a ,b ,M2 ,15 ,0x2ad7d2bb )
II(b ,c ,d ,a ,M9 ,21 ,0xeb86d391 )
所有这些完成之后，将a、b、c、d分别在原来基础上再加上A、B、C、D。
即a = a + A，b = b + B，c = c + C，d = d + D
然后用下一分组数据继续运行以上算法。
*/
void mainCalculate(unsigned int * x)
{
	unsigned int a = temp[0];
	unsigned int b = temp[1];
	unsigned int c = temp[2];
	unsigned int d = temp[3];
	FF(a, b, c, d, x[0], 7, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[1], 12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[2], 17, 0x242070db); /* 3 */
	FF(b, c, d, a, x[3], 22, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[4], 7, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[5], 12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[6], 17, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[7], 22, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[8], 7, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[9], 12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

										   /* Round 2 */
	GG(a, b, c, d, x[1], 5, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[6], 9, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[5], 5, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], 9, 0x2441453); /* 22 */
	GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[4], 20, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[9], 5, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[3], 14, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[8], 20, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[2], 9, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[7], 14, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

										   /* Round 3 */
	HH(a, b, c, d, x[5], 4, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[8], 11, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[1], 4, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[4], 11, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[7], 16, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[0], 11, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[3], 16, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[6], 23, 0x4881d05); /* 44 */
	HH(a, b, c, d, x[9], 4, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[2], 23, 0xc4ac5665); /* 48 */

										  /* Round 4 */
	II(a, b, c, d, x[0], 6, 0xf4292244); /* 49 */
	II(d, a, b, c, x[7], 10, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[5], 21, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[3], 10, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[1], 21, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[8], 6, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[6], 15, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[4], 6, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[2], 15, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[9], 21, 0xeb86d391); /* 64 */

	a += temp[0];
	b += temp[1];
	c += temp[2];
	d += temp[3];
	temp[0] = a;
	temp[1] = b;
	temp[2] = c;
	temp[3] = d;

}
void  FinalExe(char * md5_str)
{
	int i = 0;
	char temp_char='\0';
	char * key = "0123456789abcdef";
	//char md5_str[33] = { '\0' };
	while (i < 4)
	{   
		temp_char = key[((temp[i]) & 0xf0)>>4];
		md5_str[8*i+0] = temp_char;
		temp_char = key[(temp[i]) & 0x0f];
		md5_str[8 * i+1] = temp_char;

		temp_char = key[((temp[i] >> 8) & 0xf0)>>4];
		md5_str[8 * i + 2] = temp_char;
		temp_char = key[(temp[i] >> 8) & 0x0f];
		md5_str[8 * i + 3] = temp_char;

		temp_char = key[((temp[i] >> 16) & 0xf0)>>4];
		md5_str[8 * i + 4] = temp_char;
		temp_char = key[(temp[i] >> 16) & 0x0f];
		md5_str[8 * i + 5] = temp_char;

		temp_char = key[((temp[i] >>24)& 0xf0)>>4];
		md5_str[8 * i + 6] = temp_char;
		temp_char = key[(temp[i]>>24) & 0x0f];
		md5_str[8 * i + 7] = temp_char;
		
		i += 1;

}
	printf("%s" ,md5_str);
}
void  getMD5(char * raw_str,char * md5_str)
{
	unsigned int int_array_len = 0;

	unsigned int * unsigned_int_array = addBits(raw_str, &int_array_len);
	unsigned int num[16] = { 0 };
	int i = 0;
	while (i < int_array_len)//N*64 N*16 *4
	{
		for (int j = 0; j < 16; j++)
		{
			num[j] = unsigned_int_array[i + j];
		}
		mainCalculate(num);
		i += 16;
	}
	 FinalExe(md5_str);
	 
}



int main()
{
	//str_len("asdsb\0");
	int i = 0;
	char md5_str[33] = { '\0' };
	 getMD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\0",md5_str);
	
	printf("\n%s", md5_str);
	system("pause");
    return 0;
}

/*
另一种版本的部分写的比较好的地方
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len);
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len);
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len)
{
unsigned int i = 0,j = 0;
while(j < len)
{
output[j] = input[i] & 0xFF;
output[j+1] = (input[i] >> 8) & 0xFF;
output[j+2] = (input[i] >> 16) & 0xFF;
output[j+3] = (input[i] >> 24) & 0xFF;
i++;
j+=4;
}
}
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len)
{
unsigned int i = 0,j = 0;
while(j < len)
{
output[i] = (input[j]) |
(input[j+1] << 8) |
(input[j+2] << 16) |
(input[j+3] << 24);
i++;
j+=4;
}
}

*/
