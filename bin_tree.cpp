#include "bin_tree.h"

// 采用递归，将二叉树数组（i是父节点，2i是左孩子，2i+1是右孩子）转为二叉链表
BIN_TREE* _bin_tree_transform_from_array(ELEM_TYPE* arr, int arrLen,int idx) {
	// 如果超过数组长度，或者数组元素为空，则返回空指针
	if (idx >= arrLen || arr[idx] == ELEM_NULL) return NULL;
	// 创建新节点，将数组对应元素赋值，并递归调用，实现左右孩子的赋值
	BIN_TREE* t = (BIN_TREE*)malloc(sizeof(BIN_TREE));
	t->data = arr[idx];
	t->left = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2 - 1);
	t->right = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2);
	// 左右指针标记设置为是孩子而非线索
	t->leftIsChild = BOOLEAN_TRUE;
	t->rightIsChild = BOOLEAN_TRUE;
	return t;
}

STATUS BIN_TREE_TRANSFORM_FROM_ARRAY(ELEM_TYPE* arr, int arrLen, BIN_TREE** tree) {
	*tree = _bin_tree_transform_from_array(arr, arrLen, 0);
	if (*tree != NULL)
		return STATUS_SUCCESS;
	else
		return STATUS_FAIL;
}

// 采用递归，将二叉链表转换为二叉树数组（i是父节点，2i是左孩子，2i+1是右孩子）
void _bin_tree_transform_to_array(BIN_TREE* tree,SEQ_LIST* list,int idx) {
	if (tree != NULL) {
		// 如果要放置元素的索引超过列表长度，则用空元素拓展列表
		if (idx >= list->length) {
			int len = idx - list->length + 1;
			for (int i = 0; i < len; i++) {
				SEQ_LIST_ADD(list, ELEM_NULL);
			}
		}
		// 将数据放在列表的指定位置，并递归左子树和右子树
		SEQ_LIST_PUT(list, idx, tree->data);
		if(tree->leftIsChild) _bin_tree_transform_to_array(tree->left, list, 2 * idx);
		if(tree->rightIsChild) _bin_tree_transform_to_array(tree->right, list, 2 * idx + 1);
	}
}

