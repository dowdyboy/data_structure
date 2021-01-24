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

// 算法思路与邻接矩阵版相同，注释参见graph_matrix.cpp
BIN_TREE* _graph_link_min_generated_tree_create_tree_helper(GRAPH_LINK* graph, int* edgeFromIdxes, int* edgeToIdxes, int idx, BOOLEAN* isAccess) {
	BIN_TREE* t = (BIN_TREE*)malloc(sizeof(BIN_TREE));
	t->data = graph->nodes[idx].data;
	t->left = NULL;
	t->right = NULL;
	t->leftIsChild = BOOLEAN_TRUE;
	t->rightIsChild = BOOLEAN_TRUE;
	int childCount = 0;
	BIN_TREE* firstChild = NULL;
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		if (!isAccess[i] && edgeFromIdxes[i] == idx) {
			isAccess[i] = BOOLEAN_TRUE;
			if (childCount == 0) {
				t->left = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i], isAccess);
				firstChild = t->left;
				childCount++;
			}
			else {
				firstChild->right = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i], isAccess);
				firstChild = firstChild->right;
				childCount++;
			}
		}
		else if (!isAccess[i] && edgeToIdxes[i] == idx) {
			isAccess[i] = BOOLEAN_TRUE;
			if (childCount == 0) {
				t->left = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeFromIdxes[i], isAccess);
				firstChild = t->left;
				childCount++;
			}
			else {
				firstChild->right = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeFromIdxes[i], isAccess);
				firstChild = firstChild->right;
				childCount++;
			}
		}
	}
	return t;
}

// 算法思路与邻接矩阵版相同，注释参见graph_matrix.cpp
BIN_TREE* _graph_link_min_generated_tree_create_tree(GRAPH_LINK* graph, int* edgeFromIdxes, int* edgeToIdxes, int idx) {
	BIN_TREE* t = NULL;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount - 1));

	for (int i = 0; i < graph->nodeCount - 1; i++) isAccess[i] = BOOLEAN_FALSE;

	t = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, idx, isAccess);

	free(isAccess);
	return t;
}

// 算法思路与邻接矩阵版相同，注释参见graph_matrix.cpp
STATUS GRAPH_LINK_MIN_GENERATED_TREE_PRIM(GRAPH_LINK* graph, BIN_TREE** tree, int startIdx) {
	if (startIdx < 0 || startIdx > graph->nodeCount - 1) return STATUS_FAIL;
	int currentTopIdx = startIdx;
	int* currentEdgePowerValues = (int*)malloc(sizeof(int) * graph->nodeCount);
	int* currentEdgePrevIdxes = (int*)malloc(sizeof(int) * graph->nodeCount);
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));
	int selectedEdgePos = 0;

	for (int i = 0; i < graph->nodeCount; i++) {
		currentEdgePowerValues[i] = INT_MAX;
		currentEdgePrevIdxes[i] = -1;
	}
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}

	while (selectedEdgePos < graph->nodeCount - 1) {
		int minIdx = 0, minPower = INT_MAX;
		for (int i = 0; i < graph->nodeCount; i++) {
			if (currentEdgePowerValues[i] > -1) {
				if (i == currentTopIdx) {
					currentEdgePowerValues[i] = -1;
				}
				else {
					// 找出当前最新访问节点到遍历节点的边的权值
					int a2bPower = 0, b2aPower = 0;
					GRAPH_LINK_ARC* p = graph->nodes[currentTopIdx].arc;
					while (p != NULL) {
						if (p->index == i) {
							a2bPower = p->power;
							break;
						}
						p = p->next;
					}
					p = graph->nodes[i].arc;
					while (p != NULL) {
						if (p->index == currentTopIdx) {
							b2aPower = p->power;
							break;
						}
						p = p->next;
					}
					if (a2bPower > 0
						&& b2aPower > 0
						&& a2bPower == b2aPower
						&& a2bPower < currentEdgePowerValues[i]) {
						currentEdgePowerValues[i] = a2bPower;
						currentEdgePrevIdxes[i] = currentTopIdx;
					}
				}
			}
			if (currentEdgePowerValues[i] > -1 && currentEdgePowerValues[i] < minPower) {
				minPower = currentEdgePowerValues[i];
				minIdx = i;
			}
		}
		selectedEdgeFromIdxes[selectedEdgePos] = currentEdgePrevIdxes[minIdx];
		selectedEdgeToIdxes[selectedEdgePos] = minIdx;
		currentTopIdx = minIdx;
		selectedEdgePos++;
	}

	*tree = _graph_link_min_generated_tree_create_tree(graph, selectedEdgeFromIdxes, selectedEdgeToIdxes, startIdx);

	free(currentEdgePowerValues);
	free(currentEdgePrevIdxes);
	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	return STATUS_SUCCESS;
}

