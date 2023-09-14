#include "JunctionPoint.h"

JunctionPoint::JunctionPoint() noexcept {}

JunctionPoint::JunctionPoint(const std::wstring& junctionPoint) noexcept: junctionPoint(junctionPoint) {}

JunctionPoint::JunctionPoint(std::wstring&& junctionPoint) noexcept: junctionPoint(std::move(junctionPoint)) {}

JunctionPoint::JunctionPoint(const JunctionPoint& other) noexcept: junctionPoint(other.junctionPoint) {}

JunctionPoint::JunctionPoint(JunctionPoint&& other) noexcept: junctionPoint(std::move(other.junctionPoint)) {}

JunctionPoint& JunctionPoint::operator=(const JunctionPoint& other) noexcept {
    if (this == &other) {
        return *this;
    }
    junctionPoint = other.junctionPoint;
    return *this;
}

JunctionPoint& JunctionPoint::operator=(JunctionPoint&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    junctionPoint = std::move(other.junctionPoint);
    return *this;
}

std::wstring& JunctionPoint::operator*() noexcept {
    return junctionPoint;
}

void JunctionPoint::MountFor(const std::wstring_view targetDir) const {
    return JunctionPoint::Mount(junctionPoint, targetDir);
}

void JunctionPoint::CreateFor(const std::wstring_view targetDir) const {
    return JunctionPoint::Create(junctionPoint, targetDir);
}

void JunctionPoint::Unmount() const {
    return JunctionPoint::Unmount(junctionPoint);
}

void JunctionPoint::Delete() const {
    return JunctionPoint::Delete(junctionPoint);
}

void JunctionPoint::RemountFor(const std::wstring_view targetDir) const {
    Unmount();
    MountFor(targetDir);
}
