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
	int hash_idx = data % hash->size;  // �����hashλ��
	int idx = -1;  // ��¼���մ��λ��
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		// �Ӽ���hashλ�����ʼ˳�����
		if (hash->data[i % hash->size] == NULL) {
			// ����ҵ���һ��Ϊ�յ�λ�ã����λ�ü����մ��λ��
			idx = i % hash->size;
			break;
		}
		else if (hash->data[i % hash->size]->data == data) {
			// ���Ѱ�ҵĹ����У�������Ҫ��ŵ�Ԫ�أ�ֱ�ӷ���
			return STATUS_SUCCESS;
		}
	}
	if (idx > -1) {
		// ����ҵ���λ�ã�����Ԫ�غ󷵻�
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		// �ռ�����������ʧ��
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_SEQ(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // ����hashλ��
	for (int i = hash_idx; i < hash_idx + hash->size; i++) {
		// ��hashλ�����ʼ����
		int idx = i % hash->size;
		if (hash->data[idx] == NULL) {
			// ������ҹ����У������˿�λ�����ʾҪ��ѯ��Ԫ�ز�����
			return BOOLEAN_FALSE;
		}
		else if (hash->data[idx]->data == data) {
			// �ҵ����سɹ�
			return BOOLEAN_TRUE;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS HASH_ARRAY_ADD_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // ����hashλ��
	int idx = -1;  // ��¼���մ��λ��
	for (int i = 0; 0 < 1; i++) {
		int x = hash_idx + i * i;  // �����μ������һ��λ��
		int y = hash_idx - i * i;  // ��ǰ���μ������һ��λ��
		// ���λ�ó�����������Χ���������ѯʧ��
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) break;
		if (x >= 0 && x < hash->size) {
			if (hash->data[x] == NULL) {
				// �ҵ���λ�ã�������ѯ�ɹ�
				idx = x;
				break;
			}
			else if (hash->data[x]->data == data) {
				// ���Ѱ�ҵĹ����У�������Ҫ��ŵ�Ԫ�أ�ֱ�ӷ���
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
		// ����ҵ���λ�ã�����Ԫ�غ󷵻�
		HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
		d->data = data;
		d->next = NULL;
		hash->data[idx] = d;
		return STATUS_SUCCESS;
	}
	else {
		// �ռ�����������ʧ��
		return STATUS_FAIL;
	}
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_DOUBLE(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // ����hashλ��
	for (int i = 0; 0 < 1; i++) {
		// �������λ��
		int x = hash_idx + i * i;
		int y = hash_idx - i * i;
		// �������λ�ó�����Χ����û�ҵ�
		if ((x < 0 || x >= hash->size) && (y < 0 || y >= hash->size)) return BOOLEAN_FALSE;
		if (x >= 0 && x < hash->size) {
			// ����ҵ���λ��Ϊ�գ�����û�иò�ѯԪ��
			// ����ҵ��ˣ����سɹ�
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
	int hash_idx = data % hash->size;  // ����hashλ��
	HASH_ARRAY_DATA* d = (HASH_ARRAY_DATA*)malloc(sizeof(HASH_ARRAY_DATA));
	d->data = data;
	d->next = NULL;
	if (hash->data[hash_idx] == NULL) {
		// ���λ��Ϊ�գ���Ԫ�ط����λ��
		hash->data[hash_idx] = d;
	}
	else {
		// ���򣬱�������
		HASH_ARRAY_DATA* p = hash->data[hash_idx];
		while (p->next != NULL) {
			if (p->data == data) {
				// ���Ѱ�ҵĹ����У�������Ҫ��ŵ�Ԫ�أ�ֱ�ӷ���
				return STATUS_SUCCESS;
			}
			p = p->next;
		}
		if (p->data == data) {
			// ���Ѱ�ҵĹ����У�������Ҫ��ŵ�Ԫ�أ�ֱ�ӷ���
			return STATUS_SUCCESS;
		}
		else {
			// ����Ԫ�ؼ�������ĩβ
			p->next = d;
		}
	}
	return STATUS_SUCCESS;
}

BOOLEAN HASH_ARRAY_IS_CONTAIN_ELEM_LINK(HASH_ARRAY* hash, ELEM_TYPE data) {
	int hash_idx = data % hash->size;  // ����hashλ��
	HASH_ARRAY_DATA* p = hash->data[hash_idx];
	// ��������
	while (p != NULL) {
		if (p->data == data) {
			// ����ҵ������سɹ�
			return BOOLEAN_TRUE;
		}
		p = p->next;
	}
	return BOOLEAN_FALSE;
}

