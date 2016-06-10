
#include "./CourseInterpreter.h"

using namespace project;

using project::WeekDay;



CourseInterpreter::CourseInterpreter(std::istream& _in)
    noexcept(false):
    in(_in)
{

}



// - Note
//      Get the [code] and [id]
// - Expected Input
//      PRI4402-09
// - Return
//      0 : string : Code
//      1 : int    : ID
// - Throws
//      std::invalid_argument
auto CourseInterpreter::get_code_id(string& _str)
    noexcept(false)
{
    // Acquireing Code / ID
    auto pos = _str.find('-');
    if(pos == std::string::npos){
        throw std::invalid_argument{
            "get_code_id() : the argument is not expected format"
        };
    }

    std::string key = _str.substr(0, pos);

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
auto CourseInterpreter::get_time_info(string& _str)
    noexcept(false)
{
    // 0 : Acquire *Day* info
    // ---- ---- ---- ---- ---- ---- ---- ---- ----

    WeekDay day = WeekDay::Invalid;

    for(int idx = 0; idx < week_len; ++idx){
        // Compare string's first 3 byte character
        // with Korean character
        if(std::memcmp(_str.c_str(),
                       KorWeek[idx].c_str(),
                       3 == 0))
        {
            day = static_cast<WeekDay>(idx);
            break;
        }
    }
    // If not found, then the string is invalid.
    // Throw the exception.
    if(day == WeekDay::Invalid){
        throw std::invalid_argument{
            "get_time_info() : the argument is not expected format"
        };
    }


    // 1 : Acquire *Start* time info
    // ---- ---- ---- ---- ---- ---- ---- ---- ----

    // get the FIRST position of '.'
    // 3 skips the first utf-8 character
    auto pos = _str.find('.', 3);

    _str[pos] = _str[pos+1];    // "5.0" >> "500"
    _str[pos+1] = ' ';          // "500" >> "50 "

    // Now we changed "5.0" to "50"
    // Then convert the string to decimal integer
    auto start = std::atoi(&_str[pos-1]);


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
auto CourseInterpreter::get_point(std::string& _str)
    noexcept(false)
{
    if(std::isdigit(_str[0]) == false){
        throw std::invalid_argument{
            "get_score() : the argument is not a number"
        };
    }
    return std::stoi(_str);
}



auto CourseInterpreter::columns() noexcept(false)
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
        std::string msg = "Parsor Stream is not good";
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
Course CourseInterpreter::generate() noexcept(false)
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
            // Make lecture time object
            LecTime lec{std::move(info)};

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



std::vector<string>
    CourseInterpreter::tokenize(string& _str, char _delim) noexcept
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




