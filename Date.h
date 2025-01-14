#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
    // Constructors
    explicit Date(int y): year(y), month(1), day(1) {
    }

    Date(int y, int m): year(y), month(m), day(1) {
    }

    Date(int y, int m, int d): year(y), month(m), day(d) {
    }

    Date &addMonths(int n) {
        year += (month + n) / 12;
        month = (month + n) % 12;
        return *this;
    }

    Date &addDays(int n) {
        int d = daysToDate() + n;
        int y = year, m = 1;
        while (d > daysInMonth(y, m)) {
            d -= daysInMonth(y, m);
            m++;
            if (m > 12) {
                m = 1;
                y++;
            }
        }
        day = d;
        month = m;
        year = y;

        return *this;
    }

    static bool isLeapYear(int y) {
        return (y % 4 || (y % 100 == 0 && y % 400)) ? false : true;
    }

    [[nodiscard]] static string toString(const Date date) {
        // Changes number date to a string version with named months
        string ss;
        switch (date.month) {
            case 1:
                ss = "Jan ";
            case 2:
                ss = "Feb ";
            case 3:
                ss = "March ";
            case 4:
                ss = "April ";
            case 5:
                ss = "May ";
            case 6:
                ss = "June ";
            case 7:
                ss = "July ";
            case 8:
                ss = "Aug ";
            case 9:
                ss = "Sep ";
            case 10:
                ss = "Oct ";
            case 11:
                ss = "Nov ";
            case 12:
                ss = "Dec ";
            default:
                ss = "Invalid Month Entered";
        }
        return ss;
    }

    [[nodiscard]] int daysToDate() const {
        int days_in_month[]{
            31, isLeapYear(year) ? 29 : 28, 31,
            30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        int days = 0;
        for (int m = 0; m < month - 1; m++) {
            days += days_in_month[m];
        }
        days += day;
        return days;
    }

    [[nodiscard]] int getYear() const {
        return year;
    }

    [[nodiscard]] int getMonth() const {
        return month;
    }

    [[nodiscard]] int getDay() const {
        return day;
    }

    // TODO: Overload operator+ here
    friend Date operator+(Date date, int n) {
        return date.addDays(n);
    }

private:
    int year, month, day;

    static int daysInMonth(int y, int m) {
        int days_in_month[]{
            31, isLeapYear(y) ? 29 : 28, 31,
            30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        return days_in_month[m - 1];
    }
};
