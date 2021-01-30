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
	// ��ϵȨֵ��ֵ��ʼ������Ϊ0����ʾ�ޱ�
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

	// ��ʼ��ջ�ͷ��ʱ��
	SEQ_STACK_INIT(&idx_stack);
	SEQ_STACK_INIT(&val_stack);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// ��0��������������ջ�����ջ���գ�����ѭ��
	SEQ_STACK_PUSH(&idx_stack,0);
	SEQ_STACK_PUSH(&val_stack, graph->nodes[0]);
	while (idx_stack.base != idx_stack.top) {
		int idx,next_idx = -1;
		ELEM_TYPE val;
		SEQ_STACK_GET_TOP(&idx_stack,&idx);
		SEQ_STACK_GET_TOP(&val_stack, &val);
		// ��ȡջ�����������ݣ������������δ�����ʣ�����з��ʲ����÷���λ
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// Ѱ�ұ����ʽڵ�ĵ�һ��δ�����ʹ��ĳ�����ָ���������
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				next_idx = i;
				break;
			}
		}
		// ����ҵ�������������������ջ������˵����ǰ�ڵ���߶��Ѿ������ʹ��ˣ�������ǰ�ڵ�
		if (next_idx > -1) {
			SEQ_STACK_PUSH(&idx_stack,next_idx);
			SEQ_STACK_PUSH(&val_stack, graph->nodes[next_idx]);
		}
		else {
			SEQ_STACK_POP(&idx_stack, &idx);
			SEQ_STACK_POP(&val_stack, &val);
		}
	}

	// �ͷ�ջ�ͱ�ǿռ�
	free(isAccess);
	SEQ_STACK_DESTORY(&val_stack);
	SEQ_STACK_DESTORY(&idx_stack);
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_BFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE)) {
	SEQ_QUEUE idx_queue, val_queue;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// ��ʼ���������кͱ������
	SEQ_QUEUE_INIT(&idx_queue);
	SEQ_QUEUE_INIT(&val_queue);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// ��0�������ڵ���ӣ�����Ӳ��գ�ִ��ѭ��
	SEQ_QUEUE_ENQUEUE(&idx_queue, 0);
	SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[0]);
	while (idx_queue.head != idx_queue.rear) {
		int idx;
		ELEM_TYPE val;
		SEQ_QUEUE_DEQUEUE(&idx_queue,&idx);
		SEQ_QUEUE_DEQUEUE(&val_queue, &val);
		// ͷ�ڵ���ӣ�����ýڵ�δ����������з��ʲ����ñ��
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// ������ǰ�ڵ�δ�����ʹ��ĳ��ߺ�̽ڵ㣬���
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				SEQ_QUEUE_ENQUEUE(&idx_queue,i);
				SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[i]);
			}
		}
	}

	// �ͷſռ�
	free(isAccess);
	SEQ_QUEUE_DESTORY(&idx_queue);
	SEQ_QUEUE_DESTORY(&val_queue);
	return STATUS_SUCCESS;
}

// ������ѡ��ıߣ���ʼ�ڵ���������ֹ�ڵ����������������������ֵܶ�������ʽ��
BIN_TREE* _graph_matrix_min_generated_tree_create_tree_helper(GRAPH_MATRIX* graph, int* edgeFromIdxes, int* edgeToIdxes, int idx, BOOLEAN* isAccess) {
	BIN_TREE* t = (BIN_TREE*)malloc(sizeof(BIN_TREE));
	t->data = graph->nodes[idx];
	t->left = NULL;
	t->right = NULL;
	t->leftIsChild = BOOLEAN_TRUE;
	t->rightIsChild = BOOLEAN_TRUE;
	int childCount = 0;
	BIN_TREE* firstChild = NULL;
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		// �������бߣ�ѡ��δ�����ʹ���������ʼ�ڵ���������ֹ�ڵ�����Ϊ��ǰ�ڵ�ı�
		if (!isAccess[i] && edgeFromIdxes[i] == idx) {
			// ���øñߵķ��ʱ��
			isAccess[i] = BOOLEAN_TRUE;
			if (childCount == 0) {
				// ��������ɵĵ�һ���ڵ㣬�ݹ�������ӽڵ㣬�����������ϣ���������������ָ�루�������ӣ�
				t->left = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i],isAccess);
				firstChild = t->left;
				childCount++;
			}
			else {
				// ����������ɵ�һ���ڵ㣬˵�����Ǹýڵ�ĵ�һ�����ӣ��ݹ���ã������ɵĽڵ��������������������
				// ������������ָ������
				firstChild->right = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i],isAccess);
				firstChild = firstChild->right;
				childCount++;
			}
		}
		else if (!isAccess[i] && edgeToIdxes[i] == idx) {
			// ͬ�ϣ�������Ѱ����ʼ�ڵ������뵱ǰ�ڵ�����һ�µģ�������Ѱ�ҽ����ڵ������뵱ǰ�ڵ�����һ�µ�
			isAccess[i] = BOOLEAN_TRUE;
			if (childCount == 0) {
				t->left = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeFromIdxes[i],isAccess);
				firstChild = t->left;
				childCount++;
			}
			else {
				firstChild->right = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeFromIdxes[i],isAccess);
				firstChild = firstChild->right;
				childCount++;
			}
		}
	}
	return t;
}

