#include "b_tree.h"

// 初始化节点对象
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

// 销毁节点对象
void _b_tree_node_destory(B_TREE_NODE* node) {
	free(node->data);
	free(node->children);
	free(node);
}

// 向节点对象插入一个数据（不考虑分裂，只是单纯插入）
int _b_tree_node_insert_data(B_TREE_NODE* node,ELEM_TYPE data) {
	int idx = 0;
	// 找到插入的位置索引
	while (idx < node->count) {
		if (data < node->data[idx]) {
			break;
		}
		idx++;
	}
	// 移动关键字数组和孩子指针数组
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

// 向节点插入一个元素，并考虑分裂
int _b_tree_node_insert_data_split(B_TREE_NODE* p, ELEM_TYPE data, B_TREE* tree) {
	// 先直接将该元素插入节点
	int idx = _b_tree_node_insert_data(p, data);
	// 如果插入后节点中关键字个数超标，需要分裂，执行循环
	while (p->count > tree->max_key_count) {
		int midIdx = p->count / 2;  // 要向上分裂的元素的索引
		B_TREE_NODE* old_node = p;  // 保存旧节点指针
		ELEM_TYPE mid_data = p->data[midIdx];  // 取出要分裂的元素值
		B_TREE_NODE* parent_node = p->parent;  // 被插入节点的父节点
		B_TREE_NODE* left_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));  // 分裂后的左半部分节点
		B_TREE_NODE* right_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));  // 分裂后的右半部分节点

		// 初始化新节点
		_b_tree_node_init(left_node, tree);
		_b_tree_node_init(right_node, tree);
		// 将原节点的数组和孩子指针，分别拷贝到新创建的节点
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
		// 销毁原节点
		_b_tree_node_destory(old_node);

		if (parent_node == NULL) {
			// 如果原节点的父节点为空，则说明原节点是根节点，因此向上分裂需要创建新的根节点
			parent_node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));
			_b_tree_node_init(parent_node, tree);
			// 修改根指针
			tree->root = parent_node;
		}
		// 将要向上分裂的数据插入到父节点，并获得插入的位置
		int p_idx = _b_tree_node_insert_data(parent_node, mid_data);
		// 将父节点插入的位置的左右孩子分别指向分裂的左右节点
		parent_node->children[p_idx] = left_node;
		parent_node->children[p_idx + 1] = right_node;
		left_node->parent = parent_node;
		right_node->parent = parent_node;

		// 当前指针指向父节点，循环判断是否完成了分裂
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
	// 阶数需为奇数
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
		// 如果当前树为空，新建一个节点，将数据插入，并修改根指针
		B_TREE_NODE* node = (B_TREE_NODE*)malloc(sizeof(B_TREE_NODE));
		_b_tree_node_init(node,tree);
		_b_tree_node_insert_data(node, data);
		tree->root = node;
	}
	else {
		// 如果当前树不空，则先找到数据要插入的节点
		B_TREE_NODE* p = tree->root;
		while (p->children[0] != NULL) {
			int idx = 0;
			while (idx < p->count) {
				// 找到将向下前进的子节点的索引
				if (data < p->data[idx]) {
					break;
				}
				idx++;
			}
			// 当前指针向下前进，直到p指针指向的是叶节点
			p = p->children[idx];
		}

		// 插入数据
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
		// 循环找当前节点的元素是否有匹配
		for (int i = 0; i < p->count; i++) {
			if (p->data[i] == data) {
				// 找到则返回成功
				return BOOLEAN_TRUE;
			}
			else if (data < p->data[i]) {
				// 如果查询数据小，则当前指针向左孩子前进
				p = p->children[i];
				break;
			}
			else if (i == p->count - 1 && data > p->data[i]) {
				// 如果查询数据大，且查到了最后，则当前指针向右孩子前进
				p = p->children[i + 1];
				break;
			}
		}
	}
	// 查找失败
	return BOOLEAN_FALSE;
}
