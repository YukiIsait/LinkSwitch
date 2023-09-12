#pragma once
#include <string>

class JunctionPoint {
public:
    static void Mount(const std::wstring& junctionPoint, const std::wstring& targetDir);
    static void Create(const std::wstring& junctionPoint, const std::wstring& targetDir);
    static void Unmount(const std::wstring& junctionPoint);
    static void Delete(const std::wstring& junctionPoint);
    static bool IsJunctionPoint(const std::wstring& path);

private:
    std::wstring junctionPoint;

public:
    JunctionPoint() noexcept;
    JunctionPoint(const std::wstring& junctionPoint) noexcept;
    JunctionPoint(std::wstring&& junctionPoint) noexcept;
    JunctionPoint(const JunctionPoint& other) noexcept;
    JunctionPoint(JunctionPoint&& other) noexcept;

    JunctionPoint& operator=(const JunctionPoint& other) noexcept;
    JunctionPoint& operator=(JunctionPoint&& other) noexcept;

    std::wstring& operator*() noexcept;

    void MountFor(const std::wstring& targetDir) const;
    void CreateFor(const std::wstring& targetDir) const;
    void Unmount() const;
    void Delete() const;
    void RemountFor(const std::wstring& targetDir) const;
};
