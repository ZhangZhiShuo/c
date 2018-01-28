// RBTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"
/*
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
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
		printf("右孩子不存在 左旋失败！");
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
		if (parent->lchild == x)//x 是parent的左孩子
		{
			parent->lchild = y;
		}
		else if (parent->rchild == x)//x 是parent的右孩子
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
* 对红黑树的节点(x)进行右旋转
*
* 右旋示意图(对节点x进行右旋)：
*            px                               px
*           /                                /
*          x                                y
*         /  \      --(右旋)-->            /  \                     #
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
		printf("左孩子不存在 右旋失败！");
		return;
	}
	RBTreeNodeP yr =NULL;
	if (y->rchild)
	{
		yr = y->rchild;
	}
	if (px == NULL)//x为根节点
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
添加操作：
第一步: 将红黑树当作一颗二叉查找树，将节点插入。
红黑树本身就是一颗二叉查找树，将节点插入后，该树仍然是一颗二叉查找树。
也就意味着，树的键值仍然是有序的。此外，无论是左旋还是右旋，若旋转之前这棵树是二叉查找树，旋转之后它一定还是二叉查找树。
这也就意味着，任何的旋转和重新着色操作，都不会改变它仍然是一颗二叉查找树的事实。

第二步：将插入的节点着色为"红色"。
重新温习一下红黑树的特性：
(1) 每个节点或者是黑色，或者是红色。
(2) 根节点是黑色。
(3) 每个叶子节点是黑色。 [注意：这里叶子节点，是指为空的叶子节点！]
(4) 如果一个节点是红色的，则它的子节点必须是黑色的。
(5) 从一个节点到该节点的所有叶子节点的所有路径上包含相同数目的黑节点。
将插入的节点着色为红色，不会违背"特性(5)"！少违背一条特性，就意味着我们需要处理的情况越少。接下来，就要努力的让这棵树满足其它性质即可

第三步: 通过一系列的旋转或着色等操作，使之重新成为一颗红黑树。
第二步中，将插入节点着色为"红色"之后，不会违背"特性(5)"。那它到底会违背哪些特性呢？
对于"特性(1)"，显然不会违背了。因为我们已经将它涂成红色了。
对于"特性(2)"，显然也不会违背。在第一步中，我们是将红黑树当作二叉查找树，然后执行的插入操作。而根据二叉查找数的特点，插入操作不会改变根节点。所以，根节点仍然是黑色。
对于"特性(3)"，显然不会违背了。这里的叶子节点是指的空叶子节点，插入非空节点并不会对它们造成影响。
对于"特性(4)"，是有可能违背的！
那接下来，想办法使之"满足特性(4)"，就可以将树重新构造成红黑树了。
*/

void rbtree_insert(RBTreeNodeP x,RBTreeP rbtreep)

