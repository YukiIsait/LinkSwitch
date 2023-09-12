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

void* Win32Handle::operator=(void* handle) noexcept {
    if (this->handle != nullptr) {
        ::CloseHandle(this->handle);
    }
    this->handle = handle;
    return handle;
}

Win32Handle::operator void*() const noexcept {
    return handle;
}
