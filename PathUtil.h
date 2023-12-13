#pragma once
#include <string>

class PathUtil {
public:
    static std::wstring GetParent(std::wstring_view path);
    static std::wstring GetFullPath(std::wstring_view path);
    static size_t FindExtension(std::wstring_view path);
    static std::wstring Combine(std::wstring_view pathIn, std::wstring_view pathMore);
    static std::wstring GetProgramFileName();
    static std::wstring ReplaceExtension(std::wstring_view path, std::wstring_view ext);
    static std::wstring_view GetFileNameWithoutExtension(std::wstring_view filePath);
    static std::wstring_view GetFileName(std::wstring_view filePath);
};
