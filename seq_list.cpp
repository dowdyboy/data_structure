
#include "seq_list.h"

STATUS SEQ_LIST_INIT(SEQ_LIST* list) {
	list->data = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE) * SEQ_LIST_INIT_SIZE);
	list->length = 0;
	list->max_size = SEQ_LIST_INIT_SIZE;
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_INSERT(SEQ_LIST* list, int idx, ELEM_TYPE data) {
	if (idx < 0 || idx > list->length) return STATUS_FAIL;
	// 判断是否超出长度，进行拓展数组长度
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
	// 定义下索引和上索引
	int low = 0, high = list->length - 1;
	// 如果下索引小于等于上索引
	while (low <= high) {
		// 计算中间索引
		int mid = (low + high) / 2;
		if (list->data[mid] == data) {
			// 查找到，返回
			return BOOLEAN_TRUE;
		}
		else if (list->data[mid] > data) {
			// 如果要查的数据比中间索引数据小，则数据可能在前半段，更新上索引
			high = mid - 1;
		}
		else {
			// 否则数据可能在后半段，更新下索引
			low = mid + 1;
		}
	}
	return BOOLEAN_FALSE;
}

STATUS SEQ_LIST_INSERT_SORT(SEQ_LIST* list) {
	for (int i = 1; i < list->length; i++) {
		ELEM_TYPE tmp = list->data[i];
		BOOLEAN isInsert = BOOLEAN_FALSE;
		// 在前面已经有序的元素中寻找要插入的位置（从后向前找）
		for (int k = i - 1; k >= 0; k--) {
			if (tmp > list->data[k]) {
				// 如果找到了一个比当前元素小的，则将当前元素插入到这个元素之后
				list->data[k + 1] = tmp;
				isInsert = BOOLEAN_TRUE;
				break;
			}
			else {
				// 否则将元素依次向后移动
				list->data[k + 1] = list->data[k];
			}
		}
		if (!isInsert) {
			// 如果上面的过程中没有找到插入位置，则将当前元素插入在开头位置
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
		// 采用折半查找法，找当前元素要插入的位置
		while (low <= high) {
			int mid = (low + high) / 2;
			if (list->data[mid] < tmp) {
				low = mid + 1;
			}
			else if (list->data[mid] > tmp) {
				high = mid - 1;
			}
			else {
				// 找到与当前元素相同的，则可将当前元素插入到这个位置，其余元素依次后移
				idx = mid;
				break;
			}
		}
		if(idx == -1) idx = low;
		// 将元素依次后移，腾出位置
		for (int k = i - 1; k >= idx; k--) {
			list->data[k + 1] = list->data[k];
		}
		list->data[idx] = tmp;
	}
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_SHELL_SORT(SEQ_LIST* list) {
	// 计算步长
	int dk = list->length < 3 ? 1 : list->length % 2 == 0 ? list->length - 1 : list->length - 2;
	while (dk >= 1) {
		// 依据步长，执行插入排序
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
		// 缩短步长，进行下一次插入排序
		dk -= 2;
	}
	return STATUS_SUCCESS;
}

STATUS SEQ_LIST_BUBBLE_SORT(SEQ_LIST* list) {
	for (int i = list->length; i >= 0; i--) {
		BOOLEAN isSwap = BOOLEAN_FALSE;
		for (int k = 1; k < i; k++) {
			// 比较相邻元素，将大的向后冒泡
			if (list->data[k - 1] > list->data[k]) {
				ELEM_TYPE tmp = list->data[k - 1];
				list->data[k - 1] = list->data[k];
				list->data[k] = tmp;
				isSwap = BOOLEAN_TRUE;
			}
		}
		// 如果上面没有发生过交换，则表明已经有序了，退出循环
		if (!isSwap) break;
	}
	return STATUS_SUCCESS;
}

void _seq_list_quick_sort(SEQ_LIST* list, int low, int high) {
	if (low < high) {
		int ori_low = low, ori_high = high;
		ELEM_TYPE t = list->data[low];  // 将基准元素暂存
		while (low < high) {
			// 高索引向前移动，直到找到比基准元素小的
			while (low < high && list->data[high] >= t) high--;
			if (low < high) {
				// 进行位置交换
				list->data[low] = list->data[high];
				low++;
			}
			// 低索引向后移动，直到找到比基准元素大的
			while (low < high && list->data[low] <= t) low++;
			if (low < high) {
				// 进行位置交换
				list->data[high] = list->data[low];
				high--;
			}
		}
		// 将基准元素放在最终确定的位置上
		list->data[low] = t;
		// 递归调用，对基准之前和基准之后的元素分别进行快排
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
			// 在当前元素之后的元素中选出最小的
			if (list->data[k] < min) {
				min = list->data[k];
				min_idx = k;
			}
		}
		// 将选出的最小元素和当前元素交换
		min = list->data[i];
		list->data[i] = list->data[min_idx];
		list->data[min_idx] = min;
	}
	return STATUS_SUCCESS;
}

void _seq_list_heap_sort(SEQ_LIST* list,int idx,int limit) {
	int l_idx = idx * 2 + 1, r_idx = idx * 2 + 2;  // 计算当前节点的左孩子和右孩子的位置索引
	int max_val_idx = idx;
	// 如果当前索引还属于非叶节点索引，则执行循环
	while (idx < limit / 2) {
		// 在当前节点，左孩子，右孩子中选出值最大的节点索引
		if (l_idx < limit && list->data[l_idx] > list->data[max_val_idx]) max_val_idx = l_idx;
		if (r_idx < limit && list->data[r_idx] > list->data[max_val_idx]) max_val_idx = r_idx;
		if (max_val_idx != idx) {
			// 如果最大索引不是当前节点，则将最大索引和当前索引位置对换
			ELEM_TYPE tmp = list->data[idx];
			list->data[idx] = list->data[max_val_idx];
			list->data[max_val_idx] = tmp;
			// 并将当前索引下移，和计算新的左右孩子索引
			idx = max_val_idx;
			l_idx = idx * 2 + 1;
			r_idx = idx * 2 + 2;
		}
		else {
			// 否则的话，则认为堆调整完毕，退出循环
			break;
		}
	}
}

STATUS SEQ_LIST_HEAP_SORT(SEQ_LIST* list) {
	// 先将序列调整为大根堆（从第一个非叶节点，向前调整）
	for (int i = list->length / 2 - 1; i >= 0; i--) {
		_seq_list_heap_sort(list,i,list->length);
	}
	// 依次将堆顶交换到末尾位置，并再次调整成堆
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
		int mid = (low + high) / 2;  // 计算中间位置
		// 将前半和后半依次递归调用归并排序
		_seq_list_merge_sort(list, low, mid);
		_seq_list_merge_sort(list, mid + 1, high);
		// 分配临时存储空间
		ELEM_TYPE* tmp = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * list->length);
		int a = low, b = mid + 1;
		int idx = low;
		// 在已经排好序的前半和后半序列，选择小的元素放在临时空间
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
		// 将排好序的元素移到原数组中，并释放临时空间
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
