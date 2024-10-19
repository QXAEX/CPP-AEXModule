#include "../h/Process.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
typedef BOOL(WINAPI* enumWindows)(WNDENUMPROC, LPARAM);
typedef DWORD(WINAPI* getWindowThreadProcessId)(HWND, LPDWORD);
typedef HWND(WINAPI* findWindowW)(LPCWSTR, LPCWSTR);
typedef int(WINAPI* getWindowTextA)(HWND, LPSTR, int);
static enumWindows EnumWindows_ = (enumWindows)GetProcAddress(LoadLibraryA("user32.dll"), "EnumWindows");
static getWindowThreadProcessId GetWindowThreadProcessId_ = (getWindowThreadProcessId)GetProcAddress(LoadLibraryA("user32.dll"), "GetWindowThreadProcessId");
static findWindowW FindWindowW_ = (findWindowW)GetProcAddress(LoadLibraryA("user32.dll"), "FindWindowW");
static getWindowTextA GetWindowTextA_ = (getWindowTextA)GetProcAddress(LoadLibraryA("user32.dll"), "GetWindowTextA");
using namespace Process;
std::string Process::GetProcessPath(DWORD processID) {
    char path[MAX_PATH];
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess != NULL) {
        if (GetModuleFileNameExA(hProcess, NULL, path, MAX_PATH) != 0) {
            CloseHandle(hProcess);
            return std::string(path);
        }
        CloseHandle(hProcess);
    }
    return "";
}

std::string Process::GetProcessCommandLine(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess != NULL) {
        DWORD size = 1024;
        char* buffer = new char[size];
        if (QueryFullProcessImageNameA(hProcess, 0, buffer, &size)) {
            std::string commandLine(buffer);
            delete[] buffer;
            CloseHandle(hProcess);
            return commandLine;
        }
        delete[] buffer;
        CloseHandle(hProcess);
    }
    return "";
}

std::string Process::GetWindowTitle(HWND hwnd)
{
    const int bufferSize = 1024;
    char buffer[bufferSize];
    GetWindowTextA_(hwnd, buffer, bufferSize);
    return std::string(buffer);
}

HWND Process::GetProcessWinHandle(DWORD processID)
{
    struct EnumWindowsArg {
        HWND hwndWindow; // ´°¿Ú¾ä±ú
        DWORD dwProcessID; // ½ø³ÌID
    };
    EnumWindowsArg hwnd{};
    hwnd.dwProcessID = processID;
    hwnd.hwndWindow = NULL;
    HWND hwndRet = NULL;
    EnumWindows_([](HWND hwnd, LPARAM lParam) -> BOOL {
        EnumWindowsArg* pArg = (EnumWindowsArg*)lParam;
        DWORD windowProcessID = 0;
        GetWindowThreadProcessId_(hwnd, &windowProcessID);
        if (windowProcessID  == pArg->dwProcessID){
            pArg->hwndWindow = hwnd;
            return FALSE;
        }
        return TRUE;
        }, (LPARAM)&hwnd);
    if (hwnd.hwndWindow)
    {
        hwndRet = hwnd.hwndWindow;
    }
    return hwndRet;
}

std::vector<ProcessInfo> Process::ProcessList() {
    std::vector<ProcessInfo> processes;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return processes;
    }

    PROCESSENTRY32 pe32{};
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            ProcessInfo info;
            info.PID = pe32.th32ProcessID;
            info.WName = pe32.szExeFile;
            info.Name = Text::text_to_str(info.WName);
            info.Path = GetProcessPath(pe32.th32ProcessID);
            info.CommandLine = GetProcessCommandLine(pe32.th32ProcessID);
            
            info.WinHandle = GetProcessWinHandle(pe32.th32ProcessID);
            
            if (info.WinHandle != 0) {
                info.WinTitle = GetWindowTitle(info.WinHandle);
            }
            processes.push_back(info);
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return processes;
}

DWORD Process::ProcessGetID(std::string processName)
{
    std::vector<ProcessInfo> processes = ProcessList();
    for (ProcessInfo& process : processes) {
        if (process.Name == processName) {
            return process.PID;
        }
    }
    return -1;
}

std::string Process::ProcessGetName(DWORD processID)
{
    std::vector<ProcessInfo> processes = ProcessList();
    for (ProcessInfo& process : processes) {
        if (process.PID == processID) {
            return process.Name;
        }
    }
    return "";
}

HWND Process::ProcessGetWinHandle(DWORD processID)
{
    std::vector<ProcessInfo> processes = ProcessList();
    for (ProcessInfo& process : processes) {
        if (process.PID == processID) {
            return FindWindowW_(NULL, process.WName.c_str());
        }
    }
    return NULL;
}
