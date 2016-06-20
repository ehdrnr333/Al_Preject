// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Stage.h
//  Updated  : 16/06/17
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      The collection of `Stage/` directory's headers
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _PROJ_STAGE_H_
#define _PROJ_STAGE_H_

#include "./Model.h"

#include "./Stage/Time.hpp"
#include "./Stage/Plan.hpp"
#include "./Stage/Chain.hpp"

namespace project
{
    // - Note
    //      Course Chain 을 표현하는 클래스
    //      실제 Course 클래스의 Type size는 훨씬 
    //      커질 수 있기 때문에, Unique한 index만으로 
    //      Course의 Chain을 표현한다.
    using CrsChain = Chain<int>;
    using CrsSchedule = project::CrsTable<Course>;
 

    // - Note
    //      Course List를 기반으로 Chain의 목록을 만든다
    // - Expected Input
    //      CrsList : 임의의 기준으로 정렬된 Course의 리스트
    Vec<CrsChain> MakeChains(const Vec<Course>& CrsList);

    // - Note
    //      Stage 알고리즘의 구현
    // 
    //      The algorithm starts with sorted CourseList
    //      course를 Template argument로 사용하였을 경우
    //      공간 비용이 큰 점을 고려하여
    //      CrsList를 기준으로 한 index방식을 사용하였다.
    Deq<CrsSchedule>
        stage_schedule(Vec<Course> _CrsList, 
                       const int max_stage,
                       std::function<bool(const Deq<int>&)> filter);
}
#endif
