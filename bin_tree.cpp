#include "bin_tree.h"

BIN_TREE* _bin_tree_transform_from_array(ELEM_TYPE* arr, int arrLen,int idx) {
	if (idx >= arrLen || arr[idx] == ELEM_NULL) return NULL;
	BIN_TREE* t = (BIN_TREE*)malloc(sizeof(BIN_TREE));
	t->data = arr[idx];
	t->left = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2 - 1);
	t->right = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2);
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

void _bin_tree_transform_to_array(BIN_TREE* tree,SEQ_LIST* list,int idx) {
	if (tree != NULL) {
		if (idx >= list->length) {
			int len = idx - list->length + 1;
			for (int i = 0; i < len; i++) {
				SEQ_LIST_ADD(list, ELEM_NULL);
			}
		}
		SEQ_LIST_PUT(list, idx, tree->data);
		if(tree->leftIsChild) _bin_tree_transform_to_array(tree->left, list, 2 * idx);
		if(tree->rightIsChild) _bin_tree_transform_to_array(tree->right, list, 2 * idx + 1);
	}
}

STATUS BIN_TREE_TRANSFORM_TO_ARRAY(BIN_TREE* tree, ELEM_TYPE** arr, int* arrLen) {
	SEQ_LIST list;
	SEQ_LIST_INIT(&list);
	_bin_tree_transform_to_array(tree, &list, 1);
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

