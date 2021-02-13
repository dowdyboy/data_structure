#include "stdio.h"
#include "seq_list.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"
#include "chars.h"
#include "bin_tree.h"
#include "graph_matrix.h"
#include "graph_link.h"
#include "balance_bin_tree.h"
#include "b_tree.h"
#include "hash.h"


/*
TODO:
1. 哈夫曼编码
2. B树移除元素
3. 附加：红黑树，B+树
*/

void myPrint(ELEM_TYPE d) {
	printf("print : %d\n", d);
}

void printGraphMatrix(GRAPH_MATRIX g) {
	for (int i = 0; i < g.nodeCount; i++) {
		for (int k = 0; k < g.nodeCount; k++) {
			printf(" %d ", g.relations[i][k]);
		}
		printf("\n");
	}
}

void printGraphLink(GRAPH_LINK g) {
	int** mat = (int**)malloc(sizeof(int*) * g.nodeCount);
	for (int i = 0; i < g.nodeCount; i++) {
		mat[i] = (int*)malloc(sizeof(int) * g.nodeCount);
	}
	for (int i = 0; i < g.nodeCount; i++) {
		for (int k = 0; k < g.nodeCount; k++) {
			mat[i][k] = 0;
		}
	}
	for (int i = 0; i < g.nodeCount; i++) {
		GRAPH_LINK_ARC* p = g.nodes[i].arc;
		while (p != NULL) {
			mat[i][p->index] = p->power;
			p = p->next;
		}
	}
	for (int i = 0; i < g.nodeCount; i++) {
		for (int k = 0; k < g.nodeCount; k++) {
			printf(" %d ", mat[i][k]);
		}
		printf("\n");
	}
	for (int i = 0; i < g.nodeCount; i++) {
		free(mat[i]);
	}
	free(mat);
}

void printBinTree(BIN_TREE* tree, int deep) {
	if (tree != NULL) {
		for (int i = 0; i < deep; i++) {
			printf(" -- ");
		}
		printf("%d\n", tree->data);
		printBinTree(tree->left, deep + 1);
		printBinTree(tree->right, deep + 1);
	}
}

void printBTree(B_TREE_NODE* tree,int deep) {
	if (tree != NULL) {
		for (int i = 0; i < deep; i++) {
			printf(" - ");
		}
		for (int i = 0; i < tree->count; i++) {
			printf(" %d ", tree->data[i]);
		}
		printf(" (%d,%d) ",tree, tree->parent);
		printf("\n");
		for (int i = 0; i < tree->count + 1; i++) {
			printBTree(tree->children[i], deep + 1);
		}
	}
}

void printBalanceBinTree(BALANCE_BIN_TREE* tree,int deep) {
	if (tree != NULL) {
		for (int i = 0; i < deep; i++) {
			printf(" -- ");
		}
		printf("%d\n", tree->data);
		printBalanceBinTree(tree->left, deep + 1);
		printBalanceBinTree(tree->right, deep + 1);
	}
}

void testSeqList() {
	SEQ_LIST a;

	SEQ_LIST_INIT(&a);
	for (int i = 0; i < 13; i++) {
		SEQ_LIST_ADD(&a, i);
	}
	for (int i = 0; i < a.length; i++) {
		printf("%d  ", a.data[i]);
	}
	printf("\n%d\n", a.length);
	SEQ_LIST_PUT(&a, 9, 99);
	for (int i = 0; i < a.length; i++) {
		printf("%d  ", a.data[i]);
	}
	printf("\n%d\n", a.length);

	int r = 0;
	SEQ_LIST_GET(&a, 9, &r);
	printf("\n%d\n", r);
}

