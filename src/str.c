#include <string.h>
#include <stdlib.h>

#include "str.h"

/**
 * @brief 对一个字符串进行复制，同时自带内存回收机制
 * @param s 字符串
 * @return char *返回创建的字符串
 */
string_t str_static(char *s) {
    static int cursor = 0;
    static char *strings[STRING_EXTRA_LIMIT] = {};
    static int str_len[STRING_EXTRA_LIMIT] = {};
    static int str_rfr[STRING_EXTRA_LIMIT] = {};
    int len = strlen(s);
    for(int i = 0; len <= STRING_SHORT_STD && i < STRING_EXTRA_LIMIT; i++){
        if(len == str_len[i] && strings[i] != NULL && strcmp(strings[i], s) == 0){
            str_rfr[i]++;
            string_t ret_str = {
                .size = len,
                .data = strings[i]
            };
            return ret_str;
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
    string_t ret_str = {
        .size = len,
        .data = strings[ret]
    };
    return ret_str;
}

str_view str_cut(char *dst, int offset, int len) {
    str_view ret = {
        .start = dst + offset,
        .len = len
    };
    return ret;
}


int compare_str_view(str_view a, str_view b) {
    for(int i = 0; i < a.len && i < b.len; i++){
        if(a.start[i] != b.start[i]){
            return a.start[i] - b.start[i];
        }
    }
    return a.len - b.len;
}


string_t view_to_str(str_view view) {
    char ret[view.len + 1];
    strncpy(ret, view.start, view.len);
    return str_static(ret);
}


int sort_as_str(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int sort_as_string(const void* a, const void* b) {
    return strcmp(str(*(string_t*)a), str(*(string_t*)b));
}
