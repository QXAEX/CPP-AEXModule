#pragma once
#include "Text.h"
#include <windows.h>
#include <string>
namespace System {
	/*
	* ��ȡϵͳʱ��
	* @param format �Ƿ��ʽ��
	*/
	std::string GetTime(bool format = false);
	/*
	* ȡ����Ŀ¼
	* @param pid ����ID,Ĭ��Ϊ��ǰ����ID
	* @return ����Ŀ¼
	*/
	std::string GetRunPath(DWORD pid = NULL);
	/*
	* ȡ����ʱ��
	* @return ����ʱ��(����)
	*/
	__int64 GetRunTime();
	/*
	* ���ݴ�С����(1:BIT -> 2:KB -> 3:MB -> 4:GB)
	* @param size ��С(λ)
	* @param type ת������,��ַ(1:BIT -> 2:KB -> 3:MB -> 4:GB)
	* @param time ʱ�����,�ɿ�(����ÿ��������1������ݴ�С)
	* @return ת������ڴ��С
	*/
	double DataSizeConversion(double size, int& type, __int64 time = -1);
	/*
	* ����Ŀ¼
	* @param path Ŀ¼·��
	* @return �Ƿ�ɹ�
	*/
	bool CreateDir(std::string path);
	/*
	* ɾ��Ŀ¼
	* @param path Ŀ¼·��
	* @return �Ƿ�ɹ�
	*/
	bool RemoveDir(std::string path);
};