void testLinkList() {
	LINK_LIST a;
	LINK_LIST_INIT(&a);
	for (int i = 0; i < 5; i++) {
		LINK_LIST_ADD(&a, i);
	}
	for (int i = 0; i < a.length; i++) {
		int d;
		LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n",a.length);
	LINK_LIST_INSERT(&a,2,99);
	for (int i = 0; i < a.length; i++) {
		int d;
		LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);
	LINK_LIST_DELETE(&a, 0);
	LINK_LIST_DELETE(&a, 1);
	for (int i = 0; i < a.length; i++) {
		int d;
		LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);
	LINK_LIST_PUT(&a, 0, 99);
	LINK_LIST_PUT(&a, 1, 88);
	for (int i = 0; i < a.length; i++) {
		int d;
		LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);
	LINK_LIST_CLEAR(&a);
	for (int i = 0; i < a.length; i++) {
		int d;
		LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);
}

void testDlLinkList() {
	DL_LINK_LIST a;

	DL_LINK_LIST_INIT(&a);
	for (int i = 0; i < 5; i++) {
		DL_LINK_LIST_ADD(&a,i);
	}

	for (int i = 0; i < a.length; i++) {
		int d;
		DL_LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);

	DL_LINK_LIST_INSERT(&a,1,99);
	DL_LINK_LIST_INSERT(&a, 0, 88);

	for (int i = 0; i < a.length; i++) {
		int d;
		DL_LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);

	DL_LINK_LIST_DELETE(&a, 3);

	for (int i = 0; i < a.length; i++) {
		int d;
		DL_LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);

	DL_LINK_LIST_PUT(&a, 5, 999);

	for (int i = 0; i < a.length; i++) {
		int d;
		DL_LINK_LIST_GET(&a, i, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", a.length);

	DL_LINK_LIST_CLEAR(&a);

	printf("\n%d\n", a.length);

}

void testSeqStack() {
	SEQ_STACK s;
	SEQ_STACK_INIT(&s);
	for (int i = 0; i < 9; i++) {
		SEQ_STACK_PUSH(&s, i);
	}
	printf("\n%d\n", s.top - s.base);
	while (s.base != s.top) {
		int d;
		SEQ_STACK_POP(&s, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", s.top - s.base);
}

void testLinkStack() {
	LINK_STACK s;
	LINK_STACK_INIT(&s);
	for (int i = 0; i < 9; i++) {
		LINK_STACK_PUSH(&s,i);
	}
	printf("\n%d\n", s.length);
	while (s.node != NULL) {
		int d;
		LINK_STACK_POP(&s, &d);
		printf(" %d ", d);
	}
	printf("\n%d\n", s.length);
}

void testSeqQueue() {
	SEQ_QUEUE q;
	SEQ_QUEUE_INIT(&q);
	for (int i = 0; i < 9; i++) {
		SEQ_QUEUE_ENQUEUE(&q, i);
	}
	ELEM_TYPE d;
	while (q.head != q.rear) {
		SEQ_QUEUE_DEQUEUE(&q,&d);
		printf(" %d ", d);
	}
}

void testLinkQueue() {
	LINK_QUEUE q;
	LINK_QUEUE_INIT(&q);
	for (int i = 0; i < 9; i++) {
		LINK_QUEUE_ENQUEUE(&q, i);
	}
	while (q.length != 0) {
		ELEM_TYPE d;
		LINK_QUEUE_DEQUEUE(&q, &d);
		printf(" %d ", d);
	}
}

void testChars() {
	const char* a = "hello world", * b = "he";
	printf("%d", IndexOf_BF(a, b));
	printf("\n");
	const char* x = "abcabcabaabcacbasde", * y = "abaabcac";
	printf("%d", IndexOf_KMP(x, y));
	printf("\n");
}

void testBinTree() {
	BIN_TREE* t = NULL;
	/*int arrLen = 10;
	int* arr = (int*)malloc(sizeof(int) * (arrLen + 1));
	for (int i = 0; i < arrLen; i++) {
		arr[i] = i;
	}*/
	int arrLen = 15;
	int* arr = (int*)malloc(sizeof(int) * (arrLen + 1));
	arr[0] = 31; arr[1] = 23; arr[2] = 12; arr[3] = 66; arr[4] = -1;
	arr[5] = 5; arr[6] = 17; arr[7] = 70; arr[8] = 62; arr[9] = -1;
	arr[10] = -1; arr[11] = -1; arr[12] = 88; arr[13] = -1; arr[14] = 55;
	BIN_TREE_TRANSFORM_FROM_ARRAY(arr, arrLen, &t);
	free(arr);

	BIN_TREE_INDEX_DLR(t);

	BIN_TREE_ERGODIC_DLR(t, myPrint);
	printf("\n");
	BIN_TREE_ERGODIC_LDR(t, myPrint);
	printf("\n");
	BIN_TREE_ERGODIC_LRD(t, myPrint);
	printf("\n");

	int c = 0;
	BIN_TREE_NODE_COUNT(t,&c);
	printf("count : %d\n\n", c);

	ELEM_TYPE* t_arr=NULL;
	int t_arr_len;
	BIN_TREE_TRANSFORM_TO_ARRAY(t, &t_arr, &t_arr_len);
	for (int i = 0; i < t_arr_len; i++) {
		printf(" %d ", t_arr[i]);
	}

	printf("\n\n==============================\n\n");

	printf("%d", t->left->left->right->right->data);
}

void testGraphMatrix() {
	GRAPH_MATRIX g;
	GRAPH_MATRIX_INIT(&g,7);
	for (int i = 0; i < g.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g,i,i);
	}
	GRAPH_MATRIX_ADD_EDGE(&g, 0, 1, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 0, 2, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 0, 3, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 1, 4, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 1, 5, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 1, 6, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 2, 6, 1);
	GRAPH_MATRIX_ADD_EDGE(&g, 4, 5, 1);

	printGraphMatrix(g);
	printf("\n");
	GRAPH_MATRIX_DFS(&g,myPrint);
	printf("\n");
	GRAPH_MATRIX_BFS(&g, myPrint);

	GRAPH_MATRIX_DESTROY(&g);

	printf("\n\n");

	GRAPH_MATRIX g2;
	BIN_TREE* t = NULL,*t2 = NULL;
	GRAPH_MATRIX_INIT(&g2, 6);
	for (int i = 0; i < g2.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g2, i, i);
	}
	GRAPH_MATRIX_ADD_EDGE(&g2, 0, 1, 6);
	GRAPH_MATRIX_ADD_EDGE(&g2, 0, 3, 5);
	GRAPH_MATRIX_ADD_EDGE(&g2, 0, 2, 1);
	GRAPH_MATRIX_ADD_EDGE(&g2, 1, 2, 5);
	GRAPH_MATRIX_ADD_EDGE(&g2, 1, 4, 3);
	GRAPH_MATRIX_ADD_EDGE(&g2, 2, 4, 5);
	GRAPH_MATRIX_ADD_EDGE(&g2, 2, 3, 7);
	GRAPH_MATRIX_ADD_EDGE(&g2, 2, 5, 4);
	GRAPH_MATRIX_ADD_EDGE(&g2, 3, 5, 2);
	GRAPH_MATRIX_ADD_EDGE(&g2, 4, 5, 6);
	printGraphMatrix(g2);

	GRAPH_MATRIX_MIN_GENERATED_TREE_PRIM(&g2,&t,0);
	printf("\n");
	BIN_TREE_ERGODIC_DLR(t, myPrint);

	GRAPH_MATRIX_MIN_GENERATED_TREE_KRUSKAL(&g2, &t2);
	printf("\n");
	BIN_TREE_ERGODIC_DLR(t2, myPrint);

	GRAPH_MATRIX_DESTROY(&g2);

	printf("\n");

	GRAPH_MATRIX g3;
	int** dijResult = NULL;
	int** powerMat0 = NULL, ** pathMat0 = NULL;
	int* pathRet0 = NULL;
	GRAPH_MATRIX_INIT(&g3, 6);
	for (int i = 0; i < g3.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g3, i, i);
	}
	GRAPH_MATRIX_ADD_ARC(&g3, 0, 2, 10);
	GRAPH_MATRIX_ADD_ARC(&g3, 0, 4, 30);
	GRAPH_MATRIX_ADD_ARC(&g3, 0, 5, 100);
	GRAPH_MATRIX_ADD_ARC(&g3, 1, 2, 5);
	GRAPH_MATRIX_ADD_ARC(&g3, 2, 3, 50);
	GRAPH_MATRIX_ADD_ARC(&g3, 3, 5, 10);
	GRAPH_MATRIX_ADD_ARC(&g3, 4, 3, 20);
	GRAPH_MATRIX_ADD_ARC(&g3, 4, 5, 60);
	printGraphMatrix(g3);

	GRAPH_MATRIX_SHORTEST_ROUTE_DIJKSTRA(&g3,0,&dijResult);

	printf("\n");
	for (int i = 0; i < g3.nodeCount; i++) {
		for (int k = 0; k < g3.nodeCount + 1; k++) {
			printf(" %d ", dijResult[i][k]);
		}
		printf("\n");
	}

	GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD(&g3, &powerMat0, &pathMat0);
	GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD_GET_RESULT(&g3, powerMat0, pathMat0, 3, 5, &pathRet0);

	GRAPH_MATRIX_DESTROY(&g3);

	printf("\n");

	GRAPH_MATRIX g4;
	int** powerMat = NULL, **pathMat = NULL;
	int* pathResult = NULL;
	GRAPH_MATRIX_INIT(&g4, 4);
	for (int i = 0; i < g4.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g4, i, i);
	}
	GRAPH_MATRIX_ADD_ARC(&g4, 0, 1, 1);
	GRAPH_MATRIX_ADD_ARC(&g4, 0, 3, 4);
	GRAPH_MATRIX_ADD_ARC(&g4, 1, 2, 9);
	GRAPH_MATRIX_ADD_ARC(&g4, 1, 3, 2);
	GRAPH_MATRIX_ADD_ARC(&g4, 2, 0, 3);
	GRAPH_MATRIX_ADD_ARC(&g4, 2, 1, 5);
	GRAPH_MATRIX_ADD_ARC(&g4, 2, 3, 8);
	GRAPH_MATRIX_ADD_ARC(&g4, 3, 2, 6);
	printGraphMatrix(g4);
	printf("\n");

	GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD(&g4,&powerMat,&pathMat);
	GRAPH_MATRIX_SHORTEST_ROUTE_FLOYD_GET_RESULT(&g4, powerMat, pathMat, 3, 1, &pathResult);

	for (int i = 0; i < g4.nodeCount+1; i++) {
		printf(" %d ", pathResult[i]);
	}

	GRAPH_MATRIX_DESTROY(&g4);

	printf("\n\n");

	GRAPH_MATRIX g5;
	int* topoArr = NULL;
	GRAPH_MATRIX_INIT(&g5,5);
	for (int i = 0; i < g5.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g5, i, i);
	}
	GRAPH_MATRIX_ADD_ARC(&g5, 0, 1, 1);
	GRAPH_MATRIX_ADD_ARC(&g5, 0, 2, 1);
	GRAPH_MATRIX_ADD_ARC(&g5, 1, 3, 1);
	GRAPH_MATRIX_ADD_ARC(&g5, 1, 4, 1);
	GRAPH_MATRIX_ADD_ARC(&g5, 2, 3, 1);
	GRAPH_MATRIX_ADD_ARC(&g5, 3, 4, 1);
	printGraphMatrix(g5);

	printf("\n");
	GRAPH_MATRIX_TOPOLOGY_SORT(&g5, &topoArr);
	for (int i = 0; i < g5.nodeCount; i++) {
		printf(" %d ", topoArr[i]);
	}

	GRAPH_MATRIX_DESTROY(&g5);
	printf("\n\n");

	GRAPH_MATRIX g6;
	int* keyRouteArr = NULL;
	GRAPH_MATRIX_INIT(&g6, 9);
	for (int i = 0; i < g6.nodeCount; i++) {
		GRAPH_MATRIX_PUT_NODE_VALUE(&g6, i, i);
	}
	GRAPH_MATRIX_ADD_ARC(&g6, 0, 1, 6);
	GRAPH_MATRIX_ADD_ARC(&g6, 0, 2, 4);
	GRAPH_MATRIX_ADD_ARC(&g6, 0, 3, 5);
	GRAPH_MATRIX_ADD_ARC(&g6, 1, 4, 1);
	GRAPH_MATRIX_ADD_ARC(&g6, 2, 4, 1);
	GRAPH_MATRIX_ADD_ARC(&g6, 3, 5, 2);
	GRAPH_MATRIX_ADD_ARC(&g6, 4, 6, 9);
	GRAPH_MATRIX_ADD_ARC(&g6, 4, 7, 7);
	GRAPH_MATRIX_ADD_ARC(&g6, 5, 7, 4);
	GRAPH_MATRIX_ADD_ARC(&g6, 6, 8, 2);
	GRAPH_MATRIX_ADD_ARC(&g6, 7, 8, 4);
	printGraphMatrix(g6);

	printf("\n");
	GRAPH_MATRIX_KEY_ROUTE(&g6,&keyRouteArr);

	for (int i = 0; i < g6.nodeCount; i++) {
		printf(" %d ", keyRouteArr[i]);
	}
	GRAPH_MATRIX_DESTROY(&g6);

}

