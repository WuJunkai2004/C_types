#include "container.h"

#include <stdio.h>
#include "list.h"


/**
 * @brief 创建一个栈
 * @param sizeof(type) 类型的大小
 * @return stack 返回创建的栈
 */
stack stack_create_by(int sizeof_type) {
    stack s;
    s._inner_list = list_create_by(sizeof_type);
    s._idx = -1;
    return s;
}


/**
 * @brief 入栈
 * @param s 栈
 * @param value 值
 */
void stack_push_ptr(stack* this, void* value) {
    this->_idx++;
    if(this->_idx >= this->_inner_list.length){
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
void* stack_top_ptr(stack* this) {
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
void* stack_pop_ptr(stack* this) {
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
int stack_size(stack* this) {
    return this->_idx + 1;
}


/**
 * @brief 释放栈
 * @param s 栈
 */
void stack_free(stack* this) {
    list_free(&(this->_inner_list));
}