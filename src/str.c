#include <string.h>
#include <stdlib.h>

#include "str.h"

/**
 * @brief 对一个字符串进行复制，同时自带内存回收机制
 * @param s 字符串
 * @return str 返回创建的字符串
 */
str str_static(str s) {
    static int cursor = 0;
    static str strings[STRING_EXTRA_LIMIT] = {};
    static int str_len[STRING_EXTRA_LIMIT] = {};
    static int str_use[STRING_EXTRA_LIMIT] = {};
    int len = strlen(s);
    for(int i = 0; len <= STRING_SHORT_STD && i < STRING_EXTRA_LIMIT; i++){
        if(len == str_len[i] && strings[i] != NULL && strcmp(strings[i], s) == 0){
            str_use[i]++;
            return strings[i];
        }
    }
    for(; strings[cursor] != NULL;cursor = (cursor + 1) % STRING_EXTRA_LIMIT){
        if(str_use[cursor] <= 1){
            free(strings[cursor]);
            strings[cursor] = NULL;
            break;
        } else {
            str_use[cursor]--;
        }
    }
    strings[cursor] = malloc(len + 1);
    strcpy(strings[cursor], s);
    str_len[cursor] = len;
    str_use[cursor] = 1;
    int ret = cursor;
    cursor = (cursor + 1) % STRING_EXTRA_LIMIT;
    return strings[ret];
}

str_view str_cut(str dst, int offset, int len) {
    str_view ret = {
        .start = dst + offset,
        .len = len
    };
    return ret;
}


int compare_str_view(str_view a, str_view b) {
    for(int i = 0; i < a.len && i < b.len; i++){
        if(a.start[i] < b.start[i]){
            return -1;
        } else if(a.start[i] > b.start[i]){
            return 1;
        }
    }
    return a.len - b.len;
}


str view_to_str(str_view view) {
    char ret[view.len + 1];
    strncpy(ret, view.start, view.len);
    return str_static(ret);
}


int sort_as_str(const void* a, const void* b) {
    return strcmp(*(str*)a, *(str*)b);
}