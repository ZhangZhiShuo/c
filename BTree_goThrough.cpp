// BTree_goThrough.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*
֪ʶ������
1.�ڴ���䷽ʽ
�ڴ���䷽ʽ�����֣�
[1]�Ӿ�̬�洢������䡣�ڴ��ڳ�������ʱ����Ѿ�����ã�����ڴ��ڳ�������������ڼ䶼���ڡ�����ȫ�ֱ�����static������
[2]��ջ�ϴ�������ִ�к���ʱ�������ھֲ������Ĵ洢��Ԫ��������ջ�ϴ���������ִ�н���ʱ��Щ�洢��Ԫ�Զ����ͷš�ջ�ڴ�������������ڴ�������ָ��У�Ч�ʺܸߣ����Ƿ�����ڴ��������ޡ�
[3]�Ӷ��Ϸ��䣬��ƶ�̬�ڴ���䡣���������е�ʱ����malloc��new����������ٵ��ڴ棬����Ա�Լ������ں�ʱ��free��delete�ͷ��ڴ档��̬�ڴ���������ɳ���Ա������ʹ�÷ǳ���������ڶ��Ϸ����˿ռ䣬�������λ��������������еĳ��������ڴ�й©��Ƶ���ط�����ͷŲ�ͬ��С�Ķѿռ佫�����������顣
2.������ڴ�ռ�
һ�����򽫲���ϵͳ����������е��ڴ���Ϊ4����������ͼ��ʾ��
������(code area)
�����ڴ�ռ�
ȫ��������(data area)
����(heap area)
ջ��(stack area)
һ����C/C++����ĳ���ռ�õ��ڴ��Ϊ���¼�������,
1��ջ����stack��   �ɱ������Զ������ͷ� �����Ϊ���к���������ľֲ������������������������ݡ����ص�ַ�ȡ��������ʽ���������ݽṹ�е�ջ��
2��������heap��    һ���ɳ���Ա�����ͷţ� ������Ա���ͷţ��������ʱ������OS���� �����䷽ʽ����������
3��ȫ��������̬������static�����ȫ�ֱ�������̬���ݡ������������������ϵͳ�ͷ�
4�����ֳ����� �����ַ������Ƿ�������ġ� �����������ϵͳ�ͷš�
5�������������ź����壨���Ա������ȫ�ֺ������Ķ����ƴ��롣
����������ӳ���
int a = 0; //ȫ�ֳ�ʼ����
char *p1; //ȫ��δ��ʼ����
int main() {
int b; //ջ
char s[] = /"abc/"; //ջ
char *p2; //ջ
char *p3 = /"123456/"; //123456//0�ڳ�������p3��ջ�ϡ�
static int c =0;//ȫ�֣���̬����ʼ����
p1 = new char[10];
p2 = new char[20];
//��������ú��ֽڵ�������ڶ�����
strcpy(p1, /"123456/"); //123456//0���ڳ����������������ܻὫ����p3��ָ���/"123456/"�Ż���һ���ط���
}
3������ջ�ıȽ�
3.1���뷽ʽ
stack: ��ϵͳ�Զ����䡣 ���磬�����ں�����һ���ֲ����� int b; ϵͳ�Զ���ջ��Ϊb���ٿռ䡣
heap: ��Ҫ����Ա�Լ����룬��ָ����С����C��malloc������C++����new�������
��p1 = (char *)malloc(10); p1 = new char[10];
��p2 = (char *)malloc(10); p2 = new char[20];
����ע��p1��p2��������ջ�еġ�
3.2�����ϵͳ����Ӧ
ջ��ֻҪջ��ʣ��ռ����������ռ䣬ϵͳ��Ϊ�����ṩ�ڴ棬���򽫱��쳣��ʾջ�����
�ѣ�����Ӧ��֪������ϵͳ��һ����¼�����ڴ��ַ��������ϵͳ�յ����������ʱ�������������Ѱ�ҵ�һ���ռ����������ռ�Ķѽ�㣬Ȼ�󽫸ý��ӿ��н��������ɾ���������ý��Ŀռ���������
���ڴ����ϵͳ����������ڴ�ռ��е��׵�ַ����¼���η���Ĵ�С�������������е�delete��������ȷ���ͷű��ڴ�ռ䡣
�����ҵ��Ķѽ��Ĵ�С��һ�����õ�������Ĵ�С��ϵͳ���Զ��Ľ�������ǲ������·�����������С�
3.3�����С������
ջ����Windows��,ջ����͵�ַ��չ�����ݽṹ����һ���������ڴ��������仰����˼��ջ���ĵ�ַ��ջ�����������ϵͳԤ�ȹ涨�õģ��� WINDOWS�£�ջ�Ĵ�С��2M��Ҳ�е�˵��1M����֮��һ������ʱ��ȷ���ĳ��������������Ŀռ䳬��ջ��ʣ��ռ�ʱ������ʾoverflow���� �ˣ��ܴ�ջ��õĿռ��С��
�ѣ�������ߵ�ַ��չ�����ݽṹ���ǲ��������ڴ�������������ϵͳ�����������洢�Ŀ����ڴ��ַ�ģ���Ȼ�ǲ������ģ�������ı����������ɵ͵�ַ��ߵ�ַ���ѵĴ�С�����ڼ����ϵͳ����Ч�������ڴ档�ɴ˿ɼ����ѻ�õĿռ�Ƚ���Ҳ�Ƚϴ�
3.4����Ч�ʵıȽ�
ջ��ϵͳ�Զ����䣬�ٶȽϿ졣������Ա���޷����Ƶġ�
������new������ڴ棬һ���ٶȱȽ������������ײ����ڴ���Ƭ,������������㡣
���⣬��WINDOWS�£���õķ�ʽ����VirtualAlloc�����ڴ棬�������ڶѣ�Ҳ����ջ������ֱ���ڽ��̵ĵ�ַ�ռ��б���һ���ڴ棬��Ȼ����������㡣�����ٶȿ죬Ҳ����
3.5�Ѻ�ջ�еĴ洢����
ջ���ں�������ʱ����һ����ջ�����������к����һ��ָ���������������һ����ִ����䣩�ĵ�ַ��Ȼ���Ǻ����ĸ����������ڴ������C�������У�����������������ջ�ģ�Ȼ���Ǻ����еľֲ�������ע�⾲̬�����ǲ���ջ�ġ�
�����κ������ý����󣬾ֲ������ȳ�ջ��Ȼ���ǲ��������ջ��ָ��ָ���ʼ��ĵ�ַ��Ҳ�����������е���һ��ָ������ɸõ�������С�
�ѣ�һ�����ڶѵ�ͷ����һ���ֽڴ�ŶѵĴ�С�����еľ��������г���Ա���š�
3.6��ȡЧ�ʵıȽ�
char s1[] = /"a/";
char *s2 = /"b/";
a��������ʱ�̸�ֵ�ģ���b���ڱ���ʱ��ȷ���ģ����ǣ����Ժ�Ĵ�ȡ�У���ջ�ϵ������ָ����ָ����ַ���(�����)�졣 ���磺
int main(){
char a = 1;
char c[] = /"1234567890/";
char *p =/"1234567890/";
a = c[1];
a = p[1];
return 0;
}
��Ӧ�Ļ�����
10: a = c[1];
00401067 8A 4D F1 mov cl,byte ptr [ebp-0Fh]
0040106A 88 4D FC mov byte ptr [ebp-4],cl
11: a = p[1];
0040106D 8B 55 EC mov edx,dword ptr [ebp-14h]
00401070 8A 42 01 mov al,byte ptr [edx+1]
00401073 88 45 FC mov byte ptr [ebp-4],al
��һ���ڶ�ȡʱֱ�ӾͰ��ַ����е�Ԫ�ض����Ĵ���cl�У����ڶ�����Ҫ�Ȱ�ָ��ֵ����edx�У��ٸ���edx��ȡ�ַ�����Ȼ���ˡ�
3.7С��
�Ѻ�ջ����Ҫ���������¼��㣺
1������ʽ��ͬ��
2���ռ��С��ͬ��
3���ܷ������Ƭ��ͬ��
4����������ͬ��
5�����䷽ʽ��ͬ��
6������Ч�ʲ�ͬ��
����ʽ������ջ���������ɱ������Զ��������������ֹ����ƣ����ڶ���˵���ͷŹ����ɳ���Ա���ƣ����ײ���memory leak��
�ռ��С��һ��������32λϵͳ�£����ڴ���Դﵽ4G�Ŀռ䣬������Ƕ��������ڴ漸����û��ʲô���Ƶġ����Ƕ���ջ������һ�㶼����һ���Ŀռ��С�ģ����磬��VC6���棬Ĭ�ϵ�ջ�ռ��С��1M����Ȼ�����ֵ�����޸ġ�
��Ƭ���⣺���ڶ�������Ƶ����new/delete�Ʊػ�����ڴ�ռ�Ĳ��������Ӷ���ɴ�������Ƭ��ʹ����Ч�ʽ��͡�����ջ�������򲻻����������⣬��Ϊջ���Ƚ�����Ķ��У���������˵�һһ��Ӧ����������Զ����������һ���ڴ���ջ�м䵯������������֮ǰ����������ĺ����ջ�����Ѿ�����������ϸ�Ŀ��Բο����ݽṹ��
�������򣺶��ڶ��������������������ϵģ�Ҳ���������ڴ��ַ���ӵķ��򣻶���ջ�����������������������µģ��������ڴ��ַ��С�ķ���������
���䷽ʽ���Ѷ��Ƕ�̬����ģ�û�о�̬����Ķѡ�ջ��2�ַ��䷽ʽ����̬����Ͷ�̬���䡣��̬�����Ǳ�������ɵģ�����ֲ������ķ��䡣��̬������malloca�������з��䣬����ջ�Ķ�̬����Ͷ��ǲ�ͬ�ģ����Ķ�̬�������ɱ����������ͷţ����������ֹ�ʵ�֡�
����Ч�ʣ�ջ�ǻ���ϵͳ�ṩ�����ݽṹ����������ڵײ��ջ�ṩ֧�֣�����ר�ŵļĴ������ջ�ĵ�ַ��ѹջ��ջ����ר�ŵ�ָ��ִ�У���;�����ջ��Ч�ʱȽϸߡ�������C/C++�������ṩ�ģ����Ļ����Ǻܸ��ӵģ�����Ϊ�˷���һ���ڴ棬�⺯���ᰴ��һ�����㷨��������㷨���Բο����ݽṹ/����ϵͳ���ڶ��ڴ����������õ��㹻��С�Ŀռ䣬���û���㹻��С�Ŀռ䣨�����������ڴ���Ƭ̫�ࣩ�����п��ܵ���ϵͳ����ȥ���ӳ������ݶε��ڴ�ռ䣬�������л���� ���㹻��С���ڴ棬Ȼ����з��ء���Ȼ���ѵ�Ч�ʱ�ջҪ�͵öࡣ
���������ǿ��Կ������Ѻ�ջ��ȣ����ڴ���new/delete��ʹ�ã�������ɴ������ڴ���Ƭ������û��ר�ŵ�ϵͳ֧�֣�Ч�ʺܵͣ����ڿ��������û�̬�ͺ���̬���л����ڴ�����룬���۱�ø��Ӱ�������ջ�ڳ�������Ӧ����㷺�ģ������Ǻ����ĵ���Ҳ����ջȥ��ɣ��������ù����еĲ��������ص�ַ�� EBP�;ֲ�����������ջ�ķ�ʽ��š����ԣ������Ƽ���Ҿ�����ջ���������öѡ�
��Ȼջ������ڶ�ĺô����������ںͶ���Ȳ�����ô����ʱ�����������ڴ�ռ䣬�����öѺ�һЩ��
�����Ƕѻ���ջ����Ҫ��ֹԽ������ķ������������ǹ���ʹ��Խ�磩����ΪԽ��Ľ��Ҫô�ǳ��������Ҫô�Ǵݻٳ���Ķѡ�ջ�ṹ���������벻���Ľ����
4.new/delete��malloc/free�Ƚ�
��C++�Ƕ���˵��ʹ��new����ѿռ���Ե�����Ĺ��캯������malloc()����������һ���������ã���������ù��캯�����������ܵĲ�����һ��unsigned long���͡�ͬ����delete���ͷŶѿռ�֮ǰ�����������������free�����򲻻ᡣ
class Time{
public:
Time(int,int,int,string);
~Time(){
cout<</"call Time/'s destructor by:/"<<name<<endl;
}
private:
int hour;
int min;
int sec;
string name;
};
Time::Time(int h,int m,int s,string n){
hour=h;
min=m;
sec=s;
name=n;
cout<</"call Time/'s constructor by:/"<<name<<endl;
}
int main(){
Time *t1;
t1=(Time*)malloc(sizeof(Time));
free(t1);
Time *t2;
t2=new Time(0,0,0,/"t2/");
delete t2;
system(/"PAUSE/");
return EXIT_SUCCESS;
}
�����
call Time/'s constructor by:t2
call Time/'s destructor by:t2
�ӽ�����Կ�����ʹ��new/delete���Ե��ö���Ĺ��캯������������������ʾ���е��õ���һ����Ĭ�Ϲ��캯�������ڶ��Ϸ����������ʱ��ֻ�ܵ���Ĭ�Ϲ��캯�������ܵ��������κι��캯����
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define LCOUNTS 1000
typedef struct BTreeNode//Ҷ�ӽ��ṹ��
{
	int data;//����
	int number;//λ�ñ�� �������е�����
	BTreeNode * lchild;//��ڵ�
	BTreeNode * rchild;//�ҽڵ�
}BTreeNode, * BTreeNodeP;

