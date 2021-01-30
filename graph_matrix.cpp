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
	// 关系权值初值初始化设置为0，表示无边
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

	// 初始化栈和访问标记
	SEQ_STACK_INIT(&idx_stack);
	SEQ_STACK_INIT(&val_stack);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// 将0号索引和数据入栈，如果栈不空，进入循环
	SEQ_STACK_PUSH(&idx_stack,0);
	SEQ_STACK_PUSH(&val_stack, graph->nodes[0]);
	while (idx_stack.base != idx_stack.top) {
		int idx,next_idx = -1;
		ELEM_TYPE val;
		SEQ_STACK_GET_TOP(&idx_stack,&idx);
		SEQ_STACK_GET_TOP(&val_stack, &val);
		// 获取栈顶索引和数据，如果该索引还未被访问，则进行访问并设置访问位
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// 寻找被访问节点的第一个未被访问过的出边所指向的索引号
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				next_idx = i;
				break;
			}
		}
		// 如果找到，将该索引和数据入栈，否则说明当前节点出边都已经被访问过了，弹出当前节点
		if (next_idx > -1) {
			SEQ_STACK_PUSH(&idx_stack,next_idx);
			SEQ_STACK_PUSH(&val_stack, graph->nodes[next_idx]);
		}
		else {
			SEQ_STACK_POP(&idx_stack, &idx);
			SEQ_STACK_POP(&val_stack, &val);
		}
	}

	// 释放栈和标记空间
	free(isAccess);
	SEQ_STACK_DESTORY(&val_stack);
	SEQ_STACK_DESTORY(&idx_stack);
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_BFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE)) {
	SEQ_QUEUE idx_queue, val_queue;
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount + 1));

	// 初始化辅助队列和标记数组
	SEQ_QUEUE_INIT(&idx_queue);
	SEQ_QUEUE_INIT(&val_queue);
	for (int i = 0; i < graph->nodeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// 将0号索引节点入队，如果队不空，执行循环
	SEQ_QUEUE_ENQUEUE(&idx_queue, 0);
	SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[0]);
	while (idx_queue.head != idx_queue.rear) {
		int idx;
		ELEM_TYPE val;
		SEQ_QUEUE_DEQUEUE(&idx_queue,&idx);
		SEQ_QUEUE_DEQUEUE(&val_queue, &val);
		// 头节点出队，如果该节点未被访问则进行访问并设置标记
		if (!isAccess[idx]) {
			(*func)(val);
			isAccess[idx] = BOOLEAN_TRUE;
		}
		// 遍历当前节点未被访问过的出边后继节点，入队
		for (int i = 0; i < graph->nodeCount; i++) {
			if (graph->relations[idx][i] != 0 && !isAccess[i]) {
				SEQ_QUEUE_ENQUEUE(&idx_queue,i);
				SEQ_QUEUE_ENQUEUE(&val_queue, graph->nodes[i]);
			}
		}
	}

	// 释放空间
	free(isAccess);
	SEQ_QUEUE_DESTORY(&idx_queue);
	SEQ_QUEUE_DESTORY(&val_queue);
	return STATUS_SUCCESS;
}

