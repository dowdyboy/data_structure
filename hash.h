#ifndef HASH_H
#define HASH_H

#include "basis.h"

typedef struct _hash_array_data {
	ELEM_TYPE data;
	_hash_array_data* next;
} HASH_ARRAY_DATA;

typedef struct _hash_array {
	HASH_ARRAY_DATA** data;
	int size;
} HASH_ARRAY;

STATUS HASH_ARRAY_INIT(HASH_ARRAY* hash, int size);  // ��ʼ��

STATUS HASH_ARRAY_ADD_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data);  // ���Ԫ�أ�˳��̽�飩

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data);  // �ж�Ԫ���Ƿ���ڣ�˳��̽�飩

STATUS HASH_ARRAY_ADD_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data);  // ���Ԫ�أ�����̽�飩

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data);  // �ж�Ԫ���Ƿ���ڣ�����̽�飩

STATUS HASH_ARRAY_ADD_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data);  // ���Ԫ�أ�����̽�飩

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data);  // �ж�Ԫ���Ƿ���ڣ�����̽�飩

#endif // !HASH_H
