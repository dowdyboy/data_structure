#ifndef GRAPH_LINK_H
#define GRAPH_LINK_H

#include "basis.h"
#include "stack.h"
#include "queue.h"

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



#endif // !GRAPH_LINK_H
