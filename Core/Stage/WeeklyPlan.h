#ifndef _WEEKLY_PLAN_H_
#define _WEEKLY_PLAN_H_
#include <string>
#include <vector>

namespace project
{
    // Date Time
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class Date, 
              class Clock>
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
        if (_lhs.date < _rhs.date) {    return true;    }
        if (_lhs.clock < _rhs.clock)   
            {   return true;  }
        else 
            {   return false; }
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
    template<class Date,
             class Clock, class Duration>
    class TaskTime 
    {
        DateTime<Date, Clock> st;
        Duration len;

    public:
        TaskTime(DateTime _start, Duration _dur):
            st(_start), len(_dur)
        {}

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


    // Task Time Collision Check
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template<class Date, class C, class Dur>
    constexpr 
        bool Collide(const TaskTime<Date, C, Dur>& _lhs,
                     const TaskTime<Date, C, Dur>& _rhs) 
        noexcept
    {
        // Different day?
        if (_lhs.st.date() != _rhs.st.date())
            {   return false;   }
        // |L| <= |R|
        if (_lhs.end() <= _rhs.start())
            {   return false;   }
        // |R| <= |L|
        else if (_rhs.end() <= _lhs.start())
            {   return false;   }
        // They are colliding
        else
            {   return true;    }
    }


    // Plan
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class ID, class Job, class Time>
    class Plan
    {
        static_assert(std::is_copy_assignable<Time>::type == false, "class Plan");
        static_assert(std::is_copy_constructible<Time>::type == false, "class Plan");

    public:
        const ID   id;
        const Job  job;
        std::vector<Time> times;


        Plan(const ID& _id, const Job& _job, 
             const Time _tm) :
            id(_id), job(_job)
        {
            times.emplace_back(_tm);
        }

        Time& operator[](int idx) 
            noexcept(false)
        {
            return times.at(idx);
        }

        const Time& operator[](int idx) const 
            noexcept(false)
        {
            return times.at(idx);
        }
    
        auto begin() noexcept {
            return times.begin();
        }
        auto end() noexcept{
            return times.end();
        }
        const auto begin() const noexcept {
            return times.cbegin();
        }
        const auto end() const noexcept {
            return times.cend();
        }
    };


    // Plan Collision Check
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class I, class J, class T>
    constexpr
        bool Collide(const Plan<I, J, T>& _lhs, 
                     const Plan<I, J, T>& _rhs) noexcept
    {
        for (const auto& ltm : _lhs) {
            for (const auto& rtm : _rhs) {
                if (Collide(ltm, rtm) == true) {
                    return true;
                }
            }
        }
        return false;
    }


}

#endif
