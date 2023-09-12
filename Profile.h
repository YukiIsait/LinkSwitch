#pragma once
#include <vector>
#include <string>

class Profile {
private:
    static std::wstring InternalReadString(const std::wstring& fileName, const std::wstring* appName, const std::wstring* keyName);
    static std::vector<std::wstring> InternalReadNames(const std::wstring& fileName, const std::wstring* appName);

public:
    static std::vector<std::wstring> ReadSections(const std::wstring& fileName);
    static std::vector<std::wstring> ReadKeys(const std::wstring& fileName, const std::wstring& appName);
    static std::wstring ReadString(const std::wstring& fileName, const std::wstring& appName, const std::wstring& keyName);

private:
    std::wstring fileName;

public:
    Profile() noexcept;
    Profile(const std::wstring& fileName) noexcept;
    Profile(std::wstring&& fileName) noexcept;
    Profile(const Profile& other) noexcept;
    Profile(Profile&& other) noexcept;

    Profile& operator=(const Profile& other) noexcept;
    Profile& operator=(Profile&& other) noexcept;

    std::wstring& operator*() noexcept;

    std::vector<std::wstring> ReadSections() const;
    std::vector<std::wstring> ReadKeys(const std::wstring& appName) const;
    std::wstring ReadString(const std::wstring& appName, const std::wstring& keyName) const;
};
