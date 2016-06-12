#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_
#include "../Base.h"


namespace project
{

    template <class Plan>
    struct Schedule
    {
        List<Plan> plist;
    };
}


#endif