#pragma once

class Win32Handle {
private:
    void* handle;

public:
    Win32Handle() noexcept;
    Win32Handle(void* handle) noexcept;
    virtual ~Win32Handle() noexcept;

    Win32Handle& operator=(void* newHandle) noexcept;
    operator void*() const noexcept;
};
