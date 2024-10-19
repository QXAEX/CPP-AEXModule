#pragma once
#include "AEXModule.h"
#include <Windows.h>
#include <list>

// 定义一个页面钩子类
class PageHook: private Memory::R3, Memory::API
{
public:
    

private:
    //更改页面保护
    void GuardPage(PVOID address) {
        DWORD oldProtect{};
        MEMORY_BASIC_INFORMATION MemoryInfoMation{};
        Memory::API::ZwQueryVirtualMemory(this->hProcess, (LPCVOID)address, MemoryBasicInformation, &MemoryInfoMation, sizeof(MemoryInfoMation), nullptr);
        Memory::R3::VirtualProtect((size_t)address, 1, MemoryInfoMation.Protect | PAGE_GUARD, &oldProtect);
    }
    //还原页面保护
    void UnGuardPage(PVOID address)
    {
        DWORD oldProtect{};
        MEMORY_BASIC_INFORMATION MemoryInfoMation{};
        Memory::API::ZwQueryVirtualMemory(this->hProcess, (LPCVOID)address, MemoryBasicInformation, &MemoryInfoMation, sizeof(MemoryInfoMation), nullptr);
        Memory::R3::VirtualProtect((size_t)address, 1, MemoryInfoMation.Protect & ~PAGE_GUARD, &oldProtect);
    }
};
