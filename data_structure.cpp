
#include "stdio.h"
#include "seq_list.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"
#include "chars.h"

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

int main() {

	testChars();

	return 0;
}
