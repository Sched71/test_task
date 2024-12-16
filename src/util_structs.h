#pragma once

#include <compare>
#include <iomanip>
#include <sstream>
#include <string>

struct TimePoint {
    unsigned hours;
    unsigned minutes;
    void Add(TimePoint const& other) {
        hours += other.hours;
        minutes += other.minutes;
        if (minutes > 60) {
            ++hours;
            minutes = minutes % 60;
        }
    }
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
    TimePoint Difference() const {
        unsigned minutes_start = start.hours * 60 + start.minutes;
        unsigned minutes_end = end.hours * 60 + end.minutes;
        unsigned minutes_diff = minutes_end - minutes_start;
        unsigned hours = minutes_diff / 60;
        unsigned minutes = minutes_diff % 60;
        return TimePoint{hours, minutes};
    }
    bool IsIn(TimePoint const& time) { return time >= start && time <= end; }
};
