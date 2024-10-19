#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <stdbool.h>

/*
* �ֽڼ����Ͷ���
*/
typedef struct {
    unsigned char* data; // �洢�ֽ�����
    long long size;      // �ֽ������С
}Byteset,*PByteset;
/*
* ��ʼ���ֽڼ�
* @param sample �ֽڼ�����(����,����ֱ��ʹ�ô�ָ��),����ΪNULL
* @param size �ֽڼ���С,ΪNULL���Զ�ʹ��strlenȡ����,���sample�����ֽڼ�Ϊ{0},����Ҫ�ֶ�ָ����С
* @return �ֽڼ�
*/
Byteset Byteset_init(unsigned char* sample, long long size);
/*
* �ͷ��ֽڼ�
* @param byteset �ֽڼ�
*/
bool Byteset_free(PByteset byteset);
/*
* �ֽڼ��Ƿ�Ϊ��
* @param byteset �ֽڼ�
* @return �ֽڼ��Ƿ�Ϊ��
*/
bool Byteset_isEmpty(PByteset byteset);