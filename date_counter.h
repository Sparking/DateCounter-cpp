#pragma once
#include <iostream>
#include <cinttypes>

namespace DateCounter {
    class SimpleDate {
    private:
        static uint8_t DAYS_IN_MONTH[12];
        static void updateDaysInMonth(uint16_t year) {
            DAYS_IN_MONTH[1] = isLeapYear(year) ? 29 : 28;
        }
    public:
        uint16_t year;
        uint8_t month;
        uint8_t date;
        SimpleDate(void);
        constexpr explicit SimpleDate(const uint16_t year, const uint8_t month, const uint8_t date) :
            year(year), month(month), date(date) {}
        constexpr SimpleDate(const SimpleDate &c) : year(c.year), month(c.month), date(c.date) {}
        static bool isLeapYear(uint16_t year) {
            return ((year % 4 == 0) || (year % 100 != 0 && year % 400 == 0));
        }
        bool operator<(const SimpleDate& b) const {
            if (year == b.year) {
                if (month == b.month)
                    return date < b.date;
                return month < b.month;
            }
            return year < b.year;
        }
        bool operator==(const SimpleDate& b) const {
            return year == b.year && month == b.month && date == b.date;
        }
        int operator-(const SimpleDate&);
        friend std::ostream &operator<<(std::ostream&, const SimpleDate&);
        friend SimpleDate &operator+=(SimpleDate&, int);
        void add(int days);
        std::string toString(void) const {
            char str[11];
            snprintf(str, 11, "%d-%02d-%02d", year, month, date);
            return std::string(str);
        }
    };
    extern std::ostream &operator<<(std::ostream &, const SimpleDate&);
    extern SimpleDate &operator+=(SimpleDate&, int);
}
