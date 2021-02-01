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

STATUS BIN_TREE_TRANSFORM_FROM_ARRAY(ELEM_TYPE* arr, int arrLen, BIN_TREE** tree);  // ������ת��Ϊ������

STATUS BIN_TREE_TRANSFORM_TO_ARRAY(BIN_TREE* tree,ELEM_TYPE** arr,int* arrLen);  // ��������ת��Ϊ������ʽ

STATUS BIN_TREE_ERGODIC_DLR(BIN_TREE* tree,void (*func)(ELEM_TYPE));  // �������

STATUS BIN_TREE_ERGODIC_LDR(BIN_TREE* tree, void (*func)(ELEM_TYPE));  // �������

STATUS BIN_TREE_ERGODIC_LRD(BIN_TREE* tree, void (*func)(ELEM_TYPE));  // �������

STATUS BIN_TREE_ERGODIC_DLR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // ������������ر������е�����

STATUS BIN_TREE_ERGODIC_LDR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // ������������ر������е�����

STATUS BIN_TREE_ERGODIC_LRD_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList , int* nodeCount);  // ������������ر������е�����

STATUS BIN_TREE_NODE_COUNT(BIN_TREE* tree,int* count);  // ��ȡ�ڵ����

STATUS BIN_TREE_INDEX_DLR(BIN_TREE* tree);  // ����������

STATUS BIN_TREE_INDEX_LDR(BIN_TREE* tree);  // ����������

STATUS BIN_TREE_INDEX_LRD(BIN_TREE* tree);  // ����������

// ============= ���� / ���� ===============

STATUS BIN_TREE_ADD_ELEM(BIN_TREE** tree, ELEM_TYPE data);  // �������������Ԫ��

BOOLEAN BIN_TREE_IS_CONTAIN_ELEM(BIN_TREE* tree,ELEM_TYPE data);  // ��������������

#endif // !BIN_TREE_H
