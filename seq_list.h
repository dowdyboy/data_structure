#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include "basis.h"

#define SEQ_LIST_INIT_SIZE 10
#define SEQ_LIST_INC_SIZE 5

// ˳�����
typedef struct _seq_list {
	ELEM_TYPE *data;
	int length;
	int max_size;
} SEQ_LIST;

STATUS SEQ_LIST_INIT(SEQ_LIST* list); // ��ʼ��

STATUS SEQ_LIST_INSERT(SEQ_LIST* list,int idx,ELEM_TYPE data); // ����

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data); // ĩβ���

STATUS SEQ_LIST_DELETE(SEQ_LIST* list,int idx); // ɾ��

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list); // ���

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data); // �޸�

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE *result); // ��ȡ

STATUS SEQ_LIST_DESTORY(SEQ_LIST* list);  // ����

// ============= ���� / ���� ===============

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_SEQ(SEQ_LIST* list, ELEM_TYPE data);  // ˳�����

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_BIN(SEQ_LIST* list, ELEM_TYPE data);  // �۰����

STATUS SEQ_LIST_INSERT_SORT(SEQ_LIST* list);  // ֱ�Ӳ�������

STATUS SEQ_LIST_HALF_INSERT_SORT(SEQ_LIST* list);  // �۰��������

STATUS SEQ_LIST_SHELL_SORT(SEQ_LIST* list);  // ϣ������

STATUS SEQ_LIST_BUBBLE_SORT(SEQ_LIST* list);  // ð������

STATUS SEQ_LIST_QUICK_SORT(SEQ_LIST* list);  // ��������

STATUS SEQ_LIST_SELECT_SORT(SEQ_LIST* list);  // ѡ������

STATUS SEQ_LIST_HEAP_SORT(SEQ_LIST* list);  // ������

STATUS SEQ_LIST_MERGE_SORT(SEQ_LIST* list);  // �鲢����


#endif
