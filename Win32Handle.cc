#include "Win32Handle.h"
#include <Windows.h>

Win32Handle::Win32Handle() noexcept: handle(nullptr) {}

Win32Handle::Win32Handle(void* handle) noexcept: handle(handle) {}

Win32Handle::~Win32Handle() noexcept {
    if (handle != nullptr) {
        ::CloseHandle(handle);
        handle = nullptr;
    }
}

Win32Handle& Win32Handle::operator=(void* newHandle) noexcept {
    if (handle != nullptr) {
        ::CloseHandle(handle);
    }
    handle = newHandle;
    return *this;
}

Win32Handle::operator void*() const noexcept {
    return handle;
}
