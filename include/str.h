#ifndef __STR_HEADER__
#define __STR_HEADER__

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8

#define str_new(len) malloc(len)

#define str(x) ({(x).data;})

typedef struct{
    int size;
    char *data;
} string_t;

string_t str_static(char*);

typedef struct{
    const char *start;
    int len;
} str_view;

#define VIEW_TAG "%.*s"
#define VIEW_ARG(view) view.len, view.start

str_view str_cut(char* , int, int);

int compare_str_view(str_view, str_view);

string_t view_to_str(str_view);

#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})

int sort_as_str(const void*, const void*);
int sort_as_string(const void*, const void*);


#endif
