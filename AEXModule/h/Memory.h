#pragma once
#include <Windows.h>
#include "Byteset.h"
#include "Text.h"
#include <iostream>
#include <TlHelp32.h>
#include <winternl.h>
/*
* 操作内存（注意管理员运行）
*/
namespace Memory {
	class API {
	public:
		typedef struct _UNICODE_STRING {
			USHORT Length;
			USHORT MaximumLength;
			PWSTR Buffer;
		} UNICODE_STRING, * PUNICODE_STRING;
		typedef struct _OBJECT_ATTRIBUTES {
			ULONG Length;
			HANDLE RootDirectory;
			PUNICODE_STRING ObjectName;
			ULONG Attributes;
			PVOID SecurityDescriptor;
			PVOID SecurityQualityOfService;
		} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;
		typedef struct _CLIENT_ID {
			HANDLE UniqueProcess;
			HANDLE UniqueThread;
		} CLIENT_ID, * PCLIENT_ID;
		typedef NTSTATUS(NTAPI* zwOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
		typedef NTSTATUS(NTAPI* zwWriteVirtualMemory)(HANDLE ProcessHandle, LPCVOID address, LPVOID value, SIZE_T Rlength, SIZE_T* Olength);
		typedef NTSTATUS(NTAPI* zwReadVirtualMemory)(HANDLE ProcessHandle, LPCVOID address, LPVOID value, SIZE_T Rlength, SIZE_T* Olength);
		typedef NTSTATUS(NTAPI* zwProtectVirtualMemory)(HANDLE ProcessHandle, LPCVOID address, size_t* size, DWORD protection, PDWORD oldProtection);
		typedef NTSTATUS(NTAPI* zwAllocateVirtualMemory)(HANDLE ProcessHandle, size_t* BaseAddress, size_t ZeroBits, size_t* RegionSize, size_t AllocationType, size_t Protect);
		typedef NTSTATUS(NTAPI* zwFreeVirtualMemory)(HANDLE ProcessHandle, size_t* BaseAddress, size_t* RegionSize, size_t FreeType);
		typedef struct _MEMORY_BASIC_INFORMATION {
			PVOID BaseAddress;
			PVOID AllocationBase;
			DWORD AllocationProtect;
			SIZE_T RegionSize;
			DWORD State;
			DWORD Protect;
			DWORD Type;
		} MEMORY_BASIC_INFORMATION, * PMEMORY_BASIC_INFORMATION;
		typedef enum _MEMORY_INFORMATION_CLASS {
			MemoryBasicInformation,
			MemoryWorkingSetInformation,
			MemoryMappedFilenameInformation,
			MemoryRegionInformation,
			MemoryWorkingSetExInformation,
			MemorySharedCommitInformation,
			MemoryImageInformation,
			MemoryRegionInformationEx,
			MemoryPrivilegedBasicInformation,
			MemoryEnclaveInformation,
			MemoryBasicInformationCapped,
			MemoryPhysicalContiguityInformation,
			MemoryPhysicalContiguityInformationEx,
			MemoryStateInformation,
			MemoryProtectionInformation,
			MemoryTypeInformation,
			MemoryBasicInformationEx,
			MemoryMaximumInformation
		} MEMORY_INFORMATION_CLASS;
		typedef NTSTATUS(NTAPI* zwQueryVirtualMemory)(HANDLE ProcessHandle, LPCVOID address, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
		typedef NTSTATUS(NTAPI* zwClose)(HANDLE Handle);
		typedef HANDLE(WINAPI* createToolhelp32Snapshot)(DWORD, HANDLE);
		typedef BOOL(WINAPI* thread32First)(HANDLE hSnapshot, PTHREADENTRY32 lpte);
		typedef BOOL(WINAPI* thread32Next)(HANDLE hSnapshot, PTHREADENTRY32 lpte);
		typedef void (NTAPI* rtlWow64GetProcessMachines)(HANDLE, PUSHORT, PUSHORT);
		typedef NTSTATUS(NTAPI* zwSuspendThread)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
		typedef NTSTATUS(NTAPI* zwResumeThread)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
		typedef NTSTATUS(NTAPI* zwGetContextThread)(HANDLE ThreadHandle, PCONTEXT Context);
		typedef NTSTATUS(NTAPI* zwSetContextThread)(HANDLE ThreadHandle, PCONTEXT Context);
		typedef NTSTATUS(NTAPI* zwOpenThread)(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
	public:
		zwOpenProcess ZwOpenProcess;
		zwWriteVirtualMemory ZwWriteVirtualMemory;
		zwReadVirtualMemory ZwReadVirtualMemory;
		zwProtectVirtualMemory ZwProtectVirtualMemory;
		zwAllocateVirtualMemory ZwAllocateVirtualMemory;
		zwFreeVirtualMemory ZwFreeVirtualMemory;
		zwQueryVirtualMemory ZwQueryVirtualMemory;
		createToolhelp32Snapshot CreateToolhelp32Snapshot;
		thread32First Thread32First;
		thread32Next Thread32Next;
		rtlWow64GetProcessMachines RtlWow64GetProcessMachines;
		zwSuspendThread ZwSuspendThread;
		zwResumeThread ZwResumeThread;
		zwGetContextThread ZwGetContextThread;
		zwSetContextThread ZwSetContextThread;
		zwOpenThread ZwOpenThread;
		zwClose ZwClose;
	public:
		BOOL if_init;
		API();
		~API() = default;
	};
	class R3: private API {
	public:
		HANDLE hProcess;
		DWORD PID;
	public:
		R3() = default;
		R3(DWORD pid);
		~R3();
		/*
		* 打开进程
		* @param pid 进程ID
		*/
		bool Open(DWORD pid);
		/*
		* 关闭进程链接
		*/
		void Close() const;
		/*
		* 是否64位进程
		* @return 是否64位进程,true:64位,false:32位
		*/
		bool Is64() const;
		/*
		* 读模块基址
		* @param moduleName 模块名称
		* @return 模块基址
		*/
		size_t GetModuleBase(std::string moduleName) const;
		/*
		* 写内存
		* @param address 内存地址
		* @param value 写入值
		* @param isVirtual 是否破虚拟保护, 默认false
		* @return 是否写入成功
		*/
		bool Write(size_t address, Byteset value, bool isVirtual = false) const;
		/*
		* 读内存
		* @param address 内存地址
		* @param value 读取值
		* @param rlength 读取长度
		* @param isVirtual 是否破虚拟保护, 默认false
		* @return 是否读取成功
		*/
		bool Read(size_t address, Byteset& value, SIZE_T rlength, bool isVirtual = false) const;
		/*
		* 修改内存属性
		* @param address 内存地址
		* @param size 内存大小
		* @param protection 保护模式
		* @param oldProtection 原保护模式
		* @return 是否修改成功
		*/
		bool VirtualProtect(size_t address, size_t size, DWORD protection, PDWORD oldProtection) const;
		/*
		* 申请内存空间
		* @param size 申请大小, 默认1024字节
		* @return 申请到的内存地址
		*/
		size_t Allocate(size_t size = 1024) const;
		/*
		* 释放内存空间
		* @param address 内存地址
		* @param size 内存大小, 默认1024字节
		* @return 是否释放成功
		* 注意: 释放的内存必须是由Allocate申请的
		*/
		bool Free(size_t address, size_t size = 1024) const;
		/*
		* 搜索内存
		* @param buffer 要搜索的字节串
		* @param vagueContent 模糊查找的忽略字节集,默认为nullptr
		* @param startAddress 内存地址(起始), 默认NULL
		* @param endAddress 内存地址(结束), 默认-1(搜索整个进程)
		* @param type 查询内存属性(默认-1),-1:All,0:可读可写可执行,1:可读写,2:只读,3:可写可执行,4:可读可执行,5:可执行
		* @param limit 查找数量 0:不限制, 默认10
		* @param isVirtual 是否破虚拟保护, 默认false
		* @return 找到的内存地址集合
		*/
		std::vector<size_t> Search(Byteset buffer,Byteset vagueContent = nullptr, size_t startAddress = NULL, size_t endAddress = -1,  int type = -1,size_t limit = 10, bool isVirtual = false) const;
		/*
		* hook跳转(64位hook的字节码长度为14字节,32位hook的字节码长度为5字节,注意补码)
		* @param address 内存地址
		* @param newAddress 新跳转地址
		* @param complement 要补充的字节集,默认为nullptr,如果当前环境为64位程序,则hook的数据长度为16字节
		* @param isVirtual 是否破虚拟保护, 默认false
		* @return 是否跳转成功
		*/
		bool hookJump(size_t address, size_t newAddress, Byteset complement = nullptr, bool isVirtual = false) const;
		/*
		* 指针连读
		* @param address 内存地址
		* @param offsets 指针偏移集合,默认为nullptr
		* @param isVirtual 是否破虚拟保护, 默认false
		* @return 连读的指针值
		*/
		Byteset pointerChain(size_t address, std::initializer_list<size_t> offsets = {}, bool isVirtual = false) const;
	};
	#pragma pack(push, 1)
	#ifdef _WIN64
	typedef struct _R3HOOK_INFO {
		unsigned long long rax;
		unsigned int eax;
		unsigned short ax;
		unsigned char al;
		unsigned long long rcx;
		unsigned int ecx;
		unsigned short cx;
		unsigned char cl;
		unsigned long long rdx;
		unsigned int edx;
		unsigned short dx;
		unsigned char dl;
		unsigned long long rbx;
		unsigned int ebx;
		unsigned short bx;
		unsigned char bl;
		unsigned long long rsp;
		unsigned int esp;
		unsigned short sp;
		unsigned char spl;
		unsigned long long rbp;
		unsigned int ebp;
		unsigned short bp;
		unsigned char bpl;
		unsigned long long rsi;
		unsigned int esi;
		unsigned short si;
		unsigned char sil;
		unsigned long long rdi;
		unsigned int edi;
		unsigned short di;
		unsigned char dil;
		unsigned long long r8;
		unsigned int r8d;
		unsigned short r8w;
		unsigned char r8b;
		unsigned long long r9;
		unsigned int r9d;
		unsigned short r9w;
		unsigned char r9b;
		unsigned long long r10;
		unsigned int r10d;
		unsigned short r10w;
		unsigned char r10b;
		unsigned long long r11;
		unsigned int r11d;
		unsigned short r11w;
		unsigned char r11b;
		unsigned long long r12;
		unsigned int r12d;
		unsigned short r12w;
		unsigned char r12b;
		unsigned long long r13;
		unsigned int r13d;
		unsigned short r13w;
		unsigned char r13b;
		unsigned long long r14;
		unsigned int r14d;
		unsigned short r14w;
		unsigned char r14b;
		unsigned long long r15;
		unsigned int r15d;
		unsigned short r15w;
		unsigned char r15b;
	} R3HOOK_INFO, * PR3HOOK_INFO;
	#else
	typedef struct _R3HOOK_INFO {
		unsigned int eax;
		unsigned short ax;
		unsigned char al;
		unsigned int ecx;
		unsigned short cx;
		unsigned char cl;
		unsigned int edx;
		unsigned short dx;
		unsigned char dl;
		unsigned int ebx;
		unsigned short bx;
		unsigned char bl;
		unsigned int esp;
		unsigned short sp;
		unsigned int ebp;
		unsigned short bp;
		unsigned int esi;
		unsigned short si;
		unsigned int edi;
		unsigned short di;
	} R3HOOK_INFO, * PR3HOOK_INFO; 
	#endif
	#pragma pack(pop)
	class R3HOOK : private R3 {
	private:
		bool isInstalled;
		bool is64_;
		bool isVirtual;
		bool isCapture;
		size_t address;
		Byteset complement;
		Byteset temp;
		size_t newAddress;
		DWORD PID;
	public:
		R3HOOK();
		R3HOOK(DWORD pid, size_t address, Byteset complement = nullptr);
		~R3HOOK();
		/*
		* 设置是否破虚拟保护
		* @param isVirtual 是否破虚拟保护
		*/
		void setVirtual(bool isVirtual);
		/*
		* 实时截取(不再需要调用Capture函数来请求截取)
		* @param flag 是否启用,true:启用,false:禁用
		*/
		void setCapture(bool flag);
		/*
		* 安装钩子(64位hook的字节码长度为14字节,32位hook的字节码长度为5字节,注意补码)
		* @param pid 进程ID
		* @param address 内存地址
		* @param callBack 钩子回调函数
		* @param complement 要补充的字节集,默认为nullptr
		* @return 是否安装成功
		*/
		bool Install(DWORD pid, size_t address,Byteset complement = nullptr);
		/*
		* 截取数据
		*/
		void Capture();
		/*
		* 读取数据
		* @return 读取的数据
		*/
		R3HOOK_INFO ReadData() const;
		/*
		* 卸载钩子
		*/
		void Uninstall();
	};
	class EmbeddedCall : private R3 {
	private:
		typedef bool (WINAPI* embeddedCall)(int param1);
	private:
		DWORD PID;
		PVOID address;
		size_t size;

	public:
		EmbeddedCall();
		EmbeddedCall(DWORD pid,size_t size);
		~EmbeddedCall();
		/*
		* 初始化
		* @param pid 进程ID
		* @param size 内存大小
		* @return 是否初始化成功
		*/
		bool Init(DWORD pid, size_t size);
		/*
		* 释放资源
		*/
		void Unit();
		/*
		* 分配内存大小(可用于扩充内存空间)
		* @param size 内存大小
		* @return 是否分配成功
		*/
		bool AllocateMemory(size_t size);
		/*
		* 置入代码
		* @param code 代码
		* @param index 起始位置,默认为0
		* @return 是否设置成功
		*/
		bool SetCode(Byteset code, size_t index = NULL);
		/*
		* 调用函数
		* @param index 函数起始位置,从0开始
		* @param args 函数参数
		* @return 函数返回值
		*/
		template<typename Ret, typename... Args>
		Ret Call(int index, Args... args) {
			if (this->address == NULL) return Ret();
			PVOID addr = reinterpret_cast<PVOID>(reinterpret_cast<size_t>(this->address) + index);
			return (reinterpret_cast<Ret(WINAPI*)(Args...)>(addr))(args...);
		}
	};
	#ifdef _WIN64
	typedef struct _VEHHOOK_INFO {
		DWORD64 rax;
		DWORD64 rcx;
		DWORD64 rdx;
		DWORD64 rbx;
		DWORD64 rsp;
		DWORD64 rbp;
		DWORD64 rsi;
		DWORD64 rdi;
		DWORD64 rip;
		DWORD64 r8;
		DWORD64 r9;
		DWORD64 r10;
		DWORD64 r11;
		DWORD64 r12;
		DWORD64 r13;
		DWORD64 r14;
		DWORD64 r15;
		M128A xmm0;
		M128A xmm1;
		M128A xmm2;
		M128A xmm3;
		M128A xmm4;
		M128A xmm5;
		M128A xmm6;
		M128A xmm7;
		M128A xmm8;
		M128A xmm9;
		M128A xmm10;
		M128A xmm11;
		M128A xmm12;
		M128A xmm13;
		M128A xmm14;
		M128A xmm15;
	} VEHHOOK_INFO, * PVEHHOOK_INFO;
	#else
	typedef struct _VEHHOOK_INFO {
		DWORD eax;
		DWORD ecx;
		DWORD edx;
		DWORD ebx;
		DWORD esp;
		DWORD ebp;
		DWORD esi;
		DWORD edi;
		DWORD eip;
	} VEHHOOK_INFO, * PVEHHOOK_INFO;
	#endif
	/*
	* VEH回调函数类型
	* @param info 异常信息
	* @return 是否跳过异常指令段,true:跳过,false:不跳过(不跳过就会还原(原属性/int3)执行,后续要出发请自行再修改) (HOOKJUMP模式下,返回什么都不影响原指令执行)
	*/
	typedef bool (* VEHCallBack)(PEXCEPTION_POINTERS info);
	//操作模式
	enum VEH_TYPE {
		INT3,//int3异常断点 
		INT3_HOOKJUMP,//int3HOOK_JUMP模式
		HARDWARE_BREAKPOINT,//硬件断点(谨记,此模式至多4个地址,超过则会新增失败)
		HAEDWARE_HOOKJUMP,//硬件HOOK_JUMP模式
		PAGE,//页面异常断点
	};
	typedef struct _VEHHOOK_PARAM{
		DWORD code;//异常代码标识(用于在回调中区分你的hook地址)
		PVOID address;//异常地址
		VEHCallBack callBack;//回调函数
		DWORD type = INT3;//操作模式,默认INT3模式
		DWORD size = NULL;//补码大小,被hook的指令行有几个字节就填多少
		Byteset data = nullptr;//要写入的数据(仅在HOOK_JUMP模式有效)
	}VEHHOOK_PARAM, * PVEHHOOK_PARAM;
	typedef struct _VEHHOOK_HANDLE {
		PVOID veh;//VEHHook对象指针
		DWORD code;//异常代码标识(用于在回调中区分你的hook地址)
		PVOID address;//异常地址
		VEHCallBack callBack;//回调函数
		DWORD type;//操作模式
		bool isInstalled;//是否安装(操作模式为INT3时,被异常处理回调函数返回假则自动卸载)
		Byteset oldAddrData;//原地址数据
		DWORD size;//补码大小,如果指令为mov eax,0,并且操作的是这行的第一位,则补码大小要从这行到下一行指令中间的长度
		HANDLE threadId;//线程ID(仅在HARDWARE_BREAKPOINT模式有效)
		PVOID newAddress;//新地址(仅在HOOK_JUMP模式有效)
		Byteset newAddrData;//新地址数据(仅在HOOK_JUMP模式有效)
		DWORD newAddrSize;//新地址大小(仅在HOOK_JUMP模式有效)
		DWORD oldProtection;//原保护模式(仅在PAGE模式有效)
		DWORD newProtection;//新保护模式(仅在PAGE模式有效)
	} VEHHOOK_HANDLE, * PVEHHOOK_HANDLE;
	class VEHHook : private API, public R3 {
	private:
		PVOID exceptionHandler;
		static LONG NTAPI ExceptionHandler(PEXCEPTION_POINTERS ExceptionInfo);
	public:
		VEHHook();
		~VEHHook();
		/*
		* 安装VEH钩子
		* @return 是否安装成功,全局只允许安装一个VEH钩子,重复安装会返回失败
		*/
		bool Install();
		/*
		* 卸载VEH钩子
		* @return 是否卸载成功
		*/
		bool Uninstall();
		/*
		* 添加异常地址
		* @param param 参数结构体
		* @return 错误CODE(0:成功,-1:地址修改失败,-2:回调函数为空,-3:code或地址重复,-4:VEH钩子未安装,-5: 所有硬件断点寄存器都被占用)
		*/
		DWORD AddAddress(VEHHOOK_PARAM param);
		/*
		* 删除异常地址
		* @param code 异常代码标识(用于在回调中区分你的hook地址)
		* @return true=成功,false=失败
		*/
		bool DelAddress(DWORD code);
		/*
		* 修改异常地址(将原本被触发过异常的code数据,重新修改触发,HOOK_JUMP模式下,修改新地址以及新内存数据)
		* @param code 异常代码标识(用于在回调中区分你的hook地址)
		* @param newAddress 新地址
		* @param data 要写入的数据(仅在HOOK_JUMP模式有效)
		* @return 是否修改成功
		*/
		bool ModAddress(DWORD code,Byteset data = nullptr);
		/*
		* 获取寄存器
		* @param info 异常信息
		* @return 寄存器指针
		*/
		VEHHOOK_INFO GetRegisters(PEXCEPTION_POINTERS info);
		/*
		* 读模块基址
		* @param moduleName 模块名称
		* @return 模块基址
		*/
		size_t GetModuleBase(std::string moduleName) const;
		/*
		* 取地址内部异常处理信息
		* @param address 地址
		* @return 内部异常处理信息
		*/
		PVEHHOOK_HANDLE GetHandle(PVOID address);
	};
};