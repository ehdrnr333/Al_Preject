#include "./Day.h"

using namespace project;



std::ostream&
    project::operator<< (std::ostream& _out,
                         const WeekDay _day)
    noexcept(false)
{
    return _out << EngWeek[int_cast(_day)];
}
