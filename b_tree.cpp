#include "b_tree.h"

// ��ʼ���ڵ����
void _b_tree_node_init(B_TREE_NODE* node, B_TREE* tree) {
	node->count = 0;
	node->parent = NULL;
	node->children = (B_TREE_NODE**)malloc(sizeof(B_TREE_NODE*) * (tree->max_child_count + 1));
	node->data = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (tree->max_key_count + 1));
	for (int i = 0; i < tree->max_child_count + 1; i++) {
		node->children[i] = NULL;
	}
	for (int i = 0; i < tree->max_key_count + 1; i++) {
		node->data[i] = ELEM_NULL;
	}
}

// ���ٽڵ����
void _b_tree_node_destory(B_TREE_NODE* node) {
	free(node->data);
	free(node->children);
	free(node);
}

// ��ڵ�������һ�����ݣ������Ƿ��ѣ�ֻ�ǵ������룩
int _b_tree_node_insert_data(B_TREE_NODE* node,ELEM_TYPE data) {
	int idx = 0;
	// �ҵ������λ������
	while (idx < node->count) {
		if (data < node->data[idx]) {
			break;
		}
		idx++;
	}
	// �ƶ��ؼ�������ͺ���ָ������
	for (int i = node->count; i > idx; i--) {
		node->data[i] = node->data[i - 1];
	}
	for (int i = node->count + 1; i > idx; i--) {
		node->children[i] = node->children[i - 1];
	}
	node->data[idx] = data;
	node->children[idx] = NULL;
	node->count++;
	return idx;
}

// ��ڵ����һ��Ԫ�أ������Ƿ���
int _b_tree_node_insert_data_split(B_TREE_NODE* p, ELEM_TYPE data, B_TREE* tree) {
	// ��ֱ�ӽ���Ԫ�ز���ڵ�
	int idx = _b_tree_node_insert_data(p, data);
	// ��������ڵ��йؼ��ָ������꣬��Ҫ���ѣ�ִ��ѭ��
	while (p->count > tree->max_key_count) {
		int midIdx = p->count / 2;  // Ҫ���Ϸ��ѵ�Ԫ�ص�����
		B_TREE_NODE* old_node = p;  // ����ɽڵ�ָ��
		ELEM_TYPE mid_data = p->data[midIdx];  // ȡ��Ҫ���ѵ�Ԫ��ֵ
		B_TREE_NODE* parent_node = p->parent;  // ������ڵ�ĸ��ڵ�
		B_TREE_NODE* left_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));  // ���Ѻ����벿�ֽڵ�
		B_TREE_NODE* right_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));  // ���Ѻ���Ұ벿�ֽڵ�

		// ��ʼ���½ڵ�
		_b_tree_node_init(left_node, tree);
		_b_tree_node_init(right_node, tree);
		// ��ԭ�ڵ������ͺ���ָ�룬�ֱ𿽱����´����Ľڵ�
		for (int i = 0; i < midIdx; i++) {
			left_node->data[i] = old_node->data[i];
		}
		for (int i = 0; i <= midIdx; i++) {
			left_node->children[i] = old_node->children[i];
			if (left_node->children[i]) {
				left_node->children[i]->parent = left_node;
			}
		}
		left_node->count = (old_node->count - 1) / 2;
		for (int i = midIdx + 1; i < old_node->count; i++) {
			right_node->data[i - midIdx - 1] = old_node->data[i];
		}
		for (int i = midIdx + 1; i <= old_node->count; i++) {
			right_node->children[i - midIdx - 1] = old_node->children[i];
			if (right_node->children[i - midIdx - 1]) {
				right_node->children[i - midIdx - 1]->parent = right_node;
			}
		}
		right_node->count = (old_node->count - 1) / 2;
		// ����ԭ�ڵ�
		_b_tree_node_destory(old_node);

		if (parent_node == NULL) {
			// ���ԭ�ڵ�ĸ��ڵ�Ϊ�գ���˵��ԭ�ڵ��Ǹ��ڵ㣬������Ϸ�����Ҫ�����µĸ��ڵ�
			parent_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));
			_b_tree_node_init(parent_node, tree);
			// �޸ĸ�ָ��
			tree->root = parent_node;
		}
		// ��Ҫ���Ϸ��ѵ����ݲ��뵽���ڵ㣬����ò����λ��
		int p_idx = _b_tree_node_insert_data(parent_node, mid_data);
		// �����ڵ�����λ�õ����Һ��ӷֱ�ָ����ѵ����ҽڵ�
		parent_node->children[p_idx] = left_node;
		parent_node->children[p_idx + 1] = right_node;
		left_node->parent = parent_node;
		right_node->parent = parent_node;

		// ��ǰָ��ָ�򸸽ڵ㣬ѭ���ж��Ƿ�����˷���
		p = parent_node;
	}
	return idx;
}


