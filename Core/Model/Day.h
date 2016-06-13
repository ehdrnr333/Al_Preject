// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Day.h
//  Updated  : 16/06/01
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Specific type for Day concept
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef DAY_H
#define DAY_H

#include "../Base.h"

namespace project
{
    // - Note
    //      WeekDay literal
    enum WeekDay : int {
        Invalid = -1,
        Sun = 0,  Mon = 1,  Tue = 2,  Wed = 3,
        Thu = 4,  Fri = 5,  Sat = 6
    };

    static constexpr auto week = 7;

    std::ostream& operator<< (std::ostream& _out,
                              const WeekDay _day)
        noexcept(false);

    static Ary<const string, week> EngWeek =
    {
        u8"Sun",  u8"Mon",  u8"Tue",  u8"Wed",
        u8"Thu",  u8"Fri",  u8"Sat"
    };

    static Ary<const string, week> KorWeek =
    {
        u8"일", u8"월", u8"화", u8"수",
        u8"목", u8"금", u8"토"
    };

}

#endif // DAY_H
