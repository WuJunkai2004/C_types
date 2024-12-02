#include "list.h"

#include <stdlib.h>
#include <string.h>


/**
 * @brief 创建一个链表
 * @param sizeof(type) 类型的大小
 * @return list 返回创建的链表
 */
list list_create_by(int sizeof_type) {
    list l;
    l._type_size = sizeof_type;
    l.length = 0;
    l._capacity = 8;
    l._data = malloc(sizeof_type * l._capacity);
    return l;
}


/**
 * @brief 创建一个链表, 并初始化一些值
 * @param sizeof(type) 类型的大小
 * @param length 长度
 * @param values 值
 */
list list_init_by(int sizeof_type, int length, void* values) {
    list l = list_create_by(sizeof_type);
    while(l._capacity < length){
        list_enlarge(&l);
    }
    l.length = length;
    memcpy(l._data, values, sizeof_type * length);
    return l;
}


/**
 * @brief 设置链表的元素
 * @param l 链表
 * @param index 索引
 * @param value 值
 */
void list_set_ptr(list* this, int index, void* value) {
    if( index < 0 || index >= this->length){
        return;
    }
    memcpy(this->_data + index * this->_type_size, value, this->_type_size);
}


/**
 * @brief 获取链表的元素
 * @param l 链表
 * @param index 索引
 * @return void* 返回索引对应的元素
 */
void*list_get_ptr(list* this, int index) {
    if( index < 0 || index >= this->_capacity){
        return NULL;
    }
    return this->_data + index * this->_type_size;
}

void list_append_ptr(list* this, void* value) {
    if( this->length >= this->_capacity){
        list_enlarge(this);
    }
    memcpy(this->_data + this->length * this->_type_size, value, this->_type_size);
    this->length++;
}


/**
 * @brief 删除链表的元素
 * @param l 链表
 * @param index 索引
 */
void list_erase(list* this, int index) {
    if(index >= this->length || index < 0){
        return;
    }
    if(index == this->length - 1){
        this->length--;
        return;
    }
    memmove(this->_data + index * this->_type_size, this->_data + (index + 1) * this->_type_size, (this->length - index - 1) * this->_type_size);
    this->length--;
}


/**
 * @brief 被动扩容链表
 * @param l 链表
 */
void list_enlarge(list* this) {
    if(this->_capacity < 64){
        this->_capacity *= 2;
    } else {
        this->_capacity += 32;
    }
    this->_data = realloc(this->_data, this->_type_size * this->_capacity);
}


/**
 * @brief 主动扩容链表
 * @param l 链表
 * @param new_capacity 新的容量(小于当前容量则无效)
 */
void list_expand(list* this, int new_capacity) {
    if(new_capacity <= this->_capacity){
        return;
    }
    this->_capacity = new_capacity;
    this->_data = realloc(this->_data, this->_type_size * this->_capacity);
}


/**
 * @brief 排序链表
 * @param l 链表
 * @param cmp 比较函数
 */
void list_sort(list* this, int(*cmp)(const void*, const void*)) {
    qsort(this->_data, this->length, this->_type_size, cmp);
}


/**
 * @brief 反转链表
 * @param l 链表
 */
void list_reverse(list* this) {
    void* temp = malloc(this->_type_size);
    for(int i = 0; i < this->length / 2; i++){
        memcpy(temp, this->_data + i * this->_type_size, this->_type_size);
        memcpy(this->_data + i * this->_type_size, this->_data + (this->length - i - 1) * this->_type_size, this->_type_size);
        memcpy(this->_data + (this->length - i - 1) * this->_type_size, temp, this->_type_size);
    }
    free(temp);
}

/**
 * @brief 释放链表
 * @param l 链表
 */
void list_free(list* this) {
    free(this->_data);
}





/**
 * @brief 内置排序函数
 */
int sort_as_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int sort_as_double(const void* a, const void *b){
    return *(double*)a - *(double*)b;
}