// 根据所选择的边（起始节点索引和终止节点索引），创建树（孩子兄弟二叉树形式）
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
		// 遍历所有边，选择未被访问过，并且起始节点索引或终止节点索引为当前节点的边
		if (!isAccess[i] && edgeFromIdxes[i] == idx) {
			// 设置该边的访问标记
			isAccess[i] = BOOLEAN_TRUE;
			if (childCount == 0) {
				// 如果是生成的第一个节点，递归调用其子节点，放在左子树上，并保存左子树的指针（即，左孩子）
				t->left = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i],isAccess);
				firstChild = t->left;
				childCount++;
			}
			else {
				// 如果不是生成第一个节点，说明不是该节点的第一个孩子，递归调用，将生成的节点放在左子树的右子树上
				// 并将左子树的指针下移
				firstChild->right = _graph_matrix_min_generated_tree_create_tree_helper(graph, edgeFromIdxes, edgeToIdxes, edgeToIdxes[i],isAccess);
				firstChild = firstChild->right;
				childCount++;
			}
		}
		else if (!isAccess[i] && edgeToIdxes[i] == idx) {
			// 同上，上面是寻找起始节点索引与当前节点索引一致的，这里是寻找结束节点索引与当前节点索引一致的
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

// 生成树的包装函数，主要提供访问标记的创建和释放
BIN_TREE* _graph_matrix_min_generated_tree_create_tree(GRAPH_MATRIX* graph,int* edgeFromIdxes,int* edgeToIdxes,int idx) {
	BIN_TREE* t = NULL;
	// 创建边访问标记
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * (graph->nodeCount - 1));

	for (int i = 0; i < graph->nodeCount - 1; i++) isAccess[i] = BOOLEAN_FALSE;

	// 执行生成树逻辑
	t = _graph_matrix_min_generated_tree_create_tree_helper(graph,edgeFromIdxes,edgeToIdxes,idx,isAccess);

	// 释放标记
	free(isAccess);
	return t;
}

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_PRIM(GRAPH_MATRIX* graph, BIN_TREE** tree, int startIdx) {
	if (startIdx < 0 || startIdx > graph->nodeCount - 1) return STATUS_FAIL;
	// 创建辅助变量
	int currentTopIdx = startIdx;  // 当前最新访问到的节点的索引
	int* currentEdgePowerValues = (int*)malloc(sizeof(int) * graph->nodeCount);  // 当前挂靠在每个节点上的边的权值
	int* currentEdgePrevIdxes = (int*)malloc(sizeof(int) * graph->nodeCount);  // 当前每个节点挂靠边的终止节点索引
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // 已经选定的边的起始节点索引
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // 已经选定的边的终止节点索引
	int selectedEdgePos = 0;  // 已经选定的边的个数

	// 挂靠边的权值初始设置为无穷大，对应的终止节点索引设置为-1
	for (int i = 0; i < graph->nodeCount; i++) {
		currentEdgePowerValues[i] = INT_MAX;
		currentEdgePrevIdxes[i] = -1;
	}
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}

	// 如果还没找到足够的边（n-1），执行此循环
	while (selectedEdgePos < graph->nodeCount - 1) {
		int minIdx = 0, minPower = INT_MAX;
		// 遍历每个节点的挂靠边
		for (int i = 0; i < graph->nodeCount; i++) {
			// 如果该节点的挂靠边还未最终确定
			if (currentEdgePowerValues[i] > -1) {
				if (i == currentTopIdx) {
					// 如果遍历节点的索引就是所选择的挂靠边的终止索引，就认为该边为一个最小边，将该边确定
					// 或者说如果遍历节点的索引为当前最新的访问到的节点索引
					currentEdgePowerValues[i] = -1;
				}
				else {
					// 如果当前最新节点到遍历节点存在边，且边上权值小于当前遍历节点挂靠边的权值
					// 则更新挂靠边的权值，和将挂靠边的终止索引改为当前最新节点索引
					if (graph->relations[currentTopIdx][i] > 0
						&& graph->relations[i][currentTopIdx] > 0
						&& graph->relations[currentTopIdx][i] == graph->relations[i][currentTopIdx]
						&& graph->relations[currentTopIdx][i] < currentEdgePowerValues[i]) {
						currentEdgePowerValues[i] = graph->relations[currentTopIdx][i];
						currentEdgePrevIdxes[i] = currentTopIdx;
					}
				}
			}
			// 经过上面更新挂靠边的信息，然后判断是否小于当前这一轮保存的最小权值
			// 更新最小的挂靠边权值和节点索引
			if (currentEdgePowerValues[i] > -1 && currentEdgePowerValues[i] < minPower) {
				minPower = currentEdgePowerValues[i];
				minIdx = i;
			}
		}
		// 根据选择的最小挂靠边对应的节点索引，保存最小边的起始节点索引和终止节点索引
		// 并更新当前最新访问节点索引为最小边对应的节点索引
		selectedEdgeFromIdxes[selectedEdgePos] = currentEdgePrevIdxes[minIdx];
		selectedEdgeToIdxes[selectedEdgePos] = minIdx;
		currentTopIdx = minIdx;
		selectedEdgePos++;
	}

	// 根据选择的最小边，创建最小生出树
	*tree = _graph_matrix_min_generated_tree_create_tree(graph, selectedEdgeFromIdxes, selectedEdgeToIdxes, startIdx);
	
	// 释放空间
	free(currentEdgePowerValues);
	free(currentEdgePrevIdxes);
	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	return STATUS_SUCCESS;
}

