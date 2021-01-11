#ifndef CHARS_H
#define CHARS_H

#include "basis.h"
#include <string.h>

// BF算法进行字符串模式匹配
int IndexOf_BF(const char* src, const char* mat);

// KMP算法进行字符串模式匹配
int IndexOf_KMP(const char* src, const char* mat);

#endif