#ifndef TIME_FILTER_H
#define TINE_FILTER_H
#include "../Model.h"
#include "./TimeFlag.h"	

using namespace std;
using namespace project;

class TimeFilter {
	Vec<Vec<Course>>				name_filtered;
	Vec<Vec<pair<int, TimeFlag>>> name_filtered_parsed;
	Vec<Vec<Vec<int>>>			result_indexes;
	Vec<Vec<Course>>				result;
private:
public:
	TimeFilter(Vec<Vec<Course>>& _name_filtered);
	Vec<Vec<Course>>& get_result();
private:
	void parse_to_flag(const Vec<Course>& courses);
	void filter_time();
	void parse_result();
};

#endif
