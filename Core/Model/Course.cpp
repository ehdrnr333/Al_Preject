#include "./Course.h"

using namespace project;


Course::Course(string&& _code,
               int _id, int _point) noexcept(false):
    Plan(std::move(_code), _id), point(_point)
{
    auto&& check = _id | _point;
    if(check < 0){
        throw std::invalid_argument{
            "Course() : ID / Point must be positive. "
        };
    }
}

void Course::addTime(LecTime _lec) noexcept(false)
{
    this->times.emplace_back(std::move(_lec));
}

const Course::base_type::id_type& 
	Course::code() const 
	noexcept 
{
    return this->planid();
}

const Course::base_type::job_type& 
	Course::id() const 
	noexcept 
{
    return this->planjob();
}

size_t Course::count() const noexcept
{
    return this->times.size();
}

const LecTime& Course::operator[](size_t i)  const
    noexcept(false)
{
    return this->times.at(i);
}





std::ostream&
    project::operator << (std::ostream& _out,
                          const Course& _crs)
    noexcept(false)
{
    _out << "{ "
        << "\"code\" : \"" << _crs.code() << "\", "
        << "\"id\" : \"" << _crs.id() << "\", "
        << "\"point\" : \"" << _crs.point
        << "\"times \" : [";
    for(const auto& lec : _crs.times){
        _out << lec;
    }
    _out << "]\" }";

    return _out;
}

