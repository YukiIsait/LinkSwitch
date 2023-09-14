#include "JunctionPoint.h"
#include "Win32Exception.h"
#include "Win32Handle.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <memory>

struct ReparseDataBuffer {
    DWORD ReparseTag;
    WORD ReparseDataLength;
    WORD Reserved;
    struct {
        WORD SubstituteNameOffset;
        WORD SubstituteNameLength;
        WORD PrintNameOffset;
        WORD PrintNameLength;
        WCHAR PathBuffer[1];
    } MountPointReparseBuffer;
};

std::pair<std::unique_ptr<ReparseDataBuffer>, size_t> CreateMountPointReparseDataBuffer(const std::wstring_view substituteName, const std::wstring_view printName) noexcept {
    size_t substituteNameSize = (substituteName.size() + 1) * sizeof(wchar_t);
    size_t printNameSize = (printName.size() + 1) * sizeof(wchar_t);
    size_t reparseDataBufferSize = UFIELD_OFFSET(ReparseDataBuffer, MountPointReparseBuffer.PathBuffer) + substituteNameSize + printNameSize;
    std::unique_ptr<ReparseDataBuffer> reparseDataBuffer(reinterpret_cast<ReparseDataBuffer*>(new uint8_t[reparseDataBufferSize]));
    reparseDataBuffer->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
    reparseDataBuffer->ReparseDataLength = static_cast<uint16_t>(reparseDataBufferSize - UFIELD_OFFSET(ReparseDataBuffer, MountPointReparseBuffer));
    reparseDataBuffer->Reserved = 0;
    reparseDataBuffer->MountPointReparseBuffer.SubstituteNameOffset = 0;
    reparseDataBuffer->MountPointReparseBuffer.SubstituteNameLength = static_cast<uint16_t>(substituteNameSize - sizeof(wchar_t));
    reparseDataBuffer->MountPointReparseBuffer.PrintNameOffset = static_cast<uint16_t>(substituteNameSize);
    reparseDataBuffer->MountPointReparseBuffer.PrintNameLength = static_cast<uint16_t>(printNameSize - sizeof(wchar_t));
    std::memcpy(reparseDataBuffer->MountPointReparseBuffer.PathBuffer, substituteName.data(), substituteNameSize);
    std::memcpy(reinterpret_cast<uint8_t*>(reparseDataBuffer->MountPointReparseBuffer.PathBuffer) + substituteNameSize, printName.data(), printNameSize);
    return std::make_pair(std::move(reparseDataBuffer), reparseDataBufferSize);
}

void JunctionPoint::Mount(const std::wstring_view junctionPoint, const std::wstring_view targetDir) {
    DWORD targetDirFullPathSize = ::GetFullPathNameW(targetDir.data(), 0, nullptr, nullptr);
    Win32Exception::ThrowLastErrorIf(targetDirFullPathSize == 0);
    std::wstring targetDirNtPath(targetDirFullPathSize + 4, 0);
    std::wmemcpy(targetDirNtPath.data(), L"\\??\\", 4);
    targetDirFullPathSize = ::GetFullPathNameW(targetDir.data(), targetDirFullPathSize, targetDirNtPath.data() + 4, nullptr);
    Win32Exception::ThrowLastErrorIf(targetDirFullPathSize == 0);
    targetDirNtPath.resize(targetDirNtPath.size() - 1);
    Win32Handle reparsePoint = ::CreateFileW(junctionPoint.data(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
    Win32Exception::ThrowLastErrorIf(reparsePoint == INVALID_HANDLE_VALUE);
    std::pair<std::unique_ptr<ReparseDataBuffer>, size_t> reparseData = CreateMountPointReparseDataBuffer(targetDirNtPath, L"");
    DWORD bytesReturned;
    BOOL ret = ::DeviceIoControl(reparsePoint, FSCTL_SET_REPARSE_POINT, reparseData.first.get(), static_cast<DWORD>(reparseData.second), nullptr, 0, &bytesReturned, nullptr);
    Win32Exception::ThrowLastErrorIf(!ret);
}

void JunctionPoint::Create(const std::wstring_view junctionPoint, const std::wstring_view targetDir) {
    Win32Exception::ThrowLastErrorIf(!::CreateDirectoryW(junctionPoint.data(), nullptr));
    try {
        Mount(junctionPoint, targetDir);
    } catch (const Win32Exception& e) {
        ::RemoveDirectoryW(junctionPoint.data());
        throw e;
    }
}

void JunctionPoint::Unmount(const std::wstring_view junctionPoint) {
    ReparseDataBuffer reparseDataBuffer = {
        .ReparseTag = IO_REPARSE_TAG_MOUNT_POINT
    };
    Win32Handle reparsePoint = ::CreateFileW(junctionPoint.data(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
    Win32Exception::ThrowLastErrorIf(reparsePoint == INVALID_HANDLE_VALUE);
    DWORD bytesReturned;
    BOOL ret = ::DeviceIoControl(reparsePoint, FSCTL_DELETE_REPARSE_POINT, &reparseDataBuffer, UFIELD_OFFSET(ReparseDataBuffer, MountPointReparseBuffer), nullptr, 0, &bytesReturned, nullptr);
    Win32Exception::ThrowLastErrorIf(!ret);
}

void JunctionPoint::Delete(const std::wstring_view junctionPoint) {
    Unmount(junctionPoint);
    ::RemoveDirectoryW(junctionPoint.data());
}

bool JunctionPoint::IsJunctionPoint(const std::wstring_view path) {
    DWORD attributes = ::GetFileAttributesW(path.data());
    Win32Exception::ThrowLastErrorIf(attributes == INVALID_FILE_ATTRIBUTES);
    if ((attributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT)) != (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT)) {
        return false;
    }
    return true;
}