void testGraphLink() {
	GRAPH_LINK g;
	GRAPH_LINK_INIT(&g,7);
	for (int i = 0; i < g.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g, i, i);
	}
	GRAPH_LINK_ADD_EDGE(&g, 0, 1, 1);
	GRAPH_LINK_ADD_EDGE(&g, 0, 2, 1);
	GRAPH_LINK_ADD_EDGE(&g, 0, 3, 1);
	GRAPH_LINK_ADD_EDGE(&g, 1, 4, 1);
	GRAPH_LINK_ADD_EDGE(&g, 1, 5, 1);
	GRAPH_LINK_ADD_EDGE(&g, 1, 6, 1);
	GRAPH_LINK_ADD_EDGE(&g, 2, 6, 1);
	GRAPH_LINK_ADD_EDGE(&g, 4, 5, 1);

	printGraphLink(g);
	printf("\n");
	GRAPH_LINK_DFS(&g, myPrint);
	printf("\n");
	GRAPH_LINK_BFS(&g, myPrint);

	GRAPH_LINK_DESTROY(&g);

	printf("\n\n");

	GRAPH_LINK g2;
	BIN_TREE* t = NULL, * t2 = NULL;
	GRAPH_LINK_INIT(&g2, 6);
	for (int i = 0; i < g2.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g2, i, i);
	}
	GRAPH_LINK_ADD_EDGE(&g2, 0, 1, 6);
	GRAPH_LINK_ADD_EDGE(&g2, 0, 3, 5);
	GRAPH_LINK_ADD_EDGE(&g2, 0, 2, 1);
	GRAPH_LINK_ADD_EDGE(&g2, 1, 2, 5);
	GRAPH_LINK_ADD_EDGE(&g2, 1, 4, 3);
	GRAPH_LINK_ADD_EDGE(&g2, 2, 4, 5);
	GRAPH_LINK_ADD_EDGE(&g2, 2, 3, 7);
	GRAPH_LINK_ADD_EDGE(&g2, 2, 5, 4);
	GRAPH_LINK_ADD_EDGE(&g2, 3, 5, 2);
	GRAPH_LINK_ADD_EDGE(&g2, 4, 5, 6);
	printGraphLink(g2);

	GRAPH_LINK_MIN_GENERATED_TREE_PRIM(&g2, &t, 0);
	printf("\n");
	BIN_TREE_ERGODIC_DLR(t, myPrint);

	GRAPH_LINK_MIN_GENERATED_TREE_KRUSKAL(&g2, &t2);
	printf("\n");
	BIN_TREE_ERGODIC_DLR(t2, myPrint);

	GRAPH_LINK_DESTROY(&g2);

	printf("\n");

	GRAPH_LINK g3;
	int** dijResult = NULL;
	int** powerMat0 = NULL, ** pathMat0 = NULL;
	int* pathRet0 = NULL;
	GRAPH_LINK_INIT(&g3, 6);
	for (int i = 0; i < g3.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g3, i, i);
	}
	GRAPH_LINK_ADD_ARC(&g3, 0, 2, 10);
	GRAPH_LINK_ADD_ARC(&g3, 0, 4, 30);
	GRAPH_LINK_ADD_ARC(&g3, 0, 5, 100);
	GRAPH_LINK_ADD_ARC(&g3, 1, 2, 5);
	GRAPH_LINK_ADD_ARC(&g3, 2, 3, 50);
	GRAPH_LINK_ADD_ARC(&g3, 3, 5, 10);
	GRAPH_LINK_ADD_ARC(&g3, 4, 3, 20);
	GRAPH_LINK_ADD_ARC(&g3, 4, 5, 60);
	printGraphLink(g3);

	GRAPH_LINK_SHORTEST_ROUTE_DIJKSTRA(&g3, 0, &dijResult);

	printf("\n");
	for (int i = 0; i < g3.nodeCount; i++) {
		for (int k = 0; k < g3.nodeCount + 1; k++) {
			printf(" %d ", dijResult[i][k]);
		}
		printf("\n");
	}

	GRAPH_LINK_SHORTEST_ROUTE_FLOYD(&g3, &powerMat0, &pathMat0);
	GRAPH_LINK_SHORTEST_ROUTE_FLOYD_GET_RESULT(&g3, powerMat0, pathMat0, 3, 5, &pathRet0);

	GRAPH_LINK_DESTROY(&g3);

	printf("\n");

	GRAPH_LINK g4;
	int** powerMat = NULL, ** pathMat = NULL;
	int* pathResult = NULL;
	GRAPH_LINK_INIT(&g4, 4);
	for (int i = 0; i < g4.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g4, i, i);
	}
	GRAPH_LINK_ADD_ARC(&g4, 0, 1, 1);
	GRAPH_LINK_ADD_ARC(&g4, 0, 3, 4);
	GRAPH_LINK_ADD_ARC(&g4, 1, 2, 9);
	GRAPH_LINK_ADD_ARC(&g4, 1, 3, 2);
	GRAPH_LINK_ADD_ARC(&g4, 2, 0, 3);
	GRAPH_LINK_ADD_ARC(&g4, 2, 1, 5);
	GRAPH_LINK_ADD_ARC(&g4, 2, 3, 8);
	GRAPH_LINK_ADD_ARC(&g4, 3, 2, 6);
	printGraphLink(g4);
	printf("\n");

	GRAPH_LINK_SHORTEST_ROUTE_FLOYD(&g4, &powerMat, &pathMat);
	GRAPH_LINK_SHORTEST_ROUTE_FLOYD_GET_RESULT(&g4, powerMat, pathMat, 3, 1, &pathResult);

	for (int i = 0; i < g4.nodeCount + 1; i++) {
		printf(" %d ", pathResult[i]);
	}

	GRAPH_LINK_DESTROY(&g4);

	printf("\n\n");

	GRAPH_LINK g5;
	int* topoArr = NULL;
	GRAPH_LINK_INIT(&g5, 5);
	for (int i = 0; i < g5.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g5, i, i);
	}
	GRAPH_LINK_ADD_ARC(&g5, 0, 1, 1);
	GRAPH_LINK_ADD_ARC(&g5, 0, 2, 1);
	GRAPH_LINK_ADD_ARC(&g5, 1, 3, 1);
	GRAPH_LINK_ADD_ARC(&g5, 1, 4, 1);
	GRAPH_LINK_ADD_ARC(&g5, 2, 3, 1);
	GRAPH_LINK_ADD_ARC(&g5, 3, 4, 1);
	printGraphLink(g5);

	printf("\n");
	GRAPH_LINK_TOPOLOGY_SORT(&g5, &topoArr);
	for (int i = 0; i < g5.nodeCount; i++) {
		printf(" %d ", topoArr[i]);
	}

	GRAPH_LINK_DESTROY(&g5);
	printf("\n\n");

	GRAPH_LINK g6;
	int* keyRouteArr = NULL;
	GRAPH_LINK_INIT(&g6, 9);
	for (int i = 0; i < g6.nodeCount; i++) {
		GRAPH_LINK_PUT_NODE_VALUE(&g6, i, i);
	}
	GRAPH_LINK_ADD_ARC(&g6, 0, 1, 6);
	GRAPH_LINK_ADD_ARC(&g6, 0, 2, 4);
	GRAPH_LINK_ADD_ARC(&g6, 0, 3, 5);
	GRAPH_LINK_ADD_ARC(&g6, 1, 4, 1);
	GRAPH_LINK_ADD_ARC(&g6, 2, 4, 1);
	GRAPH_LINK_ADD_ARC(&g6, 3, 5, 2);
	GRAPH_LINK_ADD_ARC(&g6, 4, 6, 9);
	GRAPH_LINK_ADD_ARC(&g6, 4, 7, 7);
	GRAPH_LINK_ADD_ARC(&g6, 5, 7, 4);
	GRAPH_LINK_ADD_ARC(&g6, 6, 8, 2);
	GRAPH_LINK_ADD_ARC(&g6, 7, 8, 4);
	printGraphLink(g6);

	printf("\n");
	GRAPH_LINK_KEY_ROUTE(&g6, &keyRouteArr);

	for (int i = 0; i < g6.nodeCount; i++) {
		printf(" %d ", keyRouteArr[i]);
	}
	GRAPH_LINK_DESTROY(&g6);
}

