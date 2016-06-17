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
        {};
        explicit Chain(Elem&& _base) :
            base(_base)
        {};
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


        // 컨테이너를 받아서 필터링한다.
        template <class InIter, class Pred>
        void append(const InIter _first, const InIter _last,
                    Pred _pred)
        {
            for (auto it = _first; it != _last; it++) {
                if (_pred(base, *it) == true) {
                    this->next.push_back(*it);
                }
            }
        }

        bool operator ==(const Chain& _rhs) const 
            noexcept
        {
            return (base == _rhs.base) 
                    && (next == _rhs.next);
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
