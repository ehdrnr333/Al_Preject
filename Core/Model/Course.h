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

namespace project
{

    // - Note
    //      Basic Course class
    //
    //      code  : Identification Code for the same courses.
    //      id    : The course's unique number
    //      point : Course Point
    class Course
    {
    public:
        const string     code;    // CSE3031
        const int32_t    id;      // [ 1, 2 ... ]
        const int32_t    point;   // [ 1, 2 ... ]
    private: 
        Vec<LecTime>     v_time;
    
    public: 
        Course(string&& _code,
               int _id, int _point) noexcept(false);

        // - Note :
        //      Add lecture time
        virtual void addTime(LecTime _lec) noexcept(false);

        // - Note :
        //      Lecture count
        size_t count() const noexcept;

        const Vec<LecTime>& times() const noexcept;

        const LecTime& operator[](int i)  const
            noexcept(false);

    };

    std::ostream& operator << (std::ostream& _out,
                               const Course& _crs)
        noexcept(false);



} // namespace project

#endif // COURSE_H
