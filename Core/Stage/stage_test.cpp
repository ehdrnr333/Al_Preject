#include "WeeklyPlan.h"
#include "Chain.h"
using namespace project;

enum WDay {
    Sun = 0,
    Mon, Tue, Wed, Thu, Fri, Sat
};

using WDate = DateTime<WDay, int32_t>;
using WTask = TaskTime<WDate, int32_t>;

// Job Code
using WPlan = Plan<string, int, WTask>;

using PlanChain = Chain<WPlan>;

auto make_sample() 
{
    WPlan A{ "A", 0, WTask{ WDay::Mon, 10, 25 } };
    A.add(WTask{ WDay::Wed, 10, 25 });

    WPlan B{ "B", 0, WTask{ WDay::Mon, 10, 25 } };

    WPlan C{ "C", 0, WTask{ WDay::Mon, 20, 35 } };
    C.add(WTask{ WDay::Wed, 20, 35 });

    WPlan D{ "D", 0, WTask{ WDay::Mon, 20, 45 } };
    D.add(WTask{ WDay::Thu, 20, 40 });

    WPlan E{ "E", 0, WTask{ WDay::Wed, 50, 75 } };
    E.add(WTask{ WDay::Thu, 35, 50 });

    WPlan F{ "F", 0, WTask{ WDay::Mon, 70, 85 } };


    std::vector<WPlan> res{ A,B,C,D,E,F };
    return res;
}


void main(void) 
{
    // sample vector
    auto vec = make_sample();

    // Sort by first TaskTime
    std::sort(vec.begin(), vec.end(), 
        [](const WPlan& _lhs, const WPlan& _rhs) -> bool
    {
        return _lhs[0].start() < _rhs[0].start();
    });

    // Meta data construction
    Vec<PlanChain> meta;
    for (auto& plan : vec) {
        PlanChain tmp{ plan };
        tmp.filter(vec);
        meta.emplace_back(std::move(tmp));
    }




}