#include "graph_matrix.h"

STATUS GRAPH_MATRIX_INIT(GRAPH_MATRIX* graph, int nodeCount) {
	graph->nodeCount = nodeCount;
	graph->nodes = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * nodeCount);
	graph->relations = (int**)malloc(sizeof(int*) * nodeCount);
	for (int i = 0; i < nodeCount; i++) {
		graph->relations[i] = (int*)malloc(sizeof(int) * nodeCount);
	}
	for (int i = 0; i < nodeCount; i++) {
		graph->nodes[i] = ELEM_NULL;
	}
	for (int i = 0; i < nodeCount; i++) {
		for (int k = 0; k < nodeCount; k++) {
			graph->relations[i][k] = 0;
		}
	}
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_PUT_NODE_VALUE(GRAPH_MATRIX* graph, int idx, ELEM_TYPE value) {
	if (idx < 0 || idx > graph->nodeCount - 1) return STATUS_FAIL;
	graph->nodes[idx] = value;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_ADD_EDGE(GRAPH_MATRIX* graph, int fromIdx, int toIdx, int power) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	graph->relations[fromIdx][toIdx] = power;
	graph->relations[toIdx][fromIdx] = power;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_REMOVE_EDGE(GRAPH_MATRIX* graph, int fromIdx, int toIdx) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	graph->relations[fromIdx][toIdx] = 0;
	graph->relations[toIdx][fromIdx] = 0;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_ADD_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx, int power) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	graph->relations[fromIdx][toIdx] = power;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_REMOVE_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	graph->relations[fromIdx][toIdx] = 0;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_DESTROY(GRAPH_MATRIX* graph) {
	free(graph->nodes);
	graph->nodes = NULL;
	for (int i = 0; i < graph->nodeCount; i++) {
		free(graph->relations[i]);
	}
	free(graph->relations);
	graph->relations = NULL;
	graph->nodeCount = 0;
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_DFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE)) {
	SEQ_STACK idx_stack,val_stack;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount+1));

	SEQ_STACK_INIT(&idx_stack);
	SEQ_STACK_INIT(&val_stack);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	SEQ_STACK_PUSH(&idx_stack,0);
	SEQ_STACK_PUSH(&val_stack, graph->nodes[0]);
	while (idx_stack.base != idx_stack.top) {
		int idx,next_idx = -1;
		ELEM_TYPE val;
		SEQ_STACK_GET_TOP(&idx_stack,&idx);
		SEQ_STACK_GET_TOP(&val_stack, &val);
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				next_idx = i;
				break;
			}
		}
		if (next_idx > -1) {
			SEQ_STACK_PUSH(&idx_stack,next_idx);
			SEQ_STACK_PUSH(&val_stack, graph->nodes[next_idx]);
		}
		else {
			SEQ_STACK_POP(&idx_stack, &idx);
			SEQ_STACK_POP(&val_stack, &val);
		}
	}


	free(isAccess);
	SEQ_STACK_DESTORY(&val_stack);
	SEQ_STACK_DESTORY(&idx_stack);
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_BFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE)) {
	SEQ_QUEUE idx_queue, val_queue;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	SEQ_QUEUE_INIT(&idx_queue);
	SEQ_QUEUE_INIT(&val_queue);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	SEQ_QUEUE_ENQUEUE(&idx_queue, 0);
	SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[0]);
	while (idx_queue.head != idx_queue.rear) {
		int idx;
		ELEM_TYPE val;
		SEQ_QUEUE_DEQUEUE(&idx_queue,&idx);
		SEQ_QUEUE_DEQUEUE(&val_queue, &val);
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				SEQ_QUEUE_ENQUEUE(&idx_queue,i);
				SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[i]);
			}
		}
	}

	free(isAccess);
	SEQ_QUEUE_DESTORY(&idx_queue);
	SEQ_QUEUE_DESTORY(&val_queue);
	return STATUS_SUCCESS;
}
