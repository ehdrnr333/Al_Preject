#ifndef TIME_FLAG_H
#define TIME_FLAG_H

#include "../Base.h"	
#include "../Model/Course.h"

namespace project
{

	class TimeFlag {
	public:
		using array_type = std::array<bool, 135>;
	private:
		array_type flags;

		const int DAY_MAX_SIZE = 27;
		const int WEEK_MAX_SIZE = DAY_MAX_SIZE * 5;
	public:
		TimeFlag();
		TimeFlag(const std::vector<LecTime>& lectures);
		bool is_collide(const TimeFlag f);
		void insert(TimeFlag f);
		
		bool get(const int index) const {
			return flags[index];
		}
	};

}

#endif