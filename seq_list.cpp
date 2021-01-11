
#include "seq_list.h"

STATUS SEQ_LIST_INIT(SEQ_LIST* list) {
	list->data = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE) * SEQ_LIST_INIT_SIZE);
	list->length = 0;
	list->max_size = SEQ_LIST_INIT_SIZE;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_INSERT(SEQ_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length) return STATUS_FAIL;
	// 判断是否超出长度，进行拓展数组长度
	if(list->length+1 > list->max_size) {
		ELEM_TYPE* old_data = list->data;
		list->data = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (list->max_size + SEQ_LIST_INC_SIZE));
		for (int i = 0; i < list->max_size; i++) {
			list->data[i] = old_data[i];
		}
		list->max_size += SEQ_LIST_INC_SIZE;
		free(old_data);
	}
	for (int i = list->length - 1; i >= idx; i--) {
		list->data[i + 1] = list->data[i];
	}
	list->data[idx] = data;
	list->length += 1;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data) {
	return SEQ_LIST_INSERT(list, list->length, data);
}

STATUS SEQ_LIST_DELETE(SEQ_LIST* list, int idx) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	for (int i = idx; i < list->length - 1; i++) {
		list->data[i] = list->data[i + 1];
	}
	list->length -= 1;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list) {
	ELEM_TYPE* old_data = list->data;
	SEQ_LIST_INIT(list);
	free(old_data);
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	list->data[idx] = data;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE* result) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	*result = list->data[idx];
	return STATUS_SUCCESS;
}
