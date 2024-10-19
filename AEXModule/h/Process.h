#pragma once
#include <windows.h>
#include "Text.h"
namespace Process {
	//ö�ٽ�����Ϣ�б�
	struct ProcessInfo {
		DWORD PID = NULL;//����ID
		std::string Name;//������
		std::wstring WName;//������(���ַ�)
		std::string WinTitle;//���̴��ڱ���
		HWND WinHandle = NULL;//���̴��ھ��
		std::string Path;//����·��
		std::string CommandLine;//����������
	};
	/*
	* ��ȡ����·��
	* @param processID ����ID
	* @return ����·��
	*/
	std::string GetProcessPath(DWORD processID);
	/*
	* ��ȡ����������
	* @param processID ����ID
	* @return ����������
	*/
	std::string GetProcessCommandLine(DWORD processID);
	/*
	* ��ȡ���ڱ���
	* @param hwnd ���ھ��
	* @return ���ڱ���
	*/
	std::string GetWindowTitle(HWND hwnd);
	/*
	* ����IDȡ���ھ��
	* @param processID ����ID
	* @return ���ھ��,NULL��ʾδ�ҵ�
	*/
	HWND GetProcessWinHandle(DWORD processID);
	/*
	* ��ȡ���н�����Ϣ
	* @return ���н��̵���Ϣ
	*/
	std::vector<ProcessInfo> ProcessList();
	/*
	* ������ȡ����ID
	* @param processName ������
	* @return ����ID,-1��ʾδ�ҵ�
	*/
	DWORD ProcessGetID(std::string processName);
	/*
	* ����IDȡ������
	* @param processID ����ID
	* @return ������,���ַ�����ʾδ�ҵ�
	*/
	std::string ProcessGetName(DWORD processID);
	/*
	* ����IDȡ���ھ��
	* @param processID ����ID
	* @return ���ھ��,NULL��ʾδ�ҵ�
	*/
	HWND ProcessGetWinHandle(DWORD processID);
};