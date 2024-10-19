#pragma once
/*
* CODE: GB2312
* author: <QX>
* createBy: 2024-08-5
* updateBy: 2024-10-17
*/
//lib库编译环境为Debug模式,方便代码调试
//如果lib加载失败就改相对路径
#define AEX_LIB_TYPE "MDd" // 根据你项目的设置 项目属性 -> C/C++ -> 代码生成 -> 运行库 进行对应名字的选择

#define AEX_LIB_PATH_TOP "../AEXModule/AEXModule/libs/AEXModule_"// 相对路径(根据你下载的AEXModule的路径去改)
#ifdef _WIN64
#define AEX_LIB_PATH_END "_64.lib"
#else
#define AEX_LIB_PATH_END ".lib"
#endif
#define AEX_LIB_PATH AEX_LIB_PATH_TOP AEX_LIB_TYPE AEX_LIB_PATH_END 
#pragma comment(lib, AEX_LIB_PATH)
#include "AEXModule/h/Process.h"				//进程方法集合				<namespace>					updateBy: 2024-08-9
#include "AEXModule/h/Text.h"						//文本方法集合				<namespace>					updateBy: 2024-09-22
#include "AEXModule/h/File.h"						//文件方法对象				<class>							updateBy: 2024-10-15
#include "AEXModule/h/Byteset.h"				//字节集对象					<class>							updateBy: 2024-09-14
#include "AEXModule/h/Memory.h"				//内存方法集合				<namespace>					updateBy: 2024-10-17
#include "AEXModule/h/Network.h"				//网络方法集合				<namespace>					updateBy: 2024-09-15
#include "AEXModule/h/Encryption.h"			//加密解密集合				<namespace>					updateBy: 2024-08-12
#include "AEXModule/h/System.h"					//系统方法集合				<namespace>					updateBy: 2024-09-14
#include "AEXModule/h/AEXStore.h"				//AEX官方数据仓库		<class>							updateBy: 2024-09-14
#include "AEXModule/h/Gui.h"						//AEX官方数据仓库		<namespace>					updateBy: 2024-09-21
#include "AEXModule/h/Thread.h"					//线程类						<class>							updateBy: 2024-10-14

