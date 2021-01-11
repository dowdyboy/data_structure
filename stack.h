#ifndef STACK_H
#define STACK_H

#include "basis.h"
#include "link_list.h"

#define SEQ_STACK_INIT_SIZE 5
#define SEQ_STACK_INC_SIZE 2

// ˳��ջ

typedef struct _seq_stack {
	ELEM_TYPE* base;
	ELEM_TYPE* top;
	int max_size;
} SEQ_STACK;

STATUS SEQ_STACK_INIT(SEQ_STACK* stack);  // ��ʼ��

STATUS SEQ_STACK_PUSH(SEQ_STACK* stack,ELEM_TYPE data);  // ��ջ

STATUS SEQ_STACK_POP(SEQ_STACK* stack,ELEM_TYPE *data);  // ��ջ

STATUS SEQ_STACK_GET_TOP(SEQ_STACK* stack, ELEM_TYPE* data);  // ��ȡջ��Ԫ��

// ��ջ

typedef LINK_LIST LINK_STACK;

STATUS LINK_STACK_INIT(LINK_STACK* stack);  // ��ʼ��

STATUS LINK_STACK_PUSH(LINK_STACK* stack, ELEM_TYPE data);  // ��ջ

STATUS LINK_STACK_POP(LINK_STACK* stack, ELEM_TYPE* data);  // ��ջ

STATUS LINK_STACK_GET_TOP(LINK_STACK* stack, ELEM_TYPE* data);  // ��ȡջ��Ԫ��


#endif // !STACK_H
