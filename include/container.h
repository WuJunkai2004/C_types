#ifndef __CONTAINER_HEADER__
#define __CONTAINER_HEADER__

#include "list.h"

/**
 * @brief stack struct
 * @param _inner_list: inner list, you can't access the data directly
 * @param _idx: index of stack, you can't access the data directly
 */
typedef struct{
    list_t _inner_list;
    int _idx;
} stack_t;

stack_t stack_create_by(int);
void    stack_push_ptr(stack_t*, void*);
void*   stack_top_ptr(stack_t*);
void*   stack_pop_ptr(stack_t*);
int     stack_size(stack_t*);
void    stack_clear(stack_t*);
void    stack_free(stack_t*);
int     stack_is_empty(stack_t*);
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
    void *_data;
    int _front;
    int _rear;
    int _data_size;
    int _max_size;
} queue_t;

queue_t queue_create_by(int, int);
void    queue_push_ptr(queue_t*, void*);
void*   queue_front_ptr(queue_t*);
void*   queue_back_ptr(queue_t*);
void*   queue_pop_front_ptr(queue_t*);
void*   queue_pop_back_ptr(queue_t*);
int     queue_size(queue_t*);
void    queue_clear(queue_t*);
void    queue_free(queue_t*);
#define queue_create(type, size) ({queue_create_by(sizeof(type), size);})
#define queue_push(q, value) ({typeof(value) _v=(value); queue_push_ptr((q), &_v);})
#define queue_front(type, q) ({*(type*)queue_front_ptr((q));})
#define queue_back(type, q) ({*(type*)queue_back_ptr((q));})
#define queue_pop_front(type, q) ({*(type*)queue_pop_front((q));})
#define queue_pop_back(type, q) ({*(type*)queue_pop_back((q));})

#endif
