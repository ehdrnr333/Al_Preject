// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Course.h
//  Updated  : 16/06/04
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Basic Course class
//
//      This class represents an university course.
//      In the project, `Course` is set of lectures in 1 week.
//
//  Task
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef COURSE_H
#define COURSE_H

#include "./LecTime.h"
#include "../Stage/Plan.hpp"

namespace project
{

    // - Note
    //      Basic Course class
    //
    //      code  : Identification Code for the same courses.
    //      id    : The course's unique number
    //      point : Course Point
    class Course : 
        public Plan<string, int32_t, LecTime>
    {
    public:
        using base_type = Plan<string, int32_t, LecTime>;
        using code_type = base_type::id_type;
        using id_type = base_type::job_type;

        int32_t    point;   // [ 1, 2 ... ]

    public: 
        Course(string&& _code,
               int _id, int _point) noexcept(false);

        // - Note :
        //      Add lecture time
        void addTime(LecTime _lec) noexcept(false);

        const code_type& code() const noexcept;

        const id_type& id() const noexcept;

        // - Note :
        //      Lecture count(== size)
        size_t count() const noexcept;

        const LecTime& operator[](size_t i)  const
            noexcept(false);

    };

    std::ostream& operator << (std::ostream& _out,
                               const Course& _crs)
        noexcept(false);



} // namespace project

#endif // COURSE_H
