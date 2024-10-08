#ifndef __STR_HEADER__
#define __STR_HEADER__

typedef char* str;

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8

#define str_new(len) malloc(len)

str str_static(str);

typedef struct{
    const str start;
    int len;
} str_view;

#define VIEW_TAG "%.*s"
#define VIEW_ARG(view) view.len, view.start

str_view str_cut(str, int, int);

int compare_str_view(str_view, str_view);

str view_to_str(str_view);

#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})

int sort_as_str(const void*, const void*);


#endif
