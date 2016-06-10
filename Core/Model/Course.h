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
private: // ---- ---- Variable ---- ----
    string          crs_code;
    std::int32_t    crs_id;
    std::int32_t    crs_point;
    std::vector<LecTime> crs_times;

public: // ---- ---- Default ---- ----
    Course(string&& _code,
           int _id, int _point) noexcept(false);

    // - Note :
    //      Identification Code for the same courses.
    // - Return
    //      CSE3031
    virtual
    const string& code()  const  noexcept;

    // - Note :
    //      The course's unique number
    // - Return
    //      [ 1, 2 ... ]
    virtual int id()  const  noexcept;

    // - Note :
    //      Course Point
    // - Return
    //      [ 1, 2 ... ]
    virtual int point() const  noexcept;

    // - Note :
    //      Add lecture time
    virtual void addTime(LecTime _lec) noexcept(false);

    // - Note :
    //      Return the vector of lecture times
    virtual 
    const std::vector<LecTime>& lectures() const noexcept;

};


std::ostream& operator << (std::ostream& _out,
                           const Course& _crs)
    noexcept(false);



} // namespace project

#endif // COURSE_H
