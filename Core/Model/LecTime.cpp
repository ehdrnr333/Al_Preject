#include "./LecTime.h"

using namespace project;

LecTime::LecTime(WeekDay _wday,
                 int _s, int _e) noexcept(false):
    TaskTime(_wday, _s, _e-_s)
{
}

WeekDay LecTime::day() const noexcept
{
    return this->base_type::date();
}





bool project::operator ==(const LecTime& _lhs,
                          const LecTime& _rhs)
    noexcept
{
    return _lhs.day() == _rhs.day()
        && _lhs.start() == _rhs.start()
        && _lhs.end()   == _rhs.end();
}

std::ostream&
    project::operator<<(std::ostream& _out,
                        const LecTime& _lec)
    noexcept(false)
{
    _out << "{ "
        << "\"day\" : \"" << _lec.date() << "\", "
        << "\"start\" : \"" << _lec.start().clock << "\", "
        << "\"end\" : \"" << _lec.end().clock << "\" } ";
    return _out;
}
