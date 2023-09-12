#pragma once

class Win32Handle {
private:
    void* handle;

public:
    Win32Handle() noexcept;
    Win32Handle(void* handle) noexcept;
    ~Win32Handle() noexcept;

    void* operator=(void* handle) noexcept;
    operator void*() const noexcept;
};
