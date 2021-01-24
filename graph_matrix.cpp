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
