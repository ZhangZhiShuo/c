// RBTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"
/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  xl   y                          x  yr
*     /   \                       /  \
*    yl   yr                     xl  yl
*
*
*/
void rbtree_left_rotate(RBTreeNodeP x,RBTreeP rbtreep)
{
	RBTreeNodeP y = x->rchild;
	if (!y) {
		printf("�Һ��Ӳ����� ����ʧ�ܣ�");
		return;
	}
	RBTreeNodeP yl = NULL;
	if (y->lchild)
	{
		 yl = y->lchild;
	}
	RBTreeNodeP parent = x->parent;
	if (parent == NULL)
	{
		rbtreep->root = y;
	}
	else
	{
		if (parent->lchild == x)//x ��parent������
		{
			parent->lchild = y;
		}
		else if (parent->rchild == x)//x ��parent���Һ���
		{
			parent->rchild = y;
		}
	}
	y->parent = parent;

	x->parent = y;
	y->lchild = x;
	
	
	if (yl)
	{
		x->rchild = yl;
		yl->parent = x;
	}
	else
	{
		x->rchild = NULL;
	}

}
/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*            px                               px
*           /                                /
*          x                                y
*         /  \      --(����)-->            /  \                     #
*        y   xr                           yl   x
*       / \                                   / \                   #
*      yl  yr                                yr  xr
*
*/
void rbtree_right_rotate(RBTreeNodeP x,RBTreeP rbtreep)
{
	RBTreeNodeP px = x->parent;
	RBTreeNodeP y = x->lchild;
	if (!y) {
		printf("���Ӳ����� ����ʧ�ܣ�");
		return;
	}
	RBTreeNodeP yr =NULL;
	if (y->rchild)
	{
		yr = y->rchild;
	}
	if (px == NULL)//xΪ���ڵ�
	{
		rbtreep->root = y;
	}
	else
	{

		if (px->rchild == x)
		{
			px->rchild = y;
		}
		else if (px->lchild == x)
		{
			px->lchild = y;
		}
	}
	y->parent = px;

	x->parent = y;
    y->rchild = x;
	if (yr)
	{
		yr->parent = x;
		x->lchild = yr;
	}
	else
	{
		x->lchild = NULL;
	}
}
/*
��Ӳ�����
��һ��: �����������һ�Ŷ�������������ڵ���롣
������������һ�Ŷ�������������ڵ����󣬸�����Ȼ��һ�Ŷ����������
Ҳ����ζ�ţ����ļ�ֵ��Ȼ������ġ����⣬������������������������ת֮ǰ������Ƕ������������ת֮����һ�����Ƕ����������
��Ҳ����ζ�ţ��κε���ת��������ɫ������������ı�����Ȼ��һ�Ŷ������������ʵ��

�ڶ�����������Ľڵ���ɫΪ"��ɫ"��
������ϰһ�º���������ԣ�
(1) ÿ���ڵ�����Ǻ�ɫ�������Ǻ�ɫ��
(2) ���ڵ��Ǻ�ɫ��
(3) ÿ��Ҷ�ӽڵ��Ǻ�ɫ�� [ע�⣺����Ҷ�ӽڵ㣬��ָΪ�յ�Ҷ�ӽڵ㣡]
(4) ���һ���ڵ��Ǻ�ɫ�ģ��������ӽڵ�����Ǻ�ɫ�ġ�
(5) ��һ���ڵ㵽�ýڵ������Ҷ�ӽڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ㡣
������Ľڵ���ɫΪ��ɫ������Υ��"����(5)"����Υ��һ�����ԣ�����ζ��������Ҫ��������Խ�١�����������ҪŬ����������������������ʼ���

������: ͨ��һϵ�е���ת����ɫ�Ȳ�����ʹ֮���³�Ϊһ�ź������
�ڶ����У�������ڵ���ɫΪ"��ɫ"֮�󣬲���Υ��"����(5)"���������׻�Υ����Щ�����أ�
����"����(1)"����Ȼ����Υ���ˡ���Ϊ�����Ѿ�����Ϳ�ɺ�ɫ�ˡ�
����"����(2)"����ȻҲ����Υ�����ڵ�һ���У������ǽ���������������������Ȼ��ִ�еĲ�������������ݶ�����������ص㣬�����������ı���ڵ㡣���ԣ����ڵ���Ȼ�Ǻ�ɫ��
����"����(3)"����Ȼ����Υ���ˡ������Ҷ�ӽڵ���ָ�Ŀ�Ҷ�ӽڵ㣬����ǿսڵ㲢������������Ӱ�졣
����"����(4)"�����п���Υ���ģ�
�ǽ���������취ʹ֮"��������(4)"���Ϳ��Խ������¹���ɺ�����ˡ�
*/

