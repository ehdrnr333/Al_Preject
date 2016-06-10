#include "./LecTime.h"

using namespace project;


LecTime::LecTime(std::tuple<WeekDay,int,int>&& tup) noexcept:
    weekday(std::get<0>(tup)),
    start_tm(std::get<1>(tup)),
    end_tm(std::get<2>(tup))
{
    if(end_tm <= start_tm){
        throw std::invalid_argument{
            "LecTime : invalid time argument "
        };
    }
}



LecTime::LecTime(WeekDay _wday,
                 int _s, int _e) noexcept(false):
    weekday(_wday),
    start_tm(_s), end_tm(_e)
{
    if(end_tm <= start_tm){
        throw std::invalid_argument{
            "LecTime : invalid time argument "
        };
    }
}

WeekDay LecTime::day() const noexcept
{
    return this->weekday;
}

int LecTime::start() const noexcept
{
    return this->start_tm;
}

int LecTime::end() const noexcept
{
    return this->end_tm;
}

int LecTime::length() const noexcept
{
    return end_tm - start_tm;
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
        << "\"day\" : \"" << _lec.day() << "\", "
        << "\"start\" : \"" << _lec.start() << "\", "
        << "\"end\" : \"" << _lec.end() << "\" } ";
    return _out;
}

bool project::do_collide(const LecTime& _lhs,
                         const LecTime& _rhs) noexcept
{
    // Different day?
    if ( _lhs.day() != _rhs.day() )
        {   return false;   }
    // |L| <= |R|
    if ( _lhs.end() <= _rhs.start() )
        {   return false;   }
    // |R| <= |L|
    else if ( _rhs.end() <= _lhs.start() )
        {   return false;   }
    // They are colliding
    else
        {   return true;    }
}