void testFind() {
	SEQ_LIST seq;
	SEQ_LIST_INIT(&seq);
	SEQ_LIST_ADD(&seq,1);
	SEQ_LIST_ADD(&seq, 3);
	SEQ_LIST_ADD(&seq, 7);
	SEQ_LIST_ADD(&seq, 8);
	SEQ_LIST_ADD(&seq, 13);
	SEQ_LIST_ADD(&seq, 16);
	SEQ_LIST_ADD(&seq, 17);

	printf("seq list:\n");
	printf(" %d\n ", SEQ_LIST_IS_CONTAIN_ELEM_SEQ(&seq, 7));
	printf(" %d\n ", SEQ_LIST_IS_CONTAIN_ELEM_SEQ(&seq, 16));
	printf(" %d\n ", SEQ_LIST_IS_CONTAIN_ELEM_BIN(&seq, 3));
	printf(" %d\n ", SEQ_LIST_IS_CONTAIN_ELEM_BIN(&seq, 16));

	LINK_LIST link;
	LINK_LIST_INIT(&link);
	LINK_LIST_ADD(&link, 1);
	LINK_LIST_ADD(&link, 3);
	LINK_LIST_ADD(&link, 7);
	LINK_LIST_ADD(&link, 8);
	LINK_LIST_ADD(&link, 13);
	LINK_LIST_ADD(&link, 16);
	LINK_LIST_ADD(&link, 17);

	printf("link list:\n");
	printf(" %d\n ", LINK_LIST_IS_CONTAIN_ELEM_SEQ(&link, 7));
	printf(" %d\n ", LINK_LIST_IS_CONTAIN_ELEM_SEQ(&link, 16));

	DL_LINK_LIST link2;
	DL_LINK_LIST_INIT(&link2);
	DL_LINK_LIST_ADD(&link2, 1);
	DL_LINK_LIST_ADD(&link2, 3);
	DL_LINK_LIST_ADD(&link2, 7);
	DL_LINK_LIST_ADD(&link2, 8);
	DL_LINK_LIST_ADD(&link2, 13);
	DL_LINK_LIST_ADD(&link2, 16);
	DL_LINK_LIST_ADD(&link2, 17);

	printf(" %d\n ", DL_LINK_LIST_IS_CONTAIN_ELEM_SEQ(&link2, 7));
	printf(" %d\n ", DL_LINK_LIST_IS_CONTAIN_ELEM_SEQ(&link2, 16));

	BIN_TREE* bt = NULL;
	BIN_TREE_ADD_ELEM(&bt, 13);
	BIN_TREE_ADD_ELEM(&bt, 7);
	BIN_TREE_ADD_ELEM(&bt, 16);
	BIN_TREE_ADD_ELEM(&bt,1);
	BIN_TREE_ADD_ELEM(&bt, 8);
	BIN_TREE_ADD_ELEM(&bt, 3);
	BIN_TREE_ADD_ELEM(&bt, 17);

	printf("bin tree:\n");
	printf("\n");
	printBinTree(bt, 0);
	printf("\n");
	printf(" %d\n ", BIN_TREE_IS_CONTAIN_ELEM(bt, 4));
	printf(" %d\n ", BIN_TREE_IS_CONTAIN_ELEM(bt, 16));

	BALANCE_BIN_TREE* bbt = NULL;
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 4); 
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 5);
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 7);
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 2);
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 1);
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 3);
	BALANCE_BIN_TREE_ADD_ELEM(&bbt, 6);

	printf("balance bin tree:\n");
	printf("\n");
	printBalanceBinTree(bbt, 0);
	printf("\n");
	printf(" %d\n ", BALANCE_BIN_TREE_IS_CONTAIN_ELEM(bbt, 3));
	printf(" %d\n ", BALANCE_BIN_TREE_IS_CONTAIN_ELEM(bbt, 7));

	HASH_ARRAY ha;
	HASH_ARRAY_INIT(&ha,20);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 1);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 3);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 5);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 21);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 41);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 61);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 81);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 2);
	HASH_ARRAY_ADD_ELEM_LINK(&ha, 3);

	printf("\nhash array :\n");
	printf("\n");
	for (int i = 0; i < ha.size; i++) {
		if (ha.data[i] != NULL) {
			printf(" %d ", ha.data[i]->data);
			HASH_ARRAY_DATA* p = ha.data[i]->next;
			if (p != NULL) {
				printf("(");
				while (p != NULL) {
					printf(" %d ", p->data);
					p = p->next;
				}
				printf(")");
			}
		}
		else {
			printf(" -1 ");
		}
	}
	printf("\n");
	printf("is contain : %d\n", HASH_ARRAY_IS_CONTAIN_ELEM_LINK(&ha, 81));
}

