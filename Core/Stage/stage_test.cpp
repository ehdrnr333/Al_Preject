#include "./Time.hpp"
#include "./Plan.hpp"
#include "./Chain.h"
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
    WPlan A{ "A", 0 };
    A.add(WTask{ WDay::Mon, 10, 15 });
    A.add(WTask{ WDay::Wed, 10, 15 });

    WPlan B{ "B", 0 };
    B.add(WTask{ WDay::Mon, 10, 15 });

    WPlan C{ "C", 0 };
    C.add(WTask{ WDay::Mon, 20, 15 });
    C.add(WTask{ WDay::Wed, 20, 15 });

    WPlan D{ "D", 0};
    D.add(WTask{ WDay::Mon, 20, 20 });
    D.add(WTask{ WDay::Thu, 20, 20 });

    WPlan E{ "E", 0 };
    E.add(WTask{ WDay::Wed, 50, 25 });
    E.add(WTask{ WDay::Thu, 35, 15 });

    WPlan F{ "F", 0};
    F.add(WTask{ WDay::Mon, 70, 15 });


    std::vector<WPlan> res{ A,B,C,D,E,F };
    return res;
}


int planner(void) 
{
    // sample vector
    auto plans = make_sample();

    // Sort by first TaskTime
    std::sort(plans.begin(), plans.end(),
        [](const WPlan& _lhs, const WPlan& _rhs) -> bool
    {
        return _lhs[0].start() < _rhs[0].start();
    });

    // 좀 더 빠른 색인을 위한 IndexMap
    Map<WPlan::id_type, int> idxmap{};
    for (int i = 0; i < plans.size(); i++) {
        auto& plan = plans[i];
        idxmap[plan.planid()] = i;
    }

    // Meta data construction
    // 같은 ID를 가진 Plan의 경우는 이 단계에서 필터링해야 한다?
    // Q. 같은 ID를 사용해도 다른 시간일 경우 허용해야 할 수 있다.
    // 필터링을 좀 더 미뤄야 하지 않는가?
    Vec<PlanChain> chains{};
    for (auto& plan : plans) 
    {
        PlanChain ch{ plan };
        int idx = idxmap[plan.planid()];

        // Filter the vector from the given index
        ch.filter(plans, idx);
        chains.emplace_back(std::move(ch));
    }


    Deq<Vec<WPlan>> PrevQue;  // 이전 Stage 큐
    Deq<Vec<WPlan>> NextQue;  // 다음 Stage 큐 
    Deq<Vec<WPlan>> DoneQue;  // 완료 Stage 큐

    // Stage 0 : 최소 1개는 존재한다!
    for (auto& plan : plans) {
        Vec<WPlan> sched(1, plan);
        PrevQue.push_back(sched);
    }

    // 두 Stage Queue의 상태를 확인.
    //   Prev     : 비어있으면 모든 가능성 확인이 끝난 것이다.
    //   Post     : 비어있어야 한다. 
    //   두 Queue가 모두 비어 있다면, DoneQue으로 이동이 끝난 것이다.
    while (PrevQue.empty() == false
           && NextQue.empty() == true)
    {
        // Stage : chains를 참조하여 확장 시작
        while (PrevQue.empty() == false) {
            // TryPop()
            // 스케줄 하나를 가져온다.
            Vec<WPlan> sch = std::move(PrevQue.front());
            PrevQue.pop_front();

            // 스케줄의 가장 마지막 일정(Plan)을 확인
            const WPlan& last = sch.back();

            // 마지막 일정에 대한 정보를 Chains에서 획득
            // Chains에 대한 Read-Only Access
            // Chains는 모든 수업에 대한 Table이므로, 
            // index map에서 range를 보장해야 한다.
            auto idx = idxmap[last.planid()];


            // 다음에 올 수 있는 수업이 없다.
            if (chains[idx].next.empty() == true) {
                // 완료. 스케줄 큐에 삽입 후 루프 반복
                DoneQue.push_back(sch);
                continue;
            }
            // 다음에 올 수 있는 수업들로 새로운 스케줄 작성
            // another : next plan
            for (auto& another : chains[idx].next)
            {
                // 이 변수는 Atomic해야 하는가?
                bool flag{ false };

                // 새로 추가하는 수업이 기존의 수업들과 충돌하지는 않는가?
                // pin : in plan
                for (const WPlan& pin : sch) {
                    // 충돌할 경우 Flag를 set하고 break
                    if (Collide(pin, another) == true) {
                        flag = true;
                        break;
                    }
                }
                // 시간 충돌이 존재하면, 확장 불가능.
                // 필터해서 제거? / 넘긴다?
                if (flag == true) {
                    DoneQue.emplace_back(sch);
                    continue;
                }
                else {
                    // 충돌하지 않는다.
                    // 복사본을 만들고 확장해야 한다
                    auto new_sch = sch;
                    new_sch.emplace_back(another);

                    // 확장된 스케줄을 다음 큐에 삽입
                    NextQue.emplace_back(new_sch);
                }
            }
        }

        // 다음 단계로 진행하기 위한 Swap
        // 이 때 이전 단계 큐는 비어있다. 
        // Swap 이후엔 다음 단계 큐가 비어있으므로 재활용이 가능하다.
        std::swap(PrevQue, NextQue);
    }



    std::cout << PrevQue.size() << std::endl;
    std::cout << NextQue.size() << std::endl;
    std::cout << DoneQue.size() << std::endl;


    return std::system("pause");
}