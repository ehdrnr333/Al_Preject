#include "./Course.hpp"

using namespace project;

std::ostream& project::operator<< (std::ostream& _out,
	const Day& _d)
	noexcept(false)
{
	return _out << DayString.at((int)_d) << std::flush;
}

bool project::operator ==(const ILecTime& _lhs,
	const ILecTime& _rhs)
	noexcept
{
	return _lhs.day() == _rhs.day()
		&& _lhs.start() == _rhs.start()
		&& _lhs.end() == _rhs.end();
}

std::ostream& project::operator<<(std::ostream& _out,
	const ILecTime& _lec)
	noexcept(false)
{
	_out << " ILecTime : { "
		<< " day   : " << _lec.day()
		<< " start : " << _lec.start()
		<< " end   : " << _lec.end()
		<< " time  : " << _lec.length() << " } ";
	return _out;
}

bool project::do_collide(const ILecTime& _lhs,
	const ILecTime& _rhs) noexcept
{
	// 1. 같은 날짜인가?
	return (_lhs.day() == _rhs.day())
		// 시작시간과 끝나는 시간을 사용한 비교.
		&& (_lhs.start() <= _rhs.start())
		&& (_rhs.start() < _lhs.end());
}


std::ostream& project::operator << (std::ostream& _out,
	const ICourse& _crs)
	noexcept(false)
{
	_out << " ICourse : { "
		<< " key   : " << _crs.key()
		<< " point : " << _crs.point();
	for (auto& time : _crs.times()) {
		_out << time;
	}
	_out << " } ";
	return _out;
}
