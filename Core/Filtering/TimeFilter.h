#ifndef TIME_FILTER_H
#define TINE_FILTER_H
#include "../Model/Course.h"
#include "../Base.h"
#include "TimeFlag.h"	

using namespace std;
using namespace project;

class TimeFilter {
	vector<vector<Course>>				name_filtered;
	vector<vector<pair<int, TimeFlag>>> name_filtered_parsed;
	vector<vector<vector<int>>>			result_indexes;
	vector<vector<Course>>				result;
private:
public:
	TimeFilter(vector<vector<Course>>& _name_filtered);
	vector<vector<Course>>& get_result();
private:
	void parse_to_flag(const vector<Course>& courses);
	void filter_time();
	void parse_result();
};

#endif
