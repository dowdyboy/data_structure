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
	while (list->length != NULL) DL_LINK_LIST_DELETE(list, 0);
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