// 算法思路与邻接矩阵版相同，注释参见graph_matrix.cpp
BOOLEAN _graph_link_min_generated_tree_has_loop(int* edgeFromIdxes, int* edgeToIdxes, int edgeCount) {
	SEQ_STACK s;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * edgeCount);
	int accessCount = 0;
	int currentStartIdx = -1, currentEndIdx = -1;

	SEQ_STACK_INIT(&s);
	for (int i = 0; i < edgeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	while (accessCount < edgeCount) {
		if (s.base == s.top) {
			int findIdx = -1;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					findIdx = i;
					break;
				}
			}
			if (findIdx > -1) {
				SEQ_STACK_PUSH(&s, edgeFromIdxes[findIdx]);
				currentStartIdx = edgeFromIdxes[findIdx];
				currentEndIdx = edgeToIdxes[findIdx];
				isAccess[findIdx] = BOOLEAN_TRUE;
				accessCount++;
			}
		}
		else {
			BOOLEAN isFindNext = BOOLEAN_FALSE;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					if (edgeFromIdxes[i] == currentEndIdx) {
						SEQ_STACK_PUSH(&s, currentEndIdx);
						currentEndIdx = edgeToIdxes[i];
						isAccess[i] = BOOLEAN_TRUE;
						accessCount++;
						isFindNext = BOOLEAN_TRUE;
						break;
					}
					else if (edgeToIdxes[i] == currentEndIdx) {
						SEQ_STACK_PUSH(&s, currentEndIdx);
						currentEndIdx = edgeFromIdxes[i];
						isAccess[i] = BOOLEAN_TRUE;
						accessCount++;
						isFindNext = BOOLEAN_TRUE;
						break;
					}
				}
			}
			if (!isFindNext) {
				SEQ_STACK_POP(&s, &currentEndIdx);
			}
			else {
				if (currentEndIdx == currentStartIdx) {
					free(isAccess);
					SEQ_STACK_DESTORY(&s);
					return BOOLEAN_TRUE;
				}
			}
		}
	}

	free(isAccess);
	SEQ_STACK_DESTORY(&s);
	return BOOLEAN_FALSE;
}

// 算法思路与邻接矩阵版相同，注释参见graph_matrix.cpp
STATUS GRAPH_LINK_MIN_GENERATED_TREE_KRUSKAL(GRAPH_LINK* graph, BIN_TREE** tree) {
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));
	int selectedEdgePos = 0;
	SEQ_LIST powerList, edgeFromIdxList, edgeToIdxList;

	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}
	SEQ_LIST_INIT(&powerList);
	SEQ_LIST_INIT(&edgeFromIdxList);
	SEQ_LIST_INIT(&edgeToIdxList);

	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = i; k < graph->nodeCount; k++) {
			// 找出两节点之间边的权值
			int a2bPower = 0, b2aPower = 0;
			GRAPH_LINK_ARC* p = graph->nodes[i].arc;
			while (p != NULL) {
				if (p->index == k) {
					a2bPower = p->power;
					break;
				}
				p = p->next;
			}
			p = graph->nodes[k].arc;
			while (p != NULL) {
				if (p->index == i) {
					b2aPower = p->power;
					break;
				}
				p = p->next;
			}
			if (i != k
				&& a2bPower > 0
				&& b2aPower > 0
				&& a2bPower == b2aPower) {
				SEQ_LIST_ADD(&powerList, a2bPower);
				SEQ_LIST_ADD(&edgeFromIdxList, i);
				SEQ_LIST_ADD(&edgeToIdxList, k);
			}
		}
	}

	for (int i = powerList.length; i > 0; i--) {
		BOOLEAN isSwap = BOOLEAN_FALSE;
		for (int k = 1; k < i; k++) {
			if (powerList.data[k] < powerList.data[k - 1]) {
				isSwap = BOOLEAN_TRUE;
				int tmp = powerList.data[k];
				powerList.data[k] = powerList.data[k - 1];
				powerList.data[k - 1] = tmp;
				tmp = edgeFromIdxList.data[k];
				edgeFromIdxList.data[k] = edgeFromIdxList.data[k - 1];
				edgeFromIdxList.data[k - 1] = tmp;
				tmp = edgeToIdxList.data[k];
				edgeToIdxList.data[k] = edgeToIdxList.data[k - 1];
				edgeToIdxList.data[k - 1] = tmp;
			}
		}
		if (!isSwap) break;
	}

	int edgeIdx = 0;
	while (selectedEdgePos < graph->nodeCount - 1 && edgeIdx < edgeFromIdxList.length) {
		selectedEdgeFromIdxes[selectedEdgePos] = edgeFromIdxList.data[edgeIdx];
		selectedEdgeToIdxes[selectedEdgePos] = edgeToIdxList.data[edgeIdx];
		edgeIdx++;
		selectedEdgePos++;
		if (_graph_link_min_generated_tree_has_loop(selectedEdgeFromIdxes, selectedEdgeToIdxes, selectedEdgePos)) {
			selectedEdgePos--;
		}
	}

	*tree = _graph_link_min_generated_tree_create_tree(graph, selectedEdgeFromIdxes, selectedEdgeToIdxes, 0);

	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	SEQ_LIST_DESTORY(&powerList);
	SEQ_LIST_DESTORY(&edgeFromIdxList);
	SEQ_LIST_DESTORY(&edgeToIdxList);
	return STATUS_SUCCESS;
}