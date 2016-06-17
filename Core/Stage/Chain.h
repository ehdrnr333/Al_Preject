#ifndef _CHAIN_H_
#define _CHAIN_H_
#include "../Base.h"
#include <functional>

namespace project
{
    // The index start from next.
    // base is not in the range
    template <class Elem>
    struct Chain
    {
        Elem       base;
        Deq<Elem>  next;

        explicit Chain(const Elem& _base) :
            base(_base)
        {}
        explicit Chain(Elem&& _base) :
            base(_base)
        {}
        // Linear 탐색?
        const Elem& at(int i) const
            noexcept(false)
        {
            return next.at(i);
        }

        // Next에 Elem을 등록
        auto append(const Elem& _elem) 
            noexcept(false)
        {
            return next.push_back(_elem);
        }

    };

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
