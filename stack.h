#ifndef STACK_H
#define STACK_H

#include "basis.h"
#include "link_list.h"

#define SEQ_STACK_INIT_SIZE 5
#define SEQ_STACK_INC_SIZE 2

// 顺序栈

typedef struct _seq_stack {
	ELEM_TYPE* base;
	ELEM_TYPE* top;
	int max_size;
} SEQ_STACK;

STATUS SEQ_STACK_INIT(SEQ_STACK* stack);  // 初始化

STATUS SEQ_STACK_PUSH(SEQ_STACK* stack,ELEM_TYPE data);  // 入栈

STATUS SEQ_STACK_POP(SEQ_STACK* stack,ELEM_TYPE *data);  // 出栈

STATUS SEQ_STACK_GET_TOP(SEQ_STACK* stack, ELEM_TYPE* data);  // 获取栈顶元素

// 链栈

typedef LINK_LIST LINK_STACK;

STATUS LINK_STACK_INIT(LINK_STACK* stack);  // 初始化

STATUS LINK_STACK_PUSH(LINK_STACK* stack, ELEM_TYPE data);  // 入栈

STATUS LINK_STACK_POP(LINK_STACK* stack, ELEM_TYPE* data);  // 出栈

STATUS LINK_STACK_GET_TOP(LINK_STACK* stack, ELEM_TYPE* data);  // 获取栈顶元素


#endif // !STACK_H
