#include "chars.h"

int IndexOf_BF(const char* src, const char* mat) {
	int srcLen = strlen(src), matLen = strlen(mat);
	int idx = 0;
	while (srcLen - idx >= matLen) {
		int i = 0;
		for (i = 0; i < matLen; i++) {
			if (src[idx + i] != mat[i]) break;
		}
		if (i == matLen) return idx;
		idx++;
	}
	return -1;
}

int IndexOf_KMP(const char* src, const char* mat) {
	int srcLen = strlen(src), matLen = strlen(mat);
	// 这里必须多分配一个空间，否则free会崩溃
	int* next = (int*)malloc(sizeof(int) * (matLen+1));
	int* nextval = (int*)malloc(sizeof(int) * (matLen + 1));
	int i = 0, j = 0;

	// 构建next数组
	next[0] = 0;
	while (i < matLen) {
		// 如果j为0，说明已经无法回退，i+1前即没有重复子串，将i+1设置为1；
		// 如果j不为0，而i和j-1的位置元素一样，表示i+1前有重复子串，则将i+1的位置设置为j；
		if (j == 0 || mat[i] == mat[j-1]) {
			i++;
			j++;
			next[i] = j;
		}
		else {
			// 如果i和j-1的位置元素不一样，则表示i处子串和j-1处子串是不重复的，则将j回退到上一个匹配的重复子串；
			j = next[j-1];
		}
	}

	// 构建nextval数组
	nextval[0] = next[0];
	for (i = 1; i < matLen; i++) {
		if (mat[i] == mat[next[i] - 1]) {
			nextval[i] = nextval[next[i] - 1];
		}
		else {
			nextval[i] = next[i];
		}
	}

	// 进行字符串匹配，idx指示主串，pos指示模式串
	int idx = 0, pos = 0;
	while (idx < srcLen) {
		if (src[idx] == mat[pos]) {
			pos++;
			// 完成匹配，释放资源，返回
			if (pos == matLen) {
				free(next);
				free(nextval);
				return idx+1-matLen;
			}
			idx++;
		}
		else {
			// 失配，若模式串已经回退到底，则主串前进一步
			if (nextval[pos] == 0) {
				idx++;
			}
			// 模式串根据next数组回退
			pos = nextval[pos] > 0 ? nextval[pos] - 1 : 0;
		}
	}
	free(next);
	free(nextval);
	return -1;
}