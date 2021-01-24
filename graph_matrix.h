#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "basis.h"
#include "stack.h"
#include "queue.h"
#include "bin_tree.h"
#include "seq_list.h"

// 图邻接矩阵定义
typedef struct _graph_matrix {
	int nodeCount;
	ELEM_TYPE* nodes;
	int** relations;
} GRAPH_MATRIX;

STATUS GRAPH_MATRIX_INIT(GRAPH_MATRIX* graph, int nodeCount);  // 初始化

STATUS GRAPH_MATRIX_PUT_NODE_VALUE(GRAPH_MATRIX* graph, int idx, ELEM_TYPE value);  // 根据索引设置节点值

STATUS GRAPH_MATRIX_ADD_EDGE(GRAPH_MATRIX* graph , int fromIdx , int toIdx , int power);  // 加边

STATUS GRAPH_MATRIX_REMOVE_EDGE(GRAPH_MATRIX* graph, int fromIdx, int toIdx);  // 移除边

STATUS GRAPH_MATRIX_ADD_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx , int power);  // 加弧

STATUS GRAPH_MATRIX_REMOVE_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx);  // 移除弧

STATUS GRAPH_MATRIX_DESTROY(GRAPH_MATRIX* graph);  // 销毁

STATUS GRAPH_MATRIX_DFS(GRAPH_MATRIX* graph , void (*func)(ELEM_TYPE));  // 深度优先遍历

STATUS GRAPH_MATRIX_BFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE));  // 广度优先遍历

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_PRIM(GRAPH_MATRIX* graph , BIN_TREE **tree , int startIdx);  // Prim算法最小生成树

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_KRUSKAL(GRAPH_MATRIX* graph, BIN_TREE** tree);  // 克鲁斯卡尔算法最小生成树




#endif // !GRAPH_MATRIX_H
