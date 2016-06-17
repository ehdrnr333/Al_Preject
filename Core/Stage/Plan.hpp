// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Plan.hpp
//  Updated  : 16/06/17
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Plan은 여러 횟수로 나뉘어저 특정 업무를 수행하는 '일정'을 
//      표현한 클래스이다. 
//      각 일정은 식별이 가능해야 하므로 ID를 지니며, 
//      해당 Plan에서 수행할 Job, 
//      수행시간을 위한 Time을 인자로 사용한다. 
//      이때 수행시간은 1개 이상으로, STL 컨테이너를 사용한다.
//
//      Time에 대해서는 Value Semantic을 따른다. 
// 
//  Task
//      타당한 타입 설계인지 확인이 필요. 
//      필요하다면 std::tuple<>로 구조를 변경하는 것도 가능.
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _PROJ_PLAN_H_
#define _PROJ_PLAN_H_
#include "../Base.h"

namespace project
{

    // - Note
    //      Plan : 일정
    //      ID   : 각 일정의 식별
    //      Job  : 수행할 Job을 표현하는 타입 
    //      Time : 수행시간
    // - Example
    //      Plan<ID, Job, Time> plan;
    template <class ID, class Job, class Time>
    class Plan
    {
    public:
        using id_type   = ID;
        using job_type  = Job;
        using time_type = Time;

    private:
        id_type   p_id;     // 각 Plan을 식별하는 ID
        job_type  p_job;    // 각 Plan에 할당된 Job
    public:
        Vec<Time> times;    // Plan을 수행하는 Time 컨테이너

        Plan(const ID& _id, const Job& _job) :
            p_id(_id), p_job(_job)
        {}

        // - Note
        //      Plan의 ID에 대한 참조
        const id_type&   planid() const noexcept 
        {
            return p_id;
        }

        // - Note
        //      Plan의 Job에 대한 참조
        const job_type&  planjob() const noexcept 
        {
            return p_job;
        }

        // - Note
        //      Plan에 시간을 추가한다. 별도의 조작이 없는 
        //      단순한 append처리
        auto add(time_type _tm) noexcept(false)
        {
            times.emplace_back(_tm);
        }

        // - Note
        //      index접근을 지원하는 operator[] overload
        time_type& operator[](int idx)
            noexcept(false)
        {
            return times.at(idx);
        }

        // - Note
        //      index접근을 지원하는 operator[] overload
        const time_type& operator[](int idx) const
            noexcept(false)
        {
            return times.at(idx);
        }

        // - Note
        //      Plan의 시간은 STL Container를 사용하므로
        //      iterator를 사용할 수 있도록 지원한다.
        auto begin() noexcept { return times.begin(); }

        // - Note
        //      Plan의 시간은 STL Container를 사용하므로
        //      iterator를 사용할 수 있도록 지원한다.
        auto end() noexcept { return times.end(); }

        // - Note
        //      Plan의 시간은 STL Container를 사용하므로
        //      iterator를 사용할 수 있도록 지원한다.
        const auto begin() const noexcept  { return times.begin(); }

        // - Note
        //      Plan의 시간은 STL Container를 사용하므로
        //      iterator를 사용할 수 있도록 지원한다.
        const auto end() const noexcept  { return times.end(); }

    };

    // - Note
    //      Plan간의 비교를 위한 operator==() 정의
    // - Complexity
    //      O(1) ~ O(n) : n은 두 Plan의 Time 개수 중 작은값.
    template <class I, class J, class T>
    constexpr 
        bool operator ==(const Plan<I, J, T>& _lhs,
                         const Plan<I, J, T>& _rhs) noexcept
    {
        return (_lhs.id() == _rhs.id())
                && (_lhs.job() == _rhs.job())
                && (_lhs.times == _rhs.times);
    }

    // - Note
    //      Plan은 Job에 대한 다수의 Time을 가지므로, 
    //      서로 Time이 충돌할 수 있다. 
    //      2중 for문을 사용해 서로 시간이 겹치는지 검사한다.
    // - Complexity
    //      O(n * m) : n, m 은 각 Plan의 Time 수
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

