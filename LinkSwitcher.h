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
    explicit LinkSwitcher(const std::wstring profileName);
    void SwitchTo(const std::wstring& key) const;
};
