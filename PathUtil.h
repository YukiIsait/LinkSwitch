#pragma once
#include <string>

class PathUtil {
public:
    static std::wstring GetParent(const std::wstring& path);
    static std::wstring GetFullPath(const std::wstring& path);
    static size_t FindExtension(const std::wstring& path);
    static std::wstring Combine(const std::wstring& pathIn, const std::wstring& pathMore);
    static std::wstring GetProgramFileName();
    static std::wstring ReplaceExtension(const std::wstring& path, const std::wstring& ext);
};
