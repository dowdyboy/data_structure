#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "basis.h"

// 单链表

typedef struct _link_list_node {
	ELEM_TYPE data;
	_link_list_node* next;
} LINK_LIST_NODE;

typedef struct _link_list {
	LINK_LIST_NODE* node;
	int length;
} LINK_LIST;

STATUS LINK_LIST_INIT(LINK_LIST* list); // 初始化

STATUS LINK_LIST_INSERT(LINK_LIST* list, int idx, ELEM_TYPE data); // 插入

STATUS LINK_LIST_ADD(LINK_LIST* list, ELEM_TYPE data); // 末尾添加

STATUS LINK_LIST_DELETE(LINK_LIST* list, int idx); // 删除

STATUS LINK_LIST_CLEAR(LINK_LIST* list); // 清空

STATUS LINK_LIST_PUT(LINK_LIST* list, int idx, ELEM_TYPE data); // 修改

STATUS LINK_LIST_GET(LINK_LIST* list, int idx, ELEM_TYPE* result); // 获取

// 双向循环链表

typedef struct _dl_link_list_node {
	ELEM_TYPE data;
	_dl_link_list_node* next;
	_dl_link_list_node* prior;
} DL_LINK_LIST_NODE;

typedef struct _dl_link_list {
	DL_LINK_LIST_NODE* node;
	int length;
} DL_LINK_LIST;

STATUS DL_LINK_LIST_INIT(DL_LINK_LIST* list); // 初始化

STATUS DL_LINK_LIST_INSERT(DL_LINK_LIST* list, int idx, ELEM_TYPE data); // 插入

STATUS DL_LINK_LIST_ADD(DL_LINK_LIST* list, ELEM_TYPE data); // 末尾添加

STATUS DL_LINK_LIST_DELETE(DL_LINK_LIST* list, int idx); // 删除

STATUS DL_LINK_LIST_CLEAR(DL_LINK_LIST* list); // 清空

STATUS DL_LINK_LIST_PUT(DL_LINK_LIST* list, int idx, ELEM_TYPE data); // 修改

STATUS DL_LINK_LIST_GET(DL_LINK_LIST* list, int idx, ELEM_TYPE* result); // 获取

#endif // !LINK_LIST_H
