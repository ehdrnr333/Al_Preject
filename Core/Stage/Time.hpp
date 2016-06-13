#ifndef _PROJ_TIME_HPP_
#define _PROJ_TIME_HPP_

namespace project
{
    // Date Time
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class Date, class Clock>
    struct DateTime
    {
        using date_type = Date;
        using clock_type = Clock;

        Date  date;
        Clock clock;

        DateTime(Date _d, Clock _c) :
            date(_d), clock(_c)
        {}
    };

    template<class D, class C>
    constexpr
        bool operator ==(const DateTime<D, C>& _lhs,
                         const DateTime<D, C>& _rhs)
        noexcept
    {
        return (_lhs.date == _rhs.date)
            && (_lhs.clock == _rhs.clock);
    }

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

    template<class D, class C>
    constexpr
        bool operator <=(const DateTime<D, C>& _lhs,
                         const DateTime<D, C>& _rhs)
        noexcept
    {
        return (_lhs < _rhs) || (_lhs == _rhs);
    }


    // Task Time
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
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
        TaskTime(Date _d, Clock _c, Duration _dur) :
            st(_d, _c), len(_dur)
        {}

        auto date() const noexcept {
            return this->st.date;
        }

        DateTime start() const noexcept {
            return st;
        }

        DateTime end() const noexcept {
            auto res = st;
            res.clock += len;
            return res;
        }

        Duration length() const noexcept {
            return len;
        }
    };


    template<class DTime, class Dur>
    constexpr
        bool operator <(const TaskTime<DTime, Dur>& _lhs,
                        const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs.start() < _rhs.start());
    }


    template<class DTime, class Dur>
    constexpr
        bool operator ==(const TaskTime<DTime, Dur>& _lhs,
                         const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs.start() == _rhs.start())
            && (_lhs.length() == _rhs.length());
    }

    template<class DTime, class Dur>
    constexpr
        bool operator <=(const TaskTime<DTime, Dur>& _lhs,
                         const TaskTime<DTime, Dur>& _rhs)
        noexcept
    {
        return (_lhs < _rhs) || (_lhs == _rhs);
    }



    // Task Time Collision Check
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template<class DateTime, class Dur>
    bool Collide(const TaskTime<DateTime, Dur>& _lhs,
                 const TaskTime<DateTime, Dur>& _rhs)
        noexcept
    {
        // Different day?
        if (_lhs.date() != _rhs.date()){
            return false;
        }
        // |L| <= |R|
        if (_lhs.end() <= _rhs.start()){
            return false;
        }
        // |R| <= |L|
        else if (_rhs.end() <= _lhs.start()){
            return false;
        }
        // They are colliding
        else{
            return true;
        }
    };


}   // namespace project

#endif