// �������İ�װ��������Ҫ�ṩ���ʱ�ǵĴ������ͷ�
BIN_TREE* _graph_matrix_min_generated_tree_create_tree(GRAPH_MATRIX* graph,int* edgeFromIdxes,int* edgeToIdxes,int idx) {
	BIN_TREE* t = NULL;
	// �����߷��ʱ��
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount - 1));

	for (int i = 0; i < graph->nodeCount - 1; i++) isAccess[i] = BOOLEAN_FALSE;

	// ִ���������߼�
	t = _graph_matrix_min_generated_tree_create_tree_helper(graph,edgeFromIdxes,edgeToIdxes,idx,isAccess);

	// �ͷű��
	free(isAccess);
	return t;
}

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_PRIM(GRAPH_MATRIX* graph, BIN_TREE** tree, int startIdx) {
	if (startIdx < 0 || startIdx > graph->nodeCount - 1) return STATUS_FAIL;
	// ������������
	int currentTopIdx = startIdx;  // ��ǰ���·��ʵ��Ľڵ������
	int* currentEdgePowerValues = (int*)malloc(sizeof(int) * graph->nodeCount);  // ��ǰ�ҿ���ÿ���ڵ��ϵıߵ�Ȩֵ
	int* currentEdgePrevIdxes = (int*)malloc(sizeof(int) * graph->nodeCount);  // ��ǰÿ���ڵ�ҿ��ߵ���ֹ�ڵ�����
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // �Ѿ�ѡ���ıߵ���ʼ�ڵ�����
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // �Ѿ�ѡ���ıߵ���ֹ�ڵ�����
	int selectedEdgePos = 0;  // �Ѿ�ѡ���ıߵĸ���

	// �ҿ��ߵ�Ȩֵ��ʼ����Ϊ����󣬶�Ӧ����ֹ�ڵ���������Ϊ-1
	for (int i = 0; i < graph->nodeCount; i++) {
		currentEdgePowerValues[i] = INT_MAX;
		currentEdgePrevIdxes[i] = -1;
	}
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}

	// �����û�ҵ��㹻�ıߣ�n-1����ִ�д�ѭ��
	while (selectedEdgePos < graph->nodeCount - 1) {
		int minIdx = 0, minPower = INT_MAX;
		// ����ÿ���ڵ�Ĺҿ���
		for (int i = 0; i < graph->nodeCount; i++) {
			// ����ýڵ�Ĺҿ��߻�δ����ȷ��
			if (currentEdgePowerValues[i] > -1) {
				if (i == currentTopIdx) {
					// ��������ڵ������������ѡ��Ĺҿ��ߵ���ֹ����������Ϊ�ñ�Ϊһ����С�ߣ����ñ�ȷ��
					// ����˵��������ڵ������Ϊ��ǰ���µķ��ʵ��Ľڵ�����
					currentEdgePowerValues[i] = -1;
				}
				else {
					// �����ǰ���½ڵ㵽�����ڵ���ڱߣ��ұ���ȨֵС�ڵ�ǰ�����ڵ�ҿ��ߵ�Ȩֵ
					// ����¹ҿ��ߵ�Ȩֵ���ͽ��ҿ��ߵ���ֹ������Ϊ��ǰ���½ڵ�����
					if (graph->relations[currentTopIdx][i] > 0
						&& graph->relations[i][currentTopIdx] > 0
						&& graph->relations[currentTopIdx][i] == graph->relations[i][currentTopIdx]
						&& graph->relations[currentTopIdx][i] < currentEdgePowerValues[i]) {
						currentEdgePowerValues[i] = graph->relations[currentTopIdx][i];
						currentEdgePrevIdxes[i] = currentTopIdx;
					}
				}
			}
			// ����������¹ҿ��ߵ���Ϣ��Ȼ���ж��Ƿ�С�ڵ�ǰ��һ�ֱ������СȨֵ
			// ������С�Ĺҿ���Ȩֵ�ͽڵ�����
			if (currentEdgePowerValues[i] > -1 && currentEdgePowerValues[i] < minPower) {
				minPower = currentEdgePowerValues[i];
				minIdx = i;
			}
		}
		// ����ѡ�����С�ҿ��߶�Ӧ�Ľڵ�������������С�ߵ���ʼ�ڵ���������ֹ�ڵ�����
		// �����µ�ǰ���·��ʽڵ�����Ϊ��С�߶�Ӧ�Ľڵ�����
		selectedEdgeFromIdxes[selectedEdgePos] = currentEdgePrevIdxes[minIdx];
		selectedEdgeToIdxes[selectedEdgePos] = minIdx;
		currentTopIdx = minIdx;
		selectedEdgePos++;
	}

	// ����ѡ�����С�ߣ�������С������
	*tree = _graph_matrix_min_generated_tree_create_tree(graph, selectedEdgeFromIdxes, selectedEdgeToIdxes, startIdx);
	
	// �ͷſռ�
	free(currentEdgePowerValues);
	free(currentEdgePrevIdxes);
	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	return STATUS_SUCCESS;
}

