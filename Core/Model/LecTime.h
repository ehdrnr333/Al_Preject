// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : LecTime.h
//  Updated  : 16/06/04
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Basic Lecture Time class
//      This class represents that 1 teaching time in 1 week.
//
//      In the project, `Lecture` means weekly teaching times.
//      Therefore, there can be multiple `Lecture Time` in 1 week.
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef LECTIME_H
#define LECTIME_H

#include "./Day.h"

namespace project
{
    // - Note
    //      1 Lecture Time in a week
    //
    //      [Start, End)
    //      In comparison, the end time can overrlap
    //      the other's start time.
    // - Concept
    //      Value Semantic
    class LecTime
    {
        WeekDay  weekday;
        int      start_tm;
        int      end_tm;

    public:
        explicit LecTime(WeekDay _wday,
                         int _s, int _e) noexcept(false);

        // - Note
        //      Calue WeekDay enumeration
        virtual WeekDay day() const noexcept;

        // - Note
        //      Start Time
        // - Example
        //      1.0 == 10
        //      2.5 == 25
        virtual int start() const noexcept;

        // - Note
        //      End Time
        // - Example
        //      5.5  == 55
        //      10.5 == 105
        virtual int end()   const noexcept;

        // - Note
        //      Lecture length
        // - Example
        //      when
        //          Start == 25
        //          End   == 40
        //      then
        //          Length == 15
        virtual int length() const noexcept;

    };

    // - Note
    //      Compare day, start, end
    bool operator ==(const LecTime& _lhs,
                     const LecTime& _rhs)
        noexcept;

    // - Note
    //      Print to basic character stream
    std::ostream& operator<<(std::ostream& _out,
                             const LecTime& _lec)
        noexcept(false);

    // - Note
    //      Check if 2 lecture collide
    //      !!! Internal mechanism can be changed later !!!
    bool do_collide(const LecTime& _lhs,
                    const LecTime& _rhs) noexcept;


}

#endif // LECTIME_H
