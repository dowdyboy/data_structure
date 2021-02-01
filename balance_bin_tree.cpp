#include "balance_bin_tree.h"

// ��������
int _balance_bin_tree_height(BALANCE_BIN_TREE* tree) {
	if (tree == NULL) return 0;
	int leftH = _balance_bin_tree_height(tree->left);
	int rightH = _balance_bin_tree_height(tree->right);
	return leftH > rightH ? 1 + leftH : 1 + rightH;
}

STATUS BALANCE_BIN_TREE_ADD_ELEM(BALANCE_BIN_TREE** tree, ELEM_TYPE data) {
	// �����½ڵ㲢��ֵ
	BALANCE_BIN_TREE* new_node = (BALANCE_BIN_TREE*)malloc(sizeof(BALANCE_BIN_TREE));
	new_node->data = data;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	if (*tree == NULL) {
		// ����ǲ���ĵ�һ���ڵ㣬�޸ĸ��ڵ�ָ�룬����
		*tree = new_node;
	}
	else {
		// ������ǲ����һ���ڵ�
		BALANCE_BIN_TREE* p = *tree;
		while (p != NULL) {
			if (data < p->data) {
				// ���Ҫ���������С�ڵ�ǰ�ڵ������
				if (p->left == NULL) {
					// ��ǰ�ڵ�û�����ӣ����½ڵ���ڵ�ǰ�ڵ��������
					p->left = new_node;
					new_node->parent = p;
					p = NULL;
				}
				else {
					// ����ǰ�ڵ�ָ�����Ƶ�����
					p = p->left;
				}
			}
			else {
				// ���Ҫ��������ݴ��ڵ��ڵ�ǰ�ڵ�����ݣ�ͬ��
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

		// ���帨������
		int typeRecord[2] = {-1,-1};  // ƽ�����������ͼ�¼��0Ϊ��1Ϊ��
		BOOLEAN isNeedAdjust = BOOLEAN_FALSE;  // �Ƿ���Ҫ����
		p = new_node;  // ָ��ָ���²���Ľڵ㣬��������̽��
		while (p != NULL) {
			// �������������������ĸ߶�
			int leftH = _balance_bin_tree_height(p->left);
			int rightH = _balance_bin_tree_height(p->right);
			if (leftH - rightH > 1 || leftH - rightH < -1) {
				// ���ƽ�����Ӳ�Ϊ0/1/-1�����������Ҫ����Ϊƽ����
				isNeedAdjust = BOOLEAN_TRUE;
				break;
			}
			else {
				// ���ƽ����������Ҫ��
				if (p->parent != NULL) {
					// ��¼��������
					if (p->parent->left == p) {
						// ������ڵ�������ǵ�ǰ�ڵ㣬��0��ʾ
						typeRecord[1] = typeRecord[0];
						typeRecord[0] = 0;
					}
					else if (p->parent->right == p) {
						// ������ڵ���Һ����ǵ�ǰ�ڵ㣬��1��ʾ
						typeRecord[1] = typeRecord[0];
						typeRecord[0] = 1;
					}
				}
				// ָ�������ƶ�
				p = p->parent;
			}
		}

		// ���������Ҫ���������жϵ�������
		if (isNeedAdjust) {
			if (typeRecord[0] == 0 && typeRecord[1] == 0) {
				// �����LL�ͣ���qָ��������Ľڵ㣬pָ���м�ڵ�
				BALANCE_BIN_TREE* q = p;
				p = p->left;
				BALANCE_BIN_TREE* legacyR = p->right;  // ���м�ڵ���Һ����ݴ�
				// LL�ͽ�������ڵ�������������q��Ϊp���Һ��ӣ���p����qԭ����λ��
				p->parent = q->parent;  // p�̳�q�ĸ��ڵ�
				p->right = q;  // ��q��Ϊp���Һ���
				q->parent = p;
				q->left = NULL;  // ��q�������ÿ�
				if (p->parent == NULL) {
					// ���p�ڵ�ĸ��ڵ��ǿգ������pΪ���ڵ㣬�޸ĸ��ڵ�ָ��
					*tree = p;
				}
				else {
					// ����p�ĸ��ڵ���/�Һ��ӣ�ָ��p
					if (p->parent->left == q) {
						p->parent->left = p;
					}
					else if (p->parent->right == q) {
						p->parent->right = p;
					}
				}
				// ���pԭ�����Һ��ӣ�������ڵ��ٴη���ƽ���������
				if (legacyR != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyR->data);
					free(legacyR);
				}
			}
			else if (typeRecord[0] == 1 && typeRecord[1] == 1) {
				// RR��ע�Ͳο�LL��
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
				// �����LR�ͣ���rָ��������Ľڵ㣬qָ���м�ڵ㣬pָ��������Ľڵ�
				BALANCE_BIN_TREE* r = p, * q = p->left;
				p = p->left->right;
				BALANCE_BIN_TREE* legacyL = p->left, * legacyR = p->right;  // ��p�����Ӻ��Һ����ݴ�
				// LR���ǽ�������Ľڵ�����ȥ�����м�ڵ��������Ľڵ�ֱ���Ϊ���Ӻ��Һ���
				p->parent = r->parent;  // p�ڵ�̳�r�ĸ��ڵ�
				p->right = r;  // ��r��Ϊp���Һ���
				r->parent = p;
				r->left = NULL;  // ��r�������ÿ�
				p->left = q;  // ��q��Ϊp������
				q->parent = p;
				q->right = NULL;  // ��q���Һ����ÿ�
				if (p->parent == NULL) {
					// ���p�ڵ�ĸ��ڵ��ǿգ������pΪ���ڵ㣬�޸ĸ��ڵ�ָ��
					*tree = p;
				}
				else {
					// ����p�ĸ��ڵ���/�Һ��ӣ�ָ��p
					if (p->parent->left == r) {
						p->parent->left = p;
					}
					else if (p->parent->right == r) {
						p->parent->right = p;
					}
				}
				// ���pԭ�������ӣ�������ڵ��ٴη���ƽ���������
				if (legacyL != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyL->data);
					free(legacyL);
				}
				// ���pԭ�����Һ��ӣ�������ڵ��ٴη���ƽ���������
				if (legacyR != NULL) {
					BALANCE_BIN_TREE_ADD_ELEM(tree, legacyR->data);
					free(legacyR);
				}
			}
			else if (typeRecord[0] == 1 && typeRecord[1] == 0) {
				// RL��ע�Ͳο�LR��
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
			// ���Ҫ���ҵ�����С�ڵ�ǰ�ڵ�����ݣ���ǰָ��������
			p = p->left;
		}
		else if (data > p->data) {
			// ���Ҫ���ҵ����ݴ��ڵ�ǰ�ڵ�����ݣ���ǰָ��������
			p = p->right;
		}
		else {
			// �ҵ�������
			return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}