STATUS BIN_TREE_TRANSFORM_TO_ARRAY(BIN_TREE* tree, ELEM_TYPE** arr, int* arrLen) {
	SEQ_LIST list;
	SEQ_LIST_INIT(&list);
	_bin_tree_transform_to_array(tree, &list, 1);
	// 将列表转换为普通的数组
	ELEM_TYPE* ret = (ELEM_TYPE*) malloc(sizeof(ELEM_TYPE) * list.length);
	for (int i = 1; i < list.length; i++) {
		ELEM_TYPE d;
		SEQ_LIST_GET(&list, i, &d);
		ret[i - 1] = d;
	}
	*arr = ret;
	*arrLen = list.length - 1;
	SEQ_LIST_DESTORY(&list);
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_ERGODIC_DLR(BIN_TREE* tree, void (*func)(ELEM_TYPE)) {
	if (tree != NULL) {
		(*func)(tree->data);
		if(tree->leftIsChild) BIN_TREE_ERGODIC_DLR(tree->left,func);
		if(tree->rightIsChild) BIN_TREE_ERGODIC_DLR(tree->right, func);
	}
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_ERGODIC_LDR(BIN_TREE* tree, void (*func)(ELEM_TYPE)) {
	if (tree != NULL) {
		if(tree->leftIsChild) BIN_TREE_ERGODIC_LDR(tree->left, func);
		(*func)(tree->data);
		if(tree->rightIsChild) BIN_TREE_ERGODIC_LDR(tree->right, func);
	}
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_ERGODIC_LRD(BIN_TREE* tree, void (*func)(ELEM_TYPE)) {
	if (tree != NULL) {
		if(tree->leftIsChild) BIN_TREE_ERGODIC_LRD(tree->left, func);
		if(tree->rightIsChild) BIN_TREE_ERGODIC_LRD(tree->right, func);
		(*func)(tree->data);
	}
	return STATUS_SUCCESS;
}

// 采用递归从二叉链表生成对应类型的节点遍历序列（type，0：先序，1：中序，2：后序）
int _bin_tree_ergodic_to_array(BIN_TREE* tree, BIN_TREE** ergodicList, int pos , int type) {
	if (tree != NULL) {
		if (type == 0) {
			ergodicList[pos++] = tree;
			pos = _bin_tree_ergodic_to_array(tree->left, ergodicList, pos, type);
			pos = _bin_tree_ergodic_to_array(tree->right, ergodicList, pos, type);
		}
		if (type == 1) {
			pos = _bin_tree_ergodic_to_array(tree->left, ergodicList, pos, type);
			ergodicList[pos++] = tree;
			pos = _bin_tree_ergodic_to_array(tree->right, ergodicList, pos, type);
		}
		if (type == 2) {
			pos = _bin_tree_ergodic_to_array(tree->left, ergodicList, pos, type);
			pos = _bin_tree_ergodic_to_array(tree->right, ergodicList, pos, type);
			ergodicList[pos++] = tree;
		}
	}
	return pos;
}

STATUS BIN_TREE_ERGODIC_DLR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList, int* nodeCount) {
	BIN_TREE_NODE_COUNT(tree, nodeCount);
	BIN_TREE** ergodicArr = (BIN_TREE**)malloc(sizeof(BIN_TREE*) * (*nodeCount + 1));
	_bin_tree_ergodic_to_array(tree, ergodicArr,0,0);
	*ergodicList = ergodicArr;
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_ERGODIC_LDR_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList, int* nodeCount) {
	BIN_TREE_NODE_COUNT(tree, nodeCount);
	BIN_TREE** ergodicArr = (BIN_TREE**)malloc(sizeof(BIN_TREE*) * (*nodeCount + 1));
	_bin_tree_ergodic_to_array(tree, ergodicArr, 0, 1);
	*ergodicList = ergodicArr;
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_ERGODIC_LRD_TO_ARRAY(BIN_TREE* tree, BIN_TREE*** ergodicList, int* nodeCount) {
	BIN_TREE_NODE_COUNT(tree, nodeCount);
	BIN_TREE** ergodicArr = (BIN_TREE**)malloc(sizeof(BIN_TREE*) * (*nodeCount + 1));
	_bin_tree_ergodic_to_array(tree, ergodicArr, 0, 2);
	*ergodicList = ergodicArr;
	return STATUS_SUCCESS;
}

int _bin_tree_node_count(BIN_TREE* tree) {
	if (tree == NULL) return 0;
	int leftCount = tree->leftIsChild ? _bin_tree_node_count(tree->left) : 0;
	int rightCount = tree->rightIsChild ? _bin_tree_node_count(tree->right) : 0;
	return 1 + leftCount + rightCount;
}

STATUS BIN_TREE_NODE_COUNT(BIN_TREE* tree, int* count) {
	*count = _bin_tree_node_count(tree);
	return STATUS_SUCCESS;
}

// 通过对应类型的节点遍历序列，进行线索化构建
void _bin_tree_index_bind(BIN_TREE** ergodicList, int nodeCount) {
	for (int i = 0; i < nodeCount; i++) {
		// 如果不是最后一个节点，且有右孩子为空，将右指针指向它的后继
		if (i != nodeCount - 1 && ergodicList[i]->right == NULL && ergodicList[i]->rightIsChild) {
			ergodicList[i]->right = ergodicList[i + 1];
			ergodicList[i]->rightIsChild = BOOLEAN_FALSE;
		}
		// 如果不是第一个节点，且有左孩子为空，将左指针指向它的前驱
		if (i != 0 && ergodicList[i]->left == NULL && ergodicList[i]->leftIsChild) {
			ergodicList[i]->left = ergodicList[i - 1];
			ergodicList[i]->leftIsChild = BOOLEAN_FALSE;
		}
	}
}

STATUS BIN_TREE_INDEX_DLR(BIN_TREE* tree) {
	int nodeCount = 0;
	BIN_TREE** ergodicList = NULL;
	BIN_TREE_ERGODIC_DLR_TO_ARRAY(tree, &ergodicList, &nodeCount);
	_bin_tree_index_bind(ergodicList, nodeCount);
	free(ergodicList);
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_INDEX_LDR(BIN_TREE* tree) {
	int nodeCount = 0;
	BIN_TREE** ergodicList = NULL;
	BIN_TREE_ERGODIC_LDR_TO_ARRAY(tree, &ergodicList, &nodeCount);
	_bin_tree_index_bind(ergodicList, nodeCount);
	free(ergodicList);
	return STATUS_SUCCESS;
}

STATUS BIN_TREE_INDEX_LRD(BIN_TREE* tree) {
	int nodeCount = 0;
	BIN_TREE** ergodicList = NULL;
	BIN_TREE_ERGODIC_LRD_TO_ARRAY(tree, &ergodicList, &nodeCount);
	_bin_tree_index_bind(ergodicList, nodeCount);
	free(ergodicList);
	return STATUS_SUCCESS;
}