typedef struct BTree//�������ṹ��
{
	BTreeNodeP bTreeNodes[LCOUNTS] ;
	int nCount;
}BTree,* BTreeP;

int * LRM(BTreeP bTreeP)//������ ������ �нڵ� 
{
	printf("\n");
	int * go_through_array = (int *)malloc(sizeof(int)*bTreeP->nCount);
	BTreeNodeP root = bTreeP->bTreeNodes[0];
	if (root == NULL)
	{
		printf("The BTree hasn't created!");

	}
	int * SS = (int *)malloc(sizeof(int)*bTreeP->nCount*2);
	//ʵ��Ϊһ����ά���� 0---bTreeP->nCount-1����ǽڵ���  bTreeP->nCount----- bTreeP->nCount*2-1
	for (int i = 0; i < bTreeP->nCount*2; i++)//��ʼ��SSջ
	{
		SS[i] = 0;
	}
	BTreeNodeP p = root;
    int top = 0;
	while (!(p == NULL&&top == 0))//pָ��NULL ��ջΪ�վ��˳� 
	{
		while (true)//���whileʱ��ջ�Ĺ���
		{
			if (p == NULL)
			{
				break;
			}
			if (SS[bTreeP->nCount+p->number] > 0)//����ڵ��Ƿ񱻱�����
			{
				break;
			}
			SS[top++] = p->number;
			SS[bTreeP->nCount + p->number]++;
			p = p->lchild;
		}
		
		if (top == 0)//��ջ���̽��� ����top==0��˵�� pָ��NULL ��ջΪ��
		{
			printf("LRM�������");
			break;
		}
		p = bTreeP->bTreeNodes[SS[--top]];
		if (SS[bTreeP->nCount + p->number] == 2)
			//����2˵������ڵ��Ǳ���������ʱ��ջ�ģ�������˽ڵ���������Ѿ������꣬�ô˽ڵ������
		{
			printf("%d	", p->data);
		}
		else
		{
			if (p->rchild == NULL)
			{
				printf("%d	", p->data);
				//go_through_array[]
			}
			else
			{
				SS[top++] = p->number;
				SS[bTreeP->nCount + p->number]++;
				p = p->rchild;
			}
		}

	}
	return 0;

}
int * MLR(BTreeP bTreeP)// �нڵ� ������ ������
{
	printf("\n");
	int * go_through_array = (int *)malloc(sizeof(int)*bTreeP->nCount);
	BTreeNodeP root = bTreeP->bTreeNodes[0];
	if (root == NULL)
	{
		printf("The BTree hasn't created!");

	}
	int * SS = (int *)malloc(sizeof(int)*bTreeP->nCount * 2);
	//ʵ��Ϊһ����ά���� 0---bTreeP->nCount-1����ǽڵ���  bTreeP->nCount----- bTreeP->nCount*2-1
	for (int i = 0; i < bTreeP->nCount * 2; i++)//��ʼ��SSջ
	{
		SS[i] = 0;
	}
	BTreeNodeP p = root;
	int top = 0;
	while (!(p == NULL&&top == 0))//pָ��NULL ��ջΪ�վ��˳� 
	{
		while (true)//���whileʱ��ջ�Ĺ���
		{
			if (p == NULL)
			{
				break;
			}
			if (SS[bTreeP->nCount + p->number] > 0)//����ڵ��Ƿ񱻱�����
			{
				break;
			}
			printf("%d	", p->data);//��ջʱ���
			SS[top++] = p->number;
			SS[bTreeP->nCount + p->number]++;
			p = p->lchild;
		}

		if (top == 0)//��ջ���̽��� ����top==0��˵�� pָ��NULL ��ջΪ��
		{
			printf("MLR�������");
			break;
		}
		p = bTreeP->bTreeNodes[SS[--top]];
		/*if (SS[bTreeP->nCount + p->number] == 2)
		{
			printf("%d	", p->data);
		}  
	   else
		{*/
			if (p->rchild == NULL)
			{
				//printf("%d	", p->data);
				//go_through_array[]
				continue;
			}
			else
			{
				//SS[top++] = p->number;
				//SS[bTreeP->nCount + p->number]++;
				p = p->rchild;
			}
		/*}*/

	}
	return 0;
}
int * LMR(BTreeP bTreeP)//������ �нڵ� ������
{
	printf("\n");
	int * go_through_array = (int *)malloc(sizeof(int)*bTreeP->nCount);
	BTreeNodeP root = bTreeP->bTreeNodes[0];
	if (root == NULL)
	{
		printf("The BTree hasn't created!");

	}
	int * SS = (int *)malloc(sizeof(int)*bTreeP->nCount * 2);
	//ʵ��Ϊһ����ά���� 0---bTreeP->nCount-1����ǽڵ���  bTreeP->nCount----- bTreeP->nCount*2-1
	for (int i = 0; i < bTreeP->nCount * 2; i++)//��ʼ��SSջ
	{
		SS[i] = 0;
	}
	BTreeNodeP p = root;
	int top = 0;
	while (!(p == NULL&&top == 0))//pָ��NULL ��ջΪ�վ��˳� 
	{
		while (true)//���whileʱ��ջ�Ĺ���
		{
			if (p == NULL)
			{
				break;
			}
			if (SS[bTreeP->nCount + p->number] > 0)//����ڵ��Ƿ񱻱�����
			{
				break;
			}
			SS[top++] = p->number;
			SS[bTreeP->nCount + p->number]++;
			p = p->lchild;
		}

		if (top == 0)//��ջ���̽��� ����top==0��˵�� pָ��NULL ��ջΪ��
		{
			printf("LMR�������");
			break;
		}
		p = bTreeP->bTreeNodes[SS[--top]];
		printf("%d	", p->data);//��ջʱ���
		/*if (SS[bTreeP->nCount + p->number] == 2)
		{
		printf("%d	", p->data);
		}
		else
		{*/
		if (p->rchild == NULL)
		{
			//printf("%d	", p->data);
			//go_through_array[]
			continue;
		}
		else
		{
			//SS[top++] = p->number;
			//SS[bTreeP->nCount + p->number]++;
			p = p->rchild;
		}
		/*}*/

	}
	return 0;
}

