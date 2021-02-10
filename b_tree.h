#ifndef B_TREE_H
#define B_TREE_H

#include "basis.h"

typedef struct _b_tree_node {
	ELEM_TYPE* data;
	_b_tree_node* parent;
	_b_tree_node** children;
	int count;  // ��ǰ�ؼ��ָ���
} B_TREE_NODE;

typedef struct _b_tree {
	int m;
	int min_key_count;
	int max_key_count;
	int min_child_count;
	int max_child_count;
	B_TREE_NODE* root;
} B_TREE;

STATUS B_TREE_INIT(B_TREE* tree,int m);  // ��ʼ��

STATUS B_TREE_ADD_ELEM(B_TREE* tree, ELEM_TYPE data);  // ���Ԫ��

STATUS B_TREE_REMOVE_ELEM(B_TREE* tree, ELEM_TYPE data);  // �Ƴ�Ԫ��

BOOLEAN B_TREE_IS_CONTAIN_ELEM(B_TREE* tree, ELEM_TYPE data);  // �ж��Ƿ����Ԫ��


#endif // !B_TREE_H
