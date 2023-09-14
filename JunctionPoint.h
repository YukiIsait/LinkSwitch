#pragma once
#include <string>

class JunctionPoint {
public:
    static void Mount(const std::wstring_view junctionPoint, const std::wstring_view targetDir);
    static void Create(const std::wstring_view junctionPoint, const std::wstring_view targetDir);
    static void Unmount(const std::wstring_view junctionPoint);
    static void Delete(const std::wstring_view junctionPoint);
    static bool IsJunctionPoint(const std::wstring_view path);

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

    void MountFor(const std::wstring_view targetDir) const;
    void CreateFor(const std::wstring_view targetDir) const;
    void Unmount() const;
    void Delete() const;
    void RemountFor(const std::wstring_view targetDir) const;
};
