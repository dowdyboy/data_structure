#ifndef GRAPH_LINK_H
#define GRAPH_LINK_H

#include "basis.h"
#include "stack.h"
#include "queue.h"
#include "bin_tree.h"
#include "seq_list.h"


// ͼ�ڽӱ�������
typedef struct _graph_link_arc {
	int index;
	int power;
	_graph_link_arc* next;
} GRAPH_LINK_ARC;

// ͼ�ڽӱ��ڵ㶨��
typedef struct _graph_link_node {
	int index;
	ELEM_TYPE data;
	GRAPH_LINK_ARC* arc;
} GRAPH_LINK_NODE;

// ͼ�ڽӱ���
typedef struct _graph_link {
	int nodeCount;
	GRAPH_LINK_NODE* nodes;
} GRAPH_LINK;


STATUS GRAPH_LINK_INIT(GRAPH_LINK* graph, int nodeCount);  // ��ʼ��

STATUS GRAPH_LINK_PUT_NODE_VALUE(GRAPH_LINK* graph, int idx, ELEM_TYPE value);  // �����������ýڵ�ֵ

STATUS GRAPH_LINK_ADD_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx, int power);  // �ӱ�

STATUS GRAPH_LINK_REMOVE_EDGE(GRAPH_LINK* graph, int fromIdx, int toIdx);  // �Ƴ���

STATUS GRAPH_LINK_ADD_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx, int power);  // �ӻ�

STATUS GRAPH_LINK_REMOVE_ARC(GRAPH_LINK* graph, int fromIdx, int toIdx);  // �Ƴ���

STATUS GRAPH_LINK_DESTROY(GRAPH_LINK* graph);  // ����

STATUS GRAPH_LINK_DFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE));  // ������ȱ���

STATUS GRAPH_LINK_BFS(GRAPH_LINK* graph, void (*func)(ELEM_TYPE));  // ������ȱ���

STATUS GRAPH_LINK_MIN_GENERATED_TREE_PRIM(GRAPH_LINK* graph, BIN_TREE** tree, int startIdx);  // Prim�㷨��С������

STATUS GRAPH_LINK_MIN_GENERATED_TREE_KRUSKAL(GRAPH_LINK* graph, BIN_TREE** tree);  // ��³˹�����㷨��С������

STATUS GRAPH_LINK_SHORTEST_ROUTE_DIJKSTRA(GRAPH_LINK* graph, int idx, int*** result);  // �Ͻ�˹�����㷨��Դ�����·��

STATUS GRAPH_LINK_SHORTEST_ROUTE_FLOYD(GRAPH_LINK* graph, int*** powerResult, int*** pathResult);  // ���������㷨����������·��

STATUS GRAPH_LINK_SHORTEST_ROUTE_FLOYD_GET_RESULT(GRAPH_LINK* graph, int** powerMatrix, int** pathMatrix, int fromIdx, int toIdx, int** result);  // �Ӹ��������㷨�Ľ�������л�ȡָ���ڵ�����·��

STATUS GRAPH_LINK_TOPOLOGY_SORT(GRAPH_LINK* graph, int** result);  // ��������

STATUS GRAPH_LINK_KEY_ROUTE(GRAPH_LINK* graph, int** result);  // �ؼ�·��

#endif // !GRAPH_LINK_H
