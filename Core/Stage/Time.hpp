// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Time.hpp
//  Updated  : 16/06/17
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      템플릿으로 만든 Time 클래스들.
//  Task
//      DateTime의 동작에 대한 명세가 불명확하고 Utility가 부족
// 
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _PROJ_TIME_HPP_
#define _PROJ_TIME_HPP_

namespace project
{
    // - Note
    //      특정한 날짜의 특정 시각을 표현하는 클래스.
    //      Date와 Clock을 가지며, Value Semantic을 따른다.
    template <class Date, class Clock>
    struct DateTime
    {
        using date_type  = Date;
        using clock_type = Clock;

        Date  date;
        Clock clock;

        explicit DateTime(Date _d, Clock _c) :
            date(_d), clock(_c)
        {}
    };

    // - Note
    //      DateTime의 비교를 위한 operator overload
    template<class D, class C>
    constexpr
        bool operator ==(const DateTime<D, C>& _lhs,
                         const DateTime<D, C>& _rhs)
        noexcept
    {
        return (_lhs.date == _rhs.date)
            && (_lhs.clock == _rhs.clock);
    }

    // - Note
    //      DateTime의 비교를 위한 operator overload
    template<class D, class C>
    constexpr
        bool operator  <(const DateTime<D, C>& _lhs,
                         const DateTime<D, C>& _rhs)
        noexcept
    {
        return (_lhs.date < _rhs.date)
            || ((_lhs.date == _rhs.date)
                && (_lhs.clock < _rhs.clock));
    }

    // - Note
    //      DateTime의 비교를 위한 operator overload
    template<class D, class C>
    constexpr
        bool operator <=(const DateTime<D, C>& _lhs,
                         const DateTime<D, C>& _rhs)
        noexcept
    {
        return (_lhs < _rhs) || (_lhs == _rhs);
    }


    // - Note
    //      특정 작업의 수행을 표현하기 위해 만든 클래스
    //      작업 수행의 시작, 끝, 시간을 반환하는
    //      start(), end(), length() 함수를 지원한다.
    //
    //      DateTime와 Duration을 가지며, 
    //      DateTime과 마찬가지로 Value Semantic을 따른다.
    template<class DateTime, class Duration>
    class TaskTime
    {
        DateTime st;
        Duration len;

    public:
        TaskTime(DateTime _start, Duration _dur) :
            st(_start), len(_dur)
        {}

        template <class Date, class Clock>
        TaskTime(Date _d, Clock _c,
                 Duration _dur) :
            st(_d, _c), len(_dur)
        {}

        // - Note
        //      Task의 수행일자(date)
        auto date() const noexcept 
        {
            return this->st.date;
        }

        // - Note
        //      Task의 시작(start)시간
        DateTime start() const noexcept 
        {
            return st;
        }

        // - Note
        //      Task의 종료(end)시간
        DateTime end() const noexcept 
        {
            auto res = st;
            res.clock += len;
            return res;
        }

        // - Note
        //      작업 시간(length).
        //      시작(start)과 끝(end)의 시간차
        Duration length() const noexcept 
        {
            return len;
        }
    };


    // - Note
    //      TaskTime 의 비교를 위한 operator overload
    template<class DTime, class Dur>
    constexpr
        bool operator <(const TaskTime<DTime, Dur>& _lhs,
                        const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs.start() < _rhs.start());
    }

    // - Note
    //      TaskTime 의 비교를 위한 operator overload
    template<class DTime, class Dur>
    constexpr
        bool operator ==(const TaskTime<DTime, Dur>& _lhs,
                         const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs.start() == _rhs.start())
            && (_lhs.length() == _rhs.length());
    }

    // - Note
    //      TaskTime 의 비교를 위한 operator overload
    template<class DTime, class Dur>
    constexpr
        bool operator <=(const TaskTime<DTime, Dur>& _lhs,
                         const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs < _rhs) || (_lhs == _rhs);
    }


    // - Note
    //      TaskTime은 시작시각과 끝시각을 가지고 있으므로,
    //      이를 기반으로 두 TaskTime이 표현하는 작업시간이
    //      서로 겹치는지 확인할 수 있다.
    template<class DateTime, class Dur>
    bool Collide(const TaskTime<DateTime, Dur>& _lhs,
                 const TaskTime<DateTime, Dur>& _rhs)
        noexcept
    {
        // Different date?
        // 서로 날짜가 다른가?
        if (_lhs.date() != _rhs.date()){
            return false;
        }
        // |L| <= |R| : 서로 시간이 겹치지 않음
        // |R| <= |L| : 서로 시간이 겹치지 않음
        if ((_lhs.end() <= _rhs.start())
            || (_rhs.end() <= _lhs.start())){
            return false;
        }
        // They must be colliding to each other
        else{
            return true;
        }
    }


}   // namespace project

#endif