{
	x->color = 'r';
	x->lchild = NULL;
	x->rchild = NULL;
	x->parent = NULL;
	if (rbtreep->root == NULL)//如果此二叉树不存在，则令x为根节点
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
			if (p->lchild == NULL)//保证p不为null
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
添加调整
*/
void rbtree_insert_fixup(RBTreeNodeP x, RBTreeP rbtreep)
{  //核心思想：将插入的红色的节点移到根节点；然后，将根节点设为黑色。
	RBTreeNodeP parent, gparent,uncle,current_node;
	current_node = x;
	while (true)
	{
		parent = current_node->parent;
		
		if (parent == NULL || parent->color == 'b')break;
		//parent 为NULL时，说明当前结点为根节点 直接将当前节点的颜色设为black即可
		//parent->color=='黑色' 时，说明当前节点满足了所有条件，不需要做调整了

		 gparent = parent->parent;
		if (gparent->lchild == parent)//父节点是祖父节点的左孩子
		{
			uncle = gparent->rchild;
			if (uncle&&uncle->color == 'r')//叔叔节点是红色
			{
				/*
				当前节点的父节点是红色，且当前节点的祖父节点的另一个子节点（叔叔节点）也是红色。
					 70b
					 /  \
					50r 80r  ----->
				   /
				 C:45r

				处理方法：
				(01) 将“父节点”设为黑色。
				(02) 将“叔叔节点”设为黑色。
				(03) 将“祖父节点”设为“红色”。
				(04) 将“祖父节点”设为“当前节点”(红色节点)；即，之后继续对“当前节点”进行操作。

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
				当前节点的父节点是红色，叔叔节点是黑色或为NULL，且当前节点是其父节点的右孩子(折线）
				 70b
				/   \
			  50b    80b
			  /             ----->
			 45r
			   \
			   C:47r
		   处理方法：
			(01) 将“父节点”作为“新的当前节点”。
			(02) 以“新的当前节点”为支点进行左旋。
			结果是转换为第三种情况继续处理（转换成金字塔型）
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
				当前节点的父节点是红色，叔叔节点是黑色或NULL，且当前节点是其父节点的左孩子
				   70b
				   /  \
				  50b  80b
				  /
				 47r
				 /
			   C:45r
		 处理方法：
		 (01) 将“父节点”设为“黑色”。
		 (02) 将“祖父节点”设为“红色”。（r 金子塔型然后进行旋转，转成       b  ）
		                              /                               / \
									 b                                r  r
									/
								   r             
		 (03) 以“祖父节点”为支点进行右旋。
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
			{   //折线-->直线
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
	//被删除节点的父节点和唯一儿子节点
	if ((x->lchild != NULL) &&( x->rchild != NULL))
	{
        //左孩子 右孩子都不为空，寻找后继节点来替代，值替代，颜色改为将要删除节点x的颜色
		//所以少的是后继节点的颜色，所以child是replace的唯一孩子（右） ，parent为replace节点的父亲节点
		//下面解决将replace替代过去之后，他的rchild的归属问题以repalce左右孩子的问题，注意分情况 
		RBTreeNodeP replace = NULL;
		replace = x->rchild;
		if (replace->lchild == NULL)//删除节点是replace节点的父节点  删除x后child 还是接在replace上
		{
			parent = replace;
			child = replace->rchild;

			//双向修改
			replace->lchild = x->lchild;
			x->lchild->parent = replace;
		}
		else//另外的情况就需要replace->parent->lchild=replace->rchild;replace->rchild->parent=replace->parent;
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

			//双向修改
			replace->rchild = x->rchild;
			x->rchild->parent = replace;
			replace->lchild = x->lchild;
			x->lchild->parent = replace;
		}
	   

		//下面解决x的父节点与replace的关系， 注意要分开讨论x是否为根节点的情况
		replace->parent = x->parent;
        if (x->parent == NULL)//x为根节点
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
		replace->color = x->color;//值替代， 颜色删除的其实是replace->color
		if (del_color == 'b')//删除的节点是黑色，才会打破红黑数平衡，如果是红色的话不用进行调整
		{

		}
    }
	else if ((x->lchild == NULL) && (x->rchild != NULL))//左孩子为空，右孩子不为空
	{
		//这种情况下，就直接删除x节点，child节点就是删除节点x的右孩子，parent是x节点的父亲节点
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
		① 情况说明：x是“红+黑”节点。
		处理方法：直接把x设为黑色，结束。此时红黑树性质全部恢复。
		*/
		if (x&&x->color == 'r')//黑+红 一黑 直接设为黑色
		{
			x->color = 'b';
			break;
		}
		/*
		② 情况说明：x是“黑+黑”节点，且x是根。
		处理方法：什么都不做，结束。此时红黑树性质全部恢复。
		*/
		else if (rbtreep->root == x)//黑+ 黑 
		{
			//什么都不做
			break;
		}
		/*
		③ 情况说明：x是“黑+黑”节点，且x不是根。
		处理方法：这种情况又可以划分为4种子情况。
		*/
		else
		{
			if (parent->lchild == x)//删除节点是父亲节点的左孩子
			{
				brother = parent->rchild;
				// Case 1: x的兄弟w是红色的  
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

				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
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
				// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
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
 					为第四步做准备
				*/

				else if ((brother->lchild&&brother->lchild->color == 'r') &&
					(!brother->rchild || brother->rchild->color == 'b') && (brother&&brother->color == 'b'))
				{
					brother->lchild->color = 'b';
					brother->color = 'r';
					rbtree_right_rotate(brother, rbtreep);//变成 金字塔 b r b 型
					brother = parent->rchild;

				}

				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
			else//删除节点是父亲节点的右孩子
			{
				brother = parent->lchild;
				if (brother->color == 'r')
				{
					brother->color = 'b';
					parent->color = 'r';
					rbtree_right_rotate(parent, rbtreep);//往少的那一边转
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

