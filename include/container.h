#ifndef __CONTAINER_HEADER__
#define __CONTAINER_HEADER__

#include "list.h"

/**
 * @brief stack struct
 * @param _inner_list: inner list, you can't access the data directly
 * @param _idx: index of stack, you can't access the data directly
 */
typedef struct{
    list _inner_list;
    int _idx;
} stack;

stack stack_create_by(int);
void  stack_push_ptr(stack*, void*);
void* stack_top_ptr(stack*);
void* stack_pop_ptr(stack*);
int   stack_size(stack*);
void  stack_free(stack*);
int   stack_is_empty(stack*);
#define stack_create(type) ({stack_create_by(sizeof(type));})
#define stack_push(s, value) ({typeof(value) _v=(value); stack_push_ptr((s), &_v);})
#define stack_top(type, s) ({*(type*)stack_top_ptr((s));})
#define stack_pop(type, s) ({*(type*)stack_pop_ptr((s));})


/**
 * @brief queue struct
 * @param _inner_list: inner list, you can't access the data directly
 * @param _front: front of queue, you can't access the data directly
 * @param _rear: rear of queue, you can't access the data directly
 * @param _max_size: max size of queue, you can't access the data directly
 */
typedef struct{
    list _inner_list;
    int _front;
    int _rear;
    int _max_size;
} queue;

#endif