// 根据每个边的起始和终止索引，判断图是否存在环路
BOOLEAN _graph_matrix_min_generated_tree_has_loop(int* edgeFromIdxes,int* edgeToIdxes,int edgeCount) {
	// 辅助变量
	SEQ_STACK s;  // 保存当前访问节点之前访问过的节点的索引
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * edgeCount);  // 边是否访问过了的标记
	int accessCount = 0;  // 已经访问过的边的个数
	int currentStartIdx = -1, currentEndIdx = -1;  // 所访问的第一个节点的索引和最新访问的节点的索引

	// 变量初始化
	SEQ_STACK_INIT(&s);
	for (int i = 0; i < edgeCount; i++) isAccess[i] = BOOLEAN_FALSE;

	// 如果还未访问所有边，则执行这个循环
	while (accessCount < edgeCount) {
		if (s.base == s.top) {
			// 如果是开始新一轮访问（栈空），先选择一个未被访问过的边
			int findIdx = -1;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					findIdx = i;
					break;
				}
			}
			if (findIdx > -1) {
				// 将所选边的开始节点索引入栈，并设置为这一轮第一个节点
				SEQ_STACK_PUSH(&s, edgeFromIdxes[findIdx]);
				currentStartIdx = edgeFromIdxes[findIdx];
				// 将所选边的终止节点索引设置为当前最新访问节点的索引
				currentEndIdx = edgeToIdxes[findIdx];
				// 设置该边访问标记，增加计数器
				isAccess[findIdx] = BOOLEAN_TRUE;
				accessCount++;
			}
		}
		else {
			// 如果不是开始新一轮访问，遍历未被访问过的边
			BOOLEAN isFindNext = BOOLEAN_FALSE;
			for (int i = 0; i < edgeCount; i++) {
				if (!isAccess[i]) {
					// 如果该边的起始索引或终止索引等于当前最新访问节点索引
					// 将当前最新访问节点索引入轨迹栈，后更新为遍历边的起始/终止索引
					// 并增加计数器和设置标记
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
				// 如果在上面的遍历中没有访问到新的边，从栈中弹出最近的访问索引作为最新访问节点索引
				SEQ_STACK_POP(&s, &currentEndIdx);
			}
			else {
				// 如果上面的遍历中访问到了新的边，判断是否构成环路
				// 即是否这一轮第一个节点索引等于最新访问节点索引
				// 如果构成环路，则释放空间并返回
				if (currentEndIdx == currentStartIdx) {
					free(isAccess);
					SEQ_STACK_DESTORY(&s);
					return BOOLEAN_TRUE;
				}
			}
		}
	}
	
	// 没有环路，释放空间并返回
	free(isAccess);
	SEQ_STACK_DESTORY(&s);
	return BOOLEAN_FALSE;
}

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_KRUSKAL(GRAPH_MATRIX* graph, BIN_TREE** tree) {
	// 辅助变量
	int* selectedEdgeFromIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // 所选最小边的起始节点索引
	int* selectedEdgeToIdxes = (int*)malloc(sizeof(int) * (graph->nodeCount - 1));  // 所选最小边的终止节点索引
	int selectedEdgePos = 0;  // 所选最小边的个数
	SEQ_LIST powerList,edgeFromIdxList,edgeToIdxList;  // 所有边权值/起始节点索引/终止节点索引列表

	// 变量初始化
	for (int i = 0; i < graph->nodeCount - 1; i++) {
		selectedEdgeFromIdxes[i] = -1;
		selectedEdgeToIdxes[i] = -1;
	}
	SEQ_LIST_INIT(&powerList);
	SEQ_LIST_INIT(&edgeFromIdxList);
	SEQ_LIST_INIT(&edgeToIdxList);

	// 遍历图全体边，并将权值/起始节点索引/终止节点索引放入列表
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

	// 冒泡排序（可优化为快速排序），根据权值从小到大排序
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

	// 如果未选择足够边，则执行该循环
	int edgeIdx = 0;
	while (selectedEdgePos < graph->nodeCount - 1 && edgeIdx < edgeFromIdxList.length) {
		// 尝试按顺序从列表中选择一个边
		selectedEdgeFromIdxes[selectedEdgePos] = edgeFromIdxList.data[edgeIdx];
		selectedEdgeToIdxes[selectedEdgePos] = edgeToIdxList.data[edgeIdx];
		edgeIdx++;
		selectedEdgePos++;
		// 如果选择该边后有环路，则回退
		if (_graph_matrix_min_generated_tree_has_loop(selectedEdgeFromIdxes, selectedEdgeToIdxes, selectedEdgePos)) {
			selectedEdgePos--;
		}
	}

	// 根据选择的边创建最小生成树
	*tree = _graph_matrix_min_generated_tree_create_tree(graph,selectedEdgeFromIdxes,selectedEdgeToIdxes,0);

	// 释放空间
	free(selectedEdgeFromIdxes);
	free(selectedEdgeToIdxes);
	SEQ_LIST_DESTORY(&powerList);
	SEQ_LIST_DESTORY(&edgeFromIdxList);
	SEQ_LIST_DESTORY(&edgeToIdxList);
	return STATUS_SUCCESS;
}


