#include "container.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/**
 * @brief 创建一个栈
 * @param sizeof(type) 类型的大小
 * @return stack_t 返回创建的栈
 */
stack_t stack_create_by(int sizeof_type) {
    stack_t s;
    s._inner_list = list_create_by(sizeof_type);
    s._idx = -1;
    return s;
}


/**
 * @brief 入栈
 * @param s 栈
 * @param value 值
 */
void stack_push_ptr(stack_t* this, void* value) {
    this->_idx++;
    if(this->_idx >= this->_inner_list._len){
        list_append_ptr(&(this->_inner_list), value);
        return;
    }
    list_set_ptr(&(this->_inner_list), this->_idx, value);
}


/**
 * @brief 获取栈顶元素
 * @param s 栈
 * @return void* 返回栈顶元素
 */
void* stack_top_ptr(stack_t* this) {
    if(this->_idx < 0){
        return NULL;
    }
    return list_get_ptr(&(this->_inner_list), this->_idx);
}


/**
 * @brief 出栈
 * @param s 栈
 * @return void* 返回出栈的元素
 */
void* stack_pop_ptr(stack_t* this) {
    if(this->_idx < 0){
        return NULL;
    }
    this->_idx--;
    return list_get_ptr(&(this->_inner_list), this->_idx + 1);
}


/**
 * @brief 获取栈的大小
 * @param s 栈
 * @return int 返回栈的大小
 */
int stack_size(stack_t* this) {
    return this->_idx + 1;
}


/**
 * @brief 释放栈
 * @param s 栈
 */
void stack_free(stack_t* this) {
    list_free(&(this->_inner_list));
}


/**
 * @brief 检查是否为空
 * @param s 栈
 */
int stack_is_empty(stack_t* this) {
    return this->_idx < 0;
}


/**
 * @brief 清空栈
 * @param s 栈
 */
void stack_clear(stack_t* this) {
    this->_idx = -1;
}


/**
 * @brief 创建一个队列
 * @param sizeof(type) 类型的大小
 * @param size 队列的大小
 */
queue_t queue_create_by(int sizeof_type, int size) {
    queue_t q;
    q._data = malloc(sizeof_type * (size + 1));
    q._data_size = sizeof_type;
    q._front = 0;
    q._rear = 0;
    q._max_size = size + 1;
    return q;
}


/**
 * @brief 入队
 * @param q 队列
 * @param value 值
 */
void queue_push_ptr(queue_t* this, void* value) {
    if(queue_size(this) >= this->_max_size){
        return;
    }
    memcpy(this->_data + this->_rear * this->_data_size, value, this->_data_size);
    this->_rear = (this->_rear + 1) % this->_max_size;
}


/**
 * @brief 获取队首元素
 * @param q 队列
 * @return void* 返回队首元素
 */
void* queue_front_ptr(queue_t* this) {
    if(queue_size(this) <= 0){
        return NULL;
    }
    return this->_data + this->_front * this->_data_size;
}


/**
 * @brief 获取队尾元素
 * @param q 队列
 * @return void* 返回队尾元素
 */
void* queue_back_ptr(queue_t* this) {
    if(queue_size(this) <= 0){
        return NULL;
    }
    return this->_data + this->_rear * this->_data_size;
}


/**
 * @brief 队首元素出队
 * @param q 队列
 * @return void* 返回出队的元素
 */
void* queue_pop_front_ptr(queue_t* this) {
    if(queue_size(this) <= 0){
        return NULL;
    }
    void* ret = this->_data + this->_front * this->_data_size;
    this->_front = (this->_front + 1) % this->_max_size;
    return ret;
}


/**
 * @brief 队尾元素出队
 * @param q 队列
 * @return void* 返回出队的元素
 */
void* queue_pop_back_ptr(queue_t* this) {
    if(queue_size(this) <= 0){
        return NULL;
    }
    this->_rear = (this->_rear - 1 + this->_max_size) % this->_max_size;
    return this->_data + this->_rear * this->_data_size;
}


/**
 * @brief 获取队列的大小
 * @param q 队列
 * @return int 返回队列的大小
 */
int queue_size(queue_t* this) {
    return (this->_rear - this->_front + this->_max_size) % this->_max_size;
}


/**
 * @brief 清空队列
 * @param q 队列
 */
void queue_clear(queue_t* this) {
    this->_front = this->_rear = 0;
}


/**
 * @brief 释放队列
 * @param q 队列
 */
void queue_free(queue_t* this) {
    free(this->_data);
}
