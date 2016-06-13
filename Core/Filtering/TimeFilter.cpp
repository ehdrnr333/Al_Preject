#include "TimeFilter.h"	


TimeFilter::TimeFilter(vector<vector<Course>>& _name_filtered) {

	name_filtered = _name_filtered;

	for (int i = 0; i < name_filtered.size(); ++i)
		parse_to_flag(name_filtered[i]);

	result.resize(name_filtered_parsed.size());
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
			(i , TimeFlag{ courses[i].lectures() }));
		
	}
	
	name_filtered_parsed.emplace_back(vt);


}
void TimeFilter::filter_time() {

	int c = 0;
	int s = 0;

	for_each(name_filtered_parsed.begin(), name_filtered_parsed.end(), [&](vector<pair<int, TimeFlag>> vt) {
	
		TimeFlag checker;

		for (int start_index = 0; start_index < vt.size(); ++start_index){
			
			for (int i = start_index; i < start_index + vt.size(); ++i){

				i = i % vt.size();

				if (!checker.is_collide(vt[i].second)) {
					checker.insert(vt[i].second);
					result_indexes[c][s].emplace_back(vt[i].first);
				}
			}
			++s;
		}
		++c;

	});

}

void TimeFilter::parse_result()
{
	for (int i = 0; i < result_indexes.size(); ++i) {
		for (int j = 0; j < result_indexes[i].size(); ++j) {
			
			for_each(result_indexes[i][j].begin(), result_indexes[i][j].end(), [&](int index) {
				result[i].emplace_back(name_filtered[i][index]);
			});
		}
	}
}


