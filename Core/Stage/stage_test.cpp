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
    WPlan A{ "A", 0, WTask{ WDay::Mon, 10, 15 } };
    A.add(WTask{ WDay::Wed, 10, 15 });

    WPlan B{ "B", 0, WTask{ WDay::Mon, 10, 15 } };

    WPlan C{ "C", 0, WTask{ WDay::Mon, 20, 15 } };
    C.add(WTask{ WDay::Wed, 20, 15 });

    WPlan D{ "D", 0, WTask{ WDay::Mon, 20, 20 } };
    D.add(WTask{ WDay::Thu, 20, 20 });

    WPlan E{ "E", 0, WTask{ WDay::Wed, 50, 25 } };
    E.add(WTask{ WDay::Thu, 35, 15 });

    WPlan F{ "F", 0, WTask{ WDay::Mon, 70, 15 } };


    std::vector<WPlan> res{ A,B,C,D,E,F };
    return res;
}


int main(void) 
{
    // sample vector
    auto plans = make_sample();

    // Sort by first TaskTime
    std::sort(plans.begin(), plans.end(),
        [](const WPlan& _lhs, const WPlan& _rhs) -> bool
    {
        return _lhs[0].start() < _rhs[0].start();
    });

    // Meta data construction
    // 같은 ID를 가진 Plan의 경우는 이 단계에서 필터링한다.
    Vec<PlanChain> chains{};
    for (auto& plan : plans) {
        PlanChain ch{ plan };
        ch.filter(plans);
        chains.emplace_back(std::move(ch));
    }

    Deq<Vec<WPlan>> PreStage;   // 이전
    Deq<Vec<WPlan>> PostStage;  // 다음 
    Deq<Vec<WPlan>> Done;   // 완료

    // Stage 0 : 최소 1개는 존재한다!
    for (auto& plan : plans) {
        Vec<WPlan> sched(1, plan);
        PreStage.push_back(sched);
    }

    while (PreStage.empty() == false
        && PostStage.empty() == true)
    {
        // Stage 1 : chains를 참조하여 확장 시작
        while (PreStage.empty() == false) {
            // 스케줄 하나를 가져온다.
            // TryPop()
            Vec<WPlan> sch = std::move(PreStage.front());
            PreStage.pop_front();

            // 스케줄의 가장 마지막 일정(Plan)을 확인
            const WPlan& last = sch.back();

            // 마지막 일정에 대한 정보를 Chains에서 획득
            // Chains에 대한 Read-Only Access
            // Chains는 모든 수업에 대한 Table이므로, iter == end()일 가능성은 없다.
            // 이상적으로는 index를 사용해 직접 접근해야 함.
            auto iter = std::find_if(chains.cbegin(), chains.cend(),
                [&](const PlanChain& _chn)
            {
                return _chn.base == last;
            });

            // 다음에 올 수 있는 수업이 없다.
            if (iter->next.empty() == true) {
                // 완료 스케줄 큐에 삽입 후 루프 반복
                Done.push_back(sch);
                continue;
            }
            // 다음에 올 수 있는 수업들로 새로운 스케줄 작성
            // another : next plan
            for (auto& another : iter->next) 
            {
                bool flag{ false };

                // 새로 추가하는 수업이 기존의 수업들과 충돌하지는 않는가?
                // pin : in plan
                for (const WPlan& in : sch) {
                    // 충돌할 경우 Flag를 set하고 break
                    if (Collide(in, another) == true) {
                        flag = true;
                        break;
                    }
                }
                // 시간 충돌이 존재하면, 확장 불가능.
                // 필터해서 제거? / 넘긴다?
                if (flag == true) {
                    Done.push_back(sch);
                    continue;
                }
                else {
                    // 충돌하지 않는다.
                    // 복사본을 만들고 확장해야 한다
                    auto new_sch = sch;
                    new_sch.push_back(another);

                    // 확장된 스케줄을 큐에 삽입
                    PostStage.push_back(new_sch);
                }
            }
        }

        // 다음 단계로 진행하기 위한 Swap
        // 이 때 이전 단계 큐는 비어있다. 
        // Swap 이후엔 다음 단계 큐가 비어있으므로 재활용이 가능하다.
        std::swap(PreStage, PostStage);
    }



    std::cout << PreStage.size() << std::endl;
    std::cout << PostStage.size() << std::endl;


    return std::system("pause");
}