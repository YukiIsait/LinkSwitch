#pragma once
#include "JunctionPoint.h"
#include "Profile.h"
#include <string>

class LinkSwitcher {
private:
    std::wstring base;
    Profile profile;
    JunctionPoint link;

public:
    explicit LinkSwitcher();
    explicit LinkSwitcher(std::wstring_view profileName);
    void SwitchTo(std::wstring_view key) const;
};
