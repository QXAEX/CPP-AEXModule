#pragma once
/*
* CODE: GB2312
* author: <QX>
* createBy: 2024-08-5
* updateBy: 2024-10-17
*/
//lib����뻷��ΪDebugģʽ,����������
//���lib����ʧ�ܾ͸����·��
#define AEX_LIB_TYPE "MDd" // ��������Ŀ������ ��Ŀ���� -> C/C++ -> �������� -> ���п� ���ж�Ӧ���ֵ�ѡ��

#define AEX_LIB_PATH_TOP "../AEXModule/AEXModule/libs/AEXModule_"// ���·��(���������ص�AEXModule��·��ȥ��)
#ifdef _WIN64
#define AEX_LIB_PATH_END "_64.lib"
#else
#define AEX_LIB_PATH_END ".lib"
#endif
#define AEX_LIB_PATH AEX_LIB_PATH_TOP AEX_LIB_TYPE AEX_LIB_PATH_END 
#pragma comment(lib, AEX_LIB_PATH)
#include "AEXModule/h/Process.h"				//���̷�������				<namespace>					updateBy: 2024-08-9
#include "AEXModule/h/Text.h"						//�ı���������				<namespace>					updateBy: 2024-09-22
#include "AEXModule/h/File.h"						//�ļ���������				<class>							updateBy: 2024-10-15
#include "AEXModule/h/Byteset.h"				//�ֽڼ�����					<class>							updateBy: 2024-09-14
#include "AEXModule/h/Memory.h"				//�ڴ淽������				<namespace>					updateBy: 2024-10-17
#include "AEXModule/h/Network.h"				//���緽������				<namespace>					updateBy: 2024-09-15
#include "AEXModule/h/Encryption.h"			//���ܽ��ܼ���				<namespace>					updateBy: 2024-08-12
#include "AEXModule/h/System.h"					//ϵͳ��������				<namespace>					updateBy: 2024-09-14
#include "AEXModule/h/AEXStore.h"				//AEX�ٷ����ݲֿ�		<class>							updateBy: 2024-09-14
#include "AEXModule/h/Gui.h"						//AEX�ٷ����ݲֿ�		<namespace>					updateBy: 2024-09-21
#include "AEXModule/h/Thread.h"					//�߳���						<class>							updateBy: 2024-10-14

