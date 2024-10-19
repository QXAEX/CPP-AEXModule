#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <stdbool.h>

/*
* 字节集类型定义
*/
typedef struct {
    unsigned char* data; // 存储字节数据
    long long size;      // 字节数组大小
}Byteset,*PByteset;
/*
* 初始化字节集
* @param sample 字节集样本(拷贝,不会直接使用此指针),可以为NULL
* @param size 字节集大小,为NULL则自动使用strlen取长度,如果sample中有字节集为{0},则需要手动指定大小
* @return 字节集
*/
Byteset Byteset_init(unsigned char* sample, long long size);
/*
* 释放字节集
* @param byteset 字节集
*/
bool Byteset_free(PByteset byteset);
/*
* 字节集是否为空
* @param byteset 字节集
* @return 字节集是否为空
*/
bool Byteset_isEmpty(PByteset byteset);