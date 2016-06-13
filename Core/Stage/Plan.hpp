#ifndef _PROJ_PLAN_H_
#define _PROJ_PLAN_H_
#include "../Base.h"

namespace project
{
    // Plan
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    template <class ID, class Job, class Time>
    class Plan
    {
    public:
        using id_type   = ID;
        using job_type  = Job;
        using time_type = Time;

    private:
        id_type   p_id;
        job_type  p_job;
    public:
        Vec<Time> times;

        Plan(const ID& _id, const Job& _job) :
            p_id(_id), p_job(_job)
        {}

        const id_type&   planid() const noexcept 
        {
            return p_id;
        }
        
        const job_type&  planjob() const noexcept 
        {
            return p_job;
        }

        auto add(time_type _tm) noexcept(false){
            times.emplace_back(_tm);
        }

        time_type& operator[](int idx)
            noexcept(false)
        {
            return times.at(idx);
        }

        const time_type& operator[](int idx) const
            noexcept(false)
        {
            return times.at(idx);
        }
    
        auto begin() noexcept {
            return times.begin();
        }
        
        auto end() noexcept   {
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