//void _b_tree_node_remove_data_merge(B_TREE_NODE* p, ELEM_TYPE data, B_TREE* tree) {
//	int idx = -1;
//	for (int i = 0; i < p->count; i++) {
//		if (p->data[i] == data) {
//			idx = i;
//			break;
//		}
//	}
//	if (idx > -1) {
//
//	}
//}

STATUS B_TREE_INIT(B_TREE* tree, int m) {
	// ������Ϊ����
	if (m % 2 == 0) return STATUS_FAIL;
	tree->m = m;
	tree->root = NULL;
	tree->max_child_count = m;
	tree->min_child_count = ceil(m / 2);
	tree->max_key_count = tree->max_child_count - 1;
	tree->min_key_count = tree->min_child_count - 1;
	return STATUS_SUCCESS;
}

STATUS B_TREE_ADD_ELEM(B_TREE* tree, ELEM_TYPE data) {
	if (tree->root == NULL) {
		// �����ǰ��Ϊ�գ��½�һ���ڵ㣬�����ݲ��룬���޸ĸ�ָ��
		B_TREE_NODE* node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));
		_b_tree_node_init(node,tree);
		_b_tree_node_insert_data(node, data);
		tree->root = node;
	}
	else {
		// �����ǰ�����գ������ҵ�����Ҫ����Ľڵ�
		B_TREE_NODE* p = tree->root;
		while (p->children[0] != NULL) {
			int idx = 0;
			while (idx < p->count) {
				// �ҵ�������ǰ�����ӽڵ������
				if (data < p->data[idx]) {
					break;
				}
				idx++;
			}
			// ��ǰָ������ǰ����ֱ��pָ��ָ�����Ҷ�ڵ�
			p = p->children[idx];
		}

		// ��������
		_b_tree_node_insert_data_split(p, data, tree);
	}
	return STATUS_SUCCESS;
}

//STATUS B_TREE_REMOVE_ELEM(B_TREE* tree, ELEM_TYPE data) {
//	B_TREE_NODE* p = tree->root;
//	BOOLEAN isFind = BOOLEAN_FALSE;
//	while (p != NULL) {
//		for (int i = 0; i < p->count; i++) {
//			if (p->data[i] == data) {
//				isFind = BOOLEAN_TRUE;
//				break;
//			}
//			else if (data < p->data[i]) {
//				p = p->children[i];
//				break;
//			}
//			else if (i == p->count - 1 && data > p->data[i]) {
//				p = p->children[i + 1];
//				break;
//			}
//		}
//		if (isFind) {
//			break;
//		}
//	}
//	if (isFind) {
//		_b_tree_node_remove_data_merge(p, data, tree);
//	}
//	return STATUS_SUCCESS;
//}

BOOLEAN B_TREE_IS_CONTAIN_ELEM(B_TREE* tree, ELEM_TYPE data) {
	if (tree == NULL) return BOOLEAN_FALSE;
	B_TREE_NODE* p = tree->root;
	while (p != NULL) {
		// ѭ���ҵ�ǰ�ڵ��Ԫ���Ƿ���ƥ��
		for (int i = 0; i < p->count; i++) {
			if (p->data[i] == data) {
				// �ҵ��򷵻سɹ�
				return BOOLEAN_TRUE;
			}
			else if (data < p->data[i]) {
				// �����ѯ����С����ǰָ��������ǰ��
				p = p->children[i];
				break;
			}
			else if (i == p->count - 1 && data > p->data[i]) {
				// �����ѯ���ݴ��Ҳ鵽�������ǰָ�����Һ���ǰ��
				p = p->children[i + 1];
				break;
			}
		}
	}
	// ����ʧ��
	return BOOLEAN_FALSE;
}
