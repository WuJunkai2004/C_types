#ifndef __STR_HEADER__
#define __STR_HEADER__

typedef char* str;

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8

#define str_new(len) malloc(len+1)

str str_static(str);

typedef struct{
    const str start;
    int len;
} str_view;

str_view str_cut(str, int, int);

int compare_str_view(str_view, str_view);


#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    str_view ({char _s[s.len+1]; memcpy(_s, s.start, s.len); _s[s.len] = '\0'; str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})

int sort_as_str(const void*, const void*);


#endif
