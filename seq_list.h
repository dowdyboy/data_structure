#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include "basis.h"

#define SEQ_LIST_INIT_SIZE 10
#define SEQ_LIST_INC_SIZE 5

// ˳�������
typedef struct _seq_list {
	ELEM_TYPE *data;
	int length;
	int max_size;
} SEQ_LIST;

STATUS SEQ_LIST_INIT(SEQ_LIST* list); // ��ʼ��

STATUS SEQ_LIST_INSERT(SEQ_LIST* list,int idx,ELEM_TYPE data); // ����

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data); // ĩβ����

STATUS SEQ_LIST_DELETE(SEQ_LIST* list,int idx); // ɾ��

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list); // ���

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data); // �޸�

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE *result); // ��ȡ

#endif