// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
//#include "../Model.h"
#include "../Stage.h"

using namespace project;

using project::Course;

// - Note
//      Course List를 기반으로 Chain의 목록을 만든다
// - Expected Input
//      CrsList : 임의의 기준으로 정렬된 Course의 리스트
Vec<CrsChain> project::MakeChains(const Vec<project::Course>& CrsList)
{
    // 반환을 위한 Chains
    Vec<CrsChain> chains{}; 

    // index loop
    for (size_t idx = 0; idx < CrsList.size(); ++idx){
        // This chain start with the 'idx'
        CrsChain tmp{ (int)idx };

        // For next courses...
        for (size_t j = idx + 1; j < CrsList.size(); ++j) {
            // Time collision
            // && Same code
            if ((Collide(CrsList[idx], CrsList[j]) == true)
                && (CrsList[idx].code() == CrsList[j].code()))
            {
                continue;
            }
            // if both course don't collide, insert to chain
            tmp.append(j);
        }

        // move the chain to chain vector('chains')
        chains.emplace_back(std::move(tmp));
    }
    return chains;
}


// - Note
//      Stage 알고리즘의 구현
// 
//      The algorithm starts with sorted CourseList
//      course를 Template argument로 사용하였을 경우
//      공간 비용이 큰 점을 고려하여
//      CrsList를 기준으로 한 index방식을 사용하였다.
Deq<CrsSchedule> 
    project::stage_schedule(Vec<Course>& _CrsList, const int max_stage,
                            std::function<bool(const Deq<int>&)> filter)
{

    // 1. 모든 Course들을
    //    첫번째(0) 수업시간(LecTime)을 기준으로 정렬한다.
    std::sort(_CrsList.begin(), _CrsList.end(),
        [](const Course& _lhs, const Course& _rhs) -> bool
    {
        return _lhs[0].start() < _rhs[0].start();
    });

    // 2. Build Chains
    //
    //    In the case, CrsChain represents...
    //      base : specific course
    //      next : every course which can be placed after 'base' course.
    Vec<CrsChain> chains = MakeChains(_CrsList);


    // 이전 Stage 큐. CrsList의 Index 기반
    // 다음 Stage 큐. CrsList의 Index 기반
    Deq<Deq<int>> PrevQue, NextQue;
    // 완료 Stage 큐
    Deq<CrsSchedule> DoneQue;

    // Stage Counter
    int stage{ 1 };

    // 3. 최초 강좌(Course)의 index를 삽입.
    //    ex) idx == 1 은 plans[1]에 해당하는 course를 의미한다.
    for (size_t idx = 0; idx < _CrsList.size(); idx++) {
        Deq<int> sched{};
        sched.emplace_back(idx);
        PrevQue.emplace_back(std::move(sched));
    }

    // 두 Stage Queue의 상태를 확인.
    //   Prev     : 새로운 스케줄의 가능성(일정의 조합)이 존재한다
    //   Post     : 단일 Stage 결과가 삽입되는 Que
    // 
    // 두 Queue가 모두 비어 있다면, 더이상 Staging을 하지 않는다.
    while (PrevQue.empty() == false && NextQue.empty() == true)
    {
        // Stage : chains를 참조하여 확장 시작
        while (PrevQue.empty() == false)
        {
            // 스케줄 하나를 가져온다.
            auto schedule = std::move(PrevQue.front());
            PrevQue.pop_front();

            // 스케줄의 가장 마지막 일정의 index 확인
            const auto idx = schedule.back();

            // Chains[i]는 CrsList[i] 이후에 
            // 추가할 수 있는 수업들의 목록이다. 
            // Chain 템플릿을 사용하였으므로, 
            // next를 검사해 추가 수업의 여부를 확인할 수 있다.
            if (chains[idx].next.empty() == true) {

                // 다음에 올 수 있는 수업이 없다.
                //  조건에 부합할 경우(max 도달)
                //  DoneQue에 삽입한다.
                if (filter(schedule) == true) {
                    CrsSchedule sch{};
                    for (int i : schedule) {
                        sch.append(_CrsList[i]);
                    }
                    DoneQue.emplace_back(std::move(sch));
                }
                continue;
            }

            // 다음에 올 수 있는 수업들로 새로운 스케줄 작성
            // anthr(another) : 추가할 새로운 수업(Course)
            for (const int anthr : chains[idx].next) {
                std::atomic<bool> flag{ false };

                // index 접근하여 
                // 기존의 수업들과 Collision 비교
                for (const int i : schedule) {
                    // 충돌할 경우 Flag를 set하고 break
                    if ((Collide(_CrsList[i], _CrsList[anthr]) == true)
                        || (_CrsList[i].code() == _CrsList[anthr].code()))
                    {
                        flag.store(true);
                        break;
                    }
                }

                // 시간 충돌이 존재하면, 확장 불가능.
                if (flag.load()) { continue; }

                // 충돌하지 않는다면
                // 복사본을 만들고 확장해야 한다

                // 복사본 생성
                // new_sch = schedule.clone();
                auto new_sch = schedule;
                // 충돌 검사가 끝난 another Course를 삽입
                new_sch.emplace_back(anthr);

                // 확장된 스케줄을 다음 큐에 삽입
                NextQue.emplace_back(std::move(new_sch));
            }

        } //  while (PrevQue.empty() == false)

        //std::cout << "Stage : " << stage << std::endl;
        //std::cout << "Prev : " << PrevQue.size() << std::endl;
        //std::cout << "Next : " << NextQue.size() << std::endl;
        //std::cout << "Done : " << DoneQue.size() << std::endl
        //    << std::endl;

        stage += 1;

        // 일정 Stage를 넘어가면 중지한다.
        if (max_stage < stage) {    break;  }

        // 다음 단계로 진행하기 위한 Swap
        // 이 때 이전(Prev) 단계 큐는 비어있다.
        // Swap 이후엔 다음(Post) 단계 큐가 비어있으므로 재활용이 가능하다.
        std::swap(PrevQue, NextQue);
        
    }
    // 최종 결과를 반환
    return DoneQue;
}
