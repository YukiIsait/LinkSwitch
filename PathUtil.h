#pragma once
#include <string>

class PathUtil {
public:
    static std::wstring GetParent(const std::wstring_view path);
    static std::wstring GetFullPath(const std::wstring_view path);
    static size_t FindExtension(const std::wstring_view path);
    static std::wstring Combine(const std::wstring_view pathIn, const std::wstring_view pathMore);
    static std::wstring GetProgramFileName();
    static std::wstring ReplaceExtension(const std::wstring_view path, const std::wstring_view ext);
};
