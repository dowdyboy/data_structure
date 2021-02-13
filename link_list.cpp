#include "link_list.h"

// 单链表

STATUS LINK_LIST_INIT(LINK_LIST* list) {
	list->node = NULL;
	list->length = 0;
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_INSERT(LINK_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length) return STATUS_FAIL;
	LINK_LIST_NODE* p = list->node;
	LINK_LIST_NODE* new_node = (LINK_LIST_NODE*)malloc(sizeof(LINK_LIST_NODE));
	new_node->data = data;
	new_node->next = NULL;
	if (idx > 0) {
		for (int i = 1; i < idx; i++) {
			p = p->next;
		}
		new_node->next = p->next;
		p->next = new_node;
	}
	else {
		new_node->next = p;
		list->node = new_node;
	}
	list->length += 1;
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_ADD(LINK_LIST* list, ELEM_TYPE data) {
	return LINK_LIST_INSERT(list, list->length, data);
}

STATUS LINK_LIST_DELETE(LINK_LIST* list, int idx) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	LINK_LIST_NODE* p = list->node;
	if (idx > 0) {
		for (int i = 1; i < idx; i++) {
			p = p->next;
		}
		LINK_LIST_NODE* q = p->next; // 这一块必须将p->next单独给个变量，否则free会失败
		p->next = q->next;
		free(q);
	}
	else {
		list->node = p->next;
		free(p);
	}
	list->length -= 1;
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_CLEAR(LINK_LIST* list) {
	while (list->length != 0) LINK_LIST_DELETE(list, 0);
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_PUT(LINK_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	LINK_LIST_NODE* p = list->node;
	for (int i = 0; i < idx; i++) {
		p = p->next;
	}
	p->data = data;
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_GET(LINK_LIST* list, int idx, ELEM_TYPE* result) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	LINK_LIST_NODE* p = list->node;
	for (int i = 0; i < idx; i++) {
		p = p->next;
	}
	*result = p->data;
	return STATUS_SUCCESS;
}

STATUS LINK_LIST_DESTORY(LINK_LIST* list) {
	return LINK_LIST_CLEAR(list);
}

STATUS LINK_LIST_IS_CONTAIN_ELEM_SEQ(LINK_LIST* list, ELEM_TYPE data) {
	LINK_LIST_NODE* p = list->node;
	while (p != NULL) {
		if (p->data == data) return BOOLEAN_TRUE;
		p = p->next;
	}
	return BOOLEAN_FALSE;
}

// 算法思路同顺序表版本，注释参见seq_list.cpp
STATUS LINK_LIST_INSERT_SORT(LINK_LIST* list) {
	LINK_LIST_NODE* current = list->node, * pre_current = NULL;
	while (current != NULL) {
		LINK_LIST_NODE* p = list->node, * pre_p = NULL;
		while (p != current && p->data <= current->data) {
			pre_p = pre_p == NULL ? p : pre_p->next;
			p = p->next;
		}
		if (p == current) {
			pre_current = pre_current == NULL ? current : pre_current->next;
			current = current->next;
		}
		else {
			LINK_LIST_NODE* q = current;
			pre_current->next = current->next;
			current = current->next;
			q->next = p;
			if (pre_p != NULL) {
				pre_p->next = q;
			}
			else {
				list->node = q;
			}
		}
	}
	return STATUS_SUCCESS;
}

// 算法思路同顺序表版本，注释参见seq_list.cpp
STATUS LINK_LIST_SELECT_SORT(LINK_LIST* list) {
	LINK_LIST_NODE* current = list->node, * pre_current = NULL;
	while (current != NULL) {
		LINK_LIST_NODE* p = current, * pre_p = NULL, * min = p, * pre_min = NULL;
		while (p != NULL) {
			if (p->data < min->data) {
				min = p;
				pre_min = pre_p;
			}
			pre_p = pre_p == NULL ? p : pre_p->next;
			p = p->next;
		}
		if (min != current) {
			pre_min->next = min->next;
			min->next = current;
			if (pre_current != NULL) {
				pre_current->next = min;
				pre_current = min;
			}
			else {
				list->node = min;
				pre_current = min;
			}
		}
		else {
			pre_current = pre_current == NULL ? current : pre_current->next;
			current = current->next;
		}
	}
	return STATUS_SUCCESS;
}


// 双向循环链表

STATUS DL_LINK_LIST_INIT(DL_LINK_LIST* list) {
	list->node = NULL;
	list->length = 0;
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_INSERT(DL_LINK_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length) return STATUS_FAIL;
	DL_LINK_LIST_NODE* p = list->node;
	DL_LINK_LIST_NODE* new_node = (DL_LINK_LIST_NODE *)malloc(sizeof(DL_LINK_LIST_NODE));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prior = NULL;
	// 根据要插入的位置，判断从前向后寻找还是从后向前寻找
	if (idx < list->length / 2) {
		for (int i = 0; i < idx; i++) {
			p = p->next;
		}
	}
	else {
		for (int i = list->length; i > idx; i--) {
			p = p->prior;
		}
	}
	if (!!p) {
		new_node->prior = p->prior;
		new_node->next = p;
		p->prior->next = new_node;
		p->prior = new_node;
		if (idx == 0) {
			list->node = new_node;
		}
	}
	else {
		// 第一个元素的插入
		list->node = new_node;
		new_node->next = new_node;
		new_node->prior = new_node;
	}
	list->length += 1;
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_ADD(DL_LINK_LIST* list, ELEM_TYPE data) {
	return DL_LINK_LIST_INSERT(list,list->length,data);
}

STATUS DL_LINK_LIST_DELETE(DL_LINK_LIST* list, int idx) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	DL_LINK_LIST_NODE* p = list->node;
	if (idx < list->length / 2) {
		for (int i = 0; i < idx; i++) {
			p = p->next;
		}
	}
	else {
		for (int i = list->length; i > idx; i--) {
			p = p->prior;
		}
	}
	if (idx == 0) {
		list->node = p->next;
	}
	p->next->prior = p->prior;
	p->prior->next = p->next;
	free(p);
	list->length -= 1;
	if (list->length == 0) {
		list->node = NULL;
	}
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_CLEAR(DL_LINK_LIST* list) {
	while (list->node != NULL) DL_LINK_LIST_DELETE(list, 0);
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_PUT(DL_LINK_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	DL_LINK_LIST_NODE* p = list->node;
	if (idx < list->length / 2) {
		for (int i = 0; i < idx; i++) {
			p = p->next;
		}
	}
	else {
		for (int i = list->length; i > idx; i--) {
			p = p->prior;
		}
	}
	p->data = data;
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_GET(DL_LINK_LIST* list, int idx, ELEM_TYPE* result) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	DL_LINK_LIST_NODE* p = list->node;
	if (idx < list->length / 2) {
		for (int i = 0; i < idx; i++) {
			p = p->next;
		}
	}
	else {
		for (int i = list->length; i > idx; i--) {
			p = p->prior;
		}
	}
	*result = p->data;
	return STATUS_SUCCESS;
}

STATUS DL_LINK_LIST_DESTORY(DL_LINK_LIST* list) {
	return DL_LINK_LIST_CLEAR(list);
}

BOOLEAN DL_LINK_LIST_IS_CONTAIN_ELEM_SEQ(DL_LINK_LIST* list, ELEM_TYPE data) {
	DL_LINK_LIST_NODE* p = list->node;
	while (p != NULL) {
		if (p->data == data) return BOOLEAN_TRUE;
		p = p->next;
	}
	return BOOLEAN_FALSE;
}

// 算法思路同顺序表版本，注释参见seq_list.cpp
STATUS DL_LINK_LIST_INSERT_SORT(DL_LINK_LIST* list) {
	DL_LINK_LIST_NODE* current = NULL;
	while (current != list->node) {
		if (current == NULL) {
			current = list->node;
		}
		DL_LINK_LIST_NODE* p = list->node;
		while (p != current && p->data <= current->data) {
			p = p->next;
		}
		if (p == current) {
			current = current->next;
		}
		else {
			DL_LINK_LIST_NODE* q = current;
			current->prior->next = current->next;
			current->next->prior = current->prior;
			current = current->next;
			q->next = p;
			q->prior = p->prior;
			q->prior->next = q;
			q->next->prior = q;
			if (p == list->node) {
				list->node = q;
			}
		}
	}
	return STATUS_SUCCESS;
}

// 算法思路同顺序表版本，注释参见seq_list.cpp
STATUS DL_LINK_LIST_SELECT_SORT(DL_LINK_LIST* list) {
	DL_LINK_LIST_NODE* current = NULL;
	while (current != list->node) {
		if (current == NULL) {
			current = list->node;
		}
		DL_LINK_LIST_NODE* p = NULL, * min = NULL;
		while (p != list->node) {
			if (p == NULL) {
				p = current;
				min = p;
			}
			if (p->data < min->data) {
				min = p;
			}
			p = p->next;
		}
		if (min != current) {
			min->prior->next = min->next;
			min->next->prior = min->prior;

			min->next = current;
			min->prior = current->prior;
			min->prior->next = min;
			min->next->prior = min;
			if (current == list->node) {
				list->node = min;
			}
		}
		else {
			current = current->next;
		}
	}
	return STATUS_SUCCESS;
}
