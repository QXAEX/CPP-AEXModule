#pragma once
#include <windows.h>
#include "Text.h"
namespace Process {
	//枚举进程信息列表
	struct ProcessInfo {
		DWORD PID = NULL;//进程ID
		std::string Name;//进程名
		std::wstring WName;//进程名(宽字符)
		std::string WinTitle;//进程窗口标题
		HWND WinHandle = NULL;//进程窗口句柄
		std::string Path;//进程路径
		std::string CommandLine;//进程命令行
	};
	/*
	* 获取进程路径
	* @param processID 进程ID
	* @return 进程路径
	*/
	std::string GetProcessPath(DWORD processID);
	/*
	* 获取进程命令行
	* @param processID 进程ID
	* @return 进程命令行
	*/
	std::string GetProcessCommandLine(DWORD processID);
	/*
	* 获取窗口标题
	* @param hwnd 窗口句柄
	* @return 窗口标题
	*/
	std::string GetWindowTitle(HWND hwnd);
	/*
	* 进程ID取窗口句柄
	* @param processID 进程ID
	* @return 窗口句柄,NULL表示未找到
	*/
	HWND GetProcessWinHandle(DWORD processID);
	/*
	* 获取所有进程信息
	* @return 所有进程的信息
	*/
	std::vector<ProcessInfo> ProcessList();
	/*
	* 进程名取进程ID
	* @param processName 进程名
	* @return 进程ID,-1表示未找到
	*/
	DWORD ProcessGetID(std::string processName);
	/*
	* 进程ID取进程名
	* @param processID 进程ID
	* @return 进程名,空字符串表示未找到
	*/
	std::string ProcessGetName(DWORD processID);
	/*
	* 进程ID取窗口句柄
	* @param processID 进程ID
	* @return 窗口句柄,NULL表示未找到
	*/
	HWND ProcessGetWinHandle(DWORD processID);
};