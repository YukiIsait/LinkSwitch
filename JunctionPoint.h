#pragma once
#include <string>

class JunctionPoint {
public:
    static void Mount(std::wstring_view junctionPoint, std::wstring_view targetDir);
    static void Create(std::wstring_view junctionPoint, std::wstring_view targetDir);
    static void Unmount(std::wstring_view junctionPoint);
    static void Delete(std::wstring_view junctionPoint);
    static bool IsJunctionPoint(std::wstring_view path);

private:
    std::wstring junctionPoint;

public:
    JunctionPoint() noexcept = default;
    JunctionPoint(const JunctionPoint& other) noexcept = default;
    JunctionPoint(std::wstring_view junctionPoint) noexcept;
    JunctionPoint(std::wstring&& junctionPoint) noexcept;
    JunctionPoint(JunctionPoint&& other) noexcept;

    JunctionPoint& operator=(const JunctionPoint& other) noexcept;
    JunctionPoint& operator=(JunctionPoint&& other) noexcept;

    std::wstring& operator*() noexcept;

    void MountFor(std::wstring_view targetDir) const;
    void CreateFor(std::wstring_view targetDir) const;
    void Unmount() const;
    void Delete() const;
    void RemountFor(std::wstring_view targetDir) const;
};