STATUS GRAPH_MATRIX_SHORTEST_ROUTE_DIJKSTRA(GRAPH_MATRIX* graph, int idx, int*** result) {
	if (idx < 0 || idx > graph->nodeCount - 1) return STATUS_FAIL;
	// 辅助变量
	int currentNodeIdx = idx;  // 当前遍历到的节点索引
	int currentFullPower = 0;  // 从源点到当前遍历节点路径的累计权值
	int* currentNodePowers = (int*)malloc(sizeof(int) * graph->nodeCount);  // 当前从源点到各个节点的路径的累计权值，用于程序控制
	int* currentRecordPowers = (int*)malloc(sizeof(int) * graph->nodeCount);  // 当前从源点到各个节点的路径的累计权值记录
	int** currentRoutes = (int**)malloc(sizeof(int*) * graph->nodeCount);  // 当前从单源点到各个节点的路径记录
	int selectedRouteCount = 0;  // 已经找到的最短路径的个数

	// 初始化辅助变量
	for (int i = 0; i < graph->nodeCount; i++) {
		// 初始设置为无穷大；记录值如果是从自己到自己，设置为0，否则初始设置为-1（表示不可达）
		currentNodePowers[i] = INT_MAX;
		currentRecordPowers[i] = i == idx ? 0 : -1;
	}
	for (int i = 0; i < graph->nodeCount; i++) currentRoutes[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// 路径记录初始全部为-1
			currentRoutes[i][k] = -1;
		}
	}

	// 如果还没有找到足够的最短路径，执行以下循环
	while (selectedRouteCount < graph->nodeCount - 1) {
		// 设置标记，用于记录本轮寻找的最小权值和对应指向的节点索引
		int minPower = INT_MAX, minIdx = -1;
		for (int i = 0; i < graph->nodeCount; i++) {
			if (currentNodeIdx == i) {
				// 如果访问到的是当前遍历到的节点，将到该节点对应的权值设置为-1，表示到这个节点的最短路径已经找到
				currentNodePowers[i] = -1;
			}
			else {
				// 如果到i节点的最短路径还没有找到
				if (currentNodePowers[i] > -1) {
					// 判断如果从当前遍历节点到i节点是否有弧，并且累计权值小于当前到该节点所记录的权值
					if (graph->relations[currentNodeIdx][i] > 0 
						&& currentFullPower + graph->relations[currentNodeIdx][i] < currentNodePowers[i]) {
						// 更新到i节点的记录权值
						currentNodePowers[i] = currentFullPower + graph->relations[currentNodeIdx][i];
						currentRecordPowers[i] = currentNodePowers[i];
						// 更新到i节点的路径记录
						if (currentNodeIdx == idx) {
							// 如果是第一次记录，记录下单源点和i节点
							currentRoutes[i][0] = currentNodeIdx;
							currentRoutes[i][1] = i;
						}
						else {
							// 如果不是第一次记录，则先将从单源点到当前遍历节点的路径记录复制到从单源点到i节点的位置上
							// 然后再在到i节点路径记录的末尾加上i节点的索引
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
					// 如果到i节点的累计权值小于记录的最小权值，则更新最小记录
					if (currentNodePowers[i] <= minPower) {
						minPower = currentNodePowers[i];
						minIdx = i;
					}
				}
			}
		}
		// 经过本轮遍历，通过最小标记，更新当前遍历节点索引和对应的累计权值；并增加计数器
		if (minIdx > -1) {
			selectedRouteCount++;
			currentNodeIdx = minIdx;
			currentFullPower = minPower;
		}
	}

	// 输出结果，二维数组形式；第0列为从单源点到i节点的累计权值，从第1列开始为到i节点的路径记录，直到路径记录值为-1结束
	*result = (int**)malloc(sizeof(int*) * graph->nodeCount);
	for (int i = 0; i < graph->nodeCount; i++) {
		(*result)[i] = (int*)malloc(sizeof(int) * (graph->nodeCount + 1));
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount + 1; k++) {
			(*result)[i][k] = k == 0 ? currentRecordPowers[i] : currentRoutes[i][k - 1];
		}
	}

	// 释放空间
	free(currentNodePowers);
	free(currentRecordPowers);
	for (int i = 0; i < graph->nodeCount; i++) {
		free(currentRoutes[i]);
	}
	free(currentRoutes);
	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD(GRAPH_MATRIX* graph, int*** powerResult, int*** pathResult) {
	// 创建累计权值矩阵，和路径记录矩阵
	int** powerMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);
	int** pathMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);

	// 根据图初始化变量
	for (int i = 0; i < graph->nodeCount; i++) {
		powerMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
		pathMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// 如果有弧，则权值矩阵对应位置设置为弧的权值，否则设置为无穷大
			powerMatrix[i][k] = graph->relations[i][k] > 0 ? graph->relations[i][k] : INT_MAX;
			// 如果是（i，i）（矩阵对角）的位置，修正权值矩阵值为0
			if (i == k) powerMatrix[i][k] = 0;
			// 如果i到k有弧，路径矩阵从i到k的位置设置为i，表示到k节点的前置节点为i，否则设置为-1表示不可达
			pathMatrix[i][k] = graph->relations[i][k] > 0 ? i : -1;
		}
	}

	// 图有n个节点，则执行n次遍历
	for (int x = 0; x < graph->nodeCount; x++) {
		for (int i = 0; i < graph->nodeCount; i++) {
			// i等于x不执行内循环，因为从i经过i再到k累计路径权值不会有任何变化
			if (i != x) {
				for (int k = 0; k < graph->nodeCount; k++) {
					// 同理，k等于x和i等于k也不执行内部逻辑
					if (k != x && i != k) {
						// 如果i到x可达，x到k可达，并且这两段的累计权值比当前从i到k的累计权值小
						// 则更新对应位置权值矩阵的值为更小的值
						// 更新对应位置路径矩阵的值为从x到k的前置节点的索引
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

	// 输出结果
	*powerResult = powerMatrix;
	*pathResult = pathMatrix;

	return STATUS_SUCCESS;
}

STATUS GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD_GET_RESULT(GRAPH_MATRIX* graph, int** powerMatrix, int** pathMatrix, int fromIdx, int toIdx, int** result) {
	if (fromIdx < 0 || fromIdx > graph->nodeCount - 1 || toIdx < 0 || toIdx > graph->nodeCount - 1 )
		return STATUS_FAIL;
	// 创建路径记录数组
	int* route = (int*)malloc(sizeof(int) * (graph->nodeCount + 1));
	int routeIdx = 1,beforeIdx = -1;

	// 初始化变量，路径记录数组值设置为-1
	for (int i = 0; i < graph->nodeCount + 1; i++) route[i] = -1;

	// 0地址记录从起始节点到终止节点的累计权值
	route[0] = powerMatrix[fromIdx][toIdx] != INT_MAX? powerMatrix[fromIdx][toIdx]:-1;
	// 如果不是从自身到自身，并且从起始节点到终止节点可达
	if (fromIdx != toIdx && powerMatrix[fromIdx][toIdx] != INT_MAX) {
		// 先将终止节点记录
		route[routeIdx++] = toIdx;
		// 再从路径矩阵中找出从起始到终止节点的前置节点索引，并记录
		beforeIdx = pathMatrix[fromIdx][toIdx];
		route[routeIdx++] = beforeIdx;
		// 如果前置节点不是起始节点，则再查找从起始节点到前置节点的前置节点，并记录
		while (beforeIdx != fromIdx) {
			beforeIdx = pathMatrix[fromIdx][beforeIdx];
			route[routeIdx++] = beforeIdx;
		}
		// 由于以上记录是倒序记录，下面的代码是将记录逆序
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

	// 输出结果
	*result = route;
	
	return STATUS_SUCCESS;
}

// 从弧的关系矩阵中找到拓扑排序的下一个节点索引
int _graph_matrix_topology_sort_find_next_node(int** arcMatrix,int nodeCount,int* isAccess) {
	int findIdx = -1;
	// 寻找入度（矩阵中的列）为0的节点的索引
	for (int k = 0; k < nodeCount; k++) {
		// 如果这个k节点还未被选择
		if (!isAccess[k]) {
			BOOLEAN isFind = BOOLEAN_TRUE;
			for (int i = 0; i < nodeCount; i++) {
				// 判断k列的所有行是否都为0（即k节点的入度为0）
				if (arcMatrix[i][k] != 0) {
					isFind = BOOLEAN_FALSE;
					break;
				}
			}
			// 如果找到了，设置访问标记
			if (isFind) {
				isAccess[k] = BOOLEAN_TRUE;
				findIdx = k;
				break;
			}
		}
	}
	if (findIdx > -1) {
		// 找到了，将该节点的所有出边全部删掉
		for (int k = 0; k < nodeCount; k++) {
			arcMatrix[findIdx][k] = 0;
		}
	}
	return findIdx;
}

STATUS GRAPH_MATRIX_TOPOLOGY_SORT(GRAPH_MATRIX* graph, int** result) {
	// 定义变量
	int* topoArray = (int*)malloc(sizeof(int) * graph->nodeCount);  // 拓扑排序节点索引结果列表
	int topoArrayPos = 0;  // 结果列表当前存储的位置
	int** arcMatrix = (int**)malloc(sizeof(int*) * graph->nodeCount);  // 弧的关系矩阵
	BOOLEAN* isAccess = (BOOLEAN*)malloc(sizeof(BOOLEAN) * graph->nodeCount);  // 节点是否已经排序的标志
	int selectedNodeCount = 0;  // 已经排序的节点个数
	int findIdx = -1;  // 找到的待排序节点的索引

	// 初始化变量
	for (int i = 0; i < graph->nodeCount; i++) {
		topoArray[i] = -1;
		isAccess[i] = BOOLEAN_FALSE;
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		arcMatrix[i] = (int*)malloc(sizeof(int) * graph->nodeCount);
	}
	for (int i = 0; i < graph->nodeCount; i++) {
		for (int k = 0; k < graph->nodeCount; k++) {
			// 弧关系直接拷贝图的关系变量
			arcMatrix[i][k] = graph->relations[i][k];
		}
	}

	// 寻找符合要求的节点进行排序，直到寻找失败
	findIdx = _graph_matrix_topology_sort_find_next_node(arcMatrix,graph->nodeCount,isAccess);
	while (findIdx > -1) {
		topoArray[topoArrayPos++] = findIdx;
		selectedNodeCount++;
		findIdx = _graph_matrix_topology_sort_find_next_node(arcMatrix, graph->nodeCount,isAccess);
	}

	// 释放空间
	for (int i = 0; i < graph->nodeCount; i++) {
		free(arcMatrix[i]);
	}
	free(arcMatrix);
	free(isAccess);
	if (selectedNodeCount < graph->nodeCount) {
		// 如果排序的节点个数小于总个数，说明还有节点无法被排序，图中有环，拓扑排序失败
		free(topoArray);
		return STATUS_FAIL;
	}
	else {
		// 排序成功，输出结果
		*result = topoArray;
		return STATUS_SUCCESS;
	}
}

STATUS GRAPH_MATRIX_KEY_ROUTE(GRAPH_MATRIX* graph, int** result) {
	int* topoResult = NULL;  // 存储拓扑排序结果
	int topoIdx = 0;

	if (GRAPH_MATRIX_TOPOLOGY_SORT(graph, &topoResult) == STATUS_SUCCESS) {
		// 如果拓扑排序成功，开始寻找关键路径
		int* nodeE = (int*)malloc(sizeof(int) * graph->nodeCount);  // 存储每个节点的最早发生时间
		int* nodeL = (int*)malloc(sizeof(int) * graph->nodeCount);  // 存储每个节点的最晚发生时间
		BOOLEAN* isKeyNode = (BOOLEAN*)malloc(sizeof(BOOLEAN) * graph->nodeCount);  // 标记节点是否为关键节点
		int* keyRoute = (int*)malloc(sizeof(int) * graph->nodeCount);  // 存储寻找的关键路径
		int keyRoutePos = 0;

		// 变量初始化
		for (int i = 0; i < graph->nodeCount; i++) {
			nodeE[i] = 0;
			nodeL[i] = 0;
			isKeyNode[i] = BOOLEAN_FALSE;
			keyRoute[i] = -1;
		}

		// 计算节点最早发生时间，按照拓扑排序从前到后
		while (topoIdx < graph->nodeCount && topoResult[topoIdx] > -1) {
			int curIdx = topoResult[topoIdx];  // 拓扑排序当前节点索引
			int maxPower = -1;  // 记录最大的时间值
			for (int i = 0; i < graph->nodeCount; i++) {
				// 如果当前节点的前驱的最早发生时间加上从该前驱到当前节点的时间大于所记录的最大时间
				// 更新记录最大时间
				if (graph->relations[i][curIdx] > 0) {
					if (nodeE[i] + graph->relations[i][curIdx] > maxPower) {
						maxPower = nodeE[i] + graph->relations[i][curIdx];
					}
				}
			}
			// 如果有最大时间值，则设置为当前节点的最早发生时间，否则设置为0（第一个节点）
			nodeE[curIdx] = maxPower == -1 ? 0 : maxPower;
			topoIdx++;
		}

		// 计算节点最晚发生时间，按照拓扑排序从后到前
		topoIdx--;
		while (topoIdx > -1 && topoResult[topoIdx] > -1) {
			int curIdx = topoResult[topoIdx];
			int minPower = INT_MAX;  // 记录最小的时间值
			for (int k = 0; k < graph->nodeCount; k++) {
				// 如果当前节点的后继节点的最晚发生时间减去从当前节点到后继节点的耗时，小于记录的最小值
				// 更新记录最小时间值
				if (graph->relations[curIdx][k] > 0) {
					if (nodeL[k] - graph->relations[curIdx][k] < minPower) {
						minPower = nodeL[k] - graph->relations[curIdx][k];
					}
				}
			}
			// 如果存在最小时间值，则设置为当前节点的最晚发生时间，否则设置为当前节点的最早发生时间（最后一个节点）
			nodeL[curIdx] = minPower == INT_MAX ? nodeE[curIdx] : minPower;
			topoIdx--;
		}

		// 计算活动（弧）最早/最晚开始时间
		for (int i = 0; i < graph->nodeCount; i++) {
			for (int k = 0; k < graph->nodeCount; k++) {
				if (graph->relations[i][k] > 0) {
					int arcE = nodeE[i];  // 活动最早开始时间（前节点最早发生时间）
					int arcL = nodeL[k] - graph->relations[i][k];  // 活动最晚开始时间（后节点最晚发生时间减去活动耗时）
					if (arcE == arcL) {
						// 如果活动最早最晚发生时间一样，则为关键活动
						// 标记两端节点为关键节点
						isKeyNode[i] = BOOLEAN_TRUE;
						isKeyNode[k] = BOOLEAN_TRUE;
					}
				}
			}
		}

		// 遍历拓扑排序结果，从中找出关键节点并存储在输出结果中
		topoIdx = 0;
		while (topoIdx < graph->nodeCount && topoResult[topoIdx] > -1) {
			if (isKeyNode[topoResult[topoIdx]]) {
				keyRoute[keyRoutePos++] = topoResult[topoIdx];
			}
			topoIdx++;
		}

		// 输出结果，释放空间
		*result = keyRoute;

		free(nodeE);
		free(nodeL);
		free(isKeyNode);
		return STATUS_SUCCESS;
	}
	else {
		// 如果拓扑排序失败，图不符合规则，无法寻找关键路径
		return STATUS_FAIL;
	}
}

