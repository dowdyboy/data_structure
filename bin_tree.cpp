#include "bin_tree.h"

// ���õݹ飬�����������飨i�Ǹ��ڵ㣬2i�����ӣ�2i+1���Һ��ӣ�תΪ��������
BIN_TREE* _bin_tree_transform_from_array(ELEM_TYPE* arr, int arrLen,int idx) {
	// ����������鳤�ȣ���������Ԫ��Ϊ�գ��򷵻ؿ�ָ��
	if (idx >= arrLen || arr[idx] == ELEM_NULL) return NULL;
	// �����½ڵ㣬�������ӦԪ�ظ�ֵ�����ݹ���ã�ʵ�����Һ��ӵĸ�ֵ
	BIN_TREE* t = (BIN_TREE*)malloc(sizeof(BIN_TREE));
	t->data = arr[idx];
	t->left = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2 - 1);
	t->right = _bin_tree_transform_from_array(arr, arrLen, (idx+1) * 2);
	// ����ָ��������Ϊ�Ǻ��Ӷ�������
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

// ���õݹ飬����������ת��Ϊ���������飨i�Ǹ��ڵ㣬2i�����ӣ�2i+1���Һ��ӣ�
void _bin_tree_transform_to_array(BIN_TREE* tree,SEQ_LIST* list,int idx) {
	if (tree != NULL) {
		// ���Ҫ����Ԫ�ص����������б��ȣ����ÿ�Ԫ����չ�б�
		if (idx >= list->length) {
			int len = idx - list->length + 1;
			for (int i = 0; i < len; i++) {
				SEQ_LIST_ADD(list, ELEM_NULL);
			}
		}
		// �����ݷ����б��ָ��λ�ã����ݹ���������������
		SEQ_LIST_PUT(list, idx, tree->data);
		if(tree->leftIsChild) _bin_tree_transform_to_array(tree->left, list, 2 * idx);
		if(tree->rightIsChild) _bin_tree_transform_to_array(tree->right, list, 2 * idx + 1);
	}
}

STATUS BIN_TREE_TRANSFORM_TO_ARRAY(BIN_TREE* tree, ELEM_TYPE** arr, int* arrLen) {
	SEQ_LIST list;
	SEQ_LIST_INIT(&list);
	_bin_tree_transform_to_array(tree, &list, 1);
	// ���б�ת��Ϊ��ͨ������
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

// ���õݹ�Ӷ����������ɶ�Ӧ���͵Ľڵ�������У�type��0������1������2������
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

// ͨ����Ӧ���͵Ľڵ�������У���������������
void _bin_tree_index_bind(BIN_TREE** ergodicList, int nodeCount) {
	for (int i = 0; i < nodeCount; i++) {
		// ����������һ���ڵ㣬�����Һ���Ϊ�գ�����ָ��ָ�����ĺ��
		if (i != nodeCount - 1 && ergodicList[i]->right == NULL && ergodicList[i]->rightIsChild) {
			ergodicList[i]->right = ergodicList[i + 1];
			ergodicList[i]->rightIsChild = BOOLEAN_FALSE;
		}
		// ������ǵ�һ���ڵ㣬��������Ϊ�գ�����ָ��ָ������ǰ��
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
