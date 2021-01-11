#ifndef QUEUE_H
#define QUEUE_H

#include "basis.h"
#include "link_list.h"

#define SEQ_QUEUE_INIT_SIZE 5
#define SEQ_QUEUE_INC_SIZE 2

// ˳�����

typedef struct _seq_queue {
	ELEM_TYPE* base;
	int head;
	int rear;
	int max_size;
} SEQ_QUEUE;

STATUS SEQ_QUEUE_INIT(SEQ_QUEUE* queue);  // ��ʼ��

STATUS SEQ_QUEUE_ENQUEUE(SEQ_QUEUE* queue,ELEM_TYPE data);  // ���

STATUS SEQ_QUEUE_DEQUEUE(SEQ_QUEUE* queue, ELEM_TYPE* data);  // ����

STATUS SEQ_QUEUE_GET_HEAD(SEQ_QUEUE* queue, ELEM_TYPE* data);  // ��ȡ��ͷԪ��


// ������

typedef DL_LINK_LIST LINK_QUEUE;

STATUS LINK_QUEUE_INIT(LINK_QUEUE* queue);  // ��ʼ��

STATUS LINK_QUEUE_ENQUEUE(LINK_QUEUE* queue, ELEM_TYPE data);  // ���

STATUS LINK_QUEUE_DEQUEUE(LINK_QUEUE* queue, ELEM_TYPE* data);  // ����

STATUS LINK_QUEUE_GET_HEAD(LINK_QUEUE* queue, ELEM_TYPE* data);  // ��ȡ��ͷԪ��


#endif // !QUEUE_H
