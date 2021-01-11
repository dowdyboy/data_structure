#include "queue.h"

STATUS SEQ_QUEUE_INIT(SEQ_QUEUE* queue) {
	queue->base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * SEQ_QUEUE_INIT_SIZE);
	queue->head = 0;
	queue->rear = 0;
	queue->max_size = SEQ_QUEUE_INIT_SIZE;
	return STATUS_SUCCESS;
}

STATUS SEQ_QUEUE_ENQUEUE(SEQ_QUEUE* queue, ELEM_TYPE data) {
	// 空间不够用，进行拓展
	if ((queue->rear + 1) % queue->max_size == queue->head) {
		ELEM_TYPE* old_base = queue->base;
		queue->base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (queue->max_size + SEQ_QUEUE_INC_SIZE));
		for (int i = 0; i < queue->max_size; i++) {
			queue->base[i] = old_base[i];
		}
		queue->max_size += SEQ_QUEUE_INC_SIZE;
		free(old_base);
	}
	queue->rear = (queue->rear + 1) % queue->max_size;
	queue->base[queue->rear] = data;
	return STATUS_SUCCESS;
}

STATUS SEQ_QUEUE_DEQUEUE(SEQ_QUEUE* queue, ELEM_TYPE* data) {
	if (queue->head == queue->rear) return STATUS_FAIL;
	queue->head = (queue->head + 1) % queue->max_size;
	*data = queue->base[queue->head];
	return STATUS_SUCCESS;
}

STATUS SEQ_QUEUE_GET_HEAD(SEQ_QUEUE* queue, ELEM_TYPE* data) {
	if (queue->head == queue->rear) return STATUS_FAIL;
	*data = queue->base[(queue->head + 1) % queue->max_size];
	return STATUS_SUCCESS;
}


STATUS LINK_QUEUE_INIT(LINK_QUEUE* queue) {
	return DL_LINK_LIST_INIT(queue);
}

STATUS LINK_QUEUE_ENQUEUE(LINK_QUEUE* queue, ELEM_TYPE data) {
	return DL_LINK_LIST_ADD(queue, data);
}

STATUS LINK_QUEUE_DEQUEUE(LINK_QUEUE* queue, ELEM_TYPE* data) {
	return DL_LINK_LIST_GET(queue, 0, data) | DL_LINK_LIST_DELETE(queue, 0);
}

STATUS LINK_QUEUE_GET_HEAD(LINK_QUEUE* queue, ELEM_TYPE* data) {
	return DL_LINK_LIST_GET(queue, 0, data);
}
