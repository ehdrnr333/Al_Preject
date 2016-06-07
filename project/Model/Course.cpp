#include "./Course.h"

using namespace project;


Course::Course(string&& _code,
               int _id, int _point) noexcept(false):
    crs_code(std::move(_code)),
    crs_id(_id), crs_point(_point)
{
    auto check = _id | _point;
    if(check < 0){
        throw std::invalid_argument{
            "Course ctor : argument must be positive"
        };
    }

}


const string& Course::code()  const  noexcept
{
    return this->crs_code;
}


int Course::id()  const  noexcept
{
    return this->crs_id;
}


int Course::point() const  noexcept
{
    return this->crs_point;
}


void Course::addTime(LecTime _lec) noexcept(false)
{
    this->crs_times.emplace_back(std::move(_lec));
}

const std::vector<LecTime>& Course::lectures() const noexcept
{
    return this->crs_times;
}



std::ostream&
    project::operator << (std::ostream& _out,
                          const Course& _crs)
    noexcept(false)
{
    _out << "{ "
        << "\"code\" : \"" << _crs.code() << "\", "
        << "\"id\" : \"" << _crs.id() << "\", "
        << "\"lectures\" : [";

    for(const auto& lec : _crs.lectures()){
        _out << lec;
    }
    _out << "], \"point\" : \"" << _crs.point()
         << "\" } ";
    return _out;
}

