#ifndef __STR_HEADER__
#define __STR_HEADER__

typedef char* str;

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8
str str_static(str);
#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})
int sort_as_str(const void*, const void*);


#endif