void testBTree() {
	B_TREE tree;
	B_TREE_INIT(&tree,3);
	B_TREE_ADD_ELEM(&tree,45);
	B_TREE_ADD_ELEM(&tree, 24);
	B_TREE_ADD_ELEM(&tree, 53);
	B_TREE_ADD_ELEM(&tree, 90);
	B_TREE_ADD_ELEM(&tree, 3);
	B_TREE_ADD_ELEM(&tree, 12);
	B_TREE_ADD_ELEM(&tree, 37);
	B_TREE_ADD_ELEM(&tree, 50);
	B_TREE_ADD_ELEM(&tree, 61);
	B_TREE_ADD_ELEM(&tree, 70); 
	B_TREE_ADD_ELEM(&tree, 100);
	// -- 
	B_TREE_ADD_ELEM(&tree, 30);
	B_TREE_ADD_ELEM(&tree, 26);
	B_TREE_ADD_ELEM(&tree, 85);
	B_TREE_ADD_ELEM(&tree, 7);

	for (int i = 0; i < tree.root->count; i++) {
		printf(" %d ", tree.root->data[i]);
	}
	printf("\n");
	for (int i = 0; i < tree.root->count + 1; i++) {
		printf(" %d ", tree.root->children[i]);
	}
	printf("\n\n");

	printBTree(tree.root, 0);

	printf("\n\n");

	printf("is contain : %d\n", B_TREE_IS_CONTAIN_ELEM(&tree, 26));
}

