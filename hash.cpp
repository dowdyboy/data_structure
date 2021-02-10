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
	int hash_idx = data % hash->size;
	int idx = -1;
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		if (hash->data[i % hash->size] == NULL) {
			idx = i % hash->size;
			break;
		}
		else if (hash->data[i % hash->size]->data == data) {
			return STATUS_SUCCESS;
		}
	}
	if (idx > -1) {
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		int idx = i % hash->size;
		if (hash->data[idx] == NULL) {
			return BOOLEAN_FALSE;
		}
		else if (hash->data[idx]->data == data) {
			return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS HASH_ARRAY_ADD_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;
	int idx = -1;
	for (int i = 0; 0 < 1; i++) {
		int x = hash_idx + i * i;
		int y = hash_idx - i * i;
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) break;
		if (x >= 0 && x < hash->size) {
			if (hash->data[x] == NULL) {
				idx = x;
				break;
			}
			else if (hash->data[x]->data == data) {
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
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;
	for (int i = 0; 0 < 1; i++) {
		int x = hash_idx + i * i;
		int y = hash_idx - i * i;
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) return BOOLEAN_FALSE;
		if (x >= 0 && x < hash->size) {
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
	int hash_idx = data % hash->size;
	HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
	d->data = data;
	d->next = NULL;
	if (hash->data[hash_idx] == NULL) {
		hash->data[hash_idx] = d;
	}
	else {
		HASH_ARRAY_DATA* p = hash->data[hash_idx];
		while (p->next != NULL) {
			if (p->data == data) {
				return STATUS_SUCCESS;
			}
			p = p->next;
		}
		if (p->data == data) {
			return STATUS_SUCCESS;
		}
		else {
			p->next = d;
		}
	}
	return STATUS_SUCCESS;
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;
	HASH_ARRAY_DATA* p = hash->data[hash_idx];
	while (p != NULL) {
		if (p->data == data) {
			return BOOLEAN_TRUE;
		}
		p = p->next;
	}
	return BOOLEAN_FALSE;
}

