// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : CourseInterpreter.h
//  Updated  : 16/06/04
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Interpreter to parse Text stream into Course objects
//
//  Task
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "./Course.h"

namespace project
{

// - Note
//      (none)
class CourseInterpreter
{
public:  // ---- ---- Type ---- ----
    using string = project::string;

private: // ---- ---- Variable ---- ----
    std::istream& in;


public:  // ---- ---- Default ---- ----
    explicit CourseInterpreter(std::istream& _in) noexcept(false);

    // - Note
    //      Generate the Course object from the stream
    // - Throws
    //      std::ios_base::failure  // stream state is not good.
    //      std::invalid_argument   // fail from invalid value
    Course generate() noexcept(false);


private:

    // - Note
    //      Fetch specific columns from the stream
    //      The column delimiter is '\t'
    // - Throws
    //      std::ios_base::failure  // stream state is not good.
    auto columns() noexcept(false);


    // - Note :
    //      Tokenize the string with given delimiter
    // - Expected Input / Output
    //      >> "월5.0-6.5/13:00-15:00,수5.0-6.5/13:00-15:00"
    //      << "월5.0-6.5/13:00-15:00", "수5.0-6.5/13:00-15:00"
    std::vector<string>
        tokenize(string& _str, char _delim) noexcept;

    // - Note
    //      Get the [code] and [id]
    // - Expected Input
    //      PRI4402-09
    // - Return
    //      0 : string : Code
    //      1 : int    : ID
    // - Throws
    //      std::invalid_argument
    auto get_code_id(string& _str) noexcept(false);

    // - Note :
    //      Get the exact Day from korean character
    //      Parse the start/end time from the given string
    // - Expected input
    //      ex) 수5.0-6.5/13:00-15:00
    // - Return
    //      0 : WeekDay : day
    //      1 : int     : start time
    //      2 : int     : end time
    // - Throws
    //      std::invalid_argument
    auto get_time_info(string& _str) noexcept(false);

    // - Note :
    //      `std::stoi()` wrapper function
    //      change the given string to positive integer
    // - Expected input
    //      ["1", "2" ... ]
    // - Return
    //      std::stoi(_str)
    // - Throws
    //      std::invalid_argument
    auto get_point(std::string& _str) noexcept(false);

};



} // namespace project

#endif // INTERPRETER_H
