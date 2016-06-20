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
        "Sun",  "Mon",  "Tue",  "Wed",
        "Thu",  "Fri",  "Sat"
    };

    static Ary<const string, week> KorWeek =
    {
        "일", "월", "화", "수",
        "목", "금", "토"
    };

}

#endif // DAY_H
