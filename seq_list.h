#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include "basis.h"

#define SEQ_LIST_INIT_SIZE 10
#define SEQ_LIST_INC_SIZE 5

// À≥–Ú±Ì∂®“Â
typedef struct _seq_list {
	ELEM_TYPE *data;
	int length;
	int max_size;
} SEQ_LIST;

STATUS SEQ_LIST_INIT(SEQ_LIST* list); // ≥ı ºªØ

STATUS SEQ_LIST_INSERT(SEQ_LIST* list,int idx,ELEM_TYPE data); // ≤Â»Î

STATUS SEQ_LIST_ADD(SEQ_LIST* list, ELEM_TYPE data); // ƒ©Œ≤ÃÌº”

STATUS SEQ_LIST_DELETE(SEQ_LIST* list,int idx); // …æ≥˝

STATUS SEQ_LIST_CLEAR(SEQ_LIST* list); // «Âø’

STATUS SEQ_LIST_PUT(SEQ_LIST* list, int idx, ELEM_TYPE data); // –ﬁ∏ƒ

STATUS SEQ_LIST_GET(SEQ_LIST* list, int idx, ELEM_TYPE *result); // ªÒ»°

STATUS SEQ_LIST_DESTORY(SEQ_LIST* list);  // œ˙ªŸ

// ============= ≤È’“ / ≈≈–Ú ===============

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_SEQ(SEQ_LIST* list, ELEM_TYPE data);  // À≥–Ú≤È’“

BOOLEAN SEQ_LIST_IS_CONTAIN_ELEM_BIN(SEQ_LIST* list, ELEM_TYPE data);  // ’€∞Î≤È’“

STATUS SEQ_LIST_INSERT_SORT(SEQ_LIST* list);  // ÷±Ω”≤Â»Î≈≈–Ú

STATUS SEQ_LIST_HALF_INSERT_SORT(SEQ_LIST* list);  // ’€∞Î≤Â»Î≈≈–Ú

STATUS SEQ_LIST_SHELL_SORT(SEQ_LIST* list);  // œ£∂˚≈≈–Ú

STATUS SEQ_LIST_BUBBLE_SORT(SEQ_LIST* list);  // √∞≈›≈≈–Ú

STATUS SEQ_LIST_QUICK_SORT(SEQ_LIST* list);  // øÏÀŸ≈≈–Ú

STATUS SEQ_LIST_SELECT_SORT(SEQ_LIST* list);  // —°‘Ò≈≈–Ú

STATUS SEQ_LIST_HEAP_SORT(SEQ_LIST* list);  // ∂—≈≈–Ú

STATUS SEQ_LIST_MERGE_SORT(SEQ_LIST* list);  // πÈ≤¢≈≈–Ú


#endif
