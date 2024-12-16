#include "util_structs.h"

std::istream& operator>>(std::istream& os, TimePoint& tp) {
    os >> tp.hours;
    char delim = os.get();
    os >> tp.minutes;
    if (tp.hours > 23 || tp.minutes > 59 || delim != ':') {
        throw std::runtime_error("Invalid time format");
    }
    return os;
};

std::ostream& operator<<(std::ostream& os, TimePoint const& tp) {
    os << tp.ToString();
    return os;
}