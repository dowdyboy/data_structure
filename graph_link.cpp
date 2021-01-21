#include "graph_link.h"

STATUS GRAPH_LINK_INIT(GRAPH_LINK* graph, int nodeCount) {
	graph->nodeCount = nodeCount;
	graph->nodes = (GRAPH_LINK_NODE*)malloc(sizeof(GRAPH_LINK_NODE) * nodeCount);
	for (int i = 0; i < nodeCount; i++) {
		graph->nodes[i].index = i;
		graph->nodes[i].data = ELEM_NULL;
		graph->nodes[i].arc = NULL;
	}
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_PUT_NODE_VALUE(GRAPH_LINK* graph, int idx, ELEM_TYPE value) {
	if (idx < 0 || idx > graph->nodeCount - 1) return STATUS_FAIL;
	graph->nodes[idx].data = value;
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_ADD_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx, int power) {
	return GRAPH_LINK_ADD_ARC(graph,fromIdx,toIdx,power) 
		|| GRAPH_LINK_ADD_ARC(graph, toIdx, fromIdx, power);
}

STATUS GRAPH_LINK_REMOVE_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx) {
	return GRAPH_LINK_REMOVE_ARC(graph,fromIdx,toIdx) 
		|| GRAPH_LINK_REMOVE_ARC(graph, toIdx, fromIdx);
}

STATUS GRAPH_LINK_ADD_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx, int power) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	// 创建新的弧，并根据参数赋值
	GRAPH_LINK_ARC* p = NULL;
	GRAPH_LINK_ARC* fromArc = (GRAPH_LINK_ARC*)malloc(sizeof(GRAPH_LINK_ARC));
	fromArc->index = toIdx;
	fromArc->power = power;
	fromArc->next = NULL;
	// 将弧插入节点的弧链表末尾
	if (graph->nodes[fromIdx].arc != NULL) {
		p = graph->nodes[fromIdx].arc;
		while (p->next != NULL) p = p->next;
		p->next = fromArc;
	}
	else {
		graph->nodes[fromIdx].arc = fromArc;
	}
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_REMOVE_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx) {
	if (fromIdx < 0 || toIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx > graph->nodeCount - 1)
		return STATUS_FAIL;
	if (graph->nodes[fromIdx].arc != NULL) {
		GRAPH_LINK_ARC* p = graph->nodes[fromIdx].arc;
		// 如果要删除的弧在节点弧链表队首的情况
		if (p->index == toIdx) {
			graph->nodes[fromIdx].arc = p->next;
			free(p);
		}
		else {
			// 否则根据索引号在链表中找到该弧，并删除
			GRAPH_LINK_ARC* q = p->next;
			while (q != NULL) {
				if (q->index == toIdx) {
					p->next = q->next;
					free(q);
					break;
				}
				p = q;
				q = q->next;
			}
		}
	}
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_DESTROY(GRAPH_LINK* graph) {
	// 删除每个节点的弧链表中的每个弧
	for (int i = 0; i < graph->nodeCount; i++) {
		GRAPH_LINK_ARC* p = graph->nodes[i].arc;
		while (p != NULL) {
			GRAPH_LINK_ARC* q = p;
			p = p->next;
			free(q);
		}
	}
	// 删除全部节点
	free(graph->nodes);
	graph->nodes = NULL;
	graph->nodeCount = 0;
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_DFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE)) {
	SEQ_STACK idx_stack, val_stack;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// 初始化栈和访问标记
	SEQ_STACK_INIT(&idx_stack);
	SEQ_STACK_INIT(&val_stack);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// 将0号索引和数据入栈，如果栈不空，进入循环
	SEQ_STACK_PUSH(&idx_stack, 0);
	SEQ_STACK_PUSH(&val_stack, graph->nodes[0].data);
	while (idx_stack.base != idx_stack.top) {
		int idx, next_idx = -1;
		ELEM_TYPE val;
		SEQ_STACK_GET_TOP(&idx_stack, &idx);
		SEQ_STACK_GET_TOP(&val_stack, &val);
		// 获取栈顶索引和数据，如果该索引还未被访问，则进行访问并设置访问位
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// 遍历当前节点的弧链表，寻找被访问节点的第一个未被访问过的出边所指向的索引号
		GRAPH_LINK_ARC* p = graph->nodes[idx].arc;
		while (p != NULL) {
			if (!isAccess[p->index]) {
				next_idx = p->index;
				break;
			}
			p = p->next;
		}
		// 如果找到，将该索引和数据入栈，否则说明当前节点出边都已经被访问过了，弹出当前节点
		if (next_idx > -1) {
			SEQ_STACK_PUSH(&idx_stack, next_idx);
			SEQ_STACK_PUSH(&val_stack, graph->nodes[next_idx].data);
		}
		else {
			SEQ_STACK_POP(&idx_stack, &idx);
			SEQ_STACK_POP(&val_stack, &val);
		}
	}

	// 释放空间
	free(isAccess);
	SEQ_STACK_DESTORY(&val_stack);
	SEQ_STACK_DESTORY(&idx_stack);
	return STATUS_SUCCESS;
}


STATUS GRAPH_LINK_BFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE)) {
	SEQ_QUEUE idx_queue, val_queue;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// 初始化辅助队列和标记数组
	SEQ_QUEUE_INIT(&idx_queue);
	SEQ_QUEUE_INIT(&val_queue);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// 将0号索引节点入队，如果队不空，执行循环
	SEQ_QUEUE_ENQUEUE(&idx_queue, 0);
	SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[0].data);
	while (idx_queue.head != idx_queue.rear) {
		int idx;
		ELEM_TYPE val;
		SEQ_QUEUE_DEQUEUE(&idx_queue, &idx);
		SEQ_QUEUE_DEQUEUE(&val_queue, &val);
		// 头节点出队，如果该节点未被访问则进行访问并设置标记
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// 遍历当前节点的弧链表，将出边未被访问过的节点入队
		GRAPH_LINK_ARC* p = graph->nodes[idx].arc;
		while (p != NULL) {
			if (!isAccess[p->index]) {
				SEQ_QUEUE_ENQUEUE(&idx_queue, p->index);
				SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[p->index].data);
			}
			p = p->next;
		}
	}

	// 释放空间
	free(isAccess);
	SEQ_QUEUE_DESTORY(&idx_queue);
	SEQ_QUEUE_DESTORY(&val_queue);
	return STATUS_SUCCESS;
}