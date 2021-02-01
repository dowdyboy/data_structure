#include "balance_bin_tree.h"

// 计算树高
int _balance_bin_tree_height(BALANCE_BIN_TREE* tree) {
	if (tree == NULL) return 0;
	int leftH = _balance_bin_tree_height(tree->left);
	int rightH = _balance_bin_tree_height(tree->right);
	return leftH > rightH ? 1 + leftH : 1 + rightH;
}

STATUS BALANCE_BIN_TREE_ADD_ELEM(BALANCE_BIN_TREE** tree, ELEM_TYPE data) {
	// 创建新节点并赋值
	BALANCE_BIN_TREE* new_node = (BALANCE_BIN_TREE*)malloc(sizeof(BALANCE_BIN_TREE));
	new_node->data = data;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	if (*tree == NULL) {
		// 如果是插入的第一个节点，修改根节点指针，返回
		*tree = new_node;
	}
	else {
		// 如果不是插入第一个节点
		BALANCE_BIN_TREE* p = *tree;
		while (p != NULL) {
			if (data < p->data) {
				// 如果要插入的数据小于当前节点的数据
				if (p->left == NULL) {
					// 当前节点没有左孩子，则将新节点挂在当前节点的左孩子上
					p->left = new_node;
					new_node->parent = p;
					p = NULL;
				}
				else {
					// 否则当前节点指针下移到左孩子
					p = p->left;
				}
			}
			else {
				// 如果要插入的数据大于等于当前节点的数据，同上
				if (p->right == NULL) {
					p->right = new_node;
					new_node->parent = p;
					p = NULL;
				}
				else {
					p = p->right;
				}
			}
		}

		// 定义辅助变量
		int typeRecord[2] = {-1,-1};  // 平衡树调整类型记录，0为左，1为右
		BOOLEAN isNeedAdjust = BOOLEAN_FALSE;  // 是否需要调整
		p = new_node;  // 指针指向新插入的节点，从下向上探索
		while (p != NULL) {
			// 计算左子树和右子树的高度
			int leftH = _balance_bin_tree_height(p->left);
			int rightH = _balance_bin_tree_height(p->right);
			if (leftH - rightH > 1 || leftH - rightH < -1) {
				// 如果平衡因子不为0/1/-1，则该子树需要调整为平衡树
				isNeedAdjust = BOOLEAN_TRUE;
				break;
			}
			else {
				// 如果平衡因子满足要求
				if (p->parent != NULL) {
					// 记录调整类型
					if (p->parent->left == p) {
						// 如果父节点的左孩子是当前节点，用0表示
						typeRecord[1] = typeRecord[0];
						typeRecord[0] = 0;
					}
					else if (p->parent->right == p) {
						// 如果父节点的右孩子是当前节点，用1表示
						typeRecord[1] = typeRecord[0];
						typeRecord[0] = 1;
					}
				}
				// 指针向上移动
				p = p->parent;
			}
		}

		// 如果子树需要调整，先判断调整类型
		if (isNeedAdjust) {
			if (typeRecord[0] == 0 && typeRecord[1] == 0) {
				// 如果是LL型，令q指向最上面的节点，p指向中间节点
				BALANCE_BIN_TREE* q = p;
				p = p->left;
				BALANCE_BIN_TREE* legacyR = p->right;  // 将中间节点的右孩子暂存
				// LL型将最上面节点折下来，即将q作为p的右孩子；将p放在q原来的位置
				p->parent = q->parent;  // p继承q的父节点
				p->right = q;  // 将q作为p的右孩子
				q->parent = p;
				q->left = NULL;  // 将q的左孩子置空
				if (p->parent == NULL) {
					// 如果p节点的父节点是空，则表明p为根节点，修改根节点指针
					*tree = p;
				}
				else {
					// 否则将p的父节点左/右孩子，指向p
					if (p->parent->left == q) {
						p->parent->left = p;
					}
					else if (p->parent->right == q) {
						p->parent->right = p;
					}
				}
				// 如果p原来有右孩子，则将这个节点再次放入平衡二叉树中
				if (legacyR != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyR->data);
					free(legacyR);
				}
			}
			else if (typeRecord[0] == 1 && typeRecord[1] == 1) {
				// RR型注释参考LL型
				BALANCE_BIN_TREE* q = p;
				p = p->right;
				BALANCE_BIN_TREE* legacyL = p->left;
				p->parent = q->parent;
				p->left = q;
				q->parent = p;
				q->right = NULL;
				if (p->parent == NULL) {
					*tree = p;
				}
				else {
					if (p->parent->left == q) {
						p->parent->left = p;
					}
					else if (p->parent->right == q) {
						p->parent->right = p;
					}
				}
				if (legacyL != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyL->data);
					free(legacyL);
				}
			}
			else if (typeRecord[0] == 0 && typeRecord[1] == 1) {
				// 如果是LR型，将r指向最上面的节点，q指向中间节点，p指向最下面的节点
				BALANCE_BIN_TREE* r = p, * q = p->left;
				p = p->left->right;
				BALANCE_BIN_TREE* legacyL = p->left, * legacyR = p->right;  // 将p的左孩子和右孩子暂存
				// LR型是将最下面的节点折上去，将中间节点和最上面的节点分别作为左孩子和右孩子
				p->parent = r->parent;  // p节点继承r的父节点
				p->right = r;  // 将r作为p的右孩子
				r->parent = p;
				r->left = NULL;  // 将r的左孩子置空
				p->left = q;  // 将q作为p的左孩子
				q->parent = p;
				q->right = NULL;  // 将q的右孩子置空
				if (p->parent == NULL) {
					// 如果p节点的父节点是空，则表明p为根节点，修改根节点指针
					*tree = p;
				}
				else {
					// 否则将p的父节点左/右孩子，指向p
					if (p->parent->left == r) {
						p->parent->left = p;
					}
					else if (p->parent->right == r) {
						p->parent->right = p;
					}
				}
				// 如果p原来有左孩子，则将这个节点再次放入平衡二叉树中
				if (legacyL != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyL->data);
					free(legacyL);
				}
				// 如果p原来有右孩子，则将这个节点再次放入平衡二叉树中
				if (legacyR != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyR->data);
					free(legacyR);
				}
			}
			else if (typeRecord[0] == 1 && typeRecord[1] == 0) {
				// RL型注释参考LR型
				BALANCE_BIN_TREE* r = p, * q = p->right;
				p = p->right->left;
				BALANCE_BIN_TREE* legacyL = p->left, * legacyR = p->right;
				p->parent = r->parent;
				p->left = r;
				r->parent = p;
				r->right = NULL;
				p->right = q;
				q->parent = p;
				q->left = NULL;
				if (p->parent == NULL) {
					*tree = p;
				}
				else {
					if (p->parent->left == r) {
						p->parent->left = p;
					}
					else if (p->parent->right == r) {
						p->parent->right = p;
					}
				}
				if (legacyL != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyL->data);
					free(legacyL);
				}
				if (legacyR != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyR->data);
					free(legacyR);
				}
			}
		}

	}
	return STATUS_SUCCESS;
}

BOOLEAN BALANCE_BIN_TREE_IS_CONTAIN_ELEM(BALANCE_BIN_TREE* tree, ELEM_TYPE data) {
	BALANCE_BIN_TREE* p = tree;
	while (p != NULL) {
		if (data < p->data) {
			// 如果要查找的数据小于当前节点的数据，当前指针左下移
			p = p->left;
		}
		else if (data > p->data) {
			// 如果要查找的数据大于当前节点的数据，当前指针右下移
			p = p->right;
		}
		else {
			// 找到，返回
			return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}
