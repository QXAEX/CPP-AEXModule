#pragma once
#include <windows.h>
#include <string>
#include "Byteset.h"
#include "Text.h"
#include "System.h"

/*
* �ļ���
* д��ı������㵱ǰ������ʹ�õĴ������һ��,���д������,��ע���������
*/
typedef class File {
private:
    HANDLE hfile;
    std::string path;
public:
    bool is_open;
public:
    File() = default;
    File(std::string path);
    ~File();
    /*
    * ���ļ�
    * @param path �ļ�·��
    * @param create �Ƿ񴴽��ļ�, Ĭ��Ϊfalse
    * @return �Ƿ�ɹ����ļ�
    */
    bool Open(std::string path, bool create = false);
    /*
    * �ر��ļ�
    * @return �Ƿ�ɹ��ر��ļ�
    */
    bool Close();
    /*
    * ɾ���ļ�
    * @return �Ƿ�ɹ�ɾ���ļ�
    */
    bool DelFile();
    /*
    * ���ļ�ָ�뵽ָ��λ��
    * @param pos λ��, Ĭ��Ϊ0
    * @return �Ƿ�ɹ����ļ�ָ��
    */
    bool Seek(long long pos = 0) const;
    /*
    * ȡ�ļ���С
    * @return �ļ���С
    */
    size_t Size() const;
    /*
    * д������
    * @param data ��д������
    * @return �Ƿ�ɹ�д������
    */
    bool Write(Byteset data) const;
    /*
    * ��ȡ����
    * @param size ��ȡ���ݵĴ�С
    * @return ��ȡ��������
    */
    Byteset Read(long long size) const;
    /*
    * ɾ������
    * @param size ��ɾ�����ݵĴ�С
    * @return �Ƿ�ɹ�ɾ������
    */
    bool Delete(long long size) const;
    /*
    * �滻����
    * @param new_data ���滻������
    * @param size �滻����
    * @return �Ƿ�ɹ��滻����
    */
    bool Replace(Byteset new_data,long long size) const;
    /*
    * ��������
    * @param data �����ҵ�����
    * @param index ��ʼ����λ��, Ĭ��Ϊ0
    * @param flag �Ƿ���,Ĭ��Ϊfalse
    * @return �ҵ������ݵ�λ��, -1��ʾδ�ҵ�
    */
    size_t Find(Byteset data,size_t index = NULL,bool flag = false) const;
} * PFile;