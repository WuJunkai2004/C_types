#ifndef __MAPPING_HEADER__
#define __MAPPING_HEADER__


typedef struct{
    str key;
    int value;
} map_pair;
typedef struct{
    int _capacity;
    str *keys;
    int *values;
} map;

map  map_create();
map  map_init_by(int, map_pair*);
void map_set(map*, str, int);
int  map_get(map*, str);
void map_remove(map*, str);
void map_expand(map*);
void map_free(map*);
#define map_init(...) ({map_pair _m[]={__VA_ARGS__}; map_init_by(sizeof(_m)/sizeof(map_pair), _m);})

typedef struct{
    str key;
    str value;
} dict_pair;
typedef struct{
    int _capacity;
    str *keys;
    str *values;
} dict;

dict dict_create();
dict dict_init_by(int, dict_pair*);
void dict_set(dict*, str, str);
str  dict_get(dict*, str);
void dict_remove(dict*, str);
void dict_expand(dict*);
void dict_free(dict*);
#define dict_init(...) ({dict_pair _d[]={__VA_ARGS__}; dict_init_by(sizeof(_d)/sizeof(dict_pair), _d);})


#endif