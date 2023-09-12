#include "LinkSwitcher.h"
#include "Win32Exception.h"
#include "PathUtil.h"

LinkSwitcher::LinkSwitcher(): LinkSwitcher(PathUtil::ReplaceExtension(PathUtil::GetProgramFileName(), L".ini")) {}

LinkSwitcher::LinkSwitcher(const std::wstring profileName): base(PathUtil::GetParent(PathUtil::GetProgramFileName())), profile(PathUtil::Combine(base, profileName)), link(PathUtil::Combine(PathUtil::GetParent(PathUtil::GetProgramFileName()), L"Current")) {
    try {
        base = PathUtil::Combine(base, profile.ReadString(L"App", L"Base"));
    } catch (...) {}
    try {
        link = PathUtil::Combine(base, profile.ReadString(L"App", L"Link"));
    } catch (...) {}
}

void LinkSwitcher::SwitchTo(const std::wstring& key) const {
    std::wstring target = PathUtil::Combine(base, profile.ReadString(L"Items", key));
    try {
        link.RemountFor(target);
    } catch (...) {
        link.CreateFor(target);
    }
}
