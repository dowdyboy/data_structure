#ifndef B_TREE_H
#define B_TREE_H

#include "basis.h"

typedef struct _b_tree_node {
	ELEM_TYPE* data;
	_b_tree_node* parent;
	_b_tree_node** children;
	int count;  // 当前关键字个数
} B_TREE_NODE;

typedef struct _b_tree {
	int m;
	int min_key_count;
	int max_key_count;
	int min_child_count;
	int max_child_count;
	B_TREE_NODE* root;
} B_TREE;

STATUS B_TREE_INIT(B_TREE* tree,int m);  // 初始化

STATUS B_TREE_ADD_ELEM(B_TREE* tree, ELEM_TYPE data);  // 添加元素

STATUS B_TREE_REMOVE_ELEM(B_TREE* tree, ELEM_TYPE data);  // 移除元素

BOOLEAN B_TREE_IS_CONTAIN_ELEM(B_TREE* tree, ELEM_TYPE data);  // 判断是否包含元素


#endif // !B_TREE_H
