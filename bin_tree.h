#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "basis.h"
#include "seq_list.h"

typedef struct _bin_tree {
	ELEM_TYPE data;
	_bin_tree* left;
	_bin_tree* right;
	BOOLEAN leftIsChild;
	BOOLEAN rightIsChild;
} BIN_TREE;

STATUS BIN_TREE_TRANSFORM_FROM_ARRAY(ELEM_TYPE* arr, int arrLen, BIN_TREE** tree);  // 将数组转换为二叉树

STATUS BIN_TREE_TRANSFORM_TO_ARRAY(BIN_TREE* tree,ELEM_TYPE** arr,int* arrLen);  // 将二叉树转换为数组形式

STATUS BIN_TREE_ERGODIC_DLR(BIN_TREE* tree,void (*func)(ELEM_TYPE));  // 先序遍历

STATUS BIN_TREE_ERGODIC_LDR(BIN_TREE* tree, void (*func)(ELEM_TYPE));  // 中序遍历

STATUS BIN_TREE_ERGODIC_LRD(BIN_TREE* tree, void (*func)(ELEM_TYPE));  // 后序遍历

STATUS BIN_TREE_ERGODIC_DLR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // 先序遍历，返回遍历序列的数组

STATUS BIN_TREE_ERGODIC_LDR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // 中序遍历，返回遍历序列的数组

STATUS BIN_TREE_ERGODIC_LRD_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // 后序遍历，返回遍历序列的数组

STATUS BIN_TREE_NODE_COUNT(BIN_TREE* tree,int* count);  // 获取节点个数

STATUS BIN_TREE_INDEX_DLR(BIN_TREE* tree);  // 先序线索化

STATUS BIN_TREE_INDEX_LDR(BIN_TREE* tree);  // 中序线索化

STATUS BIN_TREE_INDEX_LRD(BIN_TREE* tree);  // 后序线索化

// ============= 查找 / 排序 ===============

STATUS BIN_TREE_ADD_ELEM(BIN_TREE** tree, ELEM_TYPE data);  // 二叉排序树添加元素

BOOLEAN BIN_TREE_IS_CONTAIN_ELEM(BIN_TREE* tree,ELEM_TYPE data);  // 二叉排序树查找

#endif // !BIN_TREE_H
