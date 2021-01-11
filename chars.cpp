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
	// �����������һ���ռ䣬����free�����
	int* next = (int*)malloc(sizeof(int) * (matLen+1));
	int* nextval = (int*)malloc(sizeof(int) * (matLen + 1));
	int i = 0, j = 0;

	// ����next����
	next[0] = 0;
	while (i < matLen) {
		// ���jΪ0��˵���Ѿ��޷����ˣ�i+1ǰ��û���ظ��Ӵ�����i+1����Ϊ1��
		// ���j��Ϊ0����i��j-1��λ��Ԫ��һ������ʾi+1ǰ���ظ��Ӵ�����i+1��λ������Ϊj��
		if (j == 0 || mat[i] == mat[j-1]) {
			i++;
			j++;
			next[i] = j;
		}
		else {
			// ���i��j-1��λ��Ԫ�ز�һ�������ʾi���Ӵ���j-1���Ӵ��ǲ��ظ��ģ���j���˵���һ��ƥ����ظ��Ӵ���
			j = next[j-1];
		}
	}

	// ����nextval����
	nextval[0] = next[0];
	for (i = 1; i < matLen; i++) {
		if (mat[i] == mat[next[i] - 1]) {
			nextval[i] = nextval[next[i] - 1];
		}
		else {
			nextval[i] = next[i];
		}
	}

	// �����ַ���ƥ�䣬idxָʾ������posָʾģʽ��
	int idx = 0, pos = 0;
	while (idx < srcLen) {
		if (src[idx] == mat[pos]) {
			pos++;
			// ���ƥ�䣬�ͷ���Դ������
			if (pos == matLen) {
				free(next);
				free(nextval);
				return idx+1-matLen;
			}
			idx++;
		}
		else {
			// ʧ�䣬��ģʽ���Ѿ����˵��ף�������ǰ��һ��
			if (nextval[pos] == 0) {
				idx++;
			}
			// ģʽ������next�������
			pos = nextval[pos] > 0 ? nextval[pos] - 1 : 0;
		}
	}
	free(next);
	free(nextval);
	return -1;
}