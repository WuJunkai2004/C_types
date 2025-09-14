#include <string.h>
#include <stdlib.h>

#include "str.h"


/**
 * @brief 创建一个字符串
 * @param len 字符串长度
 */
str str_create(int len) {
    str* ret = malloc(sizeof(str) + len + 1);
    ret->size = len;
    return *ret;
}

/**
 * @brief 销毁一个字符串
 * @param s 字符串指针
 */
void str_destroy(str *s) {
    free(s);
    s = NULL;
}

str str_slice(char *dst, int offset, int len) {
    str ret = str_create(len);
    memcpy(ret.data, dst + offset, len);
    ret.data[len] = '\0';
    return ret;
}

/**
 * @brief 对一个字符串进行复制，同时自带内存回收机制
 * @param s 字符串
 * @return char *返回创建的字符串
 */
char* str_static(char *s) {
    static int cursor = 0;
    static char *strings[STRING_EXTRA_LIMIT] = {};
    static int str_len[STRING_EXTRA_LIMIT] = {};
    static int str_rfr[STRING_EXTRA_LIMIT] = {};
    int len = strlen(s);
    for(int i = 0; len <= STRING_SHORT_STD && i < STRING_EXTRA_LIMIT; i++){
        if(len == str_len[i] && strings[i] != NULL && strcmp(strings[i], s) == 0){
            str_rfr[i]++;
            return strings[i];
        }
    }
    for(; strings[cursor] != NULL;cursor = (cursor + 1) % STRING_EXTRA_LIMIT){
        if(str_rfr[cursor] <= 1){
            free(strings[cursor]);
            strings[cursor] = NULL;
            break;
        } else {
            str_rfr[cursor]--;
        }
    }
    strings[cursor] = malloc(len + 1);
    strcpy(strings[cursor], s);
    str_len[cursor] = len;
    str_rfr[cursor] = 1;
    int ret = cursor;
    cursor = (cursor + 1) % STRING_EXTRA_LIMIT;
    return strings[ret];
}

int sort_as_str(const str* a, const str* b) {
    return strcmp(a->data, b->data);
}

int sort_as_string(const char* a, const char* b) {
    return strcmp(a, b);
}
