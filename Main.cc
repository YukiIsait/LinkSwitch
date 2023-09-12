#include "LinkSwitcher.h"
#include <cstdio>

int wmain(int argc, wchar_t** argv) {
    try {
        switch (argc) {
            case 2:
                LinkSwitcher().SwitchTo(argv[1]);
                break;
            case 3:
                LinkSwitcher(argv[2]).SwitchTo(argv[1]);
                break;
            default:
                wprintf_s(L"Usage: %s <key> [profile]\n", argv[0]);
                return 1;
        }
    } catch (const std::exception& e) {
        wprintf_s(L"Failed to switch to %s.\n", argv[1]);
        puts(e.what());
        return 1;
    }
    return 0;
}
