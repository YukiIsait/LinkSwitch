#include "Win32Exception.h"
#include <Windows.h>
#include <memory>

std::unique_ptr<char, decltype(&::LocalFree)> FormatErrorMessage(uint32_t errorCode) noexcept {
    LPSTR buffer = nullptr;
    uint32_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                     nullptr, errorCode, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPSTR) &buffer, 0, nullptr);
    if (size) {
        uint16_t* lineBreak = reinterpret_cast<uint16_t*>(buffer + size - 2);
        if (*lineBreak == 0x0A0D) {
            *lineBreak = 0;
        }
    } else {
        buffer = reinterpret_cast<LPSTR>(::LocalAlloc(LMEM_FIXED, 26));
        if (buffer) {
            ::wsprintfA(buffer, "Unknown error 0x%08X.", errorCode);
        }
    }
    return std::unique_ptr<char, decltype(&::LocalFree)>(buffer, &::LocalFree);
}

Win32Exception::Win32Exception(uint32_t errorCode) noexcept: std::runtime_error(FormatErrorMessage(errorCode).get()), errorCode(errorCode) {}

uint32_t Win32Exception::GetErrorCode() const noexcept {
    return errorCode;
}

void Win32Exception::ThrowLastError() {
    throw Win32Exception(::GetLastError());
}

void Win32Exception::ThrowLastError(uint32_t errorCode) {
    ::SetLastError(errorCode);
    throw Win32Exception(errorCode);
}

void Win32Exception::ThrowLastErrorIf(bool expression) {
    if (expression) {
        ThrowLastError();
    }
}

void Win32Exception::ThrowLastErrorIf(bool expression, uint32_t errorCode) {
    if (expression) {
        ThrowLastError(errorCode);
    }
}

void Win32Exception::ThrowLastErrorIfFailed() {
    uint32_t errorCode = ::GetLastError();
    if (errorCode != ERROR_SUCCESS) {
        throw Win32Exception(errorCode);
    }
}
