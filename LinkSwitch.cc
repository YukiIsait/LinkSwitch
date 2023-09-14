#include "LinkSwitch.h"
#include "Win32Exception.h"
#include "PathUtil.h"

LinkSwitch::LinkSwitch(): LinkSwitch(PathUtil::ReplaceExtension(PathUtil::GetProgramFileName(), L".ini")) {}

LinkSwitch::LinkSwitch(std::wstring_view profileName): base(PathUtil::GetParent(PathUtil::GetProgramFileName())), profile(PathUtil::Combine(base, profileName)), link(PathUtil::Combine(PathUtil::GetParent(PathUtil::GetProgramFileName()), L"Current")) {
    try {
        base = PathUtil::Combine(base, profile.ReadString(L"App", L"Base"));
        *link = PathUtil::Combine(base, L"Current");
    } catch (...) {}
    try {
        *link = PathUtil::Combine(base, profile.ReadString(L"App", L"Link"));
    } catch (...) {}
}

void LinkSwitch::SwitchTo(std::wstring_view key) const {
    std::wstring target = PathUtil::Combine(base, profile.ReadString(L"Items", key));
    try {
        link.RemountFor(target);
    } catch (...) {
        link.CreateFor(target);
    }
}
