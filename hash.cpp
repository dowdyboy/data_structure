#include "hash.h"

STATUS HASH_ARRAY_INIT(HASH_ARRAY* hash, int size) {
	hash->data = (HASH_ARRAY_DATA**)malloc(sizeof(HASH_ARRAY_DATA*) * size);
	hash->size = size;
	for (int i = 0; i < size; i++) {
		hash->data[i] = NULL;
	}
	return STATUS_SUCCESS;
}

STATUS HASH_ARRAY_ADD_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算的hash位置
	int idx = -1;  // 记录最终存放位置
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		// 从计算hash位置向后开始顺序查找
		if (hash->data[i % hash->size] == NULL) {
			// 如果找到了一个为空的位置，则该位置即最终存放位置
			idx = i % hash->size;
			break;
		}
		else if (hash->data[i % hash->size]->data == data) {
			// 如果寻找的过程中，发现了要存放的元素，直接返回
			return STATUS_SUCCESS;
		}
	}
	if (idx > -1) {
		// 如果找到了位置，则存放元素后返回
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		// 空间已满，返回失败
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算hash位置
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		// 从hash位置向后开始查找
		int idx = i % hash->size;
		if (hash->data[idx] == NULL) {
			// 如果查找过程中，发现了空位，则表示要查询的元素不存在
			return BOOLEAN_FALSE;
		}
		else if (hash->data[idx]->data == data) {
			// 找到返回成功
			return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS HASH_ARRAY_ADD_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算hash位置
	int idx = -1;  // 记录最终存放位置
	for (int i = 0; 0 < 1; i++) {
		int x = hash_idx + i * i;  // 向后二次计算的下一个位置
		int y = hash_idx - i * i;  // 向前二次计算的下一个位置
		// 如果位置超过了索引范围，则表明查询失败
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) break;
		if (x >= 0 && x < hash->size) {
			if (hash->data[x] == NULL) {
				// 找到空位置，表名查询成功
				idx = x;
				break;
			}
			else if (hash->data[x]->data == data) {
				// 如果寻找的过程中，发现了要存放的元素，直接返回
				return STATUS_SUCCESS;
			}
		}
		if (y >= 0 && y < hash->size) {
			if (hash->data[y] == NULL) {
				idx = y;
				break;
			}
			else if (hash->data[y]->data == data) {
				return STATUS_SUCCESS;
			}
		}
	}
	if (idx > -1) {
		// 如果找到了位置，则存放元素后返回
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		// 空间已满，返回失败
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算hash位置
	for (int i = 0; 0 < 1; i++) {
		// 计算二次位置
		int x = hash_idx + i * i;
		int y = hash_idx - i * i;
		// 如果二次位置超过范围，则没找到
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) return BOOLEAN_FALSE;
		if (x >= 0 && x < hash->size) {
			// 如果找到的位置为空，表明没有该查询元素
			// 如果找到了，返回成功
			if(hash->data[x] == NULL) return BOOLEAN_FALSE;
			else if(hash->data[x]->data == data) return BOOLEAN_TRUE;
		}
		if (y >= 0 && y < hash->size) {
			if (hash->data[y] == NULL) return BOOLEAN_FALSE;
			else if (hash->data[y]->data == data) return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS HASH_ARRAY_ADD_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算hash位置
	HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
	d->data = data;
	d->next = NULL;
	if (hash->data[hash_idx] == NULL) {
		// 如果位置为空，将元素放入该位置
		hash->data[hash_idx] = d;
	}
	else {
		// 否则，遍历拉链
		HASH_ARRAY_DATA* p = hash->data[hash_idx];
		while (p->next != NULL) {
			if (p->data == data) {
				// 如果寻找的过程中，发现了要存放的元素，直接返回
				return STATUS_SUCCESS;
			}
			p = p->next;
		}
		if (p->data == data) {
			// 如果寻找的过程中，发现了要存放的元素，直接返回
			return STATUS_SUCCESS;
		}
		else {
			// 将新元素加入拉链末尾
			p->next = d;
		}
	}
	return STATUS_SUCCESS;
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // 计算hash位置
	HASH_ARRAY_DATA* p = hash->data[hash_idx];
	// 遍历拉链
	while (p != NULL) {
		if (p->data == data) {
			// 如果找到，返回成功
			return BOOLEAN_TRUE;
		}
		p = p->next;
	}
	return BOOLEAN_FALSE;
}

