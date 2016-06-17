// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File     : Chain.hpp
//  Updated  : 16/06/17
//  Author
//      Park Dong-Ha ( luncliff@gmail.com )
//  Note
//      Chain 클래스는 사슬을 타입화 한 것으로, 
//      시작을 의미하는 base와, 이후 따라오는 원소들을 
//      임의의 Container로 묶은 next로 구성된다.
// 
//      간단하게 사슬을 확장하는 append(), 
//      n번째 원소 접근을 지원하는 at(),
//      사슬을 서로 비교하는 operator==()를 정의한다.
//
//  Concept
//      인자 타입은 Move Assignable, Move Constructible 해야 한다.
//      현재로선 Container는 Random Access Iterator를 지원해야 한다.
//  Task
//      Bidirectional Iterator를 지원하도록 확장
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _CHAIN_H_
#define _CHAIN_H_
#include "../Base.h"

namespace project
{
    // The index start from next.
    // base is not in the range
    template <class Elem, class Container = Deq<Elem>>
    struct Chain
    {
        //static_assert(
        //    std::is_nothrow_move_assignable<Elem>::value == false,
        //    "The argument type must be able to move assignable");
        //static_assert(
        //    std::is_nothrow_move_constructible<Elem>::value == false,
        //    "The argument type must be able to move constructable");

        Elem       base;
        Container  next;

        // - Note
        //      Default Constructor. base가 기본생성이 불가능할 경우
        //      이를 통해 Move Construction을 하게 된다.
        explicit Chain(Elem&& _base) :
            base(_base)
        {}

        // - Note
        //      at() 멤버함수를 사용한 Random Access
        const Elem& at(int i) const noexcept(false)
        {
            return next.at(i);
        }

        // - Note
        //      at() 멤버함수를 사용한 Random Access
        Elem& at(int i) noexcept(false)
        {
            return next.at(i);
        }

        // - Note
        //      사슬의 끝에 원소를 추가
        auto append(const Elem& _elem) noexcept(false)
        {
            return next.push_back(_elem);
        }

        // - Note
        //      사슬의 끝에 원소를 추가
        auto append(Elem&& _elem) noexcept(false)
        {
            return next.emplace_back(std::move(_elem));
        }
    };

    // - Note
    //      두 Chain이 같은지 비교한다.
    //      Lexicographical Comparison
    template <class E>
    constexpr 
        bool operator ==(const Chain<E>& _lhs,
                         const Chain<E>& _rhs)
        noexcept 
    {
        return (_lhs.base == _rhs.base) 
                && (_lhs.next == _rhs.next);
    }

}

#endif
