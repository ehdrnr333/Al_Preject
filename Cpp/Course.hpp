#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
namespace project
{
    // 날짜를 표현하는 클래스
    enum class Day : int {
        Sun = 0,
        Mon, Tue, Wed, Thu, Fri, Sat
    };

    std::array<std::string, 7> DayString = {
        "Sun",
        "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    std::ostream& operator<< (std::ostream& _out, 
                              const Day& _d) 
        noexcept(false)
    {
        return _out << DayString.at((int)_d) << std::flush;
    }

    // 하나의 강의 시간을 나타내는 클래스
    // Lecture Time Interface
    struct ILecTime
    {
        // 수업 요일
        // 일, 월, 화, 수, 목, 금, 토
        virtual Day day() const abstract;
        // 시작 시각:
        // ex) 9시 == 1교시
        virtual int start() const abstract;
        // 끝 시각 
        // ex) 10시 30분 == 2.5
        virtual int end() const abstract;

        // 수업시간 총 길이.
        // 30분 단위로 계산.
        // ex) 90분 수업의 반환값 == 3
        virtual int length() const abstract;
    };

    bool operator ==(const ILecTime& _lhs, 
                     const ILecTime& _rhs)
        noexcept
    {
        return _lhs.day() == _rhs.day()
            && _lhs.start() == _rhs.start()
            && _lhs.end() == _rhs.end();
    }

    std::ostream& operator<<(std::ostream& _out, 
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

    bool do_collide(const ILecTime& _lhs,
                    const ILecTime& _rhs)
    {
        // 1. 같은 날짜인가?
        return (_lhs.day() == _rhs.day())
            // 시작시간과 끝나는 시간을 사용한 비교.
            && (_lhs.start() <= _rhs.start())
            && (_rhs.start() < _lhs.end());
    }


    // 강의 인터페이스
    //   학수번호, 강의시간 목록, 학점, 가중치를 보유
    struct ICourse
    {
        // 학수번호
        virtual
            const std::string&  key()  const  abstract;

        // 강의시간 목록
        virtual 
        std::vector<ILecTime>&  times() const abstract;

        // 학점
        virtual int point() const  abstract;

    };

    std::ostream& operator << (std::ostream& _out, 
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


    // Test codes
    namespace test
    {

        // is ILectime printable?
        void ILecTime_print(const ILecTime& _lec) 
        {
            std::cout << _lec << std::endl;;
        }

        // is ICourese printable?
        void ICourse_print(const ICourse& _crs) 
        {
            std::cout << _crs;
        }

    }   // namespace test

} // namespace project