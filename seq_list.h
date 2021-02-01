#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include "basis.h"

#define SEQ_LIST_INIT_SIZE 10
#define SEQ_LIST_INC_SIZE 5

// 顺序表定义
typedef struct _seq_list {
	ELEM_TYPE *data;
	int length;
	int max_size;
} SEQ_LIST;

STATUS SEQ_LIST_INIT(SEQ_LIST* list); // 初始化

STATUS SEQ_LIST_INSERT(SEQ_LIST* list,int idx,ELEM_TYPE data); // 插入

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data); // 末尾添加

STATUS SEQ_LIST_DELETE(SEQ_LIST* list,int idx); // 删除

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list); // 清空

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data); // 修改

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE *result); // 获取

STATUS SEQ_LIST_DESTORY(SEQ_LIST* list);  // 销毁

// ============= 查找 / 排序 ===============

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_SEQ(SEQ_LIST* list, ELEM_TYPE data);  // 顺序查找

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_BIN(SEQ_LIST* list, ELEM_TYPE data);  // 折半查找

#endif
