#pragma once

#include <compare>
#include <iomanip>
#include <sstream>
#include <string>

struct TimePoint {
    unsigned hours;
    unsigned minutes;
    auto operator<=>(TimePoint const&) const = default;
    std::string ToString() const {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << hours << ':';
        ss << std::setw(2) << std::setfill('0') << minutes;
        return ss.str();
    }
    friend std::istream& operator>>(std::istream& os, TimePoint& tp);
    friend std::ostream& operator<<(std::ostream& os, TimePoint const& tp);
};

std::istream& operator>>(std::istream& os, TimePoint& tp);
std::ostream& operator<<(std::ostream& os, TimePoint const& tp);

struct Timespan {
    TimePoint start;
    TimePoint end;
    bool IsIn(TimePoint const& time) { return time >= start && time <= end; }
};
