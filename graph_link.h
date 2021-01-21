#ifndef GRAPH_LINK_H
#define GRAPH_LINK_H

#include "basis.h"
#include "stack.h"
#include "queue.h"

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



#endif // !GRAPH_LINK_H
