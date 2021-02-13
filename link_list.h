#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "basis.h"

// ������

typedef struct _link_list_node {
	ELEM_TYPE data;
	_link_list_node* next;
} LINK_LIST_NODE;

typedef struct _link_list {
	LINK_LIST_NODE* node;
	int length;
} LINK_LIST;

STATUS LINK_LIST_INIT(LINK_LIST* list); // ��ʼ��

STATUS LINK_LIST_INSERT(LINK_LIST* list, int idx, ELEM_TYPE data); // ����

STATUS LINK_LIST_ADD(LINK_LIST* list, ELEM_TYPE data); // ĩβ���

STATUS LINK_LIST_DELETE(LINK_LIST* list, int idx); // ɾ��

STATUS LINK_LIST_CLEAR(LINK_LIST* list); // ���

STATUS LINK_LIST_PUT(LINK_LIST* list, int idx, ELEM_TYPE data); // �޸�

STATUS LINK_LIST_GET(LINK_LIST* list, int idx, ELEM_TYPE* result); // ��ȡ

STATUS LINK_LIST_DESTORY(LINK_LIST* list);  // ����

// ============= ���� / ���� ===============

STATUS LINK_LIST_IS_CONTAIN_ELEM_SEQ(LINK_LIST* list, ELEM_TYPE data);  // ˳�����

STATUS LINK_LIST_INSERT_SORT(LINK_LIST* list);  // ֱ�Ӳ�������

STATUS LINK_LIST_SELECT_SORT(LINK_LIST* list);  // ѡ������


// ˫��ѭ������

typedef struct _dl_link_list_node {
	ELEM_TYPE data;
	_dl_link_list_node* next;
	_dl_link_list_node* prior;
} DL_LINK_LIST_NODE;

typedef struct _dl_link_list {
	DL_LINK_LIST_NODE* node;
	int length;
} DL_LINK_LIST;

STATUS DL_LINK_LIST_INIT(DL_LINK_LIST* list); // ��ʼ��

STATUS DL_LINK_LIST_INSERT(DL_LINK_LIST* list, int idx, ELEM_TYPE data); // ����

STATUS DL_LINK_LIST_ADD(DL_LINK_LIST* list, ELEM_TYPE data); // ĩβ���

STATUS DL_LINK_LIST_DELETE(DL_LINK_LIST* list, int idx); // ɾ��

STATUS DL_LINK_LIST_CLEAR(DL_LINK_LIST* list); // ���

STATUS DL_LINK_LIST_PUT(DL_LINK_LIST* list, int idx, ELEM_TYPE data); // �޸�

STATUS DL_LINK_LIST_GET(DL_LINK_LIST* list, int idx, ELEM_TYPE* result); // ��ȡ

STATUS DL_LINK_LIST_DESTORY(DL_LINK_LIST* list);  // ����

// ============= ���� / ���� ===============

STATUS DL_LINK_LIST_IS_CONTAIN_ELEM_SEQ(DL_LINK_LIST* list, ELEM_TYPE data);  // ˳�����

STATUS DL_LINK_LIST_INSERT_SORT(DL_LINK_LIST* list);  // ֱ�Ӳ�������

STATUS DL_LINK_LIST_SELECT_SORT(DL_LINK_LIST* list);  // ѡ������

#endif // !LINK_LIST_H
