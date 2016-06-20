#include "TimeFlag.h"	

using namespace std;
using namespace project;

TimeFlag::TimeFlag() {

	for (int i = 0; i < WEEK_MAX_SIZE; ++i)
		flags[i] = false;

}

TimeFlag::TimeFlag(const Vec<LecTime>& lectures) {

	for (int i = 0; i < WEEK_MAX_SIZE; ++i)
		flags[i] = false;

	for (auto& l : lectures) {

		int start_index = 
			(l.start().clock / 5 - 1) + (l.day() * DAY_MAX_SIZE);

		int end_index =
			(l.end().clock / 5 - 1) + (l.day() * DAY_MAX_SIZE);

		for (int i = start_index; i <= end_index; ++i)
			flags[i] = 1;

	}
}

bool TimeFlag::is_collide(const TimeFlag f) {

	bool is_collide;

	for (int i = 0; i < WEEK_MAX_SIZE; ++i) 
		if ((flags[i] && f.get(i)) == 1) 
			is_collide = true;

	return is_collide;
}

void TimeFlag::insert(TimeFlag f) 
{
	for (int i = 0; i < WEEK_MAX_SIZE; ++i) 
		flags[i] = f.get(i);
}