void rbtree_insert(RBTreeNodeP x,RBTreeP rbtreep)

{
	x->color = 'r';
	x->lchild = NULL;
	x->rchild = NULL;
	x->parent = NULL;
	if (rbtreep->root == NULL)//����˶����������ڣ�����xΪ���ڵ�
	{
		rbtreep->root = x;
		rbtreep->root->color = 'b';
		return;
	}
	RBTreeNodeP p = rbtreep->root;
	while (true)
	{
		if (x->data < p->data)

		{
			if (p->lchild == NULL)//��֤p��Ϊnull
			{
				x->parent = p;
				p->lchild = x;
				break;
			}
			else
			{
				p = p->lchild;
			}
		}
		else
		{
			if (p->rchild == NULL)
			{
				x->parent = p;
				p->rchild = x;
				break;

			}
			else
			{
				p=p->rchild;
			}
		}
	}
	
	rbtree_insert_fixup(x, rbtreep);

}
/*
��ӵ���
*/
void rbtree_insert_fixup(RBTreeNodeP x, RBTreeP rbtreep)
{  //����˼�룺������ĺ�ɫ�Ľڵ��Ƶ����ڵ㣻Ȼ�󣬽����ڵ���Ϊ��ɫ��
	RBTreeNodeP parent, gparent,uncle,current_node;
	current_node = x;
	while (true)
	{
		parent = current_node->parent;
		
		if (parent == NULL || parent->color == 'b')break;
		//parent ΪNULLʱ��˵����ǰ���Ϊ���ڵ� ֱ�ӽ���ǰ�ڵ����ɫ��Ϊblack����
		//parent->color=='��ɫ' ʱ��˵����ǰ�ڵ���������������������Ҫ��������

		 gparent = parent->parent;
		if (gparent->lchild == parent)//���ڵ����游�ڵ������
		{
			uncle = gparent->rchild;
			if (uncle&&uncle->color == 'r')//����ڵ��Ǻ�ɫ
			{
				/*
				��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ���游�ڵ����һ���ӽڵ㣨����ڵ㣩Ҳ�Ǻ�ɫ��
					 70b
					 /  \
					50r 80r  ----->
				   /
				 C:45r

				��������
				(01) �������ڵ㡱��Ϊ��ɫ��
				(02) ��������ڵ㡱��Ϊ��ɫ��
				(03) �����游�ڵ㡱��Ϊ����ɫ����
				(04) �����游�ڵ㡱��Ϊ����ǰ�ڵ㡱(��ɫ�ڵ�)������֮������ԡ���ǰ�ڵ㡱���в�����

				C:70r
				/   \
			  50b    80b
			  /
			45r
				 */
				parent->color = 'b';
				uncle->color = 'b';
				gparent->color = 'r';
				current_node = gparent;
			}
			else if ((uncle == NULL || uncle->color == 'b') && parent->rchild == current_node)
			{/*
				��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ������ڵ��Ǻ�ɫ��ΪNULL���ҵ�ǰ�ڵ����丸�ڵ���Һ���(���ߣ�
				 70b
				/   \
			  50b    80b
			  /             ----->
			 45r
			   \
			   C:47r
		   ��������
			(01) �������ڵ㡱��Ϊ���µĵ�ǰ�ڵ㡱��
			(02) �ԡ��µĵ�ǰ�ڵ㡱Ϊ֧�����������
			�����ת��Ϊ�����������������ת���ɽ������ͣ�
				  70b
				  /  \
				 50b  80b
				 /
				47r
				/
			  C:45r

				*/
				current_node = parent;
				rbtree_left_rotate(current_node, rbtreep);
			}
			else if ((uncle == NULL || uncle->color == 'b') && parent->lchild == current_node)
			{
				/*
				��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ������ڵ��Ǻ�ɫ��NULL���ҵ�ǰ�ڵ����丸�ڵ������
				   70b
				   /  \
				  50b  80b
				  /
				 47r
				 /
			   C:45r
		 ��������
		 (01) �������ڵ㡱��Ϊ����ɫ����
		 (02) �����游�ڵ㡱��Ϊ����ɫ������r ��������Ȼ�������ת��ת��       b  ��
		                              /                               / \
									 b                                r  r
									/
								   r             
		 (03) �ԡ��游�ڵ㡱Ϊ֧�����������
				   70b
				   /  \
				  47b  80b
				  /  \
			   C:45r  50r
				*/
				parent->color = 'b';
				gparent->color = 'r';
				rbtree_right_rotate(gparent, rbtreep);

			}
		}
		else
		{
			uncle = gparent->lchild;
			if (uncle&&uncle->color == 'r')
			{
				parent->color = 'b';
				uncle->color = 'b';
				gparent->color = 'r';
				current_node = gparent;

			}
			else if ((uncle == NULL || uncle->color == 'b') && parent->lchild == current_node)
			{   //����-->ֱ��
				current_node = parent;
				rbtree_right_rotate(current_node, rbtreep);
			}
			else if ((uncle == NULL || uncle->color == 'b') && parent->rchild == current_node)
			{
				parent->color = 'b';
				gparent->color = 'r';
				rbtree_left_rotate(gparent, rbtreep);
			}
		}

	}
	rbtreep->root->color = 'b';
	
}
void rbtree_delete(RBTreeNodeP x, RBTreeP rbtreep)
{
	RBTreeNodeP parent = NULL;
	RBTreeNodeP child=NULL;
	char del_color = NULL;
	//��ɾ���ڵ�ĸ��ڵ��Ψһ���ӽڵ�
	if ((x->lchild != NULL) &&( x->rchild != NULL))
	{
        //���� �Һ��Ӷ���Ϊ�գ�Ѱ�Һ�̽ڵ��������ֵ�������ɫ��Ϊ��Ҫɾ���ڵ�x����ɫ
		//�����ٵ��Ǻ�̽ڵ����ɫ������child��replace��Ψһ���ӣ��ң� ��parentΪreplace�ڵ�ĸ��׽ڵ�
		//��������replace�����ȥ֮������rchild�Ĺ���������repalce���Һ��ӵ����⣬ע������ 
		RBTreeNodeP replace = NULL;
		replace = x->rchild;
		if (replace->lchild == NULL)//ɾ���ڵ���replace�ڵ�ĸ��ڵ�  ɾ��x��child ���ǽ���replace��
		{
			parent = replace;
			child = replace->rchild;

			//˫���޸�
			replace->lchild = x->lchild;
			x->lchild->parent = replace;
		}
		else//������������Ҫreplace->parent->lchild=replace->rchild;replace->rchild->parent=replace->parent;
		{
            while (replace->lchild != NULL)
			{
				replace = replace->lchild;
			}
			parent = replace->parent;
			child = replace->rchild;
			if (child)
			{
				child->parent = parent;
			}
			parent->lchild = child;

			//˫���޸�
			replace->rchild = x->rchild;
			x->rchild->parent = replace;
			replace->lchild = x->lchild;
			x->lchild->parent = replace;
		}
	   

		//������x�ĸ��ڵ���replace�Ĺ�ϵ�� ע��Ҫ�ֿ�����x�Ƿ�Ϊ���ڵ�����
		replace->parent = x->parent;
        if (x->parent == NULL)//xΪ���ڵ�
		{
			rbtreep->root = replace;
		}
		else
		{
			if (x->parent->lchild == x)
			{
				x->parent->lchild = replace;
			}
			else
			{
				x->parent->rchild = replace;
			}
		}
		 del_color = replace->color;
		replace->color = x->color;//ֵ����� ��ɫɾ������ʵ��replace->color
		if (del_color == 'b')//ɾ���Ľڵ��Ǻ�ɫ���Ż���ƺ����ƽ�⣬����Ǻ�ɫ�Ļ����ý��е���
		{

		}
    }
	else if ((x->lchild == NULL) && (x->rchild != NULL))//����Ϊ�գ��Һ��Ӳ�Ϊ��
	{
		//��������£���ֱ��ɾ��x�ڵ㣬child�ڵ����ɾ���ڵ�x���Һ��ӣ�parent��x�ڵ�ĸ��׽ڵ�
		child = x->rchild;
		parent = x->parent;
		if (parent)
		{
			if (x== parent->lchild)
			{
				parent->lchild = child;

			}
			else
			{
				parent->rchild = child;
			}
		}
		else
		{
			rbtreep->root = child;
		}
		del_color = x->color;
		if (del_color == 'b')
		{

		}
		
	}
	else if ((x->lchild != NULL) && (x->rchild == NULL))
	{
		child = x->lchild;
		parent = x->parent;
		if (parent)
		{
			if (x == parent->lchild)
			{
				parent->lchild = child;

			}
			else
			{
				parent->rchild = child;
			}
		}
		else
		{
			rbtreep->root = child;
		}
		del_color = x->color;
		if (del_color == 'b')
		{

		}
	}
	else
	{
		child = NULL;
		parent = x->parent;
		if (parent)
		{
			if (x == parent->lchild)
			{
				parent->lchild = child;

			}
			else
			{
				parent->rchild = child;
			}
		}
		else
		{
			rbtreep->root = child;
		}
		del_color = x->color;
		if (del_color == 'b')
		{

		}
		
	}
	free(x);
}

