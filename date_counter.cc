#include <time.h>
#include <iostream>
#include "date_counter.h"

DateCounter::SimpleDate::SimpleDate(void)
{
    time_t local_time;
    struct tm *today;

    time(&local_time);
    today = localtime(&local_time);
    year = (uint16_t)(1900 + today->tm_year);
    month = (uint8_t)today->tm_mon + 1;
    date = (uint8_t)today->tm_mday;
}

std::ostream &DateCounter::operator<<(std::ostream &os, const DateCounter::SimpleDate &d)
{
    os << d.toString();
    return os;
}

DateCounter::SimpleDate &DateCounter::operator+=(DateCounter::SimpleDate &a, int days)
{
    a.add(days);
    return a;
}

uint8_t DateCounter::SimpleDate::DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

template <typename T> static void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

int DateCounter::SimpleDate::operator-(const DateCounter::SimpleDate& dstDate)
{
    SimpleDate a = *this;
    SimpleDate b = dstDate;
    int sum = 0;
    int i;

    if (a.year == b.year) {
        updateDaysInMonth(a.year);
        if (a.month == b.month) {
            sum = a.date > b.date ? a.date - b.date : b.date - a.date;
        } else {
            if (a.month > b.month)
                swap(a, b);
            for (i = a.month - 1; i < b.month - 1; ++i)
                sum += DAYS_IN_MONTH[i];
            sum += b.date - a.date;
        }
    } else {
        if (a.year > b.year)
            swap(a, b);

        updateDaysInMonth(a.year);
        for (i = a.month - 1; i < 12; ++i)
            sum += DAYS_IN_MONTH[i];

        sum -= a.date;
        while (++a.year < b.year)
            sum += isLeapYear(a.year) ? 366 : 365;

        updateDaysInMonth(b.year);
        for (i = 0; i < b.month - 1; i++)
            sum += DAYS_IN_MONTH[i];
        sum += b.date;
    }

    return *this < dstDate ? -sum : sum;
}

void DateCounter::SimpleDate::add(int days)
{
    SimpleDate temp = *this;

    if (days < 0) {
        throw std::range_error("param should not be a negative integer");
    }

    while (temp.month <= 12) {
        updateDaysInMonth(temp.year);
        if (!(temp.month == this->month && temp.year == this->year))
            temp.date = 0;
        if (days <= DAYS_IN_MONTH[temp.month - 1] - temp.date) {
            days += temp.date;
            break;
        } else {
            days -= DAYS_IN_MONTH[temp.month - 1] - temp.date;
            ++temp.month;
            if (temp.month == 13) {
                ++temp.year;
                temp.month = 1;
            }
        }
    }

    temp.date = days;
    *this = temp;
}

