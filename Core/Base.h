// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Base.h
//  Updated  : 16/06/04
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Collection of project's base headers
//
//  Task
//      Dependency summary is required
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef BASE_H
#define BASE_H

// Standard C++ Library
#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <sstream>

#include <memory>
#include <typeinfo>
#include <type_traits>

#include <algorithm>
#include <iterator>

#include <array>
#include <vector>
#include <deque>
#include <map>

#include <exception>
#include <stdexcept>
#include <system_error>

// C Library
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

// Qt Framework ( 5.6.0 )



// Project Definitions
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

namespace project
{

    template <class T>
    constexpr std::int32_t int_cast(T&& _obj){
        return static_cast<std::int32_t>(_obj);
    }

    // - Note
    //      Aliasing for standard basic 'char' string
    using string = std::string;

    // - Note
    //      Short notation for unique_ptr
    template <typename T>
    using uptr = std::unique_ptr<T>;

    // - Note
    //      Short notation for shared_ptr
    template <typename T>
    using sptr = std::shared_ptr<T>;



    // Utilities
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    // - Note
    //      Skip the given words
    // - Example
    //      cin >> skip_tab<3> >> buffer;
    template <int hop>
    std::istream& skip_tab(std::istream& _in)
        noexcept(false)
    {
        static_assert(hop > 0, "Skip hop should be larger than 0");

        std::string buf;

        for(int i = 0; i< hop; ++i){
            std::getline(_in, buf, '\t');
        }

        return _in;
    }

    // - Note
    //      Skip the left overs
    // - Example
    //      cin >> skip_line ;
    std::istream& skip_line(std::istream& _in) noexcept(false);


    template <std::ostream& out, class T>
    void WriteLine(std::string&& _label, const T& obj)
        noexcept(false)
    {
        out << _label << obj << '\n';
    }

    template <std::ostream& out, class T>
    void WriteLine(std::string&& _label, T&& obj)
        noexcept(false)
    {
        out << _label << obj << '\n';
    }



    template <std::ostream& out, class T>
    void WriteLine(const T& obj)
        noexcept(false)
    {
        out << obj << '\n';
    }

    template <std::ostream& out, class T>
    void WriteLine(T&& obj)
        noexcept(false)
    {
        out << obj << '\n';
    }



} // namespace project

#endif // BASE_H
