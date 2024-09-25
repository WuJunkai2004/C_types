#ifndef __LIST_HEADER__
#define __LIST_HEADER__

/**
 * @brief list struct
 * @param length: length of list
 * @param _capacity: capacity of list, you can't access the data directly
 * @param _data: data of list, you can't access the data directly
 * @param _type_size: size of type, you can't access the data directly
 */
typedef struct{
    int _type_size;
    int length;
    int _capacity;
    void* _data;
} list;

list list_create_by(int);
list list_init_by(int, int, void*);
void list_set_ptr(list*, int, void*);
void*list_get_ptr(list*, int);
void list_append_ptr(list*, void*);
void list_erase(list*, int);
void list_enlarge(list*);
void list_expand(list*, int);
void list_sort(list*, int(*)(const void*, const void*));
void list_reverse(list*);
void list_free(list*);
#define list_create(type) ({list_create_by(sizeof(type));})
#define list_init(values, ...) ({typeof(values) _l[]={values, ##__VA_ARGS__}; list_init_by(sizeof(values), sizeof(_l)/sizeof(values), _l);})
#define list_get(type, l, index) ({*(type*)list_get_ptr((l), (index));})
#define list_set(l, index, value) ({typeof(value) _v=value; list_set_ptr((l), (index), &_v);})
#define list_append(l, value) ({typeof(value) _v=(value); list_append_ptr((l), &_v);})
#define list_find(l, goal) ({int _i=-1;for(int i=0; i<(l)->length; i++)if(list_get(typeof(goal), l, i)==goal){_i=i; break;}_i;})

int sort_as_int(const void*, const void*);
int sort_as_double(const void*, const void*);

#endif
