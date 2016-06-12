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
    template <class Course>
    class Interpreter
    {
    private: // ---- ---- Variable ---- ----
        std::istream& in;


    public:  // ---- ---- Default ---- ----

        explicit Interpreter(std::istream& _in) noexcept(false) :
            in(_in)
        {}

        // - Note
        //      Generate the Course object from the stream
        // - Throws
        //      std::ios_base::failure  // stream state is bad.
        //      std::invalid_argument   // invalid value
        auto generate() noexcept(false);


    private:

        // - Note
        //      Fetch specific columns from the stream
        //      The column delimiter is '\t'
        // - Throws
        //      std::ios_base::failure  // stream state is not good.
        auto columns() noexcept(false);


        // - Note
        //      Get the [code] and [id]
        // - Throws
        //      std::invalid_argument
        auto get_code_id(string& _str) noexcept(false);

        // - Note :
        //      Get the exact Day from korean character
        //      Parse the start/end time from the given string
        // - Throws
        //      std::invalid_argument
        auto get_time_info(string& _str) noexcept(false);

        // - Note :
        //      `std::stoi()` wrapper function
        //      change the given string to positive integer
        // - Throws
        //      std::invalid_argument
        auto get_point(string& _str) noexcept(false);

        // - Note :
        //      Tokenize the string with given delimiter
        std::vector<string>
            tokenize(string& _str, const char _delim) noexcept;

    };

    // Interpreter Function Definitions
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    // - Note
    //      Get the [code] and [id]
    // - Expected Input
    //      PRI4402-09
    // - Return
    //      0 : string : Code
    //      1 : int    : ID
    // - Throws
    //      std::invalid_argument
    template <class Course>
    auto Interpreter<Course>::get_code_id(string& _str)
        noexcept(false)
    {
        // Acquireing Code / ID
        auto pos = _str.find('-');
        if(pos == string::npos){
            throw std::invalid_argument{
                "get_code_id() : the argument is not expected format"
            };
        }

        string key = _str.substr(0, pos);

        auto id = std::atoi(_str.c_str() + pos + 1);


        return std::make_tuple(std::move(key), id);
    }


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
    template <class Course>
    auto Interpreter<Course>::get_time_info(string& _str)
        noexcept(false)
    {
        // 0 : Acquire *Day* info
        // ---- ---- ---- ---- ---- ---- ---- ---- ----

        project::WeekDay day = project::WeekDay::Invalid;

        for(int idx = 0; idx < week; ++idx){
            // Compare string's first 3 byte character
            // with Korean character
            if(std::memcmp(_str.c_str(),
                           KorWeek[idx].c_str(),
                           3) == 0)
            {
                day = static_cast<project::WeekDay>(idx);
                break;
            }
        }
        // If not found, then the string is invalid.
        // Throw the exception.
        if(day == project::WeekDay::Invalid){
            throw std::invalid_argument{
                "get_time_info() : the argument is not expected format"
            };
        }


        // 1 : Acquire *Start* time info
        // ---- ---- ---- ---- ---- ---- ---- ---- ----

        // get the FIRST position of '.'
        // 3 skips the first utf-8 character
        auto pos = _str.find('.', 3);

        _str[pos] = _str[pos+1];    // "10.0" >> "1000"
        _str[pos+1] = ' ';          // "1000" >> "100 "

        // Now we changed "10.0" to "100 "
        // Then convert the string to decimal integer
        int start = 0;
        if(std::isdigit(_str[pos-2])){
            start = std::atoi(&_str[pos-2]);
        }
        else{
            start = std::atoi(&_str[pos-1]);
        }


        // 2 : Acquire *End* time info
        // ---- ---- ---- ---- ---- ---- ---- ---- ----

        // get the SECOND position of '.'
        // 3 skips the first utf-8 character
        pos = _str.find('.', 3);

        _str[pos] = _str[pos+1];    // "10.5" >> "1055"
        _str[pos+1] = ' ';          // "1055" >> "105 "

        pos = _str.find('-', pos-3);    // divider between start and end
        auto end = std::atoi(&_str[pos+1]);

        return std::make_tuple(day, start, end);
    }


    // - Note :
    //      `std::stoi()` wrapper function
    //      change the given string to positive integer
    // - Expected input
    //      ["1", "2" ... ]
    // - Return
    //      std::stoi(_str)
    // - Throws
    //      std::invalid_argument
    template <class Course>
    auto Interpreter<Course>::get_point(string& _str)
        noexcept(false)
    {
        if(std::isdigit(_str[0]) == false){
            throw std::invalid_argument{
                "get_score() : the argument is not a number"
            };
        }
        return std::stoi(_str);
    }



    template <class Course>
    auto Interpreter<Course>::columns() noexcept(false)
    {
        string code, time, pt_str;
        // Fetch columns from the csv stream
        // ---- ---- ---- ---- ---- ----

        if(in){
            in >> skip_tab<3> >> code;     // Get the [Code + id]
            in >> skip_tab<4> >> time;     // Get the [Time]
            in >> skip_tab<2> >> pt_str;   // Get the [Point]

            in >> skip_line; // Skip the line
        }
        else{
            string msg = "Parsor Stream is not good";
            throw std::ios_base::failure{msg};
        }

        return std::make_tuple(std::move(code),
                               std::move(time),
                               std::move(pt_str));
    }

    // - Note
    //      Generate the Course object from the stream
    // - Throws
    //      std::exception         // eof reached
    //      std::invalid_argument  // fail from invalid value
    template <class Course>
    auto Interpreter<Course>::generate() noexcept(false)
    {

        // Selected columns
        auto cols = this->columns();

        // Parse the arguments
        // ---- ---- ---- ---- ---- ----

        auto& code_str = std::get<0>(cols);
        auto& tm_str   = std::get<1>(cols);
        auto& pt_str   = std::get<2>(cols);

        auto pkey  = get_code_id(code_str);
        auto times = tokenize(tm_str, ',');
        auto point = get_point(pt_str);

        auto code = std::move(std::get<0>(pkey));
        auto id   = std::get<1>(pkey);


        // Make Course object
        // ---- ---- ---- ---- ---- ----

        Course crs(std::move(code), id, point);

        // Create lectures
        try{
            for(auto& tm : times){
                // Parse time information
                auto&& info = get_time_info(tm);

                auto&& d = std::get<0>(info);
                auto&& s = std::get<1>(info);
                auto&& e = std::get<2>(info);

                // Make lecture time object
                LecTime lec(d, s, e);

                // insert the object
                crs.addTime(lec);
            }

        }
        catch(std::invalid_argument& invalid){
            // lecture creation failed.
            // throw the related information
            std::ostringstream sout{};

            sout << "generate() : " << invalid.what() << " : " << code_str;

            throw std::invalid_argument{sout.str()};
        }

        return crs;
    }


    template <class Course>
    std::vector<string>
        Interpreter<Course>::tokenize(string& _str,
                                      const char _delim) noexcept
    {
        // token vector
        std::vector<string> tokens{};

        // Find the position of delimitor
        auto pos = _str.find(_delim);

        // Until there are no more delims...
        while(pos != string::npos){
            // Copy the token and insert it into vector
            tokens.emplace_back(std::move(_str.substr(0, pos)));
            // Erase from the part
            _str.erase(0, pos+1);
            // Find delim again
            pos = _str.find(',');
        }
        // Push back the last token
        tokens.emplace_back(std::move(_str));

        // Return the vector
        return tokens;
    }





} // namespace project

#endif // INTERPRETER_H
