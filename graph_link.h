#ifndef GRAPH_LINK_H
#define GRAPH_LINK_H

#include "basis.h"
#include "stack.h"
#include "queue.h"
#include "bin_tree.h"
#include "seq_list.h"


// 图邻接表，弧定义
typedef struct _graph_link_arc {
	int index;
	int power;
	_graph_link_arc* next;
} GRAPH_LINK_ARC;

// 图邻接表，节点定义
typedef struct _graph_link_node {
	int index;
	ELEM_TYPE data;
	GRAPH_LINK_ARC* arc;
} GRAPH_LINK_NODE;

// 图邻接表定义
typedef struct _graph_link {
	int nodeCount;
	GRAPH_LINK_NODE* nodes;
} GRAPH_LINK;


STATUS GRAPH_LINK_INIT(GRAPH_LINK* graph, int nodeCount);  // 初始化

STATUS GRAPH_LINK_PUT_NODE_VALUE(GRAPH_LINK* graph, int idx, ELEM_TYPE value);  // 根据索引设置节点值

STATUS GRAPH_LINK_ADD_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx, int power);  // 加边

STATUS GRAPH_LINK_REMOVE_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx);  // 移除边

STATUS GRAPH_LINK_ADD_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx, int power);  // 加弧

STATUS GRAPH_LINK_REMOVE_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx);  // 移除弧

STATUS GRAPH_LINK_DESTROY(GRAPH_LINK* graph);  // 销毁

STATUS GRAPH_LINK_DFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE));  // 深度优先遍历

STATUS GRAPH_LINK_BFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE));  // 广度优先遍历

STATUS GRAPH_LINK_MIN_GENERATED_TREE_PRIM(GRAPH_LINK* graph, BIN_TREE** tree, int startIdx);  // Prim算法最小生成树

STATUS GRAPH_LINK_MIN_GENERATED_TREE_KRUSKAL(GRAPH_LINK* graph, BIN_TREE** tree);  // 克鲁斯卡尔算法最小生成树

STATUS GRAPH_LINK_SHORTEST_ROUTE_DIJKSTRA(GRAPH_LINK* graph, int idx, int*** result);  // 迪杰斯特拉算法求单源点最短路径

STATUS GRAPH_LINK_SHORTEST_ROUTE_FLOYD(GRAPH_LINK* graph, int*** powerResult, int*** pathResult);  // 弗洛伊德算法求两点间最短路径

STATUS GRAPH_LINK_SHORTEST_ROUTE_FLOYD_GET_RESULT(GRAPH_LINK* graph, int** powerMatrix, int** pathMatrix, int fromIdx, int toIdx, int** result);  // 从弗洛伊德算法的结果矩阵中获取指定节点的最短路径

STATUS GRAPH_LINK_TOPOLOGY_SORT(GRAPH_LINK* graph, int** result);  // 拓扑排序

STATUS GRAPH_LINK_KEY_ROUTE(GRAPH_LINK* graph, int** result);  // 关键路径

#endif // !GRAPH_LINK_H
