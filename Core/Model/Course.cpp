#include "./Course.h"

using namespace project;


Course::Course(string&& _code,
               int _id, int _point) noexcept(false):
    code(std::move(_code)),
    id(_id), point(_point)
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
    this->v_time.emplace_back(std::move(_lec));
}

size_t Course::count() const noexcept
{
    return this->v_time.size();
}

const Vec<LecTime>& Course::times() const noexcept
{
    return this->v_time;
}

const LecTime& Course::operator[](int i)  const
    noexcept(false)
{
    return this->v_time.at(i);
}





std::ostream&
    project::operator << (std::ostream& _out,
                          const Course& _crs)
    noexcept(false)
{
    _out << "{ "
        << "\"code\" : \"" << _crs.code << "\", "
        << "\"id\" : \"" << _crs.id << "\", "
        << "\"point\" : \"" << _crs.point
        << "\"times \" : [";
    for(const auto& lec : _crs.times()){
        _out << lec;
    }
    _out << "]\" }";

    return _out;
}

