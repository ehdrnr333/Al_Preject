#include "./Base.h"

using namespace project;

// - Note
//      Skip the left overs
// - Example
//      cin >> skip_line ;
std::istream& project::skip_line(std::istream& _in)
    noexcept(false)
{
    _in.ignore(std::numeric_limits<std::streamsize>::max(),
               '\n');
    return _in;
}
