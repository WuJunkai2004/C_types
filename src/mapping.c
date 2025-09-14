#include "str.h"
#include "mapping.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 创建一个映射
 * @return map 返回创建的映射
 */
map map_create() {
    map d;
    d._capacity = 16;
    d.keys = malloc(sizeof(char*) * d._capacity);
    for(int i = 0; i < d._capacity; i++){
        d.keys[i] = NULL;
    }
    d.values = malloc(sizeof(int) * d._capacity);
    return d;
}


map map_init_by(int len, map_pair* data){
    map m = map_create();
    for(int i=0; i<len; i++){
        map_set(&m, data[i].key, data[i].value);
    }
    return m;
}


/**
 * @brief 设置映射的键值对
 * @param d 映射
*/
void map_set(map* this, char *key, int value) {
    int is_set = 0;
    for(int i = 0; i < this->_capacity; i++){
        if(is_set == 0 && this->keys[i] == NULL){
            this->keys[i] = malloc(strlen(key) + 1);
            strcpy(this->keys[i], key);
            this->values[i] = value;
            is_set = 1;
            continue;
        }
        if(is_set == 0 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0 ){
            this->values[i] = value;
            return;
        }
        if(is_set == 1 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            this->values[i] = 0;
            return;
        }
    }
    if(is_set == 0){
        map_expand(this);
        map_set(this, key, value);
    }
}


/**
 * @brief 获取映射的值
 * @param d 映射
 * @param key 键
 * @return int 返回键对应的值
 */
int map_get(map* this, char *key) {
    for(int i = 0; i < this->_capacity; i++){
        if(this->keys[i] == NULL){
            continue;
        }
        if(strcmp(this->keys[i], key) == 0){
            return this->values[i];
        }
    }
    return 0;
}


/**
 * @brief 删除映射的键值对
 * @param d 映射
 * @param key 键
 */
void map_remove(map* this, char *key) {
    for(int i = 0; i < this->_capacity; i++){
        if(strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容映射
 * @param d 映射
 */
void map_expand(map* this) {
    this->_capacity += 16;
    this->keys = realloc(this->keys, sizeof(char*) * this->_capacity);
    for(int i=this->_capacity - 16; i < this->_capacity; i++){
        this->keys[i] = NULL;
    }
    this->values = realloc(this->values, sizeof(int) * this->_capacity);
}


/**
 * @brief 释放映射
 * @param d 映射
*/
void map_free(map* this) {
    for(int i = 0; i < this->_capacity; i++){
        free(this->keys[i]);
    }
    free(this->keys);
    free(this->values);
}


/**
 * @brief 创建一个字典
 * @return dict 返回创建的字典
 */
dict dict_create() {
    dict d;
    d._capacity = 16;
    d.keys   = malloc(sizeof(char*) * d._capacity);
    d.values = malloc(sizeof(char*) * d._capacity);
    for(int i = 0; i < d._capacity; i++){
        d.keys[i]   = NULL;
        d.values[i] = NULL;
    }
    return d;
}


dict dict_init_by(int len, dict_pair* data){
    dict d = dict_create();
    for(int i=0; i<len; i++){
        dict_set(&d, data[i].key, data[i].value);
    }
    return d;
}


/**
 * @brief 设置字典的键值对
 * @param d 字典
 */
void dict_set(dict* this, char *key, char *value) {
    int is_set = 0;
    for(int i = 0; i < this->_capacity; i++){
        if(is_set == 0 && this->keys[i] == NULL){
            this->keys[i] = malloc(strlen(key) + 1);
            strcpy(this->keys[i], key);
            this->values[i] = malloc(strlen(value) + 1);
            strcpy(this->values[i], value);
            is_set = 1;
            continue;
        }
        if(is_set == 0 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0 ){
            free(this->values[i]);
            this->values[i] = malloc(strlen(value) + 1);
            strcpy(this->values[i], value);
            return;
        }
        if(is_set == 1 && this->keys[i] != NULL && strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            free(this->values[i]);
            this->values[i] = NULL;
            return;
        }
    }
    if(is_set == 0){
        dict_expand(this);
        dict_set(this, key, value);
    }
}


/**
 * @brief 获取字典的值
 * @param d 字典
 * @param key 键
 * @return char *返回键对应的值
 */
char *dict_get(dict* this, char *key) {
    for(int i = 0; i < this->_capacity; i++){
        if(this->keys[i] == NULL){
            continue;
        }
        if(strcmp(this->keys[i], key) == 0){
            return this->values[i];
        }
    }
    return NULL;
}


/**
 * @brief 删除字典的键值对
 * @param d 字典
 * @param key 键
 */
void dict_remove(dict* this, char *key) {
    for(int i = 0; i < this->_capacity; i++){
        if(strcmp(this->keys[i], key) == 0){
            free(this->keys[i]);
            this->keys[i] = NULL;
            free(this->values[i]);
            this->values[i] = NULL;
            return;
        }
    }
}


/**
 * @brief 扩容字典
 * @param d 字典
 */
void dict_expand(dict* this) {
    this->_capacity += 16;
    this->keys   = realloc(this->keys, sizeof(char*) * this->_capacity);
    this->values = realloc(this->values, sizeof(char*) * this->_capacity);
    for(int i=this->_capacity - 16; i < this->_capacity; i++){
        this->keys[i]   = NULL;
        this->values[i] = NULL;
    }
}


/**
 * @brief 释放字典
 * @param d 字典
*/
void dict_free(dict* this) {
    for(int i = 0; i < this->_capacity; i++){
        free(this->keys[i]);
        free(this->values[i]);
    }
    free(this->keys);
    free(this->values);
}