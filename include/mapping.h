#ifndef __MAPPING_HEADER__
#define __MAPPING_HEADER__

/**
 * @brief mapping struct
 * @param key: key of mapping, a string
 * @param value: value of mapping, an integer
 */
typedef struct{
    char *key;
    int value;
} map_pair;
typedef struct{
    int _capacity;
    char* *keys;
    int *values;
} map;

map  map_create();
map  map_init_by(int, map_pair*);
void map_set(map*, char*, int);
int  map_get(map*, char*);
void map_remove(map*, char*);
void map_expand(map*);
void map_free(map*);
#define map_init(...) ({map_pair _m[]={__VA_ARGS__}; map_init_by(sizeof(_m)/sizeof(map_pair), _m);})


/**
 * @brief dictionary struct
 * @param key: key of dictionary, a string
 * @param value: value of dictionary, a string
 */
typedef struct{
    char *key;
    char *value;
} dict_pair;
typedef struct{
    int _capacity;
    char* *keys;
    char* *values;
} dict;

dict  dict_create();
dict  dict_init_by(int, dict_pair*);
void  dict_set(dict*, char*, char*);
char* dict_get(dict*, char*);
void  dict_remove(dict*, char*);
void  dict_expand(dict*);
void  dict_free(dict*);
#define dict_init(...) ({dict_pair _d[]={__VA_ARGS__}; dict_init_by(sizeof(_d)/sizeof(dict_pair), _d);})


#endif
