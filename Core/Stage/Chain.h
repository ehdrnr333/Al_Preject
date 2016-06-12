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
        template <class Cont>
        void filter(const Cont& _cont) 
        {
            // Base가 존재하는가?
            auto pos = std::find(_cont.begin(), _cont.end(),
                                 this->base);

            // 존재하지 않을 경우 Skip처리.
            // 존재할 경우, 해당 위치부터 조건에 맞는
            // Elem들을 next로 복사한다
            std::for_each(pos, _cont.end(),
                [&](const Elem& _e)
            {
                if (Collide(base, _e) != true) {
                    next.push_back(_e);
                }
            });
        }
    
    };
}

#endif
