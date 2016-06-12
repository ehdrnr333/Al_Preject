#ifndef _CHAIN_H_
#define _CHAIN_H_
#include "../Base.h"

namespace project
{
    // The index start from next.
    // base is not in the range
    template <class Elem>
    struct Chain
    {
        const Elem base;
        Deq<Elem>  next;

        explicit Chain(Elem& _base) :
            base(_base)
        {};

        // Linear
        const Elem& at(int i) const
            noexcept(false)
        {
            return next.at(i);
        }

        auto append(const Elem& _elem) 
            noexcept(false)
        {
            return next.push_back(_elem);
        }

        auto append(Elem&& _elem) 
            noexcept(false) 
        {
            return next.emplace_back(std::move(_elem));
        }
    };
}

#endif