// ����ÿ���ߵ���ʼ����ֹ�������ж�ͼ�Ƿ���ڻ�·
BOOLEAN _graph_matrix_min_generated_tree_has_loop(int* edgeFromIdxes,int* edgeToIdxes,int edgeCount) {
	// ��������
	SEQ_STACK s;  // ���浱ǰ���ʽڵ�֮ǰ���ʹ��Ľڵ������
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * edgeCount);  // ���Ƿ���ʹ��˵ı��
	int accessCount = 0;  // �Ѿ����ʹ��ıߵĸ���
	int currentStartIdx = -1, currentEndIdx = -1;  // �����ʵĵ�һ���ڵ�����������·��ʵĽڵ������

	// ������ʼ��
	SEQ_STACK_INIT(&s);
	for (int i = 0; i < edgeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// �����δ�������бߣ���ִ�����ѭ��
	while (accessCount < edgeCount) {
		if (s.base == s.top) {
			// ����ǿ�ʼ��һ�ַ��ʣ�ջ�գ�����ѡ��һ��δ�����ʹ��ı�
			int findIdx = -1;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					findIdx = i;
					break;
				}
			}
			if (findIdx > -1) {
				// ����ѡ�ߵĿ�ʼ�ڵ�������ջ��������Ϊ��һ�ֵ�һ���ڵ�
				SEQ_STACK_PUSH(&s, edgeFromIdxes[findIdx]);
				currentStartIdx = edgeFromIdxes[findIdx];
				// ����ѡ�ߵ���ֹ�ڵ���������Ϊ��ǰ���·��ʽڵ������
				currentEndIdx = edgeToIdxes[findIdx];
				// ���øñ߷��ʱ�ǣ����Ӽ�����
				isAccess[findIdx] = BOOLEAN_TRUE;
				accessCount++;
			}
		}
		else {
			// ������ǿ�ʼ��һ�ַ��ʣ�����δ�����ʹ��ı�
			BOOLEAN isFindNext = BOOLEAN_FALSE;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					// ����ñߵ���ʼ��������ֹ�������ڵ�ǰ���·��ʽڵ�����
					// ����ǰ���·��ʽڵ�������켣ջ�������Ϊ�����ߵ���ʼ/��ֹ����
					// �����Ӽ����������ñ��
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
				// ���������ı�����û�з��ʵ��µıߣ���ջ�е�������ķ���������Ϊ���·��ʽڵ�����
				SEQ_STACK_POP(&s, &currentEndIdx);
			}
			else {
				// �������ı����з��ʵ����µıߣ��ж��Ƿ񹹳ɻ�·
				// ���Ƿ���һ�ֵ�һ���ڵ������������·��ʽڵ�����
				// ������ɻ�·�����ͷſռ䲢����
				if (currentEndIdx == currentStartIdx) {
					free(isAccess);
					SEQ_STACK_DESTORY(&s);
					return BOOLEAN_TRUE;
				}
			}
		}
	}
	
	// û�л�·���ͷſռ䲢����
	free(isAccess);
	SEQ_STACK_DESTORY(&s);
	return BOOLEAN_FALSE;
}

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_KRUSKAL(GRAPH_MATRIX* graph, BIN_TREE** tree) {
	// ��������
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // ��ѡ��С�ߵ���ʼ�ڵ�����
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // ��ѡ��С�ߵ���ֹ�ڵ�����
	int selectedEdgePos = 0;  // ��ѡ��С�ߵĸ���
	SEQ_LIST powerList,edgeFromIdxList,edgeToIdxList;  // ���б�Ȩֵ/��ʼ�ڵ�����/��ֹ�ڵ������б�

	// ������ʼ��
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}
	SEQ_LIST_INIT(&powerList);
	SEQ_LIST_INIT(&edgeFromIdxList);
	SEQ_LIST_INIT(&edgeToIdxList);

	// ����ͼȫ��ߣ�����Ȩֵ/��ʼ�ڵ�����/��ֹ�ڵ����������б�
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = i; k < graph->nodeCount; k++) {
			if (i != k 
				&& graph->relations[i][k] > 0 
				&& graph->relations[k][i] > 0 
				&& graph->relations[i][k] == graph->relations[k][i]) {
				SEQ_LIST_ADD(&powerList, graph->relations[i][k]);
				SEQ_LIST_ADD(&edgeFromIdxList, i);
				SEQ_LIST_ADD(&edgeToIdxList, k);
			}
		}
	}

	// ð�����򣨿��Ż�Ϊ�������򣩣�����Ȩֵ��С��������
	for (int i = powerList.length; i > 0 ; i--) {
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

	// ���δѡ���㹻�ߣ���ִ�и�ѭ��
	int edgeIdx = 0;
	while (selectedEdgePos < graph->nodeCount - 1 && edgeIdx < edgeFromIdxList.length) {
		// ���԰�˳����б���ѡ��һ����
		selectedEdgeFromIdxes[selectedEdgePos] = edgeFromIdxList.data[edgeIdx];
		selectedEdgeToIdxes[selectedEdgePos] = edgeToIdxList.data[edgeIdx];
		edgeIdx++;
		selectedEdgePos++;
		// ���ѡ��ñߺ��л�·�������
		if (_graph_matrix_min_generated_tree_has_loop(selectedEdgeFromIdxes, selectedEdgeToIdxes, selectedEdgePos)) {
			selectedEdgePos--;
		}
	}

	// ����ѡ��ıߴ�����С������
	*tree = _graph_matrix_min_generated_tree_create_tree(graph,selectedEdgeFromIdxes,selectedEdgeToIdxes,0);

	// �ͷſռ�
	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	SEQ_LIST_DESTORY(&powerList);
	SEQ_LIST_DESTORY(&edgeFromIdxList);
	SEQ_LIST_DESTORY(&edgeToIdxList);
	return STATUS_SUCCESS;
}


