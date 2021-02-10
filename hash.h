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

STATUS HASH_ARRAY_INIT(HASH_ARRAY* hash, int size);  // 初始化

STATUS HASH_ARRAY_ADD_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data);  // 添加元素（顺序探查）

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data);  // 判断元素是否存在（顺序探查）

STATUS HASH_ARRAY_ADD_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data);  // 添加元素（二次探查）

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data);  // 判断元素是否存在（二次探查）

STATUS HASH_ARRAY_ADD_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data);  // 添加元素（拉链探查）

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data);  // 判断元素是否存在（拉链探查）

#endif // !HASH_H