void testSort() {
	SEQ_LIST sl;
	SEQ_LIST_INIT(&sl);
	// -- 
	//SEQ_LIST_ADD(&sl, 21);
	//SEQ_LIST_ADD(&sl, 25);
	//SEQ_LIST_ADD(&sl, 49);
	//SEQ_LIST_ADD(&sl, 25);
	//SEQ_LIST_ADD(&sl, 16);
	//SEQ_LIST_ADD(&sl, 8);
	//SEQ_LIST_ADD(&sl, 25);
	// -- 
	//SEQ_LIST_ADD(&sl, 1);
	//SEQ_LIST_ADD(&sl, 4);
	//SEQ_LIST_ADD(&sl, 6);
	//SEQ_LIST_ADD(&sl, 7);
	//SEQ_LIST_ADD(&sl, 16);
	// -- 
	//SEQ_LIST_ADD(&sl, 16);
	//SEQ_LIST_ADD(&sl, 7);
	//SEQ_LIST_ADD(&sl, 6);
	//SEQ_LIST_ADD(&sl, 4);
	//SEQ_LIST_ADD(&sl, 1);
	// -- 
	/*SEQ_LIST_ADD(&sl, 46);
	SEQ_LIST_ADD(&sl, 8);
	SEQ_LIST_ADD(&sl, 16);
	SEQ_LIST_ADD(&sl, 23);
	SEQ_LIST_ADD(&sl, 6);
	SEQ_LIST_ADD(&sl, 1);
	SEQ_LIST_ADD(&sl, 8);
	SEQ_LIST_ADD(&sl, 56);
	SEQ_LIST_ADD(&sl, 33);
	SEQ_LIST_ADD(&sl, 22);
	SEQ_LIST_ADD(&sl, 3);
	SEQ_LIST_ADD(&sl, 9);
	SEQ_LIST_ADD(&sl, 68);
	SEQ_LIST_ADD(&sl, 72);
	SEQ_LIST_ADD(&sl, 54);
	SEQ_LIST_ADD(&sl, 41);
	SEQ_LIST_ADD(&sl, 30);
	SEQ_LIST_ADD(&sl, 29);
	SEQ_LIST_ADD(&sl, 7);*/
	// --
	//SEQ_LIST_ADD(&sl, 9);
	//SEQ_LIST_ADD(&sl, 6);

	printf("origin:\n");
	for (int i = 0; i < sl.length; i++) {
		printf(" %d ", sl.data[i]);
	}
	printf("\n");

	printf("sort:\n");
	//SEQ_LIST_INSERT_SORT(&sl);
	//SEQ_LIST_HALF_INSERT_SORT(&sl);
	//SEQ_LIST_SHELL_SORT(&sl);
	//SEQ_LIST_BUBBLE_SORT(&sl);
	//SEQ_LIST_QUICK_SORT(&sl);
	//SEQ_LIST_SELECT_SORT(&sl);
	//SEQ_LIST_MERGE_SORT(&sl);
	SEQ_LIST_HEAP_SORT(&sl);
	for (int i = 0; i < sl.length; i++) {
		printf(" %d ", sl.data[i]);
	}
	printf("\n\n\n");

	LINK_LIST ll;
	LINK_LIST_INIT(&ll);
	// -- 
	//LINK_LIST_ADD(&ll, 21);
	//LINK_LIST_ADD(&ll, 25);
	//LINK_LIST_ADD(&ll, 49);
	//LINK_LIST_ADD(&ll, 25);
	//LINK_LIST_ADD(&ll, 16);
	//LINK_LIST_ADD(&ll, 8);
	//LINK_LIST_ADD(&ll, 25);
	// -- 
	//LINK_LIST_ADD(&ll, 1);
	//LINK_LIST_ADD(&ll, 4);
	//LINK_LIST_ADD(&ll, 6);
	//LINK_LIST_ADD(&ll, 7);
	//LINK_LIST_ADD(&ll, 16);
	// -- 
	//LINK_LIST_ADD(&ll, 16);
	//LINK_LIST_ADD(&ll, 7);
	//LINK_LIST_ADD(&ll, 6);
	//LINK_LIST_ADD(&ll, 4);
	//LINK_LIST_ADD(&ll, 1);
	// -- 
	//LINK_LIST_ADD(&ll, 46);
	//LINK_LIST_ADD(&ll, 8);
	//LINK_LIST_ADD(&ll, 16);
	//LINK_LIST_ADD(&ll, 23);
	//LINK_LIST_ADD(&ll, 6);
	//LINK_LIST_ADD(&ll, 1);
	//LINK_LIST_ADD(&ll, 8);
	//LINK_LIST_ADD(&ll, 56);
	//LINK_LIST_ADD(&ll, 33);
	//LINK_LIST_ADD(&ll, 22);
	//LINK_LIST_ADD(&ll, 3);
	//LINK_LIST_ADD(&ll, 9);
	//LINK_LIST_ADD(&ll, 68);
	//LINK_LIST_ADD(&ll, 72);
	//LINK_LIST_ADD(&ll, 54);
	//LINK_LIST_ADD(&ll, 41);
	//LINK_LIST_ADD(&ll, 30);
	//LINK_LIST_ADD(&ll, 29);
	//LINK_LIST_ADD(&ll, 7);
	// --
	//LINK_LIST_ADD(&ll, 9);
	//LINK_LIST_ADD(&ll, 6);

	printf("origin:\n");
	LINK_LIST_NODE* p = ll.node;
	while (p != NULL) {
		printf(" %d ", p->data);
		p = p->next;
	}
	printf("\n");

	printf("sort:\n");
	//LINK_LIST_INSERT_SORT(&ll);
	LINK_LIST_SELECT_SORT(&ll);
	p = ll.node;
	while (p != NULL) {
		printf(" %d ", p->data);
		p = p->next;
	}
	printf("\n\n\n");

	DL_LINK_LIST dll;
	DL_LINK_LIST_INIT(&dll);
	// -- 
	//DL_LINK_LIST_ADD(&dll, 21);
	//DL_LINK_LIST_ADD(&dll, 25);
	//DL_LINK_LIST_ADD(&dll, 49);
	//DL_LINK_LIST_ADD(&dll, 25);
	//DL_LINK_LIST_ADD(&dll, 16);
	//DL_LINK_LIST_ADD(&dll, 8);
	//DL_LINK_LIST_ADD(&dll, 25);
	// -- 
	//DL_LINK_LIST_ADD(&dll, 1);
	//DL_LINK_LIST_ADD(&dll, 4);
	//DL_LINK_LIST_ADD(&dll, 6);
	//DL_LINK_LIST_ADD(&dll, 7);
	//DL_LINK_LIST_ADD(&dll, 16);
	// -- 
	//DL_LINK_LIST_ADD(&dll, 16);
	//DL_LINK_LIST_ADD(&dll, 7);
	//DL_LINK_LIST_ADD(&dll, 6);
	//DL_LINK_LIST_ADD(&dll, 4);
	//DL_LINK_LIST_ADD(&dll, 1);
	// -- 
	//DL_LINK_LIST_ADD(&dll, 46);
	//DL_LINK_LIST_ADD(&dll, 8);
	//DL_LINK_LIST_ADD(&dll, 16);
	//DL_LINK_LIST_ADD(&dll, 23);
	//DL_LINK_LIST_ADD(&dll, 6);
	//DL_LINK_LIST_ADD(&dll, 1);
	//DL_LINK_LIST_ADD(&dll, 8);
	//DL_LINK_LIST_ADD(&dll, 56);
	//DL_LINK_LIST_ADD(&dll, 33);
	//DL_LINK_LIST_ADD(&dll, 22);
	//DL_LINK_LIST_ADD(&dll, 3);
	//DL_LINK_LIST_ADD(&dll, 9);
	//DL_LINK_LIST_ADD(&dll, 68);
	//DL_LINK_LIST_ADD(&dll, 72);
	//DL_LINK_LIST_ADD(&dll, 54);
	//DL_LINK_LIST_ADD(&dll, 41);
	//DL_LINK_LIST_ADD(&dll, 30);
	//DL_LINK_LIST_ADD(&dll, 29);
	//DL_LINK_LIST_ADD(&dll, 7);
	// --
	//DL_LINK_LIST_ADD(&dll, 9);
	//DL_LINK_LIST_ADD(&dll, 6);

	printf("origin:\n");
	DL_LINK_LIST_NODE* dp = NULL;
	while (dp != dll.node) {
		if (dp == NULL) {
			dp = dll.node;
		}
		printf(" %d ", dp->data);
		dp = dp->next;
	}
	printf("\n");

	printf("sort:\n");
	//DL_LINK_LIST_INSERT_SORT(&dll);
	DL_LINK_LIST_SELECT_SORT(&dll);
	dp = NULL;
	while (dp != dll.node) {
		if (dp == NULL) {
			dp = dll.node;
		}
		printf(" %d ", dp->data);
		dp = dp->next;
	}
	printf("\n\n\n");
}

int main() {

	testSort();

	return 0;
}
