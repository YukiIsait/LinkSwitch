#include "Win32Exception.h"
#include <Windows.h>

std::string Win32Exception::FormatErrorMessage(uint32_t errorCode) noexcept {
    LPSTR buffer = nullptr;
    uint32_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                                     nullptr,
                                     errorCode,
                                     MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
                                     (LPSTR) &buffer,
                                     0,
                                     nullptr);
    if (!size) {
        return std::string("Unknown Win32Exception.");
    }
    std::string message(buffer, size);
    message.erase(message.find_last_not_of("\x20\x0D\x0A") + 1);
    ::LocalFree(buffer);
    return message;
}

uint32_t Win32Exception::GetErrorCode() const noexcept {
    return errorCode;
}

Win32Exception::Win32Exception(uint32_t errorCode) noexcept: std::runtime_error(FormatErrorMessage(errorCode)), errorCode(errorCode) {}

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
