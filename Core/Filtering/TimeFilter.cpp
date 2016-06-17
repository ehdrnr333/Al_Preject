#include "TimeFilter.h"	
using namespace project;

TimeFilter::TimeFilter(vector<vector<Course>>& _name_filtered) {

	name_filtered = _name_filtered;

	for (int i = 0; i < name_filtered.size(); ++i)
		parse_to_flag(name_filtered[i]);

	result_indexes.resize(name_filtered_parsed.size());

	filter_time();
	parse_result();
}

vector<vector<Course>>& TimeFilter::get_result()
{
	return result;
}

void TimeFilter::parse_to_flag(const vector<Course>& courses)
{
	vector<pair<int, TimeFlag>> vt;

	for (int i = 0; i < courses.size(); ++i){
		
		vt.emplace_back(pair<int, TimeFlag>
			(i , TimeFlag{ courses[i] }));
	
	}
	
	name_filtered_parsed.emplace_back(vt);


}
void TimeFilter::filter_time() {

	int c = 0;
	int s = 0;

	for (auto& vt : name_filtered_parsed) {

		for (int start_index = 0; start_index < vt.size(); ++start_index) {

			TimeFlag checker;
			vector<int> one_case;

			for (int i = 0; i < vt.size(); ++i) {

				auto index = start_index + i;
				index = index % vt.size();

				if (!checker.is_collide(vt[index].second)) {
					checker.insert(vt[index].second);
					one_case.emplace_back(vt[index].first);
				}
			}

			result_indexes[c].emplace_back(one_case);
		}
		++c;

	}


}

void TimeFilter::parse_result()
{
	for (int i = 0; i < result_indexes.size(); ++i) {

		for (int j = 0; j < result_indexes[i].size(); ++j) {

			vector<Course> vc;

			for (auto& c : result_indexes[i][j]) 
				vc.emplace_back(name_filtered[i][c]);

			result.emplace_back(vc);
			
		}
	}

}


