#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "basis.h"
#include "stack.h"
#include "queue.h"
#include "bin_tree.h"
#include "seq_list.h"

// ͼ�ڽӾ�����
typedef struct _graph_matrix {
	int nodeCount;
	ELEM_TYPE* nodes;
	int** relations;
} GRAPH_MATRIX;

STATUS GRAPH_MATRIX_INIT(GRAPH_MATRIX* graph, int nodeCount);  // ��ʼ��

STATUS GRAPH_MATRIX_PUT_NODE_VALUE(GRAPH_MATRIX* graph, int idx, ELEM_TYPE value);  // �����������ýڵ�ֵ

STATUS GRAPH_MATRIX_ADD_EDGE(GRAPH_MATRIX* graph , int fromIdx , int toIdx , int power);  // �ӱ�

STATUS GRAPH_MATRIX_REMOVE_EDGE(GRAPH_MATRIX* graph, int fromIdx, int toIdx);  // �Ƴ���

STATUS GRAPH_MATRIX_ADD_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx , int power);  // �ӻ�

STATUS GRAPH_MATRIX_REMOVE_ARC(GRAPH_MATRIX* graph, int fromIdx, int toIdx);  // �Ƴ���

STATUS GRAPH_MATRIX_DESTROY(GRAPH_MATRIX* graph);  // ����

STATUS GRAPH_MATRIX_DFS(GRAPH_MATRIX* graph , void (*func)(ELEM_TYPE));  // ������ȱ���

STATUS GRAPH_MATRIX_BFS(GRAPH_MATRIX* graph, void (*func)(ELEM_TYPE));  // ������ȱ���

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_PRIM(GRAPH_MATRIX* graph , BIN_TREE **tree , int startIdx);  // Prim�㷨��С������

STATUS GRAPH_MATRIX_MIN_GENERATED_TREE_KRUSKAL(GRAPH_MATRIX* graph, BIN_TREE** tree);  // ��³˹�����㷨��С������




#endif // !GRAPH_MATRIX_H
