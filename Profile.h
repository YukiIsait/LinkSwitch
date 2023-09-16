#pragma once
#include <vector>
#include <string>

class Profile {
private:
    static std::wstring InternalReadString(std::wstring_view fileName, const std::wstring_view* appName, const std::wstring_view* keyName);
    static std::vector<std::wstring> InternalReadNames(std::wstring_view fileName, const std::wstring_view* appName);

public:
    static std::vector<std::wstring> ReadSections(std::wstring_view fileName);
    static std::vector<std::wstring> ReadKeys(std::wstring_view fileName, std::wstring_view appName);
    static std::wstring ReadString(std::wstring_view fileName, std::wstring_view appName, std::wstring_view keyName);

private:
    std::wstring fileName;

public:
    Profile() noexcept = default;
    Profile(const Profile& other) noexcept = default;
    Profile(std::wstring_view fileName) noexcept;
    Profile(std::wstring&& fileName) noexcept;
    Profile(Profile&& other) noexcept;

    Profile& operator=(const Profile& other) noexcept;
    Profile& operator=(Profile&& other) noexcept;

    std::wstring& operator*() noexcept;

    std::vector<std::wstring> ReadSections() const;
    std::vector<std::wstring> ReadKeys(std::wstring_view appName) const;
    std::wstring ReadString(std::wstring_view appName, std::wstring_view keyName) const;
};