STATUS GRAPH_MATRIX_SHORTEST_ROUTE_DIJKSTRA(GRAPH_MATRIX* graph, int idx, int*** result) {
	if (idx < 0 || idx > graph->nodeCount - 1) return STATUS_FAIL;
	// ��������
	int currentNodeIdx = idx;  // ��ǰ�������Ľڵ�����
	int currentFullPower = 0;  // ��Դ�㵽��ǰ�����ڵ�·�����ۼ�Ȩֵ
	int* currentNodePowers = (int*)malloc(sizeof(int) * graph->nodeCount);  // ��ǰ��Դ�㵽�����ڵ��·�����ۼ�Ȩֵ�����ڳ������
	int* currentRecordPowers = (int*)malloc(sizeof(int) * graph->nodeCount);  // ��ǰ��Դ�㵽�����ڵ��·�����ۼ�Ȩֵ��¼
	int** currentRoutes = (int**)malloc(sizeof(int*) * graph->nodeCount);  // ��ǰ�ӵ�Դ�㵽�����ڵ��·����¼
	int selectedRouteCount = 0;  // �Ѿ��ҵ������·���ĸ���

	// ��ʼ����������
	for (int i = 0; i < graph->nodeCount; i++) {
		// ��ʼ����Ϊ����󣻼�¼ֵ����Ǵ��Լ����Լ�������Ϊ0�������ʼ����Ϊ-1����ʾ���ɴ
		currentNodePowers[i] = INT_MAX;
		currentRecordPowers[i] = i == idx ? 0 : -1;
	}
	for (int i = 0; i < graph->nodeCount; i++) currentRoutes[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// ·����¼��ʼȫ��Ϊ-1
			currentRoutes[i][k] = -1;
		}
	}

	// �����û���ҵ��㹻�����·����ִ������ѭ��
	while (selectedRouteCount < graph->nodeCount - 1) {
		// ���ñ�ǣ����ڼ�¼����Ѱ�ҵ���СȨֵ�Ͷ�Ӧָ��Ľڵ�����
		int minPower = INT_MAX, minIdx = -1;
		for (int i = 0; i < graph->nodeCount; i++) {
			if (currentNodeIdx == i) {
				// ������ʵ����ǵ�ǰ�������Ľڵ㣬�����ýڵ��Ӧ��Ȩֵ����Ϊ-1����ʾ������ڵ�����·���Ѿ��ҵ�
				currentNodePowers[i] = -1;
			}
			else {
				// �����i�ڵ�����·����û���ҵ�
				if (currentNodePowers[i] > -1) {
					// �ж�����ӵ�ǰ�����ڵ㵽i�ڵ��Ƿ��л��������ۼ�ȨֵС�ڵ�ǰ���ýڵ�����¼��Ȩֵ
					if (graph->relations[currentNodeIdx][i] > 0 
						&& currentFullPower + graph->relations[currentNodeIdx][i] < currentNodePowers[i]) {
						// ���µ�i�ڵ�ļ�¼Ȩֵ
						currentNodePowers[i] = currentFullPower + graph->relations[currentNodeIdx][i];
						currentRecordPowers[i] = currentNodePowers[i];
						// ���µ�i�ڵ��·����¼
						if (currentNodeIdx == idx) {
							// ����ǵ�һ�μ�¼����¼�µ�Դ���i�ڵ�
							currentRoutes[i][0] = currentNodeIdx;
							currentRoutes[i][1] = i;
						}
						else {
							// ������ǵ�һ�μ�¼�����Ƚ��ӵ�Դ�㵽��ǰ�����ڵ��·����¼���Ƶ��ӵ�Դ�㵽i�ڵ��λ����
							// Ȼ�����ڵ�i�ڵ�·����¼��ĩβ����i�ڵ������
							int newIdx = -1;
							for (int k = 0; k < graph->nodeCount; k++) {
								currentRoutes[i][k] = currentRoutes[currentNodeIdx][k];
								if (currentRoutes[currentNodeIdx][k] == -1 && newIdx == -1) {
									newIdx = k;
								}
							}
							currentRoutes[i][newIdx] = i;
						}
					}
					// �����i�ڵ���ۼ�ȨֵС�ڼ�¼����СȨֵ���������С��¼
					if (currentNodePowers[i] <= minPower) {
						minPower = currentNodePowers[i];
						minIdx = i;
					}
				}
			}
		}
		// �������ֱ�����ͨ����С��ǣ����µ�ǰ�����ڵ������Ͷ�Ӧ���ۼ�Ȩֵ�������Ӽ�����
		if (minIdx > -1) {
			selectedRouteCount++;
			currentNodeIdx = minIdx;
			currentFullPower = minPower;
		}
	}

	// ����������ά������ʽ����0��Ϊ�ӵ�Դ�㵽i�ڵ���ۼ�Ȩֵ���ӵ�1�п�ʼΪ��i�ڵ��·����¼��ֱ��·����¼ֵΪ-1����
	*result = (int**)malloc(sizeof(int*) * graph->nodeCount);
	for (int i = 0; i < graph->nodeCount; i++) {
		(*result)[i] = (int*)malloc(sizeof(int) * (graph->nodeCount + 1));
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount + 1; k++) {
			(*result)[i][k] = k == 0 ? currentRecordPowers[i] : currentRoutes[i][k - 1];
		}
	}

	// �ͷſռ�
	free(currentNodePowers);
	free(currentRecordPowers);
	for (int i = 0; i < graph->nodeCount; i++) {
		free(currentRoutes[i]);
	}
	free(currentRoutes);
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD(GRAPH_MATRIX* graph, int*** powerResult, int*** pathResult) {
	// �����ۼ�Ȩֵ���󣬺�·����¼����
	int** powerMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);
	int** pathMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);

	// ����ͼ��ʼ������
	for (int i = 0; i < graph->nodeCount; i++) {
		powerMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
		pathMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// ����л�����Ȩֵ�����Ӧλ������Ϊ����Ȩֵ����������Ϊ�����
			powerMatrix[i][k] = graph->relations[i][k] > 0 ? graph->relations[i][k] : INT_MAX;
			// ����ǣ�i��i��������Խǣ���λ�ã�����Ȩֵ����ֵΪ0
			if (i == k) powerMatrix[i][k] = 0;
			// ���i��k�л���·�������i��k��λ������Ϊi����ʾ��k�ڵ��ǰ�ýڵ�Ϊi����������Ϊ-1��ʾ���ɴ�
			pathMatrix[i][k] = graph->relations[i][k] > 0 ? i : -1;
		}
	}

	// ͼ��n���ڵ㣬��ִ��n�α���
	for (int x = 0; x < graph->nodeCount; x++) {
		for (int i = 0; i < graph->nodeCount; i++) {
			// i����x��ִ����ѭ������Ϊ��i����i�ٵ�k�ۼ�·��Ȩֵ�������κα仯
			if (i != x) {
				for (int k = 0; k < graph->nodeCount; k++) {
					// ͬ��k����x��i����kҲ��ִ���ڲ��߼�
					if (k != x && i != k) {
						// ���i��x�ɴx��k�ɴ���������ε��ۼ�Ȩֵ�ȵ�ǰ��i��k���ۼ�ȨֵС
						// ����¶�Ӧλ��Ȩֵ�����ֵΪ��С��ֵ
						// ���¶�Ӧλ��·�������ֵΪ��x��k��ǰ�ýڵ������
						int i2kPower = powerMatrix[i][k];
						int i2xPower = powerMatrix[i][x];
						int x2kPower = powerMatrix[x][k];
						if (i2xPower != INT_MAX 
							&& x2kPower != INT_MAX 
							&& i2xPower + x2kPower < i2kPower) {
							powerMatrix[i][k] = i2xPower + x2kPower;
							pathMatrix[i][k] = pathMatrix[x][k];
						}
					}
				}
			}
		}
	}

	// ������
	*powerResult = powerMatrix;
	*pathResult = pathMatrix;

	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD_GET_RESULT(GRAPH_MATRIX* graph, int** powerMatrix, int** pathMatrix, int fromIdx, int toIdx, int** result) {
	if (fromIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx < 0 || toIdx > graph->nodeCount - 1 )
		return STATUS_FAIL;
	// ����·����¼����
	int* route = (int*)malloc(sizeof(int) * (graph->nodeCount + 1));
	int routeIdx = 1,beforeIdx = -1;

	// ��ʼ��������·����¼����ֵ����Ϊ-1
	for (int i = 0; i < graph->nodeCount + 1; i++) route[i] = -1;

	// 0��ַ��¼����ʼ�ڵ㵽��ֹ�ڵ���ۼ�Ȩֵ
	route[0] = powerMatrix[fromIdx][toIdx] != INT_MAX? powerMatrix[fromIdx][toIdx]:-1;
	// ������Ǵ������������Ҵ���ʼ�ڵ㵽��ֹ�ڵ�ɴ�
	if (fromIdx != toIdx && powerMatrix[fromIdx][toIdx] != INT_MAX) {
		// �Ƚ���ֹ�ڵ��¼
		route[routeIdx++] = toIdx;
		// �ٴ�·���������ҳ�����ʼ����ֹ�ڵ��ǰ�ýڵ�����������¼
		beforeIdx = pathMatrix[fromIdx][toIdx];
		route[routeIdx++] = beforeIdx;
		// ���ǰ�ýڵ㲻����ʼ�ڵ㣬���ٲ��Ҵ���ʼ�ڵ㵽ǰ�ýڵ��ǰ�ýڵ㣬����¼
		while (beforeIdx != fromIdx) {
			beforeIdx = pathMatrix[fromIdx][beforeIdx];
			route[routeIdx++] = beforeIdx;
		}
		// �������ϼ�¼�ǵ����¼������Ĵ����ǽ���¼����
		beforeIdx = 1;
		routeIdx--;
		while (beforeIdx < routeIdx) {
			int tmp = route[beforeIdx];
			route[beforeIdx] = route[routeIdx];
			route[routeIdx] = tmp;
			beforeIdx++;
			routeIdx--;
		}
	}

	// ������
	*result = route;
	
	return STATUS_SUCCESS;
}

