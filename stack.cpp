
#include "stack.h"

STATUS SEQ_STACK_INIT(SEQ_STACK* stack) {
	stack->base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE)*SEQ_STACK_INIT_SIZE);
	stack->top = stack->base;
	stack->max_size = SEQ_STACK_INIT_SIZE;
	return STATUS_SUCCESS;
}

STATUS SEQ_STACK_PUSH(SEQ_STACK* stack, ELEM_TYPE data) {
	// 空间不够用，拓展空间
	if (stack->top - stack->base == stack->max_size) {
		ELEM_TYPE* new_base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (stack->max_size + SEQ_STACK_INC_SIZE));
		ELEM_TYPE* old_base = stack->base;
		for (int i = 0; i < stack->top - stack->base; i++) {
			*(new_base + i) = *(stack->base + i);
		}
		stack->top = new_base + (stack->top - stack->base);
		stack->base = new_base;
		stack->max_size += SEQ_STACK_INC_SIZE;
		free(old_base);
	}
	*stack->top++ = data;
	return STATUS_SUCCESS;
}

STATUS SEQ_STACK_POP(SEQ_STACK* stack, ELEM_TYPE* data) {
	if (stack->base == stack->top) return STATUS_FAIL;
	*data = *--stack->top;
	return STATUS_SUCCESS;
}

STATUS SEQ_STACK_GET_TOP(SEQ_STACK* stack, ELEM_TYPE* data) {
	if (stack->base == stack->top) return STATUS_FAIL;
	*data = *(stack->top-1);
	return STATUS_SUCCESS;
}

STATUS SEQ_STACK_DESTORY(SEQ_STACK* stack) {
	ELEM_TYPE* old_data = stack->base;
	stack->base = NULL;
	stack->top = 0;
	stack->max_size = 0;
	if (old_data != NULL) free(old_data);
	return STATUS_SUCCESS;
}



STATUS LINK_STACK_INIT(LINK_STACK* stack) {
	return LINK_LIST_INIT(stack);
}

STATUS LINK_STACK_PUSH(LINK_STACK* stack, ELEM_TYPE data) {
	return LINK_LIST_INSERT(stack,0,data);
}

STATUS LINK_STACK_POP(LINK_STACK* stack, ELEM_TYPE* data) {
	return LINK_LIST_GET(stack, 0, data) | LINK_LIST_DELETE(stack, 0);
}

STATUS LINK_STACK_GET_TOP(LINK_STACK* stack, ELEM_TYPE* data) {
	return LINK_LIST_GET(stack, 0, data);
}

STATUS LINK_STACK_DESTORY(LINK_STACK* stack) {
	return LINK_LIST_DESTORY(stack);
}

