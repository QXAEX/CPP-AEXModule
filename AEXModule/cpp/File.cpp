#include "../h/File.h"
File::File(std::string path)
{
	Open(path);
}
File::~File()
{
	if (this->is_open) {
		Close();
	}
}
bool File::Open(std::string path, bool create)
{
    if (this->hfile != INVALID_HANDLE_VALUE && this->hfile != NULL) {
        return this->is_open;
    }

    this->path = path;
    DWORD dwCreationDisposition = create ? CREATE_ALWAYS : OPEN_EXISTING;
    if (create) {
        if (path.find_last_of("\\/") != std::string::npos) System::CreateDir(path.substr(0, path.find_last_of("\\/")));
        this->hfile = CreateFileA(
            path.c_str(),                // 文件路径
            GENERIC_READ | GENERIC_WRITE, // 读写权限
            FILE_SHARE_READ | FILE_SHARE_WRITE, // 共享模式
            NULL,                        // 安全属性
            dwCreationDisposition,       // 创建或打开模式
            FILE_FLAG_WRITE_THROUGH,     // 文件属性
            NULL                         // 模板文件句柄
        );
    }
    else {
        // 使用 CreateFile 函数打开文件，并设置读写权限和共享模式
        this->hfile = CreateFileA(
            path.c_str(),                // 文件路径
            GENERIC_READ | GENERIC_WRITE, // 读写权限
            FILE_SHARE_READ | FILE_SHARE_WRITE, // 共享模式
            NULL,                        // 安全属性
            OPEN_EXISTING,               // 打开已存在的文件
            FILE_ATTRIBUTE_NORMAL,       // 文件属性
            NULL                         // 模板文件句柄
        );
    }

    this->is_open = this->hfile != INVALID_HANDLE_VALUE;

    if (this->hfile == INVALID_HANDLE_VALUE) {
        // 可以根据需要记录错误信息，如使用 GetLastError
        return false;
    }

    this->is_open = true;
    return this->is_open;
}

bool File::Close()
{
	if(!CloseHandle(hfile))return false;
	hfile = INVALID_HANDLE_VALUE;
	is_open = false;
	return true;
}

bool File::DelFile()
{
	if (!DeleteFileA(path.c_str())) {
		return false;
	}
	return true;
}

bool File::Seek(long long pos) const
{
	if (!this->is_open) {
		return false;
	}
	return SetFilePointer(this->hfile, (long)pos, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
}

size_t File::Size() const
{
	if (!this->is_open) {
		return 0;
	}
	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(this->hfile, &fileSize)) {
		return 0;
	}
	return static_cast<size_t>(fileSize.QuadPart);
}

bool File::Write(Byteset data) const
{
	if (!this->is_open || data.empty()) {
		return false;
	}
	return WriteFile(this->hfile, data.data(),static_cast<DWORD>(data.size()), NULL, NULL);
}

Byteset File::Read(long long size) const
{
	if (!this->is_open) {
		return Byteset();
	}
	Byteset data;
    PUCHAR buffer = new UCHAR[size];
	DWORD dwRead;
	if (!ReadFile(this->hfile, buffer,(DWORD)size,&dwRead,NULL)) {
        delete[] buffer;
		return Byteset();
	}
	data = Byteset(buffer, dwRead);
    delete[] buffer;
	return data;
}

bool File::Delete(long long size) const {
    if (!is_open) {
        return false;
    }
    LARGE_INTEGER currentPointer;
    if (!SetFilePointerEx(hfile, LARGE_INTEGER{ 0 }, &currentPointer, FILE_CURRENT)) {
        return false;
    }
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hfile, &fileSize)) {
        return false;
    }
    int remainingSize = static_cast<int>(fileSize.QuadPart - currentPointer.QuadPart);
    if (remainingSize <= size) {
        if (!SetFilePointerEx(hfile, currentPointer, nullptr, FILE_BEGIN)) {
            return false;
        }
        if (!SetEndOfFile(hfile)) {
            return false;
        }
    }
    else {
        std::vector<char> buffer(remainingSize);
        DWORD bytesRead;
        if (!ReadFile(hfile, buffer.data(), remainingSize, &bytesRead, nullptr)) {
            return false;
        }
        LARGE_INTEGER newPointer{};
        newPointer.QuadPart = currentPointer.QuadPart;
        if (!SetFilePointerEx(hfile, newPointer, nullptr, FILE_BEGIN)) {
            return false;
        }
        DWORD bytesWritten;
        if (!WriteFile(hfile, buffer.data() + size, remainingSize - size, &bytesWritten, nullptr)) {
            return false;
        }
        newPointer.QuadPart = currentPointer.QuadPart + remainingSize - size;
        if (!SetFilePointerEx(hfile, newPointer, nullptr, FILE_BEGIN)) {
            return false;
        }
        if (!SetEndOfFile(hfile)) {
            return false;
        }
    }
    return true;
}

bool File::Replace(Byteset new_data, long long size) const
{
    if (!is_open) {
        return false;
    }
    LARGE_INTEGER currentPointer;
    if (!SetFilePointerEx(hfile, LARGE_INTEGER{ 0 }, &currentPointer, FILE_CURRENT)) {
        return false;
    }
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hfile, &fileSize)) {
        return false;
    }
    int remainingSize = static_cast<int>(fileSize.QuadPart - currentPointer.QuadPart);
    if (remainingSize < static_cast<int>(size)) {
        return false;
    }
    std::vector<char> buffer(remainingSize);
    DWORD bytesRead;
    if (!ReadFile(hfile, buffer.data(), remainingSize, &bytesRead, nullptr)) {
        return false;
    }
    LARGE_INTEGER newPointer{};
    newPointer.QuadPart = currentPointer.QuadPart;
    if (!SetFilePointerEx(hfile, newPointer, nullptr, FILE_BEGIN)) {
        return false;
    }
    DWORD bytesWritten;
    if (!WriteFile(hfile, new_data.data(), size, &bytesWritten, nullptr)) {
        return false;
    }
    newPointer.QuadPart = currentPointer.QuadPart + size;
    if (!SetFilePointerEx(hfile, newPointer, nullptr, FILE_BEGIN)) {
        return false;
    }
    if (!SetEndOfFile(hfile)) {
        return false;
    }
    return true;
}

size_t File::Find(Byteset data, size_t index, bool flag) const
{
    if (!is_open) {
        return -1;
    }

    const size_t dataSize = data.size();
    LARGE_INTEGER fileSize;

    // Get file size
    if (!GetFileSizeEx(hfile, &fileSize)) {
        return -1;
    }

    // Create file mapping
    HANDLE hMapFile = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapFile == NULL) {
        return -1;
    }

    // Map view of file
    char* pFile = static_cast<char*>(MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0));
    if (pFile == NULL) {
        CloseHandle(hMapFile);
        return -1;
    }

    size_t fileSizeInBytes = static_cast<size_t>(fileSize.QuadPart);
    size_t result = -1;

    // Search for the data
    for (size_t i = index; i <= fileSizeInBytes - dataSize; ++i) {
        if (memcmp(data.data(), pFile + i, dataSize) == 0) {
            result = i;
            break;
        }
    }

    // Unmap view of file and close file mapping handle
    UnmapViewOfFile(pFile);
    CloseHandle(hMapFile);

    return result;
}

