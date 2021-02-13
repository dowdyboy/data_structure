
#include "seq_list.h"

STATUS SEQ_LIST_INIT(SEQ_LIST* list) {
	list->data = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE) * SEQ_LIST_INIT_SIZE);
	list->length = 0;
	list->max_size = SEQ_LIST_INIT_SIZE;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_INSERT(SEQ_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length) return STATUS_FAIL;
	// �ж��Ƿ񳬳����ȣ�������չ���鳤��
	if(list->length+1 > list->max_size) {
		ELEM_TYPE* old_data = list->data;
		list->data = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * (list->max_size + SEQ_LIST_INC_SIZE));
		for (int i = 0; i < list->max_size; i++) {
			list->data[i] = old_data[i];
		}
		list->max_size += SEQ_LIST_INC_SIZE;
		free(old_data);
	}
	for (int i = list->length - 1; i >= idx; i--) {
		list->data[i + 1] = list->data[i];
	}
	list->data[idx] = data;
	list->length += 1;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data) {
	return SEQ_LIST_INSERT(list, list->length, data);
}

STATUS SEQ_LIST_DELETE(SEQ_LIST* list, int idx) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	for (int i = idx; i < list->length - 1; i++) {
		list->data[i] = list->data[i + 1];
	}
	list->length -= 1;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list) {
	ELEM_TYPE* old_data = list->data;
	SEQ_LIST_INIT(list);
	free(old_data);
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length - 1) {
		return STATUS_FAIL;
	}
	list->data[idx] = data;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE* result) {
	if (idx < 0 || idx > list->length - 1) return STATUS_FAIL;
	*result = list->data[idx];
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_DESTORY(SEQ_LIST* list) {
	ELEM_TYPE* old_data = list->data;
	list->data = NULL;
	list->length = 0;
	list->max_size = 0;
	if (old_data != NULL) free(old_data);
	return STATUS_SUCCESS;
}

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_SEQ(SEQ_LIST* list, ELEM_TYPE data) {
	for (int i = 0; i < list->length; i++) {
		if (list->data[i] == data) return BOOLEAN_TRUE;
	}
	return BOOLEAN_FALSE;
}

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_BIN(SEQ_LIST* list, ELEM_TYPE data) {
	// ������������������
	int low = 0, high = list->length - 1;
	// ���������С�ڵ���������
	while (low <= high) {
		// �����м�����
		int mid = (low + high) / 2;
		if (list->data[mid] == data) {
			// ���ҵ�������
			return BOOLEAN_TRUE;
		}
		else if (list->data[mid] > data) {
			// ���Ҫ������ݱ��м���������С�������ݿ�����ǰ��Σ�����������
			high = mid - 1;
		}
		else {
			// �������ݿ����ں��Σ�����������
			low = mid + 1;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS SEQ_LIST_INSERT_SORT(SEQ_LIST* list) {
	for (int i = 1; i < list->length; i++) {
		ELEM_TYPE tmp = list->data[i];
		BOOLEAN isInsert = BOOLEAN_FALSE;
		// ��ǰ���Ѿ������Ԫ����Ѱ��Ҫ�����λ�ã��Ӻ���ǰ�ң�
		for (int k = i - 1; k >= 0; k--) {
			if (tmp > list->data[k]) {
				// ����ҵ���һ���ȵ�ǰԪ��С�ģ��򽫵�ǰԪ�ز��뵽���Ԫ��֮��
				list->data[k + 1] = tmp;
				isInsert = BOOLEAN_TRUE;
				break;
			}
			else {
				// ����Ԫ����������ƶ�
				list->data[k + 1] = list->data[k];
			}
		}
		if (!isInsert) {
			// �������Ĺ�����û���ҵ�����λ�ã��򽫵�ǰԪ�ز����ڿ�ͷλ��
			list->data[0] = tmp;
		}
	}
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_HALF_INSERT_SORT(SEQ_LIST* list) {
	for (int i = 1; i < list->length; i++) {
		ELEM_TYPE tmp = list->data[i];
		int low = 0, high = i - 1;
		int idx = -1;
		// �����۰���ҷ����ҵ�ǰԪ��Ҫ�����λ��
		while (low <= high) {
			int mid = (low + high) / 2;
			if (list->data[mid] < tmp) {
				low = mid + 1;
			}
			else if (list->data[mid] > tmp) {
				high = mid - 1;
			}
			else {
				// �ҵ��뵱ǰԪ����ͬ�ģ���ɽ���ǰԪ�ز��뵽���λ�ã�����Ԫ�����κ���
				idx = mid;
				break;
			}
		}
		if(idx == -1) idx = low;
		// ��Ԫ�����κ��ƣ��ڳ�λ��
		for (int k = i - 1; k >= idx; k--) {
			list->data[k + 1] = list->data[k];
		}
		list->data[idx] = tmp;
	}
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_SHELL_SORT(SEQ_LIST* list) {
	// ���㲽��
	int dk = list->length < 3 ? 1 : list->length % 2 == 0 ? list->length - 1 : list->length - 2;
	while (dk >= 1) {
		// ���ݲ�����ִ�в�������
		for (int i = dk; i < list->length; i += dk) {
			ELEM_TYPE tmp = list->data[i];
			BOOLEAN isInsert = BOOLEAN_FALSE;
			for (int k = i - dk; k >= 0; k -= dk) {
				if (tmp > list->data[k]) {
					list->data[k + dk] = tmp;
					isInsert = BOOLEAN_TRUE;
					break;
				}
				else {
					list->data[k + dk] = list->data[k];
				}
			}
			if (!isInsert) {
				list->data[0] = tmp;
			}
		}
		// ���̲�����������һ�β�������
		dk -= 2;
	}
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_BUBBLE_SORT(SEQ_LIST* list) {
	for (int i = list->length; i >= 0; i--) {
		BOOLEAN isSwap = BOOLEAN_FALSE;
		for (int k = 1; k < i; k++) {
			// �Ƚ�����Ԫ�أ���������ð��
			if (list->data[k - 1] > list->data[k]) {
				ELEM_TYPE tmp = list->data[k - 1];
				list->data[k - 1] = list->data[k];
				list->data[k] = tmp;
				isSwap = BOOLEAN_TRUE;
			}
		}
		// �������û�з�����������������Ѿ������ˣ��˳�ѭ��
		if (!isSwap) break;
	}
	return STATUS_SUCCESS;
}

void _seq_list_quick_sort(SEQ_LIST* list, int low, int high) {
	if (low < high) {
		int ori_low = low, ori_high = high;
		ELEM_TYPE t = list->data[low];  // ����׼Ԫ���ݴ�
		while (low < high) {
			// ��������ǰ�ƶ���ֱ���ҵ��Ȼ�׼Ԫ��С��
			while (low < high && list->data[high] >= t) high--;
			if (low < high) {
				// ����λ�ý���
				list->data[low] = list->data[high];
				low++;
			}
			// ����������ƶ���ֱ���ҵ��Ȼ�׼Ԫ�ش��
			while (low < high && list->data[low] <= t) low++;
			if (low < high) {
				// ����λ�ý���
				list->data[high] = list->data[low];
				high--;
			}
		}
		// ����׼Ԫ�ط�������ȷ����λ����
		list->data[low] = t;
		// �ݹ���ã��Ի�׼֮ǰ�ͻ�׼֮���Ԫ�طֱ���п���
		_seq_list_quick_sort(list, ori_low, low - 1);
		_seq_list_quick_sort(list, low + 1, ori_high);
	}
}

STATUS SEQ_LIST_QUICK_SORT(SEQ_LIST* list) {
	_seq_list_quick_sort(list, 0, list->length - 1);
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_SELECT_SORT(SEQ_LIST* list) {
	for (int i = 0; i < list->length; i++) {
		ELEM_TYPE min = list->data[i];
		int min_idx = i;
		for (int k = i; k < list->length; k++) {
			// �ڵ�ǰԪ��֮���Ԫ����ѡ����С��
			if (list->data[k] < min) {
				min = list->data[k];
				min_idx = k;
			}
		}
		// ��ѡ������СԪ�غ͵�ǰԪ�ؽ���
		min = list->data[i];
		list->data[i] = list->data[min_idx];
		list->data[min_idx] = min;
	}
	return STATUS_SUCCESS;
}

void _seq_list_heap_sort(SEQ_LIST* list,int idx,int limit) {
	int l_idx = idx * 2 + 1, r_idx = idx * 2 + 2;  // ���㵱ǰ�ڵ�����Ӻ��Һ��ӵ�λ������
	int max_val_idx = idx;
	// �����ǰ���������ڷ�Ҷ�ڵ���������ִ��ѭ��
	while (idx < limit / 2) {
		// �ڵ�ǰ�ڵ㣬���ӣ��Һ�����ѡ��ֵ���Ľڵ�����
		if (l_idx < limit && list->data[l_idx] > list->data[max_val_idx]) max_val_idx = l_idx;
		if (r_idx < limit && list->data[r_idx] > list->data[max_val_idx]) max_val_idx = r_idx;
		if (max_val_idx != idx) {
			// �������������ǵ�ǰ�ڵ㣬����������͵�ǰ����λ�öԻ�
			ELEM_TYPE tmp = list->data[idx];
			list->data[idx] = list->data[max_val_idx];
			list->data[max_val_idx] = tmp;
			// ������ǰ�������ƣ��ͼ����µ����Һ�������
			idx = max_val_idx;
			l_idx = idx * 2 + 1;
			r_idx = idx * 2 + 2;
		}
		else {
			// ����Ļ�������Ϊ�ѵ�����ϣ��˳�ѭ��
			break;
		}
	}
}

STATUS SEQ_LIST_HEAP_SORT(SEQ_LIST* list) {
	// �Ƚ����е���Ϊ����ѣ��ӵ�һ����Ҷ�ڵ㣬��ǰ������
	for (int i = list->length / 2 - 1; i >= 0; i--) {
		_seq_list_heap_sort(list,i,list->length);
	}
	// ���ν��Ѷ�������ĩβλ�ã����ٴε����ɶ�
	for (int i = list->length - 1; i >= 1; i--) {
		ELEM_TYPE tmp = list->data[0];
		list->data[0] = list->data[i];
		list->data[i] = tmp;
		_seq_list_heap_sort(list, 0, i);
	}
	return STATUS_SUCCESS;
}

void _seq_list_merge_sort(SEQ_LIST* list, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;  // �����м�λ��
		// ��ǰ��ͺ�����εݹ���ù鲢����
		_seq_list_merge_sort(list, low, mid);
		_seq_list_merge_sort(list, mid + 1, high);
		// ������ʱ�洢�ռ�
		ELEM_TYPE* tmp = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * list->length);
		int a = low, b = mid + 1;
		int idx = low;
		// ���Ѿ��ź����ǰ��ͺ�����У�ѡ��С��Ԫ�ط�����ʱ�ռ�
		while (a <= mid && b <= high) {
			if (list->data[a] <= list->data[b]) {
				tmp[idx++] = list->data[a++];
			}
			else {
				tmp[idx++] = list->data[b++];
			}
		}
		while(a <= mid) tmp[idx++] = list->data[a++];
		while(b <= high) tmp[idx++] = list->data[b++];
		// ���ź����Ԫ���Ƶ�ԭ�����У����ͷ���ʱ�ռ�
		for (int i = low; i <= high; i++) {
			list->data[i] = tmp[i];
		}
		free(tmp);
	}
}

STATUS SEQ_LIST_MERGE_SORT(SEQ_LIST* list) {
	_seq_list_merge_sort(list, 0, list->length - 1);
	return STATUS_SUCCESS;
}