void rbtree_delete_fixup(RBTreeP rbtreep, RBTreeNodeP child, RBTreeNodeP parent)
{
	RBTreeNodeP brother = NULL;
	RBTreeNodeP x = child;
	while (true)
	{
		/*
		�� ���˵����x�ǡ���+�ڡ��ڵ㡣
		��������ֱ�Ӱ�x��Ϊ��ɫ����������ʱ���������ȫ���ָ���
		*/
		if (x&&x->color == 'r')//��+�� һ�� ֱ����Ϊ��ɫ
		{
			x->color = 'b';
			break;
		}
		/*
		�� ���˵����x�ǡ���+�ڡ��ڵ㣬��x�Ǹ���
		��������ʲô����������������ʱ���������ȫ���ָ���
		*/
		else if (rbtreep->root == x)//��+ �� 
		{
			//ʲô������
			break;
		}
		/*
		�� ���˵����x�ǡ���+�ڡ��ڵ㣬��x���Ǹ���
		����������������ֿ��Ի���Ϊ4���������
		*/
		else
		{
			if (parent->lchild == x)//ɾ���ڵ��Ǹ��׽ڵ������
			{
				brother = parent->rchild;
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				/*
				b
			   / \  --------------->
			 b+b  r
			  3  / \
				b   b
				/    \
               b      b
				3     3

				b
			   / \
			  r   b
			 / \   \
			b+b b   b
			       
             3  3    3

				*/
				if (brother->color == 'r')
				{
					brother->color = 'b';
					parent->color = 'r';
					rbtree_left_rotate(parent, rbtreep);
					brother = parent->rchild;
                 }

				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				/*
			    b
			   / \
			  r   b
			 / \   \    ------------------------->
			b+b b   b
			 3   \  3
				  b
                  3


			 b
			/ \
		  b+r   b
		  / \    \
		 b   r    b
		     \     3
			  b
		3	  3	*/
				else if ((!brother->lchild || brother->lchild->color=='b') &&
					(!brother->rchild || brother->rchild->color == 'b') && (brother&&brother->color == 'b'))
				{
					brother->color = 'r';
					x->color = 'b';
					x = parent;
					parent = x->parent;

				}
				// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
				/*
				b
               / \
			  b+b b  --------------------------------->
			  3  / \
				 r  b
				 \   3
				  b
                  3

				b
			   / \
             b+b  b
			 3     \
			        r
				   / \
				   b  b
				   3  3
 					Ϊ���Ĳ���׼��
				*/

				else if ((brother->lchild&&brother->lchild->color == 'r') &&
					(!brother->rchild || brother->rchild->color == 'b') && (brother&&brother->color == 'b'))
				{
					brother->lchild->color = 'b';
					brother->color = 'r';
					rbtree_right_rotate(brother, rbtreep);//��� ������ b r b ��
					brother = parent->rchild;

				}

				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				/*
				b
			   / \
             b+b  b
			 3     \ --------------------------->
			        r
				   / \
				   b  b
				   3  3

                  b
				 / \
				b   b
			   /   / \
              b    b  b
			3	   3    3
				*/
				else if ((!brother->lchild||brother->lchild->color == 'b') &&
					(brother->rchild &&brother->rchild->color == 'r') && (brother&&brother->color == 'b'))
				{
					brother->color = parent->color;
					parent->color = 'b';
					brother->rchild->color= 'b';
					rbtree_left_rotate(parent, rbtreep);
					x = rbtreep->root;
				}
			}
			else//ɾ���ڵ��Ǹ��׽ڵ���Һ���
			{
				brother = parent->lchild;
				if (brother->color == 'r')
				{
					brother->color = 'b';
					parent->color = 'r';
					rbtree_right_rotate(parent, rbtreep);//���ٵ���һ��ת
					brother = parent->lchild;
				}

				
				else if ((!brother->lchild || brother->lchild->color == 'b') &&
					(!brother->rchild || brother->rchild->color == 'b') && (brother&&brother->color == 'b'))
				{
					brother->color = 'r';
					x->color = 'b';
					x = parent;
					parent = x->parent;

				}
				
				else if ((brother->lchild&&brother->lchild->color == 'r') &&
					(!brother->rchild || brother->rchild->color == 'b') && (brother&&brother->color == 'b'))
				{

					brother->color = parent->color;
					parent->color = 'b';
					brother->lchild->color = 'b';
					rbtree_right_rotate(parent, rbtreep);
					x = rbtreep->root;

				}

				else if ((!brother->lchild || brother->lchild->color == 'b') &&
					(brother->rchild &&brother->rchild->color == 'r') && (brother&&brother->color == 'b'))
				{
					brother->color = 'r';
					brother->rchild ->color= 'b';
					rbtree_left_rotate(brother, rbtreep);
					brother = parent->lchild;

				}

			}
		}
	}
}

void rbtree_gothough(RBTreeNodeP x)
{

	if (x)
	{
		rbtree_gothough(x->lchild);
		printf("%d	", x->data);
		rbtree_gothough(x->rchild);
	}
	else
	{
		return;
	}
}
int main()
{
	int datas[10] = { 2,4,6,7,5,3,4,2,4,10 };
	RBTreeP rbtreep = (RBTreeP)malloc(sizeof(RBTree));
	rbtreep->root = NULL;
	RBTreeNodeP p[10] = {0};
	for (int i = 0; i < 10; i++)
	{
		 p[i] = (RBTreeNodeP)malloc(sizeof(RBTreeNode));
		p[i]->data = datas[i];
		rbtree_insert(p[i], rbtreep);
	  }
	rbtree_gothough(rbtreep->root);
	printf("\n");
	rbtree_delete(p[3], rbtreep);
	rbtree_delete(p[4], rbtreep);
	rbtree_delete(p[7], rbtreep);
	rbtree_gothough(rbtreep->root);
	system("pause");
    return 0;
}

