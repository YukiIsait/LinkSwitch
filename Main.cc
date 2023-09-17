#include "LinkSwitch.h"
#include <optional>
#include <cstdio>

int wmain(int argc, wchar_t** argv) {
    std::optional<LinkSwitch> linkSwitch;
    try {
        switch (argc) {
            case 2:
                linkSwitch = LinkSwitch();
                break;
            case 3:
                linkSwitch = LinkSwitch(argv[2]);
                break;
            default:
                wprintf_s(L"Usage: %s <key|#> [profile]\n", argv[0]);
                return -1;
        }
        if (argv[1][0] == L'#' && argv[1][1] == 0) {
            std::vector<std::wstring> availableKeys = linkSwitch->GetAvailableKeys();
            for (size_t i = 0; i < availableKeys.size() - 1; i++) {
                fputws(availableKeys.at(i).data(), stdout);
                fputwc(L'\n', stdout);
            }
            fputws(availableKeys.at(availableKeys.size() - 1).data(), stdout);
        } else {
            linkSwitch->SwitchTo(argv[1]);
        }
    } catch (const std::exception& e) {
        puts(e.what());
        return -1;
    }
    return 0;
}
