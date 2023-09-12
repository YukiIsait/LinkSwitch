#pragma once
#include <stdexcept>
#include <string>

class Win32Exception: public std::runtime_error {
private:
    uint32_t errorCode;
    static std::string FormatErrorMessage(uint32_t errorCode) noexcept;

public:
    uint32_t GetErrorCode() const noexcept;
    explicit Win32Exception(uint32_t errorCode) noexcept;

    static void ThrowLastError();
    static void ThrowLastError(uint32_t errorCode);
    static void ThrowLastErrorIf(bool expression);
    static void ThrowLastErrorIf(bool expression, uint32_t errorCode);
    static void ThrowLastErrorIfFailed();
};
