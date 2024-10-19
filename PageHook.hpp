#pragma once
#include "AEXModule.h"
#include <Windows.h>
#include <list>

// ����һ��ҳ�湳����
class PageHook: private Memory::R3, Memory::API
{
public:
    

private:
    //����ҳ�汣��
    void GuardPage(PVOID address) {
        DWORD oldProtect{};
        MEMORY_BASIC_INFORMATION MemoryInfoMation{};
        Memory::API::ZwQueryVirtualMemory(this->hProcess, (LPCVOID)address, MemoryBasicInformation, &MemoryInfoMation, sizeof(MemoryInfoMation), nullptr);
        Memory::R3::VirtualProtect((size_t)address, 1, MemoryInfoMation.Protect | PAGE_GUARD, &oldProtect);
    }
    //��ԭҳ�汣��
    void UnGuardPage(PVOID address)
    {
        DWORD oldProtect{};
        MEMORY_BASIC_INFORMATION MemoryInfoMation{};
        Memory::API::ZwQueryVirtualMemory(this->hProcess, (LPCVOID)address, MemoryBasicInformation, &MemoryInfoMation, sizeof(MemoryInfoMation), nullptr);
        Memory::R3::VirtualProtect((size_t)address, 1, MemoryInfoMation.Protect & ~PAGE_GUARD, &oldProtect);
    }
};
