#ifndef __STR_HEADER__
#define __STR_HEADER__

#define STRING_EXTRA_LIMIT 128
#define STRING_SHORT_STD   8

typedef struct{
    int size;
    char data[0];
} str;

str     str_create(int);
void    str_destroy(str*);
str     str_slice(char* , int, int);

char*   str_static(char*);

#define STR_TAG "%.*s"
#define STR_ARG(s) (s).size, (s).data

#define string(s) ({_Generic((s),\
    int: ({char _s[256]; sprintf(_s, "%d", s); str_static(_s);}),\
    double: ({char _s[256]; sprintf(_s, "%lf", s); str_static(_s);}),\
    float: ({char _s[256]; sprintf(_s, "%f", s); str_static(_s);}),\
    char*: str_static((char*)(long long)s)\
);})

int sort_as_str(const str*, const str*);
int sort_as_string(const char*, const char*);


#endif
