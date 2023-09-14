#pragma once
#include <stdexcept>
#include <string>

class Win32Exception: public std::runtime_error {
private:
    uint32_t errorCode;

public:
    explicit Win32Exception(uint32_t errorCode) noexcept;
    virtual ~Win32Exception() noexcept override;
    uint32_t GetErrorCode() const noexcept;

    static void ThrowLastError();
    static void ThrowLastError(uint32_t errorCode);
    static void ThrowLastErrorIf(bool expression);
    static void ThrowLastErrorIf(bool expression, uint32_t errorCode);
    static void ThrowLastErrorIfFailed();
};
