#include "Profile.h"
#include "PathUtil.h"
#include "Win32Exception.h"
#include <Windows.h>

std::wstring Profile::InternalReadString(const std::wstring& fileName, const std::wstring* appName, const std::wstring* keyName) {
    std::wstring fullFileName = PathUtil::GetFullPath(fileName);
    std::wstring buffer(0x1F, 0);
    for (uint32_t size = 0x20; size < 0x10000; size += 0x20) {
        buffer.resize(static_cast<size_t>(size) - 1);
        uint32_t result = ::GetPrivateProfileStringW(appName ? appName->data() : nullptr, keyName ? keyName->data() : nullptr, nullptr, buffer.data(), size, fullFileName.data());
        Win32Exception::ThrowLastErrorIfFailed();
        Win32Exception::ThrowLastErrorIf(buffer.empty(), ERROR_BAD_ARGUMENTS);
        if (appName && keyName) {
            if (result == size - 1) {
                continue;
            }
        } else {
            if (result == size - 2) {
                continue;
            }
        }
        buffer.resize(result);
        break;
    }
    return buffer;
}

std::vector<std::wstring> Profile::InternalReadNames(const std::wstring& fileName, const std::wstring* appName) {
    std::wstring sections = InternalReadString(fileName, appName, nullptr);
    std::vector<std::wstring> result;
    size_t size = 0;
    while (size < sections.size()) {
        wchar_t* data = sections.data() + size;
        size_t length = std::wcslen(data);
        size += length + 1;
        result.emplace_back(std::wstring(data, length));
    }
    return result;
}

std::vector<std::wstring> Profile::ReadSections(const std::wstring& fileName) {
    return InternalReadNames(fileName, nullptr);
}

std::vector<std::wstring> Profile::ReadKeys(const std::wstring& fileName, const std::wstring& appName) {
    if (appName.empty()) {
        Win32Exception::ThrowLastError(ERROR_BAD_ARGUMENTS);
    }
    return InternalReadNames(fileName, &appName);
}

std::wstring Profile::ReadString(const std::wstring& fileName, const std::wstring& appName, const std::wstring& keyName) {
    if (appName.empty() || keyName.empty() || fileName.empty()) {
        Win32Exception::ThrowLastError(ERROR_BAD_ARGUMENTS);
    }
    return InternalReadString(fileName, &appName, &keyName);
}
