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
	// �����µĻ��������ݲ�����ֵ
	GRAPH_LINK_ARC* p = NULL;
	GRAPH_LINK_ARC* fromArc = (GRAPH_LINK_ARC*)malloc(sizeof(GRAPH_LINK_ARC));
	fromArc->index = toIdx;
	fromArc->power = power;
	fromArc->next = NULL;
	// ��������ڵ�Ļ�����ĩβ
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
		// ���Ҫɾ���Ļ��ڽڵ㻡������׵����
		if (p->index == toIdx) {
			graph->nodes[fromIdx].arc = p->next;
			free(p);
		}
		else {
			// ����������������������ҵ��û�����ɾ��
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
	// ɾ��ÿ���ڵ�Ļ������е�ÿ����
	for (int i = 0; i < graph->nodeCount; i++) {
		GRAPH_LINK_ARC* p = graph->nodes[i].arc;
		while (p != NULL) {
			GRAPH_LINK_ARC* q = p;
			p = p->next;
			free(q);
		}
	}
	// ɾ��ȫ���ڵ�
	free(graph->nodes);
	graph->nodes = NULL;
	graph->nodeCount = 0;
	return STATUS_SUCCESS;
}

STATUS GRAPH_LINK_DFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE)) {
	SEQ_STACK idx_stack, val_stack;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// ��ʼ��ջ�ͷ��ʱ��
	SEQ_STACK_INIT(&idx_stack);
	SEQ_STACK_INIT(&val_stack);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// ��0��������������ջ�����ջ���գ�����ѭ��
	SEQ_STACK_PUSH(&idx_stack, 0);
	SEQ_STACK_PUSH(&val_stack, graph->nodes[0].data);
	while (idx_stack.base != idx_stack.top) {
		int idx, next_idx = -1;
		ELEM_TYPE val;
		SEQ_STACK_GET_TOP(&idx_stack, &idx);
		SEQ_STACK_GET_TOP(&val_stack, &val);
		// ��ȡջ�����������ݣ������������δ�����ʣ�����з��ʲ����÷���λ
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// ������ǰ�ڵ�Ļ�����Ѱ�ұ����ʽڵ�ĵ�һ��δ�����ʹ��ĳ�����ָ���������
		GRAPH_LINK_ARC* p = graph->nodes[idx].arc;
		while (p != NULL) {
			if (!isAccess[p->index]) {
				next_idx = p->index;
				break;
			}
			p = p->next;
		}
		// ����ҵ�������������������ջ������˵����ǰ�ڵ���߶��Ѿ������ʹ��ˣ�������ǰ�ڵ�
		if (next_idx > -1) {
			SEQ_STACK_PUSH(&idx_stack, next_idx);
			SEQ_STACK_PUSH(&val_stack, graph->nodes[next_idx].data);
		}
		else {
			SEQ_STACK_POP(&idx_stack, &idx);
			SEQ_STACK_POP(&val_stack, &val);
		}
	}

	// �ͷſռ�
	free(isAccess);
	SEQ_STACK_DESTORY(&val_stack);
	SEQ_STACK_DESTORY(&idx_stack);
	return STATUS_SUCCESS;
}


STATUS GRAPH_LINK_BFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE)) {
	SEQ_QUEUE idx_queue, val_queue;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// ��ʼ���������кͱ������
	SEQ_QUEUE_INIT(&idx_queue);
	SEQ_QUEUE_INIT(&val_queue);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// ��0�������ڵ���ӣ�����Ӳ��գ�ִ��ѭ��
	SEQ_QUEUE_ENQUEUE(&idx_queue, 0);
	SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[0].data);
	while (idx_queue.head != idx_queue.rear) {
		int idx;
		ELEM_TYPE val;
		SEQ_QUEUE_DEQUEUE(&idx_queue, &idx);
		SEQ_QUEUE_DEQUEUE(&val_queue, &val);
		// ͷ�ڵ���ӣ�����ýڵ�δ����������з��ʲ����ñ��
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// ������ǰ�ڵ�Ļ�����������δ�����ʹ��Ľڵ����
		GRAPH_LINK_ARC* p = graph->nodes[idx].arc;
		while (p != NULL) {
			if (!isAccess[p->index]) {
				SEQ_QUEUE_ENQUEUE(&idx_queue, p->index);
				SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[p->index].data);
			}
			p = p->next;
		}
	}

	// �ͷſռ�
	free(isAccess);
	SEQ_QUEUE_DESTORY(&idx_queue);
	SEQ_QUEUE_DESTORY(&val_queue);
	return STATUS_SUCCESS;
}

// �㷨˼·���ڽӾ������ͬ��ע�Ͳμ�graph_matrix.cpp
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

// �㷨˼·���ڽӾ������ͬ��ע�Ͳμ�graph_matrix.cpp
BIN_TREE* _graph_link_min_generated_tree_create_tree(GRAPH_LINK* graph, int* edgeFromIdxes, int* edgeToIdxes, int idx) {
	BIN_TREE* t = NULL;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount - 1));

	for (int i = 0; i < graph->nodeCount - 1; i++) isAccess[i] = BOOLEAN_FALSE;

	t = _graph_link_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, idx, isAccess);

	free(isAccess);
	return t;
}

// �㷨˼·���ڽӾ������ͬ��ע�Ͳμ�graph_matrix.cpp
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
					// �ҳ���ǰ���·��ʽڵ㵽�����ڵ�ıߵ�Ȩֵ
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

// �㷨˼·���ڽӾ������ͬ��ע�Ͳμ�graph_matrix.cpp
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

// �㷨˼·���ڽӾ������ͬ��ע�Ͳμ�graph_matrix.cpp
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
			// �ҳ����ڵ�֮��ߵ�Ȩֵ
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