int addBtreeNode(int data,BTreeP bTreeP)//���ص�ǰ��Ҷ����
{
	
	
	/*
	BTreeNode newBTreeNode;
	BTreeNodeP newBTreeNodeP = &newBTreeNode;
	�����Ƿ�����ջ�ڴ棬�ȴ���������ʱ����ṹ����ջ�ռ��л��գ�ջ��esp ջ��edp�����ϲ㺯��λ��
	�����BTreeNode �ڴ� ʧЧ ������BTree �����е�ָ����ָ����ڴ�ͻ�ʧЧ��������һ����ջ�ռ������һ������ʱ���ջ�ڴ�ᱻ����
	���Ե���malloc����һ����ڴ�
	*/
	BTreeNodeP newBTreeNodeP = (BTreeNodeP)malloc(sizeof(BTreeNode));
	newBTreeNodeP->data = data;
	newBTreeNodeP->number = bTreeP->nCount;//���
	newBTreeNodeP->lchild = NULL;
	newBTreeNodeP->rchild = NULL;
	bTreeP->bTreeNodes[bTreeP->nCount] = newBTreeNodeP;//��ӽ�Nodes����

	//ȷ�����ڵ�
	if (bTreeP->nCount != 0)//���Ǹ��ڵ㣬��Ҫȷ�����ڵ�
	{
		int fatherNum = (bTreeP->nCount + 1) / 2 - 1;
		if ((bTreeP->nCount + 1) % 2 == 0)
		{
			bTreeP->bTreeNodes[fatherNum]->lchild = newBTreeNodeP;

		}
		else
		{
			bTreeP->bTreeNodes[fatherNum]->rchild = newBTreeNodeP;
		}
		
	}
	bTreeP->nCount++;

	return bTreeP->nCount;

}
int BTreeConstructor(int * datas,int n, BTreeP bTreeP)
{
	for (int i = 0; i < n; i++)
	{
		addBtreeNode(datas[i], bTreeP);
	}
	return bTreeP->nCount;
}

int main()
{
	int datas[10] = {1,3,4,5,6,10,2,9,4,1};
	BTreeP bTreeP= (BTreeP)malloc(sizeof(BTree));
	bTreeP->nCount = 0;
	bTreeP->bTreeNodes[0] = NULL;
    int nCount=BTreeConstructor(datas, 10, bTreeP);
	for (int i = 0; i < bTreeP->nCount; i++)
	{
		printf("%d	", bTreeP->bTreeNodes[i]->data);
	}
	LRM(bTreeP);
	MLR(bTreeP);
	LMR(bTreeP);
	system("pause");
	
    return 0;
}