// �ӻ��Ĺ�ϵ�������ҵ������������һ���ڵ�����
int _graph_matrix_topology_sort_find_next_node(int** arcMatrix,int nodeCount,int* isAccess) {
	int findIdx = -1;
	// Ѱ����ȣ������е��У�Ϊ0�Ľڵ������
	for (int k = 0; k < nodeCount; k++) {
		// ������k�ڵ㻹δ��ѡ��
		if (!isAccess[k]) {
			BOOLEAN isFind = BOOLEAN_TRUE;
			for (int i = 0; i < nodeCount; i++) {
				// �ж�k�е��������Ƿ�Ϊ0����k�ڵ�����Ϊ0��
				if (arcMatrix[i][k] != 0) {
					isFind = BOOLEAN_FALSE;
					break;
				}
			}
			// ����ҵ��ˣ����÷��ʱ��
			if (isFind) {
				isAccess[k] = BOOLEAN_TRUE;
				findIdx = k;
				break;
			}
		}
	}
	if (findIdx > -1) {
		// �ҵ��ˣ����ýڵ�����г���ȫ��ɾ��
		for (int k = 0; k < nodeCount; k++) {
			arcMatrix[findIdx][k] = 0;
		}
	}
	return findIdx;
}

STATUS GRAPH_MATRIX_TOPOLOGY_SORT(GRAPH_MATRIX* graph, int** result) {
	// �������
	int* topoArray = (int*)malloc(sizeof(int) * graph->nodeCount);  // ��������ڵ���������б�
	int topoArrayPos = 0;  // ����б�ǰ�洢��λ��
	int** arcMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);  // ���Ĺ�ϵ����
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * graph->nodeCount);  // �ڵ��Ƿ��Ѿ�����ı�־
	int selectedNodeCount = 0;  // �Ѿ�����Ľڵ����
	int findIdx = -1;  // �ҵ��Ĵ�����ڵ������

	// ��ʼ������
	for (int i = 0; i < graph->nodeCount; i++) {
		topoArray[i] = -1;
		isAccess[i] = BOOLEAN_FALSE;
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		arcMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// ����ϵֱ�ӿ���ͼ�Ĺ�ϵ����
			arcMatrix[i][k] = graph->relations[i][k];
		}
	}

	// Ѱ�ҷ���Ҫ��Ľڵ��������ֱ��Ѱ��ʧ��
	findIdx = _graph_matrix_topology_sort_find_next_node(arcMatrix,graph->nodeCount,isAccess);
	while (findIdx > -1) {
		topoArray[topoArrayPos++] = findIdx;
		selectedNodeCount++;
		findIdx = _graph_matrix_topology_sort_find_next_node(arcMatrix, graph->nodeCount,isAccess);
	}

	// �ͷſռ�
	for (int i = 0; i < graph->nodeCount; i++) {
		free(arcMatrix[i]);
	}
	free(arcMatrix);
	free(isAccess);
	if (selectedNodeCount < graph->nodeCount) {
		// �������Ľڵ����С���ܸ�����˵�����нڵ��޷�������ͼ���л�����������ʧ��
		free(topoArray);
		return STATUS_FAIL;
	}
	else {
		// ����ɹ���������
		*result = topoArray;
		return STATUS_SUCCESS;
	}
}

