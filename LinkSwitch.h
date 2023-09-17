#pragma once
#include "JunctionPoint.h"
#include "Profile.h"
#include <string>
#include <vector>

class LinkSwitch {
private:
    std::wstring base;
    Profile profile;
    JunctionPoint link;

public:
    explicit LinkSwitch();
    explicit LinkSwitch(std::wstring_view profileName);
    void SwitchTo(std::wstring_view key) const;
    std::vector<std::wstring> GetAvailableKeys() const;
};
