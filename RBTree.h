#pragma once
typedef struct RBTreeNode//������ڵ�ṹ��
{
	int data;
	char color;
	RBTreeNode * parent;
	RBTreeNode * lchild;
	RBTreeNode * rchild;
}RBTreeNode, *RBTreeNodeP;
typedef struct RBTree//������ṹ��
{
	RBTreeNodeP root;
}RBTree, *RBTreeP;
void rbtree_left_rotate(RBTreeNodeP x, RBTreeP rbtreep);
void rbtree_right_rotate(RBTreeNodeP x, RBTreeP rbtreep);
void rbtree_insert(RBTreeNodeP x, RBTreeP rbtreep);
void rbtree_insert_fixup(RBTreeNodeP x, RBTreeP rbtreep);
void rbtree_delete(RBTreeNodeP x, RBTreeP rbtreep);
void rbtree_delete_fixup(RBTreeP rbtreep, RBTreeNodeP child, RBTreeNodeP parent);
void rbtree_gothough(RBTreeNodeP x);