STATUS GRAPH_MATRIX_KEY_ROUTE(GRAPH_MATRIX* graph, int** result) {
	int* topoResult = NULL;  // �洢����������
	int topoIdx = 0;

	if (GRAPH_MATRIX_TOPOLOGY_SORT(graph, &topoResult) == STATUS_SUCCESS) {
		// �����������ɹ�����ʼѰ�ҹؼ�·��
		int* nodeE = (int*)malloc(sizeof(int) * graph->nodeCount);  // �洢ÿ���ڵ�����緢��ʱ��
		int* nodeL = (int*)malloc(sizeof(int) * graph->nodeCount);  // �洢ÿ���ڵ��������ʱ��
		BOOLEAN* isKeyNode = (BOOLEAN*)malloc(sizeof(BOOLEAN) * graph->nodeCount);  // ��ǽڵ��Ƿ�Ϊ�ؼ��ڵ�
		int* keyRoute = (int*)malloc(sizeof(int) * graph->nodeCount);  // �洢Ѱ�ҵĹؼ�·��
		int keyRoutePos = 0;

		// ������ʼ��
		for (int i = 0; i < graph->nodeCount; i++) {
			nodeE[i] = 0;
			nodeL[i] = 0;
			isKeyNode[i] = BOOLEAN_FALSE;
			keyRoute[i] = -1;
		}

		// ����ڵ����緢��ʱ�䣬�������������ǰ����
		while (topoIdx < graph->nodeCount && topoResult[topoIdx] > -1) {
			int curIdx = topoResult[topoIdx];  // ��������ǰ�ڵ�����
			int maxPower = -1;  // ��¼����ʱ��ֵ
			for (int i = 0; i < graph->nodeCount; i++) {
				// �����ǰ�ڵ��ǰ�������緢��ʱ����ϴӸ�ǰ������ǰ�ڵ��ʱ���������¼�����ʱ��
				// ���¼�¼���ʱ��
				if (graph->relations[i][curIdx] > 0) {
					if (nodeE[i] + graph->relations[i][curIdx] > maxPower) {
						maxPower = nodeE[i] + graph->relations[i][curIdx];
					}
				}
			}
			// ��������ʱ��ֵ��������Ϊ��ǰ�ڵ�����緢��ʱ�䣬��������Ϊ0����һ���ڵ㣩
			nodeE[curIdx] = maxPower == -1 ? 0 : maxPower;
			topoIdx++;
		}

		// ����ڵ�������ʱ�䣬������������Ӻ�ǰ
		topoIdx--;
		while (topoIdx > -1 && topoResult[topoIdx] > -1) {
			int curIdx = topoResult[topoIdx];
			int minPower = INT_MAX;  // ��¼��С��ʱ��ֵ
			for (int k = 0; k < graph->nodeCount; k++) {
				// �����ǰ�ڵ�ĺ�̽ڵ��������ʱ���ȥ�ӵ�ǰ�ڵ㵽��̽ڵ�ĺ�ʱ��С�ڼ�¼����Сֵ
				// ���¼�¼��Сʱ��ֵ
				if (graph->relations[curIdx][k] > 0) {
					if (nodeL[k] - graph->relations[curIdx][k] < minPower) {
						minPower = nodeL[k] - graph->relations[curIdx][k];
					}
				}
			}
			// ���������Сʱ��ֵ��������Ϊ��ǰ�ڵ��������ʱ�䣬��������Ϊ��ǰ�ڵ�����緢��ʱ�䣨���һ���ڵ㣩
			nodeL[curIdx] = minPower == INT_MAX ? nodeE[curIdx] : minPower;
			topoIdx--;
		}

		// ��������������/����ʼʱ��
		for (int i = 0; i < graph->nodeCount; i++) {
			for (int k = 0; k < graph->nodeCount; k++) {
				if (graph->relations[i][k] > 0) {
					int arcE = nodeE[i];  // ����翪ʼʱ�䣨ǰ�ڵ����緢��ʱ�䣩
					int arcL = nodeL[k] - graph->relations[i][k];  // �����ʼʱ�䣨��ڵ�������ʱ���ȥ���ʱ��
					if (arcE == arcL) {
						// ��������������ʱ��һ������Ϊ�ؼ��
						// ������˽ڵ�Ϊ�ؼ��ڵ�
						isKeyNode[i] = BOOLEAN_TRUE;
						isKeyNode[k] = BOOLEAN_TRUE;
					}
				}
			}
		}

		// ���������������������ҳ��ؼ��ڵ㲢�洢����������
		topoIdx = 0;
		while (topoIdx < graph->nodeCount && topoResult[topoIdx] > -1) {
			if (isKeyNode[topoResult[topoIdx]]) {
				keyRoute[keyRoutePos++] = topoResult[topoIdx];
			}
			topoIdx++;
		}

		// ���������ͷſռ�
		*result = keyRoute;

		free(nodeE);
		free(nodeL);
		free(isKeyNode);
		return STATUS_SUCCESS;
	}
	else {
		// �����������ʧ�ܣ�ͼ�����Ϲ����޷�Ѱ�ҹؼ�·��
		return STATUS_FAIL;
	}
}

