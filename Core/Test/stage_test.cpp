#include "./Model/Interpreter.hpp"
#include "./Model/CrsTable.hpp"
#include "./Stage/Chain.h"
#include "./Stage/Plan.hpp"
#include "./Stage/Schedule.h"

#include <functional>
using namespace std;
using namespace project;

using CrsChain = Chain<int>;

static std::string Key(const Course& crs)
{
    std::ostringstream sout;
    sout << crs.code() << '-' << crs.id();
    return sout.str();
}


Vec<CrsChain> MakeChains(const Vec<Course>& CrsList)
{
    Vec<CrsChain> chains{};
    // For all course..
    //      - CrsChain uses index.
    for(size_t idx = 0; idx < CrsList.size(); ++idx)
    {
        // This chain start with 'idx'
        CrsChain tmp{(int)idx};

        // For next courses...
        for(size_t j = idx + 1; j < CrsList.size(); ++j){
            // if both course don't collide, insert to chain
            if(Collide(CrsList[idx], CrsList[j]) == false){
                tmp.append(j);
            }
        }
        // move the chain to chain vector('chains')
        chains.emplace_back(std::move(tmp));
    }
    return chains;
}


//      course를 Template argument로 사용하였을 경우
//      공간 비용이 지나치게 큰 점을 고려하여
//      CrsList를 기준으로 한 index방식을 사용하였다.
Deq<Vec<int>> stage_loop(Vec<Course>& CrsList,
                         std::function<void(void)> pred)
{

    // Sort by first TaskTime
    std::sort(CrsList.begin(), CrsList.end(),
        [](const Course& _lhs, const Course& _rhs) -> bool
    {
        return _lhs[0].start() < _rhs[0].start();
    });

    std::cout << "Sort Done : "<< CrsList.size() << std::endl;



    // 좀 더 빠른 색인을 위한 IndexMap
    //Map<Course::code_type, int> idxmap = MakeIndexMap(CrsList);
    //std::cout << "Index Mapping done" << std::endl;

    // Meta data construction
    Vec<CrsChain> chains = MakeChains(CrsList);
    std::cout << "Chain Construction done" << std::endl;


    // 이전 Stage 큐. CrsList의 Index 기반
    // 다음 Stage 큐. CrsList의 Index 기반
    // 완료 Stage 큐. CrsList의 Index 기반
    Deq<Vec<int>> PrevQue, NextQue, DoneQue;

    // Stage 0 :
    //      최초 강좌(Course)의 index를 삽입.
    //      idx == 1 은 plans[1]에 해당하는 course를 의미한다.
    for (size_t idx = 0; idx < CrsList.size(); idx++) {
        Vec<int> sched{};
        sched.emplace_back(idx);
        PrevQue.emplace_back(std::move(sched));
    }

    int stage{ 0 };
    // 두 Stage Queue의 상태를 확인.
    //   Prev     : 비어있으면 모든 가능성 확인이 끝난 것이다.
    //   Post     : 비어있어야 한다.
    //   두 Queue가 모두 비어 있다면, DoneQue으로 이동이 끝난 것이다.
    while (PrevQue.empty() == false
            && NextQue.empty() == true)
    {
        // Stage : chains를 참조하여 확장 시작
        while (PrevQue.empty() == false) {
            // 스케줄 하나를 가져온다.
            auto schedule = std::move(PrevQue.front());
            PrevQue.pop_front();

            // 스케줄의 가장 마지막 일정의 index
            const auto& idx = schedule.back();

            // 다음에 올 수 있는 수업이 없다.
            if (chains[idx].next.empty() == true) {
                // ==== ==== ==== ==== ====
                // 완료 큐에 삽입 후 루프 반복
                pred();
                if(schedule.size() == 5){
                    DoneQue.emplace_back(std::move(schedule));
                }
                continue;
            }

            // 다음에 올 수 있는 수업들로 새로운 스케줄 작성
            // anthr(another) : next course's index
            for (const int anthr : chains[idx].next){
                // 이 변수는 Atomic해야 하는가?
                bool flag{ false };

                // 새로 추가하는 수업이 기존의 수업들과 충돌하지는 않는가?
                // pin : plan's index
                for (const int pin : schedule){
                    // 충돌할 경우 Flag를 set하고 break
                    if (Collide(CrsList[pin], CrsList[anthr]) == true){
                        flag = true;
                        break;
                    }
                }

                // 시간 충돌이 존재하면, 확장 불가능.
                // 필터해서 제거? / 넘긴다?
                if (flag == true) {

                    // ==== ==== ==== ==== ====
                    pred();
                    if(schedule.size() == 5){
                        DoneQue.emplace_back(std::move(schedule));
                    }
                    continue;
                }
                else {
                    // 충돌하지 않는다.
                    // 복사본을 만들고 확장해야 한다
                    // new_sch = schedule.clone();
                    auto new_sch = schedule;
                    new_sch.emplace_back(anthr);

                    // 확장된 스케줄을 다음 큐에 삽입
                    NextQue.emplace_back(std::move(new_sch));
                }
            }
        }

        std::cout << "Stage : " << stage << std::endl;
        std::cout << "Prev : " << PrevQue.size() << std::endl;
        std::cout << "Next : " << NextQue.size() << std::endl;
        std::cout << "Done : " << DoneQue.size() << std::endl
                  << std::endl;
        stage += 1;

        if(stage > 6){
            break;
        }
        // 다음 단계로 진행하기 위한 Swap
        // 이 때 이전 단계 큐는 비어있다.
        // Swap 이후엔 다음 단계 큐가 비어있으므로 재활용이 가능하다.
        std::swap(PrevQue, NextQue);
    }


    return DoneQue;
}


// - Note :
//      Staging algorithm
int stage_test(const std::string _ipath,
               const std::string _opath)
{
    // 0. Open the CSV file
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    std::ifstream fin{_ipath,
                      std::ios_base::in};

    // 1. Interpret the file into Course vector
    //      >> 'EveryCourse'
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    // Skip the first line (CSV headings)
    fin >> skip_line;

    Interpreter<Course> IL{fin};  // Interpreter for Course
    Vec<Course> EveryCourse;      // Course vector
    EveryCourse.reserve(2000);

    // Until the stream is good, keep going
    while (fin) {
        try {
            // Generate the course and append it to table
            auto crs = IL.generate();
            EveryCourse.emplace_back(std::move(crs));
        }
        // If generate() throws,
        // ignore and go back to loop
        catch (std::invalid_argument& invalid) {
            std::cerr << invalid.what() << std::endl;
        }
    }


    auto verify = [](void)->void{};

    auto DoneQue = stage_loop(EveryCourse, verify);


    std::cout << "Staging Done!" << std::endl;


    std::ofstream fout{_opath, ios_base::out | ios_base::trunc};

    for (auto& que : DoneQue) {
        fout << "====================" << std::endl;
        fout << que.size() << std::endl;
        for (auto& idx : que) {
            fout << Key(EveryCourse[idx]) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){

    try{
        return stage_test("./u8Test.txt", "./u8Result.txt");
        //return stage_test(argv[1], argv[2]);
    }
    catch(...){
        return EXIT_FAILURE;
    }
}
