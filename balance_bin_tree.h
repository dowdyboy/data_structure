#ifndef BALANCE_BIN_TREE_H
#define BALANCE_BIN_TREE_H

#include "basis.h"

typedef struct _balance_bin_tree {
	ELEM_TYPE data;
	_balance_bin_tree* parent;
	_balance_bin_tree* left;
	_balance_bin_tree* right;
}BALANCE_BIN_TREE;

STATUS BALANCE_BIN_TREE_ADD_ELEM(BALANCE_BIN_TREE** tree, ELEM_TYPE data);  // ƽ����������Ԫ��

BOOLEAN BALANCE_BIN_TREE_IS_CONTAIN_ELEM(BALANCE_BIN_TREE* tree, ELEM_TYPE data);  // ƽ�����������


#endif // !BALANCE_BIN_TREE_H

