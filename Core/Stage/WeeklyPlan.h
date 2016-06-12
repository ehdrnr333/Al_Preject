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
        Date  date;
        Clock clock;

        DateTime(Date _d, Clock _c) :
            date(_d), clock(_c)
        {}

        DateTime(const DateTime&) = default;
        DateTime(DateTime&&)      = default;
        DateTime& operator = (const DateTime&) = default;
        DateTime& operator = (DateTime&&)      = default;
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
        TaskTime(DateTime _start, Duration _dur):
            st(_start), len(_dur)
        {}
        template <class Date, class Clock>
        TaskTime(Date _d, Clock _c, Duration _dur) :
            st(_d, _c), len(_dur)
        {}

        TaskTime(const TaskTime&) = default;
        TaskTime(TaskTime&&)      = default;
        TaskTime& operator = (const TaskTime&) = default;
        TaskTime& operator = (TaskTime&&)      = default;

        auto date() const noexcept {
            return st.date;
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
        if (_lhs.date() != _rhs.date())
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
        ID  p_id;
        Job p_job;
    public:
        std::vector<Time> times;


        Plan(const ID& _id, const Job& _job, 
             const Time _tm) :
            p_id(_id), p_job(_job)
        {
            times.emplace_back(_tm);
        }

        Plan(const Plan& _p) = default;
        Plan(Plan&& _p) = default;

        Plan& operator =(const Plan& _p) = default;
        Plan& operator =(Plan&& _p) noexcept = default;


        const ID&   id() const noexcept {
            return p_id;
        }
        const Job&  job() const noexcept {
            return p_job;
        }


        auto add(Time _tm) noexcept(false){
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

    template <class I, class J, class T>
    constexpr 
        bool operator ==(const Plan<I, J, T>& _lhs,
            const Plan<I, J, T>& _rhs) noexcept
    {
        return (_lhs.id() == _rhs.id())
            && (_lhs.job() == _rhs.job())
            && (_lhs.times == _rhs.times);
    }


    // Plan Collision Check
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class I, class J, class T